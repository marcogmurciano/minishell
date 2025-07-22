# `t_cmd` Structure Documentation

The `t_cmd` structure represents a single command in a shell pipeline, along with its associated input/output redirections and heredoc specifications.

## Structure Definition

```c
typedef struct s_cmd {
    char    **argv;                  // Array of command arguments; argv[0] is the command itself.
    char    **infiles;               // Array of input file paths (REDIR_IN_FILES).
    char    **heredocs;              // Array of heredoc delimiters.
    int     expand_heredoc_content;  // If 1, expand variables in heredoc content; if 0, do not expand.
    int     last_in;                 // If 0, last input redirection is infile; if 1, last input is heredoc.
    char    **outfiles;              // Array of output file paths (REDIR_OUT_FILES).
    int     append;                  // If 1, append to last output file; if 0, overwrite.
    t_cmd   *next;                   // Pointer to the next command in the pipeline.
} t_cmd;
```

## Execution Flow

1. **Heredoc Processing**
   - Execute all heredocs first.
   - If a heredoc fails (e.g., user sends EOF with Ctrl+D), do **not** terminate the command. Proceed to the next heredoc or step.

2. **Opening Input Files**
   - Attempt to open all files listed in `infiles`.
   - If any input file fails to open, terminate the command and do not proceed further.

3. **Selecting Input Source**
   - If `last_in == 0`: Use the last input file (`infiles`) as the command's standard input.
   - If `last_in == 1`: Use the last heredoc as the command's standard input.

4. **Opening Output Files**
   - Attempt to open or create all files listed in `outfiles`.
   - Only the last output file is used for command output redirection.
   - If any output file fails to open or create, terminate the command and do not proceed further.

5. **Output File Mode**
   - If `append == 0`: Overwrite the last output file.
   - If `append == 1`: Append to the last output file.
