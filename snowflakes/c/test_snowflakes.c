#include "../../lib/test-framework/unity.h"
#include "libsnowflakes.h"

void setUp(void) {}

void tearDown(void) {}

static void test_canary(void) { TEST_PASS(); }

static void test_identical_right_true(void) {
  int snow1[] = {1, 2, 3, 4, 5, 6};
  int snow2[] = {4, 5, 6, 1, 2, 3};
  int start = 3;
  TEST_ASSERT_TRUE(identical_right(snow1, snow2, start));
}

static void test_swap_elem(void) {
  int values[] = {1, 2};
  swap_elem(values, 0, 1);
  int expected[] = {2, 1};
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, values, 2);
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

int main(void) {
  UnityBegin("test_snowflakes.c");
  RUN_TEST(test_canary);
  RUN_TEST(test_identical_right_true);
  RUN_TEST(test_swap_elem);
  RUN_TEST(test_identical_left);
  RUN_TEST(test_identical_left_again);
  RUN_TEST(test_are_identical_false);
  RUN_TEST(test_are_identical_true_identity);

  return UnityEnd();
}
