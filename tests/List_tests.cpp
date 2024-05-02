#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>

#include "../source/List/List.h"

TEST(ListBrackets, ListPushBackEmpty) {
    List<int> list;

    ASSERT_THROW(list[0], std::out_of_range);
}

TEST(ListBrackets, ListPushBackCheckOutOfRange) {
    List<int> list;

    list.pushBack(10);

    ASSERT_THROW(list[1], std::out_of_range);
}


TEST(ListPushBack, ListPushBackSize) {
    List<int> list;

    for (int i = 0; i < 10; ++i) {
        list.pushBack(52);
        ASSERT_EQ(list.getSize(), i + 1);
    }
}

TEST(ListPushBack, ListPushBackOneElement) {
    List<int> list;

    list.pushBack(10);

    ASSERT_EQ(list[0], 10);
}

TEST(ListPushBack, ListPushBackManyElement) {
    std::vector<int> elements = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    List<int> list;

    for (auto el: elements) {
        list.pushBack(el);
    }

    for (int i = 0; i < elements.size(); ++i) {
        ASSERT_EQ(list[i], elements[i]);
    }
}


TEST(ListPushFront, ListPushFrontSize) {
    List<int> list;

    for (int i = 0; i < 10; ++i) {
        list.pushFront(52);
        ASSERT_EQ(list.getSize(), i + 1);
    }
}

TEST(ListPushFront, ListPushFrontOneElement) {
    List<int> list;

    list.pushFront(10);

    ASSERT_EQ(list[0], 10);
}

TEST(ListPushFront, ListPushFrontManyElement) {
    std::vector<int> elements = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    List<int> list;

    for (auto el: elements) {
        list.pushFront(el);
    }

    for (int i = 0; i < elements.size(); ++i) {
        ASSERT_EQ(list[i], elements[elements.size() - i - 1]);
    }
}


TEST(ListPopFront, PopFrontEmptyList) {
    List<int> list;
    ASSERT_THROW(list.popFront(), std::out_of_range);
}

TEST(ListPopFront, PopFrontOneElement) {
    List<int> list;
    list.pushFront(10);
    list.popFront();
    ASSERT_EQ(list.getSize(), 0);
}

TEST(ListPopFront, PopFrontMultipleElements) {
    List<int> list;
    for (int i = 0; i < 10; ++i) {
        list.pushFront(i);
    }
    for (int i = 0; i < 10; ++i) {
        list.popFront();
        ASSERT_EQ(list.getSize(), 9 - i);
    }
}

TEST(ListPopFront, PopFrontCheckValue) {
    List<int> list;
    for (int i = 0; i < 10; ++i) {
        list.pushFront(i);
    }
    for (int i = 0; i < 10; ++i) {
        list.popFront();
        if (!list.getSize()) continue;
        ASSERT_EQ(list[0], 8 - i);
    }
}


TEST(ListPopBack, PopBackEmptyList) {
    List<int> list;
    ASSERT_THROW(list.popBack(), std::out_of_range);
}

TEST(ListPopBack, PopBackOneElement) {
    List<int> list;
    list.pushBack(10);
    list.popBack();
    ASSERT_EQ(list.getSize(), 0);
}

TEST(ListPopBack, PopBackMultipleElements) {
    List<int> list;
    for (int i = 0; i < 10; ++i) {
        list.pushBack(i);
    }
    for (int i = 0; i < 10; ++i) {
        list.popBack();
        ASSERT_EQ(list.getSize(), 9 - i);
    }
}

TEST(ListPopBack, PopBackCheckValue) {
    List<int> list;
    for (int i = 0; i < 10; ++i) {
        list.pushBack(i);
    }
    for (int i = 0; i < 10; ++i) {
        list.popBack();
        if (!list.getSize()) continue;
        ASSERT_EQ(list[list.getSize() - 1], 8 - i);
    }
}


/// Tests for list sort
TEST(ListSort, ListSortEmpty) {
    List<int> list;
    list.sort();
    ASSERT_EQ(list.getSize(), 0);
}

TEST(ListSort, ListSortOneElement) {
    List<int> list;
    list.pushBack(10);
    list.sort();
    ASSERT_EQ(list[0], 10);
}

TEST(ListSort, ListSortTwoElements) {
    List<int> list;
    list.pushBack(10);
    list.pushBack(5);
    list.sort();
    ASSERT_EQ(list[0], 5);
    ASSERT_EQ(list[1], 10);
}

TEST(ListSort, ListSortMultipleElements) {
    List<int> list;
    list.pushBack(10);
    list.pushBack(5);
    list.pushBack(15);
    list.pushBack(0);
    list.pushBack(20);
    list.pushBack(25);
    list.pushBack(30);
    list.pushBack(35);
    list.pushBack(40);
    list.pushBack(45);
    list.sort();
    for (int i = 0; i < list.getSize() - 1; ++i) {
        ASSERT_LE(list[i], list[i + 1]);
    }
}

TEST(ListSort, ListSortMultipleRandomElements) {
    List<int> list;

    for (int i = 0; i < 100; ++i) {
        list.pushBack(rand());
    }

    list.sort();

    for (int i = 0; i < list.getSize() - 1; ++i) {
        ASSERT_LE(list[i], list[i + 1]);
    }
}

