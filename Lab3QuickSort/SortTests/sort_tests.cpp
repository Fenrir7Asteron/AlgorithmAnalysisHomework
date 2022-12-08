#include <string>
#include "gtest/gtest.h"
#include "sort.h"

TEST(SortTestCase, SortIntArray) {
    const int TEST_SIZE = 100;
    const int MAX_VALUE = 40;

    int tested_array[TEST_SIZE], ground_truth_array[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; ++i) {
        int random_value = rand() % MAX_VALUE;
        tested_array[i] = random_value;
        ground_truth_array[i] = random_value;
    }

    bool (*comp)(const int &, const int &) = [](const int &a, const int &b) { return a < b; };
    sort(tested_array, tested_array + TEST_SIZE, comp);
    std::sort(ground_truth_array, ground_truth_array + TEST_SIZE, comp);

    for (int i = 0; i < TEST_SIZE; ++i) {
        ASSERT_EQ(tested_array[i], ground_truth_array[i]);
    }
}