#include <stdio.h>

#include "libsnowflakes.h"

int identical_right(int snow1[], int snow2[], int start) {
  int index1, index2;
  for (int offset = 0; offset < 6; offset++) {
    index1 = offset;
    index2 = (offset + start) % 6;
    if (snow1[index1] != snow2[index2])
      return 0;
  }
  return 1;
}

int identical_left(int snow1[], int snow2[], int start) {
  int snow2_index, offset, index1;
  for (offset = 6, index1 = 0; offset >= 1; offset--, index1++) {
    snow2_index = (start + offset) % 6;
    if (snow1[index1] != snow2[snow2_index])
      return 0;
  }
  return 1;
}

int are_identical(int snow1[], int snow2[]) {
  for (int start = 0; start < 6; start++) {
    if (identical_right(snow1, snow2, start))
      return 1;
    if (identical_left(snow1, snow2, start))
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
