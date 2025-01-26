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

void identify_identical(snowflake_node *snowflakes[]) {
  snowflake_node *node1, *node2;
  for (int i = 0; i < SIZE; i++) {
    node1 = snowflakes[i];
    while (node1 != NULL) {
      node2 = node1->next;
      while (node2 != NULL) {
        if (are_identical(node1->snowflake, node2->snowflake)) {
          printf("Twin snowflakes found.\n");
          return;
        }
        node2 = node2->next;
      }
      node1 = node1->next;
    }
  }
  printf("No two snowflakes are alike.\n");
}

int code(int snowflake[]) {
  int sum = 0;
  for (int i = 0; i < 6; i++)
    sum += snowflake[i];
  return sum % SIZE;
}
