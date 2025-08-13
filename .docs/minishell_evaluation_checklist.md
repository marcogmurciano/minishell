# minishell – Checklist

## 1. Compile

- [x] **Run `make -n`**: Does it use `-Wall -Wextra -Werror`?
  - [x] If **not**, select the “invalid compilation” flag.
- [x] **Does minishell compile without any errors?**
  - [x] If **not**, select the flag.
- [x] **Does the Makefile re-link unnecessarily?**
  - [x] If **yes**, select the flag.

---

## 2. Simple Command & Global Variables

- [x] **Execute a simple command** (e.g., `/bin/ls` or another command without options).
- [x] **How many global variables are used? Why?**
  - [x] Ask the student for a concrete example of why a global variable is mandatory or logical.
  - [x] Check that the global variable only provides info about the number of a received signal (not more).
- [x] **Test:**
  - [x] An empty command
  - [x] Only spaces or tabs
  - [o] If something crashes, select the “crash” flag.
  - [o] If something doesn’t work, select the “incomplete work” flag.

---

## 3. Arguments

- [x] **Execute a simple command with arguments** (e.g., `/bin/ls` with arguments, no quotes).
- [x] **Repeat with different commands/arguments.**
  - [o] If something crashes, select the “crash” flag.
  - [o] If something doesn’t work, select the “incomplete work” flag.

---

## 4. echo

- [x] **Execute `echo`** with/without arguments, including the `-n` option.
- [x] **Repeat multiple times with different arguments.**
  - [o] If something crashes, select the “crash” flag.
  - [o] If something doesn’t work, select the “incomplete work” flag.

---

## 5. exit

- [x] **Execute `exit`** with/without arguments, multiple times.
- [x] **Relaunch minishell after each test.**
  - [x] If something crashes, select the “crash” flag.
  - [x] If something doesn’t work, select the “incomplete work” flag.

---

## 6. Return Value of a Process

- [x] **Execute a command (e.g., `/bin/ls`)** and then `echo $?`.
- [x] **Compare with Bash results.**
- [x] **Repeat with wrong commands (e.g., `/bin/ls filethatdoesnotexist`).**
- [x] **Try expressions like `expr $? + $?`.**
  - [o] If something crashes, select the “crash” flag.
  - [o] If something doesn’t work, select the “incomplete work” flag.

---

## 7. Signals

- [x] **In empty prompt:**
  - [x] `ctrl-C` displays a new line and prompt.
  - [x] `ctrl-\` does nothing.
  - [x] `ctrl-D` quits minishell (relaunch for further tests).
- [x] **After typing input:**
  - [x] `ctrl-C` displays new line and prompt, buffer is clean.
  - [x] Press Enter to ensure nothing from the previous line is executed.
  - [x] `ctrl-D` does nothing.
  - [x] `ctrl-\` does nothing.
- [x] **During blocking command (e.g., `cat` or `grep "something"` with no input):**
  - [x] Test `ctrl-C`, `ctrl-\`, and `ctrl-D`.
  - [x] Repeat with different commands.
  - [o] If something crashes, select the “crash” flag.
  - [o] If something doesn’t work, select the “incomplete work” flag.

---

## 8. Double Quotes

- [x?] **Execute a command with arguments in double quotes (try including whitespaces).**
- [x] Example: `echo "cat lol.c | cat > lol.c"`
- [x] Try anything except `$`.
  - [o] If something crashes, select the “crash” flag.
  - [o] If something doesn’t work, select the “incomplete work” flag.

---

## 9. Single Quotes

- [x] **Execute commands with single quoted arguments.**
- [x] Try empty arguments, environment variables, whitespaces, pipes, redirection inside single quotes.
- [x] `echo '$USER'` should print `$USER` (nothing interpreted).

---

## 10. env

- [x] **Check if `env` displays current environment variables.**
  
---

## 11. export

- [x] **Export environment variables, create new ones, and replace old ones.**
- [x] **Check results with `env`.**

---

## 12. unset

- [x] **Export, create, replace environment variables.**
- [x] **Use `unset` to remove them.**
- [x] **Check with `env`.**

---

## 13. cd

- [x] **Use `cd` to change directories, check with `/bin/ls`.**
- [x] **Repeat multiple times, including invalid directories, `.` and `..` arguments.** 

---

## 14. pwd

- [x] **Use `pwd` in various directories, multiple times.**

---

## 15. Relative Path

- [ ] **Execute commands using relative paths.**
- [ ] **Try in different directories with complex relative paths.**

  **

---

## 16. Environment Path

- [x] **Execute commands without a path (e.g., `ls`, `wc`, `awk`).**
- [ ] **Unset `$PATH` and ensure commands fail.**
- [ ] **Set `$PATH` with multiple directories and check order of search.**

---

## 17. Redirection

- [ ] **Test `<`, `>`, `>>` redirections with various commands and arguments.**
- [ ] **Check if repeated redirections fail.**
- [ ] **Test `<<` (heredoc) (should not update history).**

---

## 18. Pipes

- [ ] **Execute commands with pipes (e.g., `cat file | grep bla | more`).**
- [ ] **Try with invalid commands, mix pipes and redirections.**

---

## 19. Go Crazy and History

- [ ] **Type a command, use `ctrl-C`, then Enter. Buffer should be clean.**
- [ ] **Can you navigate through history with Up/Down? Retry commands?**
- [ ] **Execute invalid commands (e.g., `dbskdgbksdaghsd`): Should print error, not crash.**
- [ ] **`cat | cat | ls` should behave normally.**
- [ ] **Try a long command with many arguments.**
- [ ] **Test robustness and enjoy!**

---

## 20. Environment Variables

- [x] **Use `echo` with environment variables (`$variable`) as arguments.**
- [x] **Check that `$` is interpreted as an environment variable.**
- [x] **Double quotes should interpolate `$`.**
- [x] **Check that `USER` exists (otherwise, set it).**
- [x] **`echo "$USER"` should print the variable value.**

---

## 21. Bonus (Only if mandatory part is perfect)

- [ ] **AND/OR/Parentheses:** Use `&&`, `||`, and parentheses; ensure Bash-like behavior.
- [ ] **Wildcard:** Use wildcards in arguments (current directory).
- [ ] **Surprise!**
  - [ ] Set `USER`, `echo "$USER"` → should print value.
  - [ ] `echo '"$USER"'` should print `$USER`.

---