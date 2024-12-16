# ENSEASH

## Description

ENSEASH is a minimalist shell implemented in C, providing a simple interface for executing commands on a Unix/Linux system. The shell displays an informative prompt that includes the return code or termination signal of the previous command and its execution duration in milliseconds. It supports basic command execution with arguments and allows the user to exit with the `exit` command. 


Shell made by : RHINAOUI Mohamed Tarik , CHEIKH-SIDIYA Abdellahi

---

## Features

- **Informative Prompt:**
  - Displays the exit code or termination signal of the last executed command.
  - Includes the command execution duration in milliseconds.

- **Command Execution:**
  - Handles valid, unknown and invalid commands.

- **Exit:**
  - Use the `exit` command to quit the shell.
  - Displays a goodbye message upon exiting.

- **Error Handling:**
  - Manages process creation and execution errors effectively.

- **Interactive Input:**
  - Reads user commands in real-time and executes them.

---

## How It Works

1. **Startup:**
   - On launch, the shell displays the following message:
     ```
     $ ./enseash
     Bienvenue dans la shell ENSEA.
     Pour quitter, tapez 'exit'
     ```

2. **Prompt Format:**
   - After each command, the prompt updates to show:
     - The exit code (for example: `exit:0` for success).
     - The termination signal (for example: `sign:2` for interruption).
     - Execution time in milliseconds (for example: `5ms`).
   - Example of an execution:
     ```
     enseash [exit:0|5ms] %
     enseash [sign:2|12ms] %
     ```

3. **Command Input:**
   - The shell reads and tokenizes user input to extract the command and its arguments.

4. **Execution:**
   - A child process is created using a `fork()`.
   - The child process executes the command via `execvp()`.
   - If the execution fails, the shell displays an error message.

5. **Duration Calculation:**
   - Execution time is measured using `clock_gettime()` function and converted to milliseconds.

6. **Exit:**
   - Typing `exit` terminates the shell and displays the following message:
     ```
     Bye bye...
     ```

---

## Installation and Usage

### 1. Compile and launch the Shell
To compile the source code, we can use gcc:
```bash
gcc -o enseash enseash.c
```
Launch the shell using :
```bash
./enseash
```
