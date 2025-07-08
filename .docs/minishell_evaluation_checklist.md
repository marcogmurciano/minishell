# minishell – Evaluation Checklist

## 1. Compile

- [ ] **Run `make -n`**: Does it use `-Wall -Wextra -Werror`?
  - [ ] If **not**, select the “invalid compilation” flag.
- [ ] **Does minishell compile without any errors?**
  - [ ] If **not**, select the flag.
- [ ] **Does the Makefile re-link unnecessarily?**
  - [ ] If **yes**, select the flag.

---

## 2. Simple Command & Global Variables

- [ ] **Execute a simple command** (e.g., `/bin/ls` or another command without options).
- [ ] **How many global variables are used? Why?**
  - [ ] Ask the student for a concrete example of why a global variable is mandatory or logical.
  - [ ] Check that the global variable only provides info about the number of a received signal (not more).
- [ ] **Test:**
  - [ ] An empty command
  - [ ] Only spaces or tabs
  - [ ] If something crashes, select the “crash” flag.
  - [ ] If something doesn’t work, select the “incomplete work” flag.

---

## 3. Arguments

- [ ] **Execute a simple command with arguments** (e.g., `/bin/ls` with arguments, no quotes).
- [ ] **Repeat with different commands/arguments.**
  - [ ] If something crashes, select the “crash” flag.
  - [ ] If something doesn’t work, select the “incomplete work” flag.

---

## 4. echo

- [ ] **Execute `echo`** with/without arguments, including the `-n` option.
- [ ] **Repeat multiple times with different arguments.**
  - [ ] If something crashes, select the “crash” flag.
  - [ ] If something doesn’t work, select the “incomplete work” flag.

---

## 5. exit

- [ ] **Execute `exit`** with/without arguments, multiple times.
- [ ] **Relaunch minishell after each test.**
  - [ ] If something crashes, select the “crash” flag.
  - [ ] If something doesn’t work, select the “incomplete work” flag.

---

## 6. Return Value of a Process

- [ ] **Execute a command (e.g., `/bin/ls`)** and then `echo $?`.
- [ ] **Compare with Bash results.**
- [ ] **Repeat with wrong commands (e.g., `/bin/ls filethatdoesnotexist`).**
- [ ] **Try expressions like `expr $? + $?`.**
  - [ ] If something crashes, select the “crash” flag.
  - [ ] If something doesn’t work, select the “incomplete work” flag.

---

## 7. Signals

- [ ] **In empty prompt:**
  - [ ] `ctrl-C` displays a new line and prompt.
  - [ ] `ctrl-\` does nothing.
  - [ ] `ctrl-D` quits minishell (relaunch for further tests).
- [ ] **After typing input:**
  - [ ] `ctrl-C` displays new line and prompt, buffer is clean.
  - [ ] Press Enter to ensure nothing from the previous line is executed.
  - [ ] `ctrl-D` does nothing.
  - [ ] `ctrl-\` does nothing.
- [ ] **During blocking command (e.g., `cat` or `grep "something"` with no input):**
  - [ ] Test `ctrl-C`, `ctrl-\`, and `ctrl-D`.
  - [ ] Repeat with different commands.
  - [ ] If something crashes, select the “crash” flag.
  - [ ] If something doesn’t work, select the “incomplete work” flag.

---

## 8. Double Quotes

- [ ] **Execute a command with arguments in double quotes (try including whitespaces).**
- [ ] Example: `echo "cat lol.c | cat > lol.c"`
- [ ] Try anything except `$`.
  - [ ] If something crashes, select the “crash” flag.
  - [ ] If something doesn’t work, select the “incomplete work” flag.

---

## 9. Single Quotes

- [ ] **Execute commands with single quoted arguments.**
- [ ] Try empty arguments, environment variables, whitespaces, pipes, redirection inside single quotes.
- [ ] `echo '$USER'` should print `$USER` (nothing interpreted).

---

## 10. env

- [ ] **Check if `env` displays current environment variables.**

---

## 11. export

- [ ] **Export environment variables, create new ones, and replace old ones.**
- [ ] **Check results with `env`.**

---

## 12. unset

- [ ] **Export, create, replace environment variables.**
- [ ] **Use `unset` to remove them.**
- [ ] **Check with `env`.**

---

## 13. cd

- [ ] **Use `cd` to change directories, check with `/bin/ls`.**
- [ ] **Repeat multiple times, including invalid directories, `.` and `..` arguments.**

---

## 14. pwd

- [ ] **Use `pwd` in various directories, multiple times.**

---

## 15. Relative Path

- [ ] **Execute commands using relative paths.**
- [ ] **Try in different directories with complex relative paths.**

---

## 16. Environment Path

- [ ] **Execute commands without a path (e.g., `ls`, `wc`, `awk`).**
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

- [ ] **Use `echo` with environment variables (`$variable`) as arguments.**
- [ ] **Check that `$` is interpreted as an environment variable.**
- [ ] **Double quotes should interpolate `$`.**
- [ ] **Check that `USER` exists (otherwise, set it).**
- [ ] **`echo "$USER"` should print the variable value.**

---

## 21. Bonus (Only if mandatory part is perfect)

- [ ] **AND/OR/Parentheses:** Use `&&`, `||`, and parentheses; ensure Bash-like behavior.
- [ ] **Wildcard:** Use wildcards in arguments (current directory).
- [ ] **Surprise!**
  - [ ] Set `USER`, `echo "$USER"` → should print value.
  - [ ] `echo '"$USER"'` should print `$USER`.

---