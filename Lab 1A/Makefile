# Makefile for a simple C project with multiple source files
# This Makefile compiles a main program and a test program, both of which depend on several object files. 

CC = gcc 
# The compiler is set to gcc, which is a widely used C compiler.

CFLAGS = -Wall -Wextra -g -std=c99 -pedantic
# The CFLAGS variable contains the flags to be passed to the compiler.
# The -Wall flag enables all compiler's warning messages.
# The -Wextra flag enables additional warning messages that are not included in -Wall.
# The -g flag generates debug information in the operating system's native format.
# The -std=c99 flag specifies that the C99 standard should be used for compilation.
# The -pedantic flag enforces strict ISO C compliance.

all: main test
# The main program is built from main.o, mod.o, factorial.o, and power.o.
# The test program is built from unittest.o, mod.o, factorial.o, and power.o.

####################################################

# TODO: You will be completing the following lines in the Makefile to fulfill the targets and dependencies. Following explanations are provided so you can use them to complete the lines.

# The -o flag specifies the name of the output file.
# The $@ symbol is a special variable in Makefiles that represents the target name.
# The $< symbol is a special variable in Makefiles that represents the first prerequisite (dependency) of the target.
# The $^ symbol is a special variable in Makefiles that represents all the prerequisites of the target.
# The -c flag tells the compiler to compile the source files into object files, but not to link them.

main: main.o mod.o factorial.o power.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c mathlib.h
	$(CC) $(CFLAGS) -c $<

mod.o: mod.c mathlib.h
	$(CC) $(CFLAGS) -c $<

factorial.o: factorial.c mathlib.h
	$(CC) $(CFLAGS) -c $<

power.o: power.c mathlib.h
	$(CC) $(CFLAGS) -c $<

# The test program is built from unittest.o, mod.o, factorial.o, and power.o.
test: unittest.o mod.o factorial.o power.o
	$(CC) $(CFLAGS) -o $@ $^

unittest.o: unittest.c mathlib.h
	$(CC) $(CFLAGS) -c $<


# Shortcut for executing the main program: Type `make run` to run the main program.
run: main
	./main

clean:
	clear # clears the terminal screen
	rm -f *.o *.gch main test
# The -f flag tells the rm command to ignore nonexistent files and arguments, and never prompt.
# The clean target is a common convention in Makefiles to remove all generated files.
# This is useful for cleaning up the directory and starting fresh.


.PHONY: main test run clean 
# The .PHONY target is a special built-in target in Makefiles that tells make that the targets are not files. 
