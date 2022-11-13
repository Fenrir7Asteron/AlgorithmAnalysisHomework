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

//TEST(DynamicArrayTestCase, ArrayIntRemoveCheck) {
//    Array<int> array = Array<int>();
//    array.insert(3);
//    ASSERT_EQ(array.size(), 1);
//    ASSERT_EQ(array[0], 3);
//
//    array.remove(0);
//    ASSERT_EQ(array.size(), 0);
//
//    array.insert(3);
//    array.insert(7);
//    array.insert(9);
//    ASSERT_EQ(array.size(), 3);
//
//    array.remove(1);
//    ASSERT_EQ(array.size(), 2);
//    ASSERT_EQ(array[0], 3);
//    ASSERT_EQ(array[1], 9);
//
//    array.remove(0);
//    ASSERT_EQ(array.size(), 1);
//    ASSERT_EQ(array[0], 9);
//}

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

    array->~Array();

    ASSERT_EQ(array->size(), 0);
}