CC=gcc
CFLAGS=-Wall -std=c11 -pedantic
FILES=hashtable.c test.c test_util.c

.PHONY: test clean

test: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)
	rm -f test.output
	./test > test.output

clean:
	rm -f test
