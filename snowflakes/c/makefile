.POSIX:
.SUFFIXES:

CC = gcc
LDLIBS = -lm

CFLAGS = -std=gnu11
CFLAGS += -g
CFLAGS += -Og
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

# This is the optimization used on kattis
# CFLAGS += -O2

# These are further exercism flags
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
# CFLAGS += -Werror
CFLAGS += -Wmissing-declarations

all: test snowflakes

.PHONY:
test: tests.out
	./tests.out

snowflakes: snowflakes.o libsnowflakes.o
	$(CC) $(LDFLAGS) -o snowflakes snowflakes.o libsnowflakes.o $(LDLIBS)

snowflakes.o: snowflakes.c libsnowflakes.h
	$(CC) $(CFLAGS) -c snowflakes.c $(LDLIBS)

libsnowflakes.o: libsnowflakes.c libsnowflakes.h
	$(CC) $(CFLAGS) -c libsnowflakes.c $(LDLIBS)

.PHONY: clean
clean:
	rm -rf snowflakes *.o *.out

tests.out: test_snowflakes.c libsnowflakes.c libsnowflakes.h
	${CC} $(CFLAGS) ../../lib/test-framework/unity.c test_snowflakes.c libsnowflakes.c -o tests.out $(LDLIBS)
