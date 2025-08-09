#!/usr/bin/env bash
set -euo pipefail

BIN=${1:-./minishell}
LOGDIR=${2:-vglogs}
SUPP=${3:-tests/vg_readline.supp}
STRICT=${STRICT:-0}   # set STRICT=1 to exit non-zero if any "definitely lost" > 0 (after suppressions)

mkdir -p "$LOGDIR"

# Delete all logs from previous runs in LOGDIR before starting new tests
find "$LOGDIR" -type f -name '*.log' -delete
find "$LOGDIR" -type f -name '*.summary' -delete

# Force stable (English) output for parsing
export LANG=C
export LC_ALL=C

# Extract the four leak summary lines and FD summary from one valgrind log
summarize_log() {
  local f="$1"

  echo "---- $(basename "$f") ----"

  # Try to print the entire 'LEAK SUMMARY' block, else fallback to individual greps
  if grep -q "LEAK SUMMARY:" "$f"; then
    # Print the header + next lines until a blank line or EOF
    awk '
      /LEAK SUMMARY:/ {on=1}
      on {print; if ($0 ~ /^[[:space:]]*$/) exit}
    ' "$f"
  else
    # Fallback: print each line if found
    grep -m1 -E "definitely lost:" "$f" || true
    grep -m1 -E "indirectly lost:" "$f" || true
    grep -m1 -E "possibly lost:" "$f" || true
    grep -m1 -E "still reachable:" "$f" || true
  fi

  # File descriptor summary (Valgrind prints e.g.: "FILE DESCRIPTORS: N open at exit.")
  grep -m1 -E "FILE DESCRIPTORS" "$f" || true

  echo
}

# Gather all log files for a given test name (parent + children)
gather_logs() {
  local base="$1"
  local -a logs=()
  # Child processes will use %p in the filename; include parent in case there were no children
  for f in "${base}".*.log "${base}.log"; do
    [[ -f "$f" ]] && logs+=("$f")
  done
  printf "%s\n" "${logs[@]:-}"
}

# Parse numeric bytes for "definitely lost" to support STRICT mode
definitely_lost_bytes() {
  # Extract the first number (bytes) from "definitely lost: X bytes"
  sed -nE 's/.*definitely lost:[[:space:]]*([0-9,]+)[[:space:]]*bytes.*/\1/p' | tr -d ','
}

run_test() {
  local name="$1"
  local input="$2"
  local base="$LOGDIR/$name"
  local summary="$base.summary"

  # Clean previous logs for this test
  rm -f "${base}.log" "${base}".*.log "$summary"

  local VALGRIND=(
    valgrind
    --tool=memcheck
    --leak-check=full
    --show-leak-kinds=all
    --track-origins=yes
    --trace-children=yes
    --track-fds=yes
    --error-exitcode=99
    "--suppressions=$SUPP"
    "--log-file=${base}.%p.log"
  )

  # Feed scripted input; don’t stop the suite if valgrind returns 99
  printf "%s\nexit\n" "$input" | "${VALGRIND[@]}" "$BIN" || true

  # Aggregate summaries
  {
    echo "=== $name ==="
    echo "Logs pattern: ${base}.%p.log (and/or ${base}.log)"
    echo

    mapfile -t logs < <(gather_logs "$base")
    if (( ${#logs[@]} == 0 )); then
      echo "No valgrind logs found for $name"
      echo
    else
      local total_def_lost=0
      for f in "${logs[@]}"; do
        summarize_log "$f" || true

        # STRICT mode accumulation
        if (( STRICT )); then
          local n
          n=$(grep -m1 -E "definitely lost:" "$f" | definitely_lost_bytes || echo "0")
          n=${n:-0}
          # Only add if it's a valid integer
          [[ "$n" =~ ^[0-9]+$ ]] && total_def_lost=$(( total_def_lost + n ))
        fi
      done

      if (( STRICT )); then
        echo "Total definitely lost (bytes) across processes: $total_def_lost"
        echo
        if (( total_def_lost > 0 )); then
          echo "STRICT mode: failing due to definitely lost > 0"
          exit 2
        fi
      fi
    fi
  } > "$summary"

  cat "$summary"
}

# Test battery adapted to shells without ';', '&&', '||'
run_test "simple_echo" 'echo hello'
run_test "echo_n_flags" 'echo -n -n -n hello'
run_test "pwd_builtin" 'pwd'
run_test "env_listing" 'env'

run_test "export_new" 'export FOO=bar
env | grep -E "^FOO="'

run_test "export_update" 'export FOO=bar
export FOO=baz
env | grep -E "^FOO="'

run_test "unset_var" 'export FOO=x
unset FOO
env | grep -v "^FOO="'

run_test "cd_change" 'pwd
cd /
pwd
cd -'

run_test "nonexistent_cmd" 'this_command_does_not_exist'

run_test "exit_status_ok" '/bin/true
echo $?'

run_test "exit_status_fail" '/bin/false
echo $?'

run_test "redir_in" 'cat < Makefile | head -n 1'

run_test "redir_out_trunc" 'echo hi > /tmp/ms_out
cat /tmp/ms_out'

run_test "redir_out_append" 'echo a > /tmp/ms_app
echo b >> /tmp/ms_app
cat /tmp/ms_app'

run_test "pipeline_simple" 'echo hello | tr a-z A-Z'
run_test "pipeline_multi" 'echo one two three | tr " " "\n" | wc -l'

run_test "vars_expand" 'export X=42
echo $X'

run_test "vars_nonexistent" 'unset Y
echo $Y'

run_test "quotes_single" "echo 'a \$NOT_EXPANDED b'"

run_test "quotes_double" 'export A=1
echo "a $A b"'

# Heredoc demos (keep when heredoc is complete)
run_test "heredoc_no_expand" 'cat <<EOF
raw$VALUE
EOF'

run_test "heredoc_expand" 'export V=K
cat <<EOF
=$V=
EOF'