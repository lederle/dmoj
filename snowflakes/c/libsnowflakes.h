#ifndef __SNOWFLAKES__
#define __SNOWFLAKES__

#define SIZE 100000

typedef struct snowflake_node {
  int snowflake[6];
  struct snowflake_node *next;
} snowflake_node;

int identical_right(int snow1[], int snow2[], int start);
int identical_left(int snow1[], int snow2[], int start);
int are_identical(int snow1[], int snow2[]);
void identify_identical(snowflake_node *snowflakes[]);
int code(int snowflake[]);

#endif
