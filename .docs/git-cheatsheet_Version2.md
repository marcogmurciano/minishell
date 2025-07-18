# Git Cheatsheet

This cheatsheet covers the most common and useful Git commands, with clear explanations, examples, and differences between similar commands.

---

## 1. Configuration

| Command | Description | Example |
|---|---|---|
| `git config --global user.name "Your Name"` | Sets the global Git username. Used for all repos unless overridden. | `git config --global user.name "Alice"` |
| `git config --local user.name "Your Name"` | Sets the username for the current repository only. | `git config --local user.name "Bob"` |
| `git config --global user.email "you@example.com"` | Sets global email. Used for all repos unless overridden. | `git config --global user.email "alice@example.com"` |
| `git config -l` | Lists all current Git configurations. | |

**Difference**:  
`--global` applies to all repositories, `--local` applies only to the current repository.

---

## 2. Repository Basics

| Command | Description | Example |
|---|---|---|
| `git init` | Initializes a new, empty Git repository in the current directory. | `git init` |
| `git clone <repo_url>` | Copies an existing remote repository to your local machine. | `git clone https://github.com/user/repo.git` |

**Difference**:  
- `git init` creates a new repo from scratch.  
- `git clone` copies an existing repo (including history).

---

## 3. Staging and Committing

| Command | Description | Example |
|---|---|---|
| `git status` | Shows the status of changes as untracked, modified, or staged. | `git status` |
| `git add <file>` | Stages a specific file for commit. | `git add hello.py` |
| `git add .` | Stages all files (new, modified) in the current directory and subdirectories. | `git add .` |
| `git commit -m "msg"` | Commits staged changes with a message. | `git commit -m "Add new feature"` |
| `git commit -a -m "msg"` | Adds & commits all tracked files (skips untracked files). | `git commit -a -m "Fix bug"` |

**Difference**:  
- `git add` stages changes; `git commit` records them in history.
- `git commit -a` auto-stages all tracked files, but not new untracked files (use `git add` for new files).

---

## 4. Branching

| Command | Description | Example |
|---|---|---|
| `git branch` | Lists all local branches. | `git branch` |
| `git branch <name>` | Creates a new branch, but does not switch to it. | `git branch feature-x` |
| `git checkout <branch>` | Switches to the specified branch. | `git checkout feature-x` |
| `git checkout -b <branch>` | Creates and switches to a new branch. | `git checkout -b hotfix` |
| `git switch <branch>` | Switches to a branch (safer and simpler than `checkout`). | `git switch main` |
| `git switch -c <branch>` | Creates and switches to a new branch. | `git switch -c feature-y` |
| `git branch -d <branch>` | Deletes the specified branch (safe, prevents deleting unmerged). | `git branch -d feature-x` |
| `git branch -D <branch>` | Forces deletion of a branch (even if not merged). | `git branch -D old-feature` |

**Difference**:  
- `git checkout` can switch branches or restore files; `git switch` is just for switching branches.
- `git branch -d` is safe (won't delete unmerged branches), `git branch -D` forces deletion.

---

## 5. Merging & Rebasing

| Command | Description | Example |
|---|---|---|
| `git merge <branch>` | Merges the given branch into the current branch, creating a merge commit if needed. | `git merge feature-x` |
| `git rebase <branch>` | Moves or reapplies commits from one branch onto another, rewrites history. | `git rebase main` |

**Difference**:  
- `merge` preserves branch history and creates merge commits.
- `rebase` creates a linear history by replaying commits, but rewrites commit hashes/history.  
- Rebasing is best before sharing your branch; merging is safer for shared history.

---

## 6. Remote Repositories

| Command | Description | Example |
|---|---|---|
| `git remote -v` | Lists all remotes for this repo. | |
| `git remote add <name> <url>` | Adds a new remote repository. | `git remote add origin https://github.com/user/repo.git` |
| `git push <remote> <branch>` | Uploads local branch commits to the remote branch. | `git push origin main` |
| `git pull <remote> <branch>` | Fetches and merges changes from remote into current branch. | `git pull origin main` |
| `git fetch <remote>` | Downloads objects and refs from another repository without merging. | `git fetch origin` |

**Difference**:  
- `git fetch` gets changes but does not merge;  
- `git pull` does `fetch` + `merge` (or `rebase` if configured).

---

## 7. Viewing History

| Command | Description | Example |
|---|---|---|
| `git log` | Shows commit history with details. | `git log` |
| `git log --oneline` | Shows each commit as one line (condensed). | |
| `git log --graph --oneline --all` | Visualizes branch structure/history. | |
| `git show <commit>` | Shows details of a specific commit. | `git show 4a5e6c7` |

---

## 8. Undoing Changes

| Command | Description | Example |
|---|---|---|
| `git checkout -- <file>` | Discards changes in a file (restores last committed version). | `git checkout -- hello.py` |
| `git restore <file>` | Restores file to last commit (modern, safer than `checkout`). | `git restore hello.py` |
| `git reset <file>` | Unstages a staged file (keeps working directory changes). | `git reset hello.py` |
| `git reset --hard` | Discards all working directory & staging changes (DANGEROUS). | `git reset --hard` |
| `git revert <commit>` | Creates a new commit that undoes the changes from a specific commit. | `git revert 4a5e6c7` |

**Difference**:  
- `git checkout -- <file>` and `git restore <file>` both discard local changes in a file, but `restore` is preferred in newer Git.
- `git reset` (without `--hard`) only affects staging; `--hard` also wipes working directory.
- `git revert` is safe for undoing public commits (creates new commit), `reset --hard` rewrites history and is dangerous for shared branches.

---

## 9. Stashing

| Command | Description | Example |
|---|---|---|
| `git stash` | Stashes (saves and removes) current changes for later. | `git stash` |
| `git stash apply` | Reapplies the latest stash (keeps stash in stash list). | `git stash apply` |
| `git stash pop` | Reapplies and removes the latest stash. | `git stash pop` |
| `git stash list` | Lists all saved stashes. | |

**Difference**:  
- `git stash apply` keeps the stash, `git stash pop` removes it after applying.

---

## 10. Tagging

| Command | Description | Example |
|---|---|---|
| `git tag` | Lists tags in the repo. | |
| `git tag <name>` | Creates a lightweight tag at the latest commit. | `git tag v1.0.0` |
| `git tag -a <name> -m "msg"` | Creates an annotated tag with a message. | `git tag -a v1.0.0 -m "Release 1.0.0"` |
| `git tag -d <name>` | Deletes a tag locally. | `git tag -d v1.0.0` |
| `git push <remote> <tag>` | Pushes a tag to a remote. | `git push origin v1.0.0` |

**Difference**:  
- Annotated tags (`-a`) store more info (author, date, message), lightweight tags do not.

---

## 11. Useful Shortcuts

| Command | Description | Example |
|---|---|---|
| `git diff` | Shows unstaged changes in the working directory. | |
| `git diff --staged` | Shows staged changes (to be committed). | |
| `git clean -fd` | Removes all untracked files/directories (DANGEROUS). | |
| `git cherry-pick <commit>` | Applies a specific commit from another branch onto the current branch. | `git cherry-pick 4a5e6c7` |

---

## 12. Help

| Command | Description | Example |
|---|---|---|
| `git help <command>` | Shows help for a specific command. | `git help commit` |
| `<command> --help` | Alternative help usage. | `git status --help` |

---

## Tips

- **.gitignore**: Use this file to specify files/folders that Git should ignore.
- **SSH keys**: Use SSH keys for secure authentication with remotes.
- **Aliases**: Create Git aliases for custom shortcuts (e.g., `git config --global alias.st status`).

---

## Further Reading

- [Official Git Documentation](https://git-scm.com/doc)
- [Pro Git Book](https://git-scm.com/book/en/v2)
