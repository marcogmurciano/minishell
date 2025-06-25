# Minishell: Detailed Functional Checklist

This document expands the concise project outline into a detailed, actionable checklist, referencing function names and relevant implementation notes. Each section corresponds to a core requirement for your minishell project as outlined in the subject.

---

## 1. Prompt Display

✅ **Requirement:**  
- Display a prompt while waiting for new user input.

**Implementation:**  
- Use `readline(const char *prompt)` to display the prompt and read input.

---

## 2. Command History

✅ **Requirements:**  
- Maintain a working command history, allowing users to recall and edit previous commands.

**Functions Involved:**  
- `rl_clear_history()` – Clears the entire history list.
- `rl_on_new_line()` – Notifies that the cursor is on a new line.
- `rl_replace_line(const char *string, int clear_undo)` – Replaces the current input line.
- `rl_redisplay()` – Redisplays the prompt/input line.
- `add_history(const char *line)` – Adds a command to the history.

**Notes:**  
- Use these functions to manage user command history and input behavior.

---

## 3. Command Parsing & Execution

### 3.1. Input Validation

✅ **Requirement:**  
- Do not interpret unclosed quotes or special characters not specified in the subject, such as `\` (backslash) or `;` (semicolon).

### 3.2. Quote Handling

- **Single Quotes `'...'`:**  
  Prevent interpretation of meta-characters within single quotes.

- **Double Quotes `"..."`:**  
  Prevent interpretation of meta-characters within double quotes, except for `$` (environment variable expansion).

    - If an environment variable does not exist, expansion should yield an empty string.

### 3.3. Pipes

- **Requirement:**  
  - Implement pipe `|` handling so that the output of each command in a pipeline becomes the input for the next.

### 3.4. Redirections

- **Input Redirection `<`:**  
  - Redirect standard input from a file.

- **Output Redirection `>`:**  
  - Redirect standard output to a file (overwrite).

- **Heredoc Redirection `<<`:**  
  - Read input from the current source until a line containing only the given delimiter is found (do not add heredoc input to history).

- **Append Output `>>`:**  
  - Redirect standard output to a file (append mode).

### 3.5. Environment Variable Expansion

✅ **Requirement:**  
- Expand `$VAR` patterns to their environment values.

### 3.6. Special Variable: `$?`

- **Requirement:**  
  - Expand `$?` to the exit status of the most recent command in the pipeline.

---

## 4. Signal Handling

### 4.1. General Handling

- **Requirement:**  
  - Correctly handle Ctrl-C, Ctrl-D, and Ctrl-\ as in Bash.

- **Memory Management:**  
  - Free any necessary resources on signal receipt.

### 4.2. Interactive Behavior

- **Ctrl-C:**  
  - Print a new prompt line (do not exit shell).

- **Ctrl-D:**  
  - Exit the shell.

- **Ctrl-\:**  
  - Do nothing.

**Relevant Functions:**  
- `signal(int sig, void (*func)(int))`
- `sigaction(int sig, const struct sigaction *act, struct sigaction *oact)`
- `kill(pid_t pid, int sig)`
- `exit(int status)`

---

## 5. Executable Search and Launch (Pipex)

- **Requirement:**  
  - Locate the correct executable to run, using either the `PATH` environment variable or absolute/relative paths.

**Functions Involved:**  
- `access(const char *pathname, int mode)`
- `open(const char *pathname, int flags, ...)`
- `read(int fd, void *buf, size_t count)`
- `close(int fd)`
- `fork(void)`
- `wait(int *status)`
- `waitpid(pid_t pid, int *status, int options)`

**Global Variable Restriction:**  
- Use at most one global variable, only for tracking signal status (as per subject).  
- Do not use global structures for other data.

---

## 6. Built-in Commands

Implement the following shell built-ins:

- `echo` (with `-n` option, handle parsing)
- `cd` (with relative or absolute path, only outside pipelines)
    - `getcwd(char *buf, size_t size)`
    - `chdir(const char *path)`
- `pwd` (no options)
- `export` (no options, only outside pipelines)
- `unset` (no options, only outside pipelines)
- `env` (no options or arguments)
    - `getenv(const char *name)`
- `exit` (no options, only outside pipelines)

---

## 7. Memory Management & Subject Compliance

- The `readline` function may cause memory leaks internally (these are not your responsibility).
- **Your code must be free of memory leaks.**
- Do not implement any feature not explicitly required by the subject.
- In case of doubt about behavior, refer to Bash for guidance.

---

## References

- See [docs/function_definitions.md](allowed_functions.md) for detailed function descriptions and usage examples.
- Consult the project [en.subject.md](en.subject.md) for the authoritative requirements.
