# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g

all: hookbook test

# Default target to build the main executable
hookbook: main.o PirateList.o
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files for each .c file
main.o: main.c PirateList.h
	$(CC) $(CFLAGS) -c $<

PirateList.o: PirateList.c PirateList.h
	$(CC) $(CFLAGS) -c $<

# Compile the unit test
test: unittest.o PirateList.o 
	$(CC) $(CFLAGS) -o $@ $^

unittest.o: unittest.c PirateList.h
	$(CC) $(CFLAGS) -c $<

# Clean up object files and executable
clean:
	rm -f *.o hookbook test 

# Run the program with a sample file
run: 
	./hookbook

# Phony targets
.PHONY: all hookbook test clean run
