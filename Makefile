CFLAGS = -Wall -Wextra -g -std=c11 -pedantic-errors -MD
LDLIBS = -lm

all: copy one_1 one_2 one_3 one_4 two_1 two_2 three_1 three_2 four_1 four_2

clean:
	rm -rf *.d *.o *.out copy one_1 one_2 one_3 one_4 two_1 two_2 three_1 three_2 four_1 four_2
