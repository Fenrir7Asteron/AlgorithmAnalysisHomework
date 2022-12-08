#include <string>
#include "gtest/gtest.h"
#include "Array.h"

using namespace std;

TEST(DynamicArrayTestCase, ArrayIntSanityCheck) {
    Array<int> array = Array<int>();
    array.insert(3);
    ASSERT_EQ(array.size(), 1);
    ASSERT_EQ(array[0], 3);
}

TEST(DynamicArrayTestCase, ArrayIntInsertWithIndexCheck) {
    Array<int> array = Array<int>();

    array.insert(0, 3);
    ASSERT_EQ(array.size(), 1);
    ASSERT_EQ(array[0], 3);

    array.insert(0, 5);
    ASSERT_EQ(array.size(), 2);
    ASSERT_EQ(array[0], 5);
    ASSERT_EQ(array[1], 3);

    array.insert(2, 10);
    ASSERT_EQ(array.size(), 3);
    ASSERT_EQ(array[0], 5);
    ASSERT_EQ(array[1], 3);
    ASSERT_EQ(array[2], 10);

    array.insert(1, 20);
    ASSERT_EQ(array.size(), 4);
    ASSERT_EQ(array[0], 5);
    ASSERT_EQ(array[1], 20);
    ASSERT_EQ(array[2], 3);
    ASSERT_EQ(array[3], 10);
}

TEST(DynamicArrayTestCase, ArrayIntRemoveCheck) {
    Array<int> array = Array<int>();
    array.insert(3);
    ASSERT_EQ(array.size(), 1);
    ASSERT_EQ(array[0], 3);

    array.remove(0);
    ASSERT_EQ(array.size(), 0);

    array.insert(3);
    array.insert(7);
    array.insert(9);
    ASSERT_EQ(array.size(), 3);

    array.remove(1);
    ASSERT_EQ(array.size(), 2);
    ASSERT_EQ(array[0], 3);
    ASSERT_EQ(array[1], 9);

    array.remove(0);
    ASSERT_EQ(array.size(), 1);
    ASSERT_EQ(array[0], 9);
}

TEST(DynamicArrayTestCase, ArrayStringSanityCheck) {
    Array<string> array = Array<string>();
    array.insert("test");
    ASSERT_EQ(array.size(), 1);
    ASSERT_STREQ(array[0].c_str(), "test");
}

TEST(DynamicArrayTestCase, ArrayStringInsertWithIndexCheck) {
    Array<string> array = Array<string>();

    array.insert(0, "abc");
    ASSERT_EQ(array.size(), 1);
    ASSERT_STREQ(array[0].c_str(), "abc");

    array.insert(0, "qwe");
    ASSERT_EQ(array.size(), 2);
    ASSERT_STREQ(array[0].c_str(), "qwe");
    ASSERT_STREQ(array[1].c_str(), "abc");

    array.insert(2, "kweh");
    ASSERT_EQ(array.size(), 3);
    ASSERT_STREQ(array[0].c_str(), "qwe");
    ASSERT_STREQ(array[1].c_str(), "abc");
    ASSERT_STREQ(array[2].c_str(), "kweh");

    array.insert(1, "kupo");
    ASSERT_EQ(array.size(), 4);
    ASSERT_STREQ(array[0].c_str(), "qwe");
    ASSERT_STREQ(array[1].c_str(), "kupo");
    ASSERT_STREQ(array[2].c_str(), "abc");
    ASSERT_STREQ(array[3].c_str(), "kweh");
}

TEST(DynamicArrayTestCase, ArrayStringRemoveCheck) {
    Array<string> array = Array<string>();
    array.insert("abc");
    array.insert("bfd");
    ASSERT_EQ(array.size(), 2);
    ASSERT_STREQ(array[0].c_str(), "abc");
    ASSERT_STREQ(array[1].c_str(), "bfd");

    array.remove(0);
    ASSERT_EQ(array.size(), 1);
    ASSERT_STREQ(array[0].c_str(), "bfd");

    array.remove(0);
    ASSERT_EQ(array.size(), 0);
}

TEST(DynamicArrayTestCase, ArrayDestructor) {
    auto* array = new Array<string>();
    array->insert("abc");
    array->insert("bfd");
    ASSERT_EQ(array->size(), 2);

    delete array;
}

TEST(DynamicArrayTestCase, ArrayForRange) {
    Array<float> array;
    int size = 4;
    float src[size], dst[size];
    src[0] = 5;
    src[1] = 5.3f;
    src[2] = 10.1f;
    src[3] = 2.0f;
    
    for (int i = 0; i < size; ++i) {
        array.insert(src[i]);
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(src[i], array[i]);
    }

    int j = 0;
    for (auto el : array) {
        dst[j] = el;
        ++j;
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(src[i], dst[i]);
    }
}

TEST(DynamicArrayTestCase, ArrayIterator) {
    Array<double> array;
    int size = 4;
    double src[size], dst[size];
    src[0] = 5;
    src[1] = 5.3f;
    src[2] = 10.1f;
    src[3] = 2.0f;

    for (int i = 0; i < size; ++i) {
        array.insert(src[i]);
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(src[i], array[i]);
    }

    int j = 0;
    for (auto it = array.iterator(), end = array.end(); it.hasNext(); ++it) {
        dst[j] = it.get();
        ++j;
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(src[i], dst[i]);
    }
}

TEST(DynamicArrayTestCase, ArrayIteratorSet) {
    Array<double> array;
    int size = 4;
    double src[size];
    src[0] = 5;
    src[1] = 5.3f;
    src[2] = 10.1f;
    src[3] = 2.0f;

    for (int i = 0; i < size; ++i) {
        array.insert(src[i]);
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(src[i], array[i]);
    }

    for (auto it = array.iterator(), end = array.end(); it.hasNext(); ++it) {
        it.set(2.0f);
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(array[i], 2.0f);
    }
}

TEST(DynamicArrayTestCase, ArrayReverseIterator) {
    Array<double> array;
    int size = 4;
    double src[size], dst[size];
    src[0] = 5;
    src[1] = 5.3f;
    src[2] = 10.1f;
    src[3] = 2.0f;

    for (int i = 0; i < size; ++i) {
        array.insert(src[i]);
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(src[i], array[i]);
    }

    int j = 0;
    for (auto it = array.reverseIteratorBegin(), end = array.reverseIteratorEnd(); it < end; ++it) {
        dst[j] = *it;
        ++j;
    }

    for (int i = 0; i < size; ++i) {
        ASSERT_FLOAT_EQ(src[i], dst[size - i - 1]);
    }
}