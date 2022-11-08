CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm
FILES=btree.c ../btree.c ../test_util.c ../test.c

.PHONY: test clean

test: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)
	rm -f test.output
	./test > test.output

clean:
	rm -f test
