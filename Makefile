CFLAGS = -Wall -Wextra -g -std=c11 -pedantic-errors
LDLIBS = -lm

all: ht copy one_1 one_2 one_3 one_4 two_1 two_2 three_1 three_2 four_1 four_2 ds ll

clean:
	rm -rf *.o *.out ht copy one_1 one_2 one_3 one_4 two_1 two_2 three_1 three_2 four_1 four_2 ds ll
