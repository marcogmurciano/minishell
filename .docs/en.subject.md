# Minishell  
_As beautiful as a shell_  

**Version:** 7.1  

## Summary  
This project is about creating a simple shell.  
Yes, your own little bash.  
You will learn a lot about processes and file descriptors.  

---

## Contents  
- [Introduction](#introduction)  
- [Common Instructions](#common-instructions)  
- [Mandatory part](#mandatory-part)  
- [Bonus part](#bonus-part)  
- [Submission and peer-evaluation](#submission-and-peer-evaluation)  

---

## Introduction  
The existence of shells is linked to the very existence of IT.  
At the time, all developers agreed that communicating with a computer using aligned 1/0 switches was seriously irritating.  

It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language.  

Thanks to Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.  

---

## Common Instructions  

- Your project must be written in C.  
- Your project must be written in accordance with the Norm.  
- Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc).  
- All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.  
- If the subject requires it, you must submit a Makefile with `-Wall -Wextra -Werror` flags.  
- Your Makefile must include rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`.  
- For bonuses, include a `bonus` rule in Makefile. Bonuses must be in a different file _bonus.{c/h}.  
- If allowed to use `libft`, place its sources and Makefile in a `libft/` folder.  
- Create test programs for your project, though they won’t be submitted or graded.  
- Submit your work to your assigned git repository. Only that work will be graded.  

---

## Mandatory part  

**Program name:** `minishell`  
**Turn in files:** Makefile, *.h, *.c  
**Makefile:** `NAME`, `all`, `clean`, `fclean`, `re`  

### External functions:  
- readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history  
- printf, malloc, free, write, access, open, read, close  
- fork, wait, waitpid, wait3, wait4  
- signal, sigaction, sigemptyset, sigaddset, kill  
- exit, getcwd, chdir, stat, lstat, fstat, unlink, execve  
- dup, dup2, pipe  
- opendir, readdir, closedir  
- strerror, perror, isatty, ttyname, ttyslot, ioctl  
- getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs  

**Libft authorized:** Yes  

### Your shell should:  
- Display a prompt when waiting for a new command  
- Have a working history  
- Search and launch executables (from `$PATH`, relative, or absolute paths)  
- Avoid using more than one global variable (only for signal number)  
- Not interpret unclosed quotes or special characters like `\` or `;`  
- Handle quotes:
  - `'` (single): prevent meta-character interpretation  
  - `"` (double): prevent meta-character interpretation, except `$`  
- Implement redirections:
  - `<` input  
  - `>` output  
  - `<<` heredoc (with delimiter, no history update needed)  
  - `>>` append output  
- Implement pipes (`|`)  
- Handle environment variables (`$VAR`)  
- Handle `$?` (last command exit status)  
- Handle:
  - `ctrl-C`: show new prompt  
  - `ctrl-D`: exit shell  
  - `ctrl-\`: do nothing  

### Builtins required:  
- `echo` with `-n`  
- `cd` with path  
- `pwd`  
- `export`  
- `unset`  
- `env`  
- `exit`  

> Note: `readline()` can cause leaks. You are not responsible for fixing them. But **your code must not leak**.

If in doubt, **take Bash as a reference**.

---

## Bonus part  

Your program has to implement:  
- `&&` and `||` (with parenthesis for priorities)  
- Wildcards `*` (for current working directory)  

**Note:** Bonus is assessed **only if the mandatory part is perfect**.

---

## Submission and peer-evaluation  

Turn in your assignment in your Git repository as usual.  
Only the content in your repository will be evaluated during defense.  
Double check filenames.

---
