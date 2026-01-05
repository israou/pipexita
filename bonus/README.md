# Pipex – 42 School Project

**Pipex** is a system programming project from 42 School that recreates the behavior of shell pipes in C. The goal is to understand how pipes work at a low level, handle processes with `fork()`, and manage file descriptors to redirect input and output between commands.

This project introduces fundamental concepts of UNIX process management, inter-process communication (IPC), and system calls.

## 📌 Project Overview

The objective of Pipex is to replicate the behavior of the shell pipe operator `|` by executing two commands and passing the output of the first command as input to the second command.

The project must demonstrate:
* **Process Management** – Using `fork()` to create child processes
* **Inter-Process Communication** – Using pipes to connect processes
* **File Descriptor Management** – Redirecting stdin/stdout with `dup2()`
* **Command Execution** – Using `execve()` to run commands
* **Error Handling** – Robust handling of system call failures

## 🎯 Behavior

### Shell Equivalent

The program replicates this shell behavior:
```bash
< file1 cmd1 | cmd2 > file2
```

Which is equivalent to:
```bash
cmd1 < file1 | cmd2 > file2
```

### Pipex Usage
```bash
./pipex file1 cmd1 cmd2 file2
```

**Example:**
```bash
# Shell command
< infile grep "hello" | wc -l > outfile

# Pipex equivalent
./pipex infile "grep hello" "wc -l" outfile
```

## 🛠️ Installation & Usage

### Requirements

* C compiler (gcc/clang)
* Make
* Unix/Linux or macOS system
* Standard C library

### Build & Run
```bash
# Clone the repository
git clone https://github.com/your-username/pipex.git
cd pipex

# Compile
make

# Run the program
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
./pipex infile "cat" "cat" outfile

# Compile bonus
make bonus

# Run bonus with multiple pipes
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" outfile

# Run bonus with here_doc
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

## 📖 Usage Examples

### Basic Examples
```bash
# Count lines containing "error" in log.txt
./pipex log.txt "grep error" "wc -l" result.txt

# Equivalent shell command
< log.txt grep error | wc -l > result.txt
```
```bash
# List files and count them
./pipex /dev/null "ls -la" "wc -l" count.txt

# Equivalent shell command
< /dev/null ls -la | wc -l > count.txt
```
```bash
# Search and sort
./pipex input.txt "grep 42" "sort" output.txt

# Equivalent shell command
< input.txt grep 42 | sort > output.txt
```

### Bonus Examples
```bash
# Multiple pipes (3 commands)
./pipex infile "cat" "grep hello" "wc -l" outfile

# Equivalent shell command
< infile cat | grep hello | wc -l > outfile
```
```bash
# Here document (heredoc)
./pipex here_doc EOF "cat" "grep hello" outfile
hello world
hello 42
EOF

# Equivalent shell command
cat << EOF | grep hello > outfile
hello world
hello 42
EOF
```
```bash
# Complex pipeline (5 commands)
./pipex infile "cat" "grep a" "sort" "uniq" "wc -l" outfile
```

## 🔧 Technical Implementation

### Key System Calls

#### 1. Pipe
```c
int pipe(int pipefd[2]);
// pipefd[0] - read end
// pipefd[1] - write end
```

#### 2. Fork
```c
pid_t fork(void);
// Returns 0 in child process
// Returns child PID in parent process
```

#### 3. Dup2
```c
int dup2(int oldfd, int newfd);
// Redirects file descriptors
// dup2(file, STDIN_FILENO)  - redirect input
// dup2(file, STDOUT_FILENO) - redirect output
```

#### 4. Execve
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
// Replaces current process with new program
```

#### 5. Wait/Waitpid
```c
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
// Wait for child process to terminate
```

### Program Flow
```
1. Open input file (file1)
2. Create pipe
3. Fork first child:
   - Redirect stdin to file1
   - Redirect stdout to pipe write end
   - Execute cmd1
4. Fork second child:
   - Redirect stdin to pipe read end
   - Redirect stdout to file2
   - Execute cmd2
5. Close all file descriptors in parent
6. Wait for both children to finish
7. Exit with appropriate status
```

### Process Diagram
```
Parent Process
    |
    |-- fork() --> Child 1 (cmd1)
    |              - stdin: file1
    |              - stdout: pipe[1]
    |              - execve(cmd1)
    |
    |-- fork() --> Child 2 (cmd2)
                   - stdin: pipe[0]
                   - stdout: file2
                   - execve(cmd2)
```

## 💡 Key Concepts

### 1. File Descriptors

Standard file descriptors:
* `0` – STDIN_FILENO (standard input)
* `1` – STDOUT_FILENO (standard output)
* `2` – STDERR_FILENO (standard error)

### 2. Path Resolution

Commands must be found in PATH environment variable:
```c
// Split PATH by ':'
char **paths = ft_split(getenv("PATH"), ':');

// Try each path with command
char *cmd_path = NULL;
for (int i = 0; paths[i]; i++)
{
    char *full_path = join_path(paths[i], cmd);
    if (access(full_path, X_OK) == 0)
    {
        cmd_path = full_path;
        break;
    }
}
```

### 3. Command Parsing

Parse command and arguments:
```bash
"grep hello" → ["grep", "hello", NULL]
"ls -la" → ["ls", "-la", NULL]
"wc -l" → ["wc", "-l", NULL]
```

### 4. Error Handling

Handle various error cases:
* File not found
* Permission denied
* Command not found
* Invalid arguments
* Fork/pipe failures

## 🎯 Bonus Features

### 1. Multiple Pipes

Handle unlimited number of commands:
```bash
./pipex file1 "cmd1" "cmd2" "cmd3" ... "cmdN" file2
```

Equivalent to:
```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdN > file2
```

### 2. Here Document (here_doc)

Support heredoc syntax:
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" file
```

Equivalent to:
```bash
cmd1 << LIMITER | cmd2 >> file
```

**Behavior:**
* Read from stdin until LIMITER is encountered
* Append to output file instead of overwriting
* Pass input through pipe to commands

## 🧪 Test Cases

### Basic Tests
```bash
# Test 1: Basic pipe
./pipex infile "cat" "grep hello" outfile
< infile cat | grep hello > outfile

# Test 2: Count lines
./pipex infile "ls -l" "wc -l" outfile
< infile ls -l | wc -l > outfile

# Test 3: Sort and unique
./pipex infile "cat" "sort" outfile
< infile cat | sort > outfile
```

### Error Tests
```bash
# File doesn't exist
./pipex nofile "cat" "wc -l" outfile

# Command not found
./pipex infile "invalidcmd" "wc -l" outfile

# Permission denied
chmod 000 infile
./pipex infile "cat" "wc -l" outfile

# Invalid number of arguments
./pipex infile "cat" outfile
```

### Bonus Tests
```bash
# Multiple pipes (3 commands)
./pipex infile "cat" "grep a" "wc -l" outfile

# Here document
./pipex here_doc EOF "cat" "wc -l" outfile
line1
line2
EOF

# Multiple pipes (5 commands)
./pipex infile "cat" "grep a" "sort" "uniq" "wc" outfile
```

### Memory Leak Tests
```bash
# Check for memory leaks
valgrind --leak-check=full ./pipex infile "cat" "wc -l" outfile

# Check for file descriptor leaks
lsof -p $(pgrep pipex)
```

## ✅ Project Requirements Respected

### Mandatory Requirements
* Execute two commands with one pipe
* Handle input/output file redirection
* Proper error handling and exit codes
* Find commands in PATH environment variable
* No memory leaks
* Handle command arguments with quotes
* Proper cleanup of file descriptors

### Bonus Requirements
* Handle multiple pipes (unlimited commands)
* Support here_doc functionality
* Append mode for here_doc (>>)
* All mandatory requirements still apply

## 📚 Skills & Concepts Learned

* **Process Management** – fork(), wait(), waitpid()
* **Inter-Process Communication** – pipe(), file descriptors
* **File I/O** – open(), close(), read(), write()
* **File Descriptor Manipulation** – dup2(), redirection
* **Program Execution** – execve(), PATH resolution
* **Error Handling** – System call failures, exit codes
* **Memory Management** – Proper cleanup and leak prevention
* **Shell Behavior** – Understanding Unix pipes

## 🔍 Common Pitfalls

### 1. File Descriptor Leaks
**Problem:** Not closing all file descriptors
```c
// Always close unused ends
close(pipefd[0]);
close(pipefd[1]);
```

### 2. Zombie Processes
**Problem:** Not waiting for children
```c
// Wait for all children
while (wait(NULL) > 0)
    ;
```

### 3. PATH Resolution
**Problem:** Not handling commands without PATH
```c
// Check if command contains '/'
if (strchr(cmd, '/'))
    return (cmd);  // Absolute or relative path
```

### 4. Quotes Handling
**Problem:** Not properly parsing quoted arguments
```bash
"grep 'hello world'" # Should be treated as one argument
```

## 🛠️ Debugging Tips
```bash
# Trace system calls
strace ./pipex infile "cat" "wc -l" outfile

# Check open file descriptors
lsof -p PID

# Debug with GDB
gdb ./pipex
(gdb) run infile "cat" "wc -l" outfile

# Compare with shell
diff <(< infile cat | wc -l) outfile
```

## 👤 Author

**israa chaabi** – 42 Student | Software Engineering  
42 Login: `ichaabi`

## 📚 Resources

* [Pipes, Forks, and Dups](https://www.rozmichelle.com/pipes-forks-dups/)
* [Linux man pages](https://man7.org/linux/man-pages/)
  - `man 2 pipe`
  - `man 2 fork`
  - `man 2 dup2`
  - `man 3 execve`
* [Understanding Unix Pipes](https://www.geeksforgeeks.org/pipe-system-call/)
* [File Descriptors Explained](https://www.computerhope.com/jargon/f/file-descriptor.htm)

## ⚠️ Disclaimer

This project is part of the 42 curriculum and is shared for educational purposes only. If you are a 42 student, do not copy this repository—use it to understand the concepts and build your own implementation.

---
