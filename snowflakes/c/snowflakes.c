#include "libsnowflakes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

static int snowflakes[SIZE][6];

int main(void) {
  int n;
  assert(scanf("%d", &n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 6; j++)
      assert(scanf("%d", &snowflakes[i][j]));

  identify_identical(snowflakes, n);
  return EXIT_SUCCESS;
}
