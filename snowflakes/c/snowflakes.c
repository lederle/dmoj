#include "libsnowflakes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static snowflake_node *snowflakes[SIZE] = {NULL};

int main(void) {
  snowflake_node *snow;
  int n;
  assert(scanf("%d", &n));
  for (int i = 0; i < n; i++) {
    snow = malloc(sizeof(snowflake_node));
    if (snow == NULL) {
      fprintf(stderr, "malloc error\n");
      exit(1);
    }
    for (int j = 0; j < 6; j++)
      assert(scanf("%d", &snow->snowflake[j]));
    int snowflake_code = code(snow->snowflake);
    snow->next = snowflakes[snowflake_code];
    snowflakes[snowflake_code] = snow;
  }
  identify_identical(snowflakes);
  return EXIT_SUCCESS;
}
