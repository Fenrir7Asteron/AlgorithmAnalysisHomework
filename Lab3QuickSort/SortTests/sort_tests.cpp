#include <string>
#include "gtest/gtest.h"
#include "sort.h"
#include "../../Lab2DynamicArray/Array.h"

TEST(SortTestCase, SortRandomIntArray) {
    const int TEST_SIZE = 100;
    const int MAX_VALUE = 40;
    const int RANDOM_SEED = 12345;
    srand(RANDOM_SEED);

    int tested_array[TEST_SIZE], ground_truth_array[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; ++i) {
        int random_value = rand() % MAX_VALUE;
        tested_array[i] = random_value;
        ground_truth_array[i] = random_value;
    }

    bool (*comp)(const int &, const int &) = [](const int &a, const int &b) { return a < b; };
    sort(tested_array, tested_array + TEST_SIZE, comp);

    // Compare to ground truth std::sort.
    std::sort(ground_truth_array, ground_truth_array + TEST_SIZE, comp);

    for (int i = 0; i < TEST_SIZE; ++i) {
        ASSERT_EQ(tested_array[i], ground_truth_array[i]);
    }
}

TEST(SortTestCase, SortRandomIntArray2) {
    const int TEST_SIZE = 100;
    const int MAX_VALUE = 40;
    const int RANDOM_SEED = 12345;
    srand(RANDOM_SEED);

    int tested_array[TEST_SIZE], ground_truth_array[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; ++i) {
        int random_value = rand() % MAX_VALUE;
        tested_array[i] = random_value;
        ground_truth_array[i] = random_value;
    }

    bool (*comp)(const int &, const int &) = [](const int &a, const int &b) { return a <= b; };
    sort(tested_array, tested_array + TEST_SIZE, comp);

    // Compare to ground truth std::sort.
    std::sort(ground_truth_array, ground_truth_array + TEST_SIZE, comp);

    for (int i = 0; i < TEST_SIZE; ++i) {
        ASSERT_EQ(tested_array[i], ground_truth_array[i]);
    }
}

TEST(SortTestCase, SortAlreadySortedIntArray) {
    const int TEST_SIZE = 10000;

    int tested_array[TEST_SIZE], ground_truth_array[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; ++i) {
        int value = i + 1;
        tested_array[i] = value;
        ground_truth_array[i] = value;
    }

    bool (*comp)(const int &, const int &) = [](const int &a, const int &b) { return a < b; };
    sort(tested_array, tested_array + TEST_SIZE, comp);

    // Compare to ground truth std::sort.
    std::sort(ground_truth_array, ground_truth_array + TEST_SIZE, comp);

    for (int i = 0; i < TEST_SIZE; ++i) {
        ASSERT_EQ(tested_array[i], ground_truth_array[i]);
    }
}

TEST(SortTestCase, SortReverseSortedIntArray) {
    const int TEST_SIZE = 10000;

    int tested_array[TEST_SIZE], ground_truth_array[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; ++i) {
        int value = i + 1;
        tested_array[i] = value;
        ground_truth_array[i] = value;
    }

    bool (*comp)(const int &, const int &) = [](const int &a, const int &b) { return a > b; };
    sort(tested_array, tested_array + TEST_SIZE, comp);

    // Compare to ground truth std::sort.
    std::sort(ground_truth_array, ground_truth_array + TEST_SIZE, comp);

    for (int i = 0; i < TEST_SIZE; ++i) {
        ASSERT_EQ(tested_array[i], ground_truth_array[i]);
    }
}

TEST(SortTestCase, SortStringArray) {
    const int TEST_SIZE = 6;

    std::string tested_array[TEST_SIZE] = {"otpiowe", "abacaba", "babaca", "gfsdf", "babaca", "kek"};
    std::string ground_truth_array[TEST_SIZE] = {"otpiowe", "abacaba", "babaca", "gfsdf", "babaca", "kek"};

    bool (*comp)(const std::string &, const std::string &) = [](const std::string &a, const std::string &b) { return a < b; };
    sort(tested_array, tested_array + TEST_SIZE, comp);

    // Compare to ground truth std::sort.
    std::sort(ground_truth_array, ground_truth_array + TEST_SIZE, comp);

    for (int i = 0; i < TEST_SIZE; ++i) {
        ASSERT_STREQ(tested_array[i].c_str(), ground_truth_array[i].c_str());
    }
}

TEST(SortTestCase, SortVectorOfStrings) {
    std::vector<std::string> tested_array = {"otpiowe", "abacaba", "babaca", "gfsdf", "babaca", "kek"};
    std::vector<std::string> ground_truth_array = {"otpiowe", "abacaba", "babaca", "gfsdf", "babaca", "kek"};

    bool (*comp)(const std::string &, const std::string &) = [](const std::string &a, const std::string &b) { return a > b; };
    sort(tested_array.begin(), tested_array.end(), comp);

    // Compare to ground truth std::sort.
    std::sort(ground_truth_array.begin(), ground_truth_array.end(), comp);

    for (int i = 0; i < tested_array.size(); ++i) {
        ASSERT_STREQ(tested_array[i].c_str(), ground_truth_array[i].c_str());
    }
}