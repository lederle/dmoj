#include <stdio.h>

#include "libsnowflakes.h"

int identical_right(int snow1[], int snow2[], int start) {
  for (int offset = 0; offset < 6; offset++) {
    int index1 = offset;
    int index2 = (offset + start) % 6;
    if (snow1[index1] != snow2[index2])
      return 0;
  }
  return 1;
}

void swap_elem(int values[], int index1, int index2) {
  int tmp = values[index1];
  values[index1] = values[index2];
  values[index2] = tmp;
}

int identical_left(int snow1[], int snow2[], int start) {
  swap_elem(snow2, (start + 1) % 6, (start + 5) % 6);
  swap_elem(snow2, (start + 2) % 6, (start + 4) % 6);
  return identical_right(snow1, snow2, start);
}

int book_identical_left(int snow1[], int snow2[], int start) {
  for (int offset = 0; offset < 6; offset++) {
    int snow2_index = start - offset;
    if (snow2_index <= -1)
      snow2_index += 6;
    if (snow1[offset] != snow2[snow2_index])
      return 0;
  }
  return 1;
}

int are_identical(int snow1[], int snow2[]) {
  for (int start = 0; start < 6; start++) {
    if (identical_right(snow1, snow2, start))
      return 1;
    if (book_identical_left(snow1, snow2, start))
      return 1;
  }
  return 0;
}

void identify_identical(int snowflakes[][6], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (are_identical(snowflakes[i], snowflakes[j])) {
        printf("Twin snowflakes found.\n");
        return;
      }
    }
  }
  printf("No two snowflakes are alike.\n");
}
