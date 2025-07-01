# Minishell Implementation Task List

This list breaks down the requirements from the [minishell subject](en.subject.md) into concrete tasks. Each task corresponds to a mandatory or bonus feature specified in the project documentation.

---

## 1. Project Setup & Build

- [x] Create project structure (src, include, Makefile, etc.)
- [x] Write Makefile with `-Wall -Wextra -Werror` and required rules (`all`, `clean`, `fclean`, `re`, `$(NAME)`)
- [x] Integrate Libft in `libft/` folder if used
- [x] Ensure no unnecessary re-linking on rebuild

---

## 2. Input Handling

- [x] Display a prompt and read input using `readline()`
- [x] Add input to command history (`add_history`)
- [x] Handle history navigation via readline
- [~] Properly handle end-of-file (Ctrl-D) and signals

---

## 3. Parsing

- [x] Tokenize input line
- [ ] Parse command, arguments, redirections, and pipes
- [ ] Detect and handle invalid syntax (e.g., unclosed quotes, unsupported characters: `\` `;`)
- [ ] Build internal command representation (AST or linked lists)

---

## 4. Environment Variables

- [x] Import parent environment on startup
- [x] Handle expansion of `$VAR` in input
- [ ] Handle special variable `$?`
- [x] Support variable expansion inside double quotes, not inside single quotes

---

## 5. Builtins

Implement the following builtins (with correct behavior and error handling):

- [ ] `echo` (with `-n`, quoting, etc.)
- [ ] `cd` (with path, `~`, error cases)
- [ ] `pwd`
- [ ] `export` (new and existing variables, correct output)
- [ ] `unset`
- [ ] `env`
- [ ] `exit` (with/without arguments)

---

## 6. Executing Commands

- [ ] Search and execute commands from `$PATH`, relative or absolute
- [ ] Launch child process using `fork` and `execve`
- [ ] Handle command not found, permission errors, etc.
- [ ] Correctly propagate and set exit codes

---

## 7. Redirections

- [ ] Support input `<`, output `>`, append `>>`
- [ ] Support heredoc `<<` (no history update)
- [ ] Properly open/close files and manage file descriptors
- [ ] Handle redirection errors (open failures, permissions)

---

## 8. Pipes

- [ ] Parse and execute pipelines (multiple commands with `|`)
- [ ] Correctly set up pipes and manage file descriptors
- [ ] Wait for all child processes in a pipeline

---

## 9. Signal Handling

- [~] Handle `ctrl-C` (SIGINT): show new prompt, reset input
- [x] Handle `ctrl-D` (EOF): exit shell
- [x] Handle `ctrl-\` (SIGQUIT): do nothing
- [x] Use at most one global variable (for signal number)

---

## 10. Memory Management

- [ ] Free all allocated memory (no leaks, except those from readline)
- [ ] Clean up resources on shell exit

---

## 11. Error Handling

- [ ] Print clear error messages (e.g. command not found, syntax error)
- [ ] Ensure shell never crashes (segfault, double free, etc.)
- [ ] Handle edge cases (empty input, invalid commands)

---

## 12. Documentation

- [ ] Write/Update documentation (README, usage, etc.)
- [ ] Document each function (comments, headers)
- [ ] List external man pages/references

---

## 13. Bonus (after all mandatory features are perfect)

- [ ] Implement `&&` and `||` operators (with parenthesis support)
- [ ] Implement globbing/wildcards (`*`) in current directory

---

## 14. Testing

- [ ] Create and run test cases for all builtins and features
- [ ] Test all edge cases and error scenarios
- [ ] Test memory with tools like `valgrind`

---

## 15. Submission

- [ ] Ensure all required files are in the repository
- [ ] Double-check naming and project structure

---

**References:**  
- [Minishell Subject](en.subject.md)  
- [Function Reference](function_definitions.md)