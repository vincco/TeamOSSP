CC      = gcc
CFLAGS  = -O2 -Wall -Wextra -pthread

dining: dining.c
	$(CC) $(CFLAGS) -o dining dining.c

test: dining
	bash tests/run_tests.sh

clean:
	rm -f dining

.PHONY: test clean
