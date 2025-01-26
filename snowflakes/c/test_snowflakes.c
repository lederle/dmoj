#include "../../lib/test-framework/unity.h"
#include "libsnowflakes.h"
#include <stdlib.h>

void setUp(void) {}

void tearDown(void) {}

static void test_canary(void) { TEST_PASS(); }

static void test_identical_right_true(void) {
  int snow1[] = {1, 2, 3, 4, 5, 6};
  int snow2[] = {4, 5, 6, 1, 2, 3};
  int start = 3;
  TEST_ASSERT_TRUE(identical_right(snow1, snow2, start));
}

static void test_identical_left(void) {
  int snow1[] = {1, 2, 3, 4, 5, 6};
  int snow2[] = {3, 2, 1, 6, 5, 4};
  int start = 2;
  TEST_ASSERT_TRUE(identical_left(snow1, snow2, start));
}

static void test_identical_left_again(void) {
  int snow1[] = {1, 2, 3, 4, 5, 6};
  int snow2[] = {1, 6, 5, 4, 3, 2};
  int start = 0;
  TEST_ASSERT_TRUE(identical_left(snow1, snow2, start));
}

static void test_are_identical_false(void) {
  int snow1[] = {4, 5, 6, 4, 67, 3};
  int snow2[] = {2, 45, 34, 23, 23, 4};
  TEST_ASSERT_FALSE(are_identical(snow1, snow2));
}

static void test_are_identical_true_identity(void) {
  int snow1[] = {4, 5, 6, 4, 67, 3};
  int snow2[] = {4, 5, 6, 4, 67, 3};
  TEST_ASSERT_TRUE(are_identical(snow1, snow2));
}

static void test_identify_identical_when_found(void) {
  int s1[] = {1, 1, 0, 0, 0, 0};
  int s2[] = {0, 0, 1, 1, 0, 0};
  snowflake_node *snow1, *snow2;
  snow1 = malloc(sizeof(snowflake_node));
  snow2 = malloc(sizeof(snowflake_node));
  for (int i = 0; i < 6; i++) {
    snow1->snowflake[i] = s1[i];
    snow2->snowflake[i] = s2[i];
  }
  snow1->next = snow2;
  snow2->next = NULL;
  snowflake_node *snowflakes[SIZE] = {NULL};
  snowflakes[2] = snow1;
  printf("TEST_IDENTIFY_IDENTICAL WITH IDENTICALS: ");
  identify_identical(snowflakes);
  TEST_PASS();
}

static void test_identify_identical_when_not_found(void) {
  int s1[] = {1, 1, 0, 0, 0, 0};
  int s2[] = {0, 1, 0, 1, 0, 0};
  snowflake_node *snow1, *snow2;
  snow1 = malloc(sizeof(snowflake_node));
  snow2 = malloc(sizeof(snowflake_node));
  for (int i = 0; i < 6; i++) {
    snow1->snowflake[i] = s1[i];
    snow2->snowflake[i] = s2[i];
  }
  snow1->next = snow2;
  snow2->next = NULL;
  snowflake_node *snowflakes[SIZE] = {NULL};
  snowflakes[2] = snow1;
  printf("TEST_IDENTIFY_IDENTICAL WITH NONE IDENTICAL: ");
  identify_identical(snowflakes);
  TEST_PASS();
}

static void test_identify_identical_four_cases(void) {
  snowflake_node *snowflakes[SIZE] = {NULL};
  int lobe_length[][6] = {{3, 4, 5, 6, 1, 2},
                          {2, 3, 4, 5, 6, 7},
                          {4, 5, 6, 7, 8, 9},
                          {1, 2, 3, 4, 5, 6}};
  snowflake_node *snow;
  for (int i = 0; i < 4; i++) {
    snow = malloc(sizeof(snowflake_node));
    for (int j = 0; j < 6; j++) {
      snow->snowflake[j] = lobe_length[i][j];
    }
    snow->next = snowflakes[code(snow->snowflake)];
    snowflakes[code(snow->snowflake)] = snow;
  }
  printf("TEST_IDENTITY_IDENTICAL_FOUR_CASES: ");
  identify_identical(snowflakes);
  TEST_PASS();
}

int main(void) {
  UnityBegin("test_snowflakes.c");
  RUN_TEST(test_canary);
  RUN_TEST(test_identical_right_true);
  RUN_TEST(test_identical_left);
  RUN_TEST(test_identical_left_again);
  RUN_TEST(test_are_identical_false);
  RUN_TEST(test_are_identical_true_identity);
  RUN_TEST(test_identify_identical_when_found);
  RUN_TEST(test_identify_identical_when_not_found);
  RUN_TEST(test_identify_identical_four_cases);

  return UnityEnd();
}
