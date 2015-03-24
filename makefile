CFLAGS = -Wall -Wextra -g -std=c11 -pedantic-errors

all: ht copy kr_1a kr_1b kr_1c kr_1d

clean:
	rm -rf *.o *.out ht copy kr_1a kr_1b kr_1c kr_1d
