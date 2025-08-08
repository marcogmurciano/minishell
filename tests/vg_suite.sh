#!/usr/bin/env bash
set -euo pipefail

BIN=${1:-./minishell}
LOGDIR=${2:-vglogs}
SUPP=${3:-tests/vg_readline.supp}

mkdir -p "$LOGDIR"

VALGRIND="valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --track-fds=yes \
  --error-exitcode=99 \
  --suppressions=$SUPP \
  --quiet"

run_test() {
  local name="$1"
  local input="$2"
  local logfile="$LOGDIR/$name.log"

  printf "%s\nexit\n" "$input" | $VALGRIND --log-file="$logfile" "$BIN" || true

  # Summarize key leak lines for quick scan
  echo "=== $name ===" > "$logfile.summary"
  grep -E "definitely lost|indirectly lost|possibly lost|still reachable|OPEN FILE DESCRIPTORS" "$logfile" || true
  echo "Log: $logfile" >> "$logfile.summary"
  echo >> "$logfile.summary"
  cat "$logfile.summary"
}

# Minimal commands to exercise major subsystems. You can add more.
run_test "simple_echo" 'echo hello'
run_test "echo_n_flags" 'echo -n -n -n hello'
run_test "pwd_builtin" 'pwd'
run_test "env_listing" 'env'
run_test "export_new" 'export FOO=bar && env | grep -E "^FOO="'
run_test "export_update" 'export FOO=bar && export FOO=baz && env | grep -E "^FOO="'
run_test "unset_var" 'export FOO=x && unset FOO && env | grep -v "^FOO="'
run_test "cd_change" 'pwd && cd / && pwd && cd -'
run_test "nonexistent_cmd" 'this_command_does_not_exist'
run_test "exit_status_ok" '/bin/true; echo $?'
run_test "exit_status_fail" '/bin/false; echo $?'
run_test "redir_in" 'cat < Makefile | head -n 1'
run_test "redir_out_trunc" 'echo hi > /tmp/ms_out && cat /tmp/ms_out'
run_test "redir_out_append" 'echo a > /tmp/ms_app && echo b >> /tmp/ms_app && cat /tmp/ms_app'
run_test "pipeline_simple" 'echo hello | tr a-z A-Z'
run_test "pipeline_multi" 'echo one two three | tr " " "\n" | wc -l'
run_test "vars_expand" 'export X=42; echo $X'
run_test "vars_nonexistent" 'unset Y; echo $Y'
run_test "quotes_single" "echo 'a $NOT_EXPANDED b'"
run_test "quotes_double" "export A=1; echo \"a $A b\""
# Heredoc (delimiter EOF), no history expected; may require tty-like handling
run_test "heredoc_no_expand" 'cat <<EOF
raw$VALUE
EOF'
run_test "heredoc_expand" 'export V=K; cat <<EOF
=$V=
EOF'