#!/bin/bash

# usage: ./exercise-template.sh <exercise-name> "<description>"
# output:

set -e

ex_name=$1
description=$2
dir_name=${ex_name}

# GIT
# git checkout -b $ex_name

mkdir -p $dir_name/c
cd $dir_name/c
# the main file; scans input, prints result using ex_lib
ex_src=${ex_name}.c
# does work of the problem
ex_lib=lib${ex_name}.c
ex_lib_h=lib${ex_name}.h
ex_test=test_${ex_name}.c

touch $ex_src makefile $ex_lib $ex_lib_h $ex_test

# blank file to re-type code as practice
# touch reps.c

# summarize this particular problem in the README
touch README.md

TAB="$(printf '\t')"

# local gitignore file
cat <<EOF >>.gitignore
$ex_name
EOF

# template make file
cat <<EOF >>makefile
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

all: test $ex_name

.PHONY:
test: tests.out
${TAB}./tests.out

$ex_name: $ex_name.o lib$ex_name.o
${TAB}\$(CC) \$(LDFLAGS) -o $ex_name $ex_name.o lib$ex_name.o \$(LDLIBS)

$ex_name.o: $ex_name.c lib$ex_name.h
${TAB}\$(CC) \$(CFLAGS) -c $ex_name.c \$(LDLIBS)

lib$ex_name.o: lib$ex_name.c lib$ex_name.h
${TAB}\$(CC) \$(CFLAGS) -c lib$ex_name.c \$(LDLIBS)

.PHONY: clean
clean:
${TAB}rm -rf $ex_name *.o *.out

tests.out: test_$ex_name.c lib$ex_name.c lib$ex_name.h
${TAB}\${CC} \$(CFLAGS) ../../lib/test-framework/unity.c test_$ex_name.c lib$ex_name.c -o tests.out \$(LDLIBS)
EOF

# template c file
cat <<EOF >>$ex_src
#include <stdio.h>
#include <stdlib.h>
#include "$ex_lib_h"

// $description

int main(void) {

    return EXIT_SUCCESS;
}
EOF

#template lib src
cat <<EOF >>$ex_lib
#include "$ex_lib_h"

int $ex_name() {
    return 1;
}
EOF

#template lib header
cat <<EOF >>$ex_lib_h
#ifndef __${ex_name^^}__
#define __${ex_name^^}__

int $ex_name();

#endif
EOF

#template test file
cat <<EOF >>$ex_test
#include "../../lib/test-framework/unity.h"
#include "$ex_lib_h"

void setUp(void) {
}

void tearDown(void) {
}

static void test_canary(void) {
    TEST_PASS(); 
}

int main(void) {
    UnityBegin("$ex_test");
    RUN_TEST(test_canary);
    
    return UnityEnd();
}
EOF

# GIT
# git add .
# git clang-format
# git add .
# git commit -m "INIT: $ex_name"
