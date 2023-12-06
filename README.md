<p align="center">
    <img src="pipexm.png" alt="Badge Name">
</p>

## Overview
The Pipex project is part of the 42 school curriculum, designed to deepen understanding of UNIX processes and inter-process communication. This project replicates the behavior of a simple pipe (`|`) in a shell script, implementing a program that takes two commands as input and executes them in sequence, with the output of the first command being piped into the second.

## Goals
- To simulate the pipe mechanism in Unix-like systems.
- To handle input and output redirection.
- To effectively manage process creation and execution using `fork`, `execve`, and `waitpid`.
- To implement error handling in system programming.

## Bonuses Achieved
- Support for multiple pipes, allowing for a sequence of commands to be executed.
- Implementation of the `here_doc` functionality, similar to the shell's `<<`.

## Methodology
1. **Parsing Input:** Parsing command-line arguments to extract commands and file names.
2. **File Descriptors Management:** Creating and managing file descriptors for input, output, and pipes.
3. **Process Management:** Using `fork` to create child processes for each command.
4. **Executing Commands:** Utilizing `execve` to execute the commands in each child process.
5. **Pipe Mechanism:** Implementing the pipe mechanism to connect the output of one command to the input of the next.
6. **Here Doc Feature:** Implementing the `here_doc` functionality as an additional bonus.
7. **Error Handling:** Robust error handling throughout the program to manage system call failures.

## Installation & Usage
```bash
git clone [Your-Repo-Link]
cd pipex
make
make bonus
./pipex file1 cmd1 cmd2 file2
./pipex_bonus file1 cmd1 ... cmd10 file2
./pipex_bonus here_doc LIMITER cmd1 cmd2 file2
```
