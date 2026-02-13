CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

median: main.o io.o median.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c io.h median.h
	$(CC) $(CFLAGS) -c $<

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $<

median.o: median.c median.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o median

.PHONY: clean median