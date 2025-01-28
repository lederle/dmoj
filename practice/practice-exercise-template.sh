#!/bin/bash

# This will copy a problem from the root directory into the
# practice directory, with tests and interface but with no
# implementation. It may be useful to add the problem names to
# an anki deck to prompt solving them here in the practice directory.
# The idea also is that these pracitice directories are not long-lived,
# practice/ is in gitignore, you can do the problem and delete the work
# with no worries since this script will bootstrap the problem to
# where you can just jump in, etc.
#
# usage: ./exercise-template.sh <exercise-name> "<description>"
# output:

set -e

ex_name=$1
description=$2
dir_name=${ex_name}

# the main file; scans input, prints result using ex_lib
ex_src=${ex_name}.c

# does work of the problem
ex_lib=lib${ex_name}.c

parent_path=$(
  cd "$(dirname "${BASH_SOURCE[0]}")"
  pwd -P
)
cd "$parent_path"

mkdir -p $dir_name/c

# copy this file, don't create it
# ex_lib_h=lib${ex_name}.h
cp ../${dir_name}/c/lib${ex_name}.h ${ex_name}/c/

# copy this file, don't create it
# ex_test=test_${ex_name}.c
cp ../${dir_name}/c/test_${ex_name}.c ${ex_name}/c/

cd ${dir_name}/c

# alter the touch
# touch $ex_src makefile $ex_lib $ex_lib_h $ex_test
touch makefile $ex_src $ex_lib

# blank file to re-type code as practice
# touch reps.c

# summarize this particular problem in the README
touch README.md

TAB="$(printf '\t')"

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
cat <<EOF >>${ex_src}
#include <stdio.h>
#include <stdlib.h>
#include "lib${ex_name}.h"

// $description

int main(void) {

    return EXIT_SUCCESS;
}
EOF

#template lib src
cat <<EOF >>${ex_lib}
#include "lib${ex_name}.h"

int $ex_name() {
    return 1;
}
EOF
