CFLAGS = -Wall -Wextra -g -std=c11 -pedantic-errors

all: ht copy one_1 one_2 one_3 one_4 two_1 two_2

clean:
	rm -rf *.o *.out ht copy one_1 one_2 one_3 one_4 two_1 two_2
