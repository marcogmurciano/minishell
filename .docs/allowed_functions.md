# Function Definitions with Linux Man Page Links and Usage Examples

Below is a detailed list of each requested function, their definitions, direct links to their respective Linux man pages on [linux.die.net](https://linux.die.net/man/), and example usage (with comments).

---

## GNU Readline Library Functions

- **[readline](https://linux.die.net/man/3/readline)**  
  Reads a line from the terminal with editing and history support.

  ```c
  // Example: Read a line from stdin with prompt
  char *input = readline("Enter command: ");
  ```

- **[rl_clear_history](https://linux.die.net/man/3/readline)**  
  Clears the readline history list.

  ```c
  // Example: Clear all history entries
  rl_clear_history();
  ```

- **[rl_on_new_line](https://linux.die.net/man/3/readline)**  
  Informs readline that the cursor is on a new line.

  ```c
  // Example: Tell readline we're on a new line before redisplay
  rl_on_new_line();
  ```

- **[rl_replace_line](https://linux.die.net/man/3/readline)**  
  Replaces the contents of the readline editing buffer with a new line.

  ```c
  // Example: Replace the current input line with "hello"
  rl_replace_line("hello", 1);
  ```

- **[rl_redisplay](https://linux.die.net/man/3/readline)**  
  Redisplays the current readline line buffer on the terminal.

  ```c
  // Example: Force redisplay of the editing line
  rl_redisplay();
  ```

- **[add_history](https://linux.die.net/man/3/history)**  
  Adds a line to the readline history list.

  ```c
  // Example: Add "ls -l" to command history
  add_history("ls -l");
  ```

---

## Standard I/O and Memory Functions

- **[printf](https://linux.die.net/man/3/printf)**  
  Prints formatted output to stdout.

  ```c
  // Example: Print a message
  printf("Hello, %s!\n", "world");
  ```

- **[malloc](https://linux.die.net/man/3/malloc)**  
  Allocates memory dynamically.

  ```c
  // Example: Allocate 100 bytes
  char *buf = (char *)malloc(100);
  ```

- **[free](https://linux.die.net/man/3/free)**  
  Frees memory previously allocated by `malloc` or related functions.

  ```c
  // Example: Free allocated memory
  free(buf);
  ```

- **[write](https://linux.die.net/man/2/write)**  
  Writes data to a file descriptor.

  ```c
  // Example: Write "hello" to stdout
  write(STDOUT_FILENO, "hello\n", 6);
  ```

- **[access](https://linux.die.net/man/2/access)**  
  Checks user's permissions for a file.

  ```c
  // Example: Check if "file.txt" is readable
  if (access("file.txt", R_OK) == 0) { /* readable */ }
  ```

- **[open](https://linux.die.net/man/2/open)**  
  Opens a file or device.

  ```c
  // Example: Open a file for reading
  int fd = open("file.txt", O_RDONLY);
  ```

- **[read](https://linux.die.net/man/2/read)**  
  Reads data from a file descriptor.

  ```c
  // Example: Read 10 bytes from fd into buffer
  char buffer[10];
  ssize_t n = read(fd, buffer, 10);
  ```

- **[close](https://linux.die.net/man/2/close)**  
  Closes an open file descriptor.

  ```c
  // Example: Close file descriptor
  close(fd);
  ```

---

## Process Control Functions

- **[fork](https://linux.die.net/man/2/fork)**  
  Creates a new process by duplicating the calling process.

  ```c
  // Example: Fork a child process
  pid_t pid = fork();
  if (pid == 0) { /* child */ }
  ```

- **[wait](https://linux.die.net/man/2/wait)**  
  Waits for state changes in a child process.

  ```c
  // Example: Wait for any child to finish
  int status;
  wait(&status);
  ```

- **[waitpid](https://linux.die.net/man/2/waitpid)**  
  Waits for a specific child process to change state.

  ```c
  // Example: Wait for a specific child
  waitpid(pid, &status, 0);
  ```

- **[wait3](https://linux.die.net/man/2/wait3)**  
  Waits for child process state changes with resource usage info (BSD).

  ```c
  // Example: Wait for any child and get resource usage
  struct rusage usage;
  wait3(&status, 0, &usage);
  ```

- **[wait4](https://linux.die.net/man/2/wait4)**  
  Like `wait3`, but waits for a specific process.

  ```c
  // Example: Wait for a specific child and get resource usage
  wait4(pid, &status, 0, &usage);
  ```

---

## Signal Handling Functions

- **[signal](https://linux.die.net/man/2/signal)**  
  Sets a handler for a signal.

  ```c
  // Example: Set SIGINT handler
  signal(SIGINT, handler_function);
  ```

- **[sigaction](https://linux.die.net/man/2/sigaction)**  
  Examines and changes a signal action.

  ```c
  // Example: Set up sigaction struct
  struct sigaction sa = {0};
  sa.sa_handler = handler_function;
  sigaction(SIGINT, &sa, NULL);
  ```

- **[sigemptyset](https://linux.die.net/man/3/sigemptyset)**  
  Initializes a signal set to exclude all signals.

  ```c
  // Example: Initialize an empty signal set
  sigset_t set;
  sigemptyset(&set);
  ```

- **[sigaddset](https://linux.die.net/man/3/sigaddset)**  
  Adds a signal to a signal set.

  ```c
  // Example: Add SIGINT to signal set
  sigaddset(&set, SIGINT);
  ```

- **[kill](https://linux.die.net/man/2/kill)**  
  Sends a signal to a process or group of processes.

  ```c
  // Example: Send SIGKILL to a process
  kill(pid, SIGKILL);
  ```

---

## Termination and File System Functions

- **[exit](https://linux.die.net/man/3/exit)**  
  Causes normal program termination.

  ```c
  // Example: Exit with success status
  exit(EXIT_SUCCESS);
  ```

- **[getcwd](https://linux.die.net/man/2/getcwd)**  
  Gets the current working directory.

  ```c
  // Example: Get current directory
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  ```

- **[chdir](https://linux.die.net/man/2/chdir)**  
  Changes the current working directory.

  ```c
  // Example: Change to /tmp directory
  chdir("/tmp");
  ```

- **[stat](https://linux.die.net/man/2/stat)**  
  Gets file status.

  ```c
  // Example: Get file info
  struct stat sb;
  stat("file.txt", &sb);
  ```

- **[lstat](https://linux.die.net/man/2/lstat)**  
  Gets file status, not following symbolic links.

  ```c
  // Example: Get file info without following symlink
  lstat("link.txt", &sb);
  ```

- **[fstat](https://linux.die.net/man/2/fstat)**  
  Gets file status from an open file descriptor.

  ```c
  // Example: Get file info from fd
  fstat(fd, &sb);
  ```

- **[unlink](https://linux.die.net/man/2/unlink)**  
  Deletes a name and possibly the file it refers to.

  ```c
  // Example: Remove a file
  unlink("file.txt");
  ```

- **[execve](https://linux.die.net/man/2/execve)**  
  Executes a program.

  ```c
  // Example: Execute /bin/ls
  char *argv[] = {"ls", "-l", NULL};
  char *envp[] = {NULL};
  execve("/bin/ls", argv, envp);
  ```

---

## File Descriptor and Pipe Functions

- **[dup](https://linux.die.net/man/2/dup)**  
  Duplicates a file descriptor.

  ```c
  // Example: Duplicate fd to a new descriptor
  int newfd = dup(fd);
  ```

- **[dup2](https://linux.die.net/man/2/dup2)**  
  Duplicates one file descriptor to another.

  ```c
  // Example: Duplicate fd to fd 1 (stdout)
  dup2(fd, 1);
  ```

- **[pipe](https://linux.die.net/man/2/pipe)**  
  Creates a unidirectional data channel (pipe).

  ```c
  // Example: Create a pipe
  int pipefd[2];
  pipe(pipefd);
  ```

---

## Directory Operations

- **[opendir](https://linux.die.net/man/3/opendir)**  
  Opens a directory stream.

  ```c
  // Example: Open current directory
  DIR *dir = opendir(".");
  ```

- **[readdir](https://linux.die.net/man/3/readdir)**  
  Reads a directory entry.

  ```c
  // Example: Read entries from directory
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
      printf("%s\n", entry->d_name);
  }
  ```

- **[closedir](https://linux.die.net/man/3/closedir)**  
  Closes a directory stream.

  ```c
  // Example: Close directory
  closedir(dir);
  ```

---

## Error and Terminal Handling

- **[strerror](https://linux.die.net/man/3/strerror)**  
  Returns the error message string for an error number.

  ```c
  // Example: Print error message
  printf("Error: %s\n", strerror(errno));
  ```

- **[perror](https://linux.die.net/man/3/perror)**  
  Prints a description of the last error to stderr.

  ```c
  // Example: Print error with prefix
  perror("open");
  ```

- **[isatty](https://linux.die.net/man/3/isatty)**  
  Checks if a file descriptor refers to a terminal.

  ```c
  // Example: Check if stdin is a terminal
  if (isatty(STDIN_FILENO))
      printf("stdin is a terminal\n");
  ```

- **[ttyname](https://linux.die.net/man/3/ttyname)**  
  Returns the name of the terminal associated with a file descriptor.

  ```c
  // Example: Get terminal name for stdin
  printf("%s\n", ttyname(STDIN_FILENO));
  ```

- **[ttyslot](https://linux.die.net/man/3/ttyslot)**  
  Returns the slot number of the current user's terminal.

  ```c
  // Example: Get terminal slot number
  int slot = ttyslot();
  ```

- **[ioctl](https://linux.die.net/man/2/ioctl)**  
  Device-specific input/output operations.

  ```c
  // Example: Get terminal window size
  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  ```

---

## Environment and Terminal Capabilities

- **[getenv](https://linux.die.net/man/3/getenv)**  
  Gets the value of an environment variable.

  ```c
  // Example: Get PATH environment variable
  char *path = getenv("PATH");
  ```

- **[tcsetattr](https://linux.die.net/man/3/tcsetattr)**  
  Sets terminal attributes.

  ```c
  // Example: Set terminal attributes
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  // modify t
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  ```

- **[tcgetattr](https://linux.die.net/man/3/tcgetattr)**  
  Gets terminal attributes.

  ```c
  // Example: Get terminal attributes
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  ```

- **[tgetent](https://linux.die.net/man/3/tgetent)**  
  Loads a terminal entry from termcap database.

  ```c
  // Example: Initialize termcap entry
  char termbuf[2048];
  tgetent(termbuf, getenv("TERM"));
  ```

- **[tgetflag](https://linux.die.net/man/3/tgetflag)**  
  Gets the value of a boolean capability.

  ```c
  // Example: Check if terminal has auto-margin (am) capability
  int am = tgetflag("am");
  ```

- **[tgetnum](https://linux.die.net/man/3/tgetnum)**  
  Gets the value of a numeric capability.

  ```c
  // Example: Get number of columns
  int cols = tgetnum("co");
  ```

- **[tgetstr](https://linux.die.net/man/3/tgetstr)**  
  Gets the value of a string capability.

  ```c
  // Example: Get clear screen string
  char *cl = tgetstr("cl", NULL);
  ```

- **[tgoto](https://linux.die.net/man/3/tgoto)**  
  Returns a cursor addressing string.

  ```c
  // Example: Move cursor to (x, y)
  char *cm = tgetstr("cm", NULL);
  char *move = tgoto(cm, 10, 5);
  ```

- **[tputs](https://linux.die.net/man/3/tputs)**  
  Outputs a string with padding for terminal speed.

  ```c
  // Example: Output string to terminal
  tputs(cl, 1, putchar);
  ```

---

**Note:** If a man page does not exist at linux.die.net, consult your local man pages or the GNU documentation.
