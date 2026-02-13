CC = gcc
CFLAGS = -std=c17 -Wall  -Werror -pedantic -g

TSP: main.o location.o tsp.o cli.o city.o status.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

main.o: main.c city.h cli.h tsp.h
	$(CC) $(CFLAGS) -c $<

tsp.o: tsp.c tsp.h location.h cli.h status.h
	$(CC) $(CFLAGS) -c $<

location.o: location.c location.h status.h
	$(CC) $(CFLAGS) -c $<

cli.o: cli.c cli.h status.h
	$(CC) $(CFLAGS) -c $<

city.o: city.c city.h location.h status.h
	$(CC) $(CFLAGS) -c $<

status.o: status.c status.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o TSP

.PHONY: clean