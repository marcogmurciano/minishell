# minishell — Custom Unix Shell

A fully functional Unix shell implementation in C, supporting command execution, pipes, I/O redirections, variable expansion, and built-in commands. Demonstrates core systems programming concepts including process management, signal handling, and file descriptor manipulation.

## Features

### Core Functionality
- **Lexer & Tokenizer**: Complete tokenization with quote handling and operator detection
- **Recursive Descent Parser**: AST generation with full syntax validation
- **Command Execution**: Process creation, parent/child management via `fork/exec`
- **Pipes**: Multi-command pipeline support with proper file descriptor management
- **I/O Redirections**: Input (`<`), output (`>`), append (`>>`), and heredoc (`<<`)

### Built-in Commands
- `echo` — Print text (with `-n` flag support)
- `cd` — Change directory with `OLDPWD` tracking
- `pwd` — Print working directory
- `export` — Set environment variables
- `unset` — Remove environment variables
- `env` — Display environment
- `exit` — Terminate shell with exit code

### Advanced Features
- **Variable Expansion**: `$VAR` and `$?` (exit status)
- **Heredoc**: Multi-line input with `<<DELIMITER`
- **Signal Handling**: SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) management
- **Environment Management**: Full environment variable support and regeneration
- **Quote Handling**: Single quotes (literal) and double quotes (with expansion)

## Architecture

```
Input → Tokenizer → Parser → Expander → Syntax Check → Executor
                                                           ↓
                                                      Command Exec
                                                      (fork/exec)
```

**Key modules:**
- `src/tokenization/` — Lexical analysis
- `src/syntax/` — Parser and syntax validation
- `src/expansion/` — Variable and special character expansion
- `src/execution/` — Command execution and process management
- `src/builtins/` — Built-in command implementations
- `src/environment/` — Environment variable handling
- `src/signals/` — Signal handlers

## Build & Run

```bash
make              # Compile
./minishell       # Run shell
make clean        # Remove .o files
make fclean       # Remove all build artifacts
make re           # Rebuild
```

### Example Usage
```bash
$ ls -la | grep minishell
$ echo "Hello $USER"
$ export MY_VAR=value && echo $MY_VAR
$ cd ~ && pwd
$ cat << EOF
> multiline
> input
> EOF
```

## Technical Highlights

- **Memory Management**: Comprehensive cleanup routines to prevent leaks
- **File Descriptor Handling**: Proper management of pipes and redirections
- **Process Synchronization**: `waitpid()` for process state tracking
- **Signal Safety**: Non-blocking signal handlers
- **POSIX Compliance**: Follows POSIX shell specification where applicable

## Limitations & Future Work

- No job control (`fg`, `bg`, `jobs`)
- No history file persistence
- No readline history navigation (uses raw readline library)
- No glob expansion (`*`, `?`)
- No command substitution (`` `command` ``)

## Requirements

- GCC/Clang compiler
- Linux/Unix environment
- GNU Make
- POSIX-compliant C library

## Project Stats

- **Lines of Code**: ~3,500 (excluding libft)
- **Number of Commits**: 15+ logical phases
- **Build Time**: < 1 second
- **Memory Leaks**: 0 (validated with Valgrind)
