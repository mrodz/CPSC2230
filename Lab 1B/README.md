# cs2230 Lab 2: Treasure Hunt w/ GDB
Welcome to the GDB Lab! In this lab, you'll explore a C program and learn how to use a debugger to find a "secret" set of keys hidden within the source code. This lab is designed to reinforce how a debugger automates the process of finding and fixing bugs and helps you understand program flow, inspect memory, and test hypotheses. You'll be working with a compiled binary version of the program to solve the riddles using some combination of the GDB commands below.

## Pirate Story
Ahoy, matey! The legendary 2230 Pirate Programmers, led by Captain Ozan and Captain Alan, are seeking new crew. To prove you're worthy of a spot on our ship, you must complete the ultimate test: a pirate programmer's treasure hunt.

Our rival, the treacherous Segfault Squadron led by Captain Mike Shah, has hidden a piece of our treasure and scattered its secrets across the digital seas. We've captured a member of their crew, Quartermaster Harry, but he's locked his tongue! Luckily, we've managed to acquire a cryptic riddle from him, and we believe the answers to it will help you debug the code you'll use to find the treasure.

Find the treasure, and a place among our crew awaits. Fail, and you'll be forced to walk the plank. Now get to it!


## GDB Background
GDB (the GNU Project Debugger) is a powerful tool used by programmers to understand what's happening inside a program while it's running. Instead of relying on guesswork or endlessly adding `printf` statements, GDB allows you to pause the program, inspect the values of variables, and step through the code line by line. Think of it as your pirate spyglass, letting you see exactly where the bugs are hiding in the vast ocean of your code.

### Essential GDB Commands
Here are some of the most useful commands you'll need to navigate the code and find the treasure:

> Note: GDB provides short versions of many of its common commands. You can speed up the debugging process and reduce typos by using them. In most cases, the short version is the first letter of the long command (e.g., `r`, `b`, `n`, `p`); in others it is some other shortened version (e.g., `bt`). I've listed the short versions next to the long versions in the list below.

`run <args>` (or simply `r <args>`): This command starts the program. You'll need to use this to provide the command-line arguments that you think are correct.

`break <line_number>` or `break <function_name>` (or simply `b <line_number>`): Set a breakpoint at a specific line in the code. This will pause the program's execution so you can inspect its state.

`next` (or `n`): Step to the next line of code without stepping into a function call. Use this to move through the code line by line.

`step` (or `s`): Step to the next line of code, and step into a function call if one is present.

`print <variable_name>` (or `p <variable_name>`): Print the value of a variable. This is your most powerful tool for seeing what values the program is using and where it might be going wrong.

`display <variable_name>` (or `d <variable_name>`): Automatically prints the value of a variable whenever the program pauses. This is especially useful for watching a variable's value change as you step through a loop.

`continue` (or `c`): Resume the program's execution after it has been paused by a breakpoint.

`backtrace` (or `bt`; alteratively `where`): This command shows you the call stack, which is a list of all the functions that were called to get to the current point in the program. This is incredibly useful for tracing an error back to its origin.

`frame <frame_number>` (or `f <frame_number>`): Switch the context to a specific frame of the call stack, allowing you to investigate the values of variables that are local to certain stack frames.

`kill` (or `k`): Stops the currently-executing program (requires confirmation).

## Assignment
### Objectives
- **Understand Program Control Flow:** Learn how to step through a program's execution line-by-line using a debugger.

- **Inspect Program State:** Practice examining the values of variables and memory at different points during a program's execution.

- **Reverse-Engineer a Binary:** Use GDB to understand the logic of a compiled C program without reading the source code.

- **Problem Solving:** Solve the treasure hunt by using the GDB commands to find the correct command-line arguments.

### Files and Their Roles
- `treasure_hunt` (binary): The compiled, executable version of the C program. This is the file you will be debugging.

- `treasure_hunt_challenge` (binary): The more difficult version of the compiled executable if you're feeling ready for a challenge.

- `riddle.md`: This file contains a cryptic pirate riddle that hints at the required command-line argument “keys” to find the treasure.

- `riddle.mp3`: A music version of the riddle.

### Tasks
1. **Start GDB:** Begin a GDB session with the compiled binary and your initial command-line arguments. **You are not given the source or object files** so if you accidentally delete one of the object or executable files, you will have to download them again (you cannot compile them yourself). You are required to create a log file to save your work. To do so, run GDB and use the following commands in the debugger:
```
set logging file treasure_hunt.log
set logging enabled on
set trace-commands on
show logging
```
Note that you **must run these commands every time you restart GDB as the log is how you will be graded** (based on your process and discovery of correct arguments).

1. **Debug the Program:** Use the GDB commands from the "Essential GDB Commands" section to step through the program, inspect variables, and find the correct command-line arguments.

2. **Solve the Riddle:** Once you have found all correct arguments, run the program one final time to claim confirm your solution. The arguments themselves form your map to the real treasure!

3. **Submit to Gradescope**: Make sure to **submit your `treasure_hunt.log` file** to Gradescope before the deadline.

### Tips
- Start by setting a breakpoint at the `main` function.

- Use `step` to follow the program into each function call.

- Use `print` and `display` liberally to see what values are being compared.

- Use `break walk_the_plank` to set a breakpoint at the failure condition and then use `backtrace` to see where the error came from and `frame` to investigate values.

Good luck, and may you find the treasure!

---

<small>
This lab is provided for educational and non-commercial purposes only, under the principles of fair use. The material is intended for the personal use of students for learning and debugging practice. Any distribution or use of this content for other purposes is not permitted. The content was created by Harry Jain (September 2025) with the assistance of AI tools.
</small>