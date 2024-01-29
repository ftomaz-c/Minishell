# Minishell
<p align= "center"> 
	Minishell
	<a href= "https://github.com/ftomaz-c/Minishell/wiki">
		wiki
	</a>
</p>

## Overview

1. [Project Description](#project-description)
2. [Features to Implement](#features-to-implement)
	- [Bonus Features](#bonus-features)
3. Usage
4. [External Functions](#external-functions)
	- [Standard I/O Functions](#standard-io-functions)
	- [Memory Management Functions](#memory-management-functions)
	- [File I/O Functions](#file-io-functions)
	- [Process and Signal Handling Functions](#process-and-signal-handling-functions)
	- [Other Functions](#other-functions)
5. [Authors](#authors)
6. [Resources](#resources)

## Project Description

The Minishell project is a simplified shell implementation, designed to provide basic command-line functionality similar to that of a standard Unix shell.

## Features to Implement

- **Command Execution**: Minishell allows users to execute commands entered via the command-line interface. It supports executing both built-in shell commands (e.g., cd, echo, exit) and external commands (e.g., system binaries, user-defined executables).

- **Input/Output Redirection**: Users can redirect the input and output streams of commands using redirection operators (<, >). This feature enables file input/output operations and facilitates piping between commands.

- **Environment Variable Handling**: Minishell manages environment variables, allowing users to view, set, and unset environment variables. It provides functionality similar to the export and unset commands in Unix shells.

- **Signal Handling**: The shell handles signals such as Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT) gracefully, providing mechanisms for signal handling and process termination.

### Bonus Features:

- **Logical Operators (&& and ||)**: Minishell supports logical operators for command chaining, allowing users to specify conditional execution based on the success or failure of previous commands. Parentheses can be used to define execution priorities.

- **Wildcard Expansion**: Wildcards are supported for pattern matching in filenames within the current working directory. This feature enhances the flexibility of command-line input by allowing users to specify multiple files or directories using a single expression.

## Usage

## External functions

### Standard I/O Functions

These functions handle input and output operations, including reading input from the user, printing output to the terminal, and managing terminal-related operations.

| Function Name | Description | Library | Return Type | Parameters | Example Usage |
|---------------|-------------|---------|-------------|------------|---------------|
| readline      | Reads a line from the input stream | <readline/readline.h> | char* | None | readline(stdin); |
| rl_clear_history | Clears the history list | <readline/history.h> | void | None | rl_clear_history(); |
| rl_on_new_line | Handles newline character in readline | <readline/readline.h> | void | None | rl_on_new_line(); |
| rl_replace_line | Replaces the current line in readline | <readline/readline.h> | void | const char* text | rl_replace_line("new line"); |
| rl_redisplay | Redraws the current input line in readline | <readline/readline.h> | void | None | rl_redisplay(); |
| add_history | Adds a line to the history list | <readline/history.h> | void | const char* line | add_history("new command"); |
| printf | Prints formatted output | <stdio.h> | int | const char* format, ... | printf("Hello, world!\n"); |
| perror | Prints a descriptive error message to stderr | <stdio.h> | void | const char* s | perror("Error message"); |
| write | Writes to a file descriptor | <unistd.h> | ssize_t | int fd, const void* buf, size_t count | write(fd, buffer, strlen(buffer)); |
| ioctl | Performs device-specific operations | <sys/ioctl.h> | int | int fd, unsigned long request, ... | ioctl(fd, request, ...); |
| tgetent | Initializes the termcap database | <curses.h> | int | char* bp, const char* name | tgetent(bp, name); |
| tgetflag | Gets a boolean entry from the termcap database | <curses.h> | int | const char* id | flag = tgetflag("cm"); |
| tgetnum | Gets a numeric entry from the termcap database | <curses.h> | int | const char* id | rows = tgetnum("li"); |
| tgetstr | Gets a string entry from the termcap database | <curses.h> | char* | const char* id, char** area | cm = tgetstr("cm", &bp); |
| tgoto | Builds a cursor-addressing string | <curses.h> | char* | const char* cap, int col, int row | sequence = tgoto(cap, col, row); |
| tputs | Outputs a string of termcap commands | <curses.h> | int | const char* str, int affcnt, int (*putc)(int) | tputs(sequence, 1, putchar); |
|isatty	|Checks if a file descriptor refers to a terminal|	<unistd.h>	|int	|int fd	|is_terminal = isatty(fd);|
|ttyname|	Returns the name of the terminal device associated with a file descriptor|	<unistd.h>|	char*|	int fd|	terminal_name = ttyname(fd);|
|ttyslot|	Gets the slot number of the current terminal in the tty structure array|	<unistd.h>|	int|	None|	slot_number = ttyslot();|



### Memory Management Functions

These functions handle dynamic memory allocation and deallocation, allowing the program to manage memory resources efficiently.

| Function Name | Description | Library | Return Type | Parameters | Example Usage |
|---------------|-------------|---------|-------------|------------|---------------|
| malloc | Allocates memory dynamically | <stdlib.h> | void* | size_t size | ptr = malloc(10 * sizeof(int)); |
| free | Deallocates memory previously allocated by malloc | <stdlib.h> | void | void* ptr | free(ptr); |


### File I/O Functions

These functions facilitate file input/output operations, including opening, reading, writing, and closing files, as well as obtaining file status information.

| Function Name | Description | Library | Return Type | Parameters | Example Usage |
|---------------|-------------|---------|-------------|------------|---------------|
| access | Checks whether a file exists and has certain permissions | <unistd.h> | int | const char* path, int mode | access("file.txt", F_OK); |
| open | Opens or creates a file | <fcntl.h> | int | const char* path, int flags, mode_t mode | fd = open("file.txt", O_RDWR); |
| read | Reads data from a file descriptor | <unistd.h> | ssize_t | int fd, void* buf, size_t count | read(fd, buffer, sizeof(buffer)); |
| close | Closes a file descriptor | <unistd.h> | int | int fd | close(fd); |
| stat | Gets file status | <sys/stat.h> | int | const char* path, struct stat* buf | stat("file.txt", &st); |
| lstat | Gets symbolic link status | <sys/stat.h> | int | const char* path, struct stat* buf | lstat("link", &st); |
| fstat | Gets file status using file descriptor | <sys/stat.h> | int | int fd, struct stat* buf | fstat(fd, &st); |
| unlink | Removes a file or symbolic link | <unistd.h> | int | const char* path | unlink("file.txt"); |
| dup | Duplicates a file descriptor | <unistd.h> | int | int oldfd | newfd = dup(oldfd); |
| dup2 | Duplicates a file descriptor to a specific descriptor | <unistd.h> | int | int oldfd, int newfd | dup2(oldfd, newfd); |
| pipe | Creates a pipe | <unistd.h> | int | int pipefd[2] | pipe(pipefd); |


### Process and Signal Handling Functions

These functions are related to process management and signal handling, including creating processes, waiting for process termination, and handling signals.

| Function Name | Description | Library | Return Type | Parameters | Example Usage |
|---------------|-------------|---------|-------------|------------|---------------|
| fork | Creates a new process by duplicating the existing process | <unistd.h> | pid_t | None | pid = fork(); |
| wait | Waits for the child process to terminate | <sys/wait.h> | pid_t | int* status | wait(&status); |
| waitpid | Waits for a specific child process to terminate | <sys/wait.h> | pid_t | pid_t pid, int* status, int options | waitpid(pid, &status, 0); |
| wait3 | Similar to waitpid with additional options | <sys/wait.h> | pid_t | int* status, int options, struct rusage* usage | wait3(&status, 0, &usage); |
| wait4 | Similar to waitpid with additional options | <sys/wait.h> | pid_t | pid_t pid, int* status, int options, struct rusage* usage | wait4(pid, &status, 0, &usage); |
| signal | Sets a signal handler for a specific signal | <signal.h> | sighandler_t | int signum, sighandler_t handler | signal(SIGINT, handler); |
| sigaction | Sets action for a specific signal | <signal.h> | int | int signum, const struct sigaction* act, struct sigaction* oldact | sigaction(SIGINT, &action, NULL); |
| sigemptyset | Initializes an empty signal set | <signal.h> | int | sigset_t* set | sigemptyset(&set); |
| sigaddset | Adds a signal to a signal set | <signal.h> | int | sigset_t* set, int signum | sigaddset(&set, SIGINT); |
| kill | Sends a signal to a process or a group of processes | <signal.h> | int | pid_t pid, int sig | kill(pid, SIGTERM); |
| exit | Terminates the calling process | <stdlib.h> | void | int status | exit(EXIT_SUCCESS); |

### Other Functions

These functions serve various purposes, including working with directories, environment variables, and terminal settings.

| Function Name | Description | Library | Return Type | Parameters | Example Usage |
|---------------|-------------|---------|-------------|------------|---------------|
| getcwd | Gets the current working directory | <unistd.h> | char* | char* buf, size_t size | getcwd(buffer, sizeof(buffer)); |
| chdir | Changes the current working directory | <unistd.h> | int | const char* path | chdir("/path/to/directory"); |
| execve | Executes a program | <unistd.h> | int | const char* path, char* const argv[], char* const envp[] | execve("/bin/ls", args, env); |
| opendir | Opens a directory stream | <dirent.h> | DIR* | const char* dirname | dir = opendir("."); |
| readdir | Reads a directory stream | <dirent.h> | struct dirent* | DIR* dir | entry = readdir(dir); |
| closedir | Closes a directory stream | <dirent.h> | int | DIR* dir | closedir(dir); |
| strerror | Returns the string describing an error code | <string.h> | char* | int errnum | printf("Error: %s\n", strerror(errno)); |
|perror|	Prints a descriptive error message to stderr|	<stdio.h>|	void|	const char* s|	perror("Error message");|
|isatty|	Checks if a file descriptor refers to a terminal|	<unistd.h>|	int|	int fd|	is_terminal = isatty(fd);|
|ttyname|	Returns the name of the terminal device associated with a file descriptor|	<unistd.h>|	char*|	int fd|	terminal_name = ttyname(fd);|
|ttyslot|	Gets the slot number of the current terminal in the tty structure array|	<unistd.h>|	int|	None|	slot_number = ttyslot();|
|ioctl|	Performs device-specific operations|	<sys/ioctl.h>|	int|	int fd, unsigned long request, ...|	ioctl(fd, request, ...);|
|getenv|	Retrieves the value of an environment variable|	<stdlib.h>|	char*|	const char* name|	value = getenv("PATH");|
|tcsetattr|	Sets terminal attributes|	<termios.h>|	int|	int fd, int optional_actions, const struct termios* termios_p|	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);|
|tcgetattr|	Gets terminal attributes|	<termios.h>|	int|	int fd, struct termios* termios_p|	tcgetattr(STDIN_FILENO, &old_termios);|

## Authors

[ftomaz-c](https://github.com/ftomaz-c) Fábio Tomaz Castim<br>
[CarolinaRVB](https://github.com/CarolinaRVB) Carolina Vela Bastos

## Resources

[Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) - a brief description of the features that are present in the Bash shell;<br>
[Book Online: Introduction to Systems Programming: a Hands-on Approach](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/) by
Gustavo A. Junipero Rodriguez-Rivera and
Justin Ennen; <br>
[maiadegraaf - minishell](https://github.com/maiadegraaf/minishell) - git;<br>
[madebypixel102](https://github.com/madebypixel02/minishell) - git;<br>
[Minishell: Building a mini-bash (a @42 project)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218) - MannBell<br>
