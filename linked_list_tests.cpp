//
// Created by adjsky on 3/5/21.
//

#include <vector>

#include "catch.hpp"
#include "linked_list.hpp"

TEST_CASE("Iteration over list") {
    std::initializer_list<int> init_list{ 4, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> array{ init_list };
    LinkedList<int> list{ init_list };

    SECTION("Iteration over list initialized with initializer list") {
        int c = 0;
        for (int val : list) {
            REQUIRE(val == array[c]);
            c++;
        }
    }

    SECTION("Iteration over moved list") {
        auto moved_list{ std::move(list) };
        int c = 0;
        for (int val : moved_list) {
            REQUIRE(val == array[c]);
            c++;
        }
    }

    SECTION("Iteration over list moved by assignment") {
        auto moved_list = std::move(list);
        int c = 0;
        for (int val : moved_list) {
            REQUIRE(val == array[c]);
            c++;
        }
    }

    SECTION("Iteration over copied list") {
        auto copyList{ list };
        int c = 0;
        for (int val : copyList) {
            REQUIRE(val == array[c]);
            c++;
        }
    }

    SECTION("Iteration over list copied by assignment") {
        auto copyList = list;
        int c = 0;
        for (int val : copyList) {
            REQUIRE(val == array[c]);
            c++;
        }
    }
}

TEST_CASE("Move operations") {
    LinkedList<int> list{ 1, 2, 3, 4, 5 };
    LinkedList<int>::size_type size{ list.size() };

    SECTION("Construct") {
        auto movedList{ std::move(list) };
        REQUIRE(list.size() == 0);
        REQUIRE_FALSE(list.begin() != LinkedListIterator<int>(nullptr));
        REQUIRE(movedList.size() == size);
    }

    SECTION("Assign") {
        auto movedList = std::move(list);
        REQUIRE(list.size() == 0);
        REQUIRE_FALSE(list.begin() != LinkedListIterator<int>(nullptr));
        REQUIRE(movedList.size() == size);
    }
}

TEST_CASE("Copy operations") {
    LinkedList<int> list{ 1, 2, 3, 4 };

    SECTION("Construct") {
        auto copyList{ list };
        REQUIRE(copyList.size() == list.size());
    }

    SECTION("Assign") {
        auto copyList = list ;
        REQUIRE(copyList.size() == list.size());
    }

    SECTION("Assign to filled list") {
        LinkedList<int> list2{ 1, 2 };
        list = list2;
        REQUIRE(list.size() == list2.size());
    }
}

TEST_CASE("Appending and prepending") {
    LinkedList<int> list{};

    SECTION("Append") {
        for (int i = 5; i < 8; i++) {
            list.append(i);
            REQUIRE(list.back() == i);
        }
    }

    SECTION("Prepend") {
        for (int i = 5; i < 8; i++) {
            list.prepend(i);
            REQUIRE(list.front() == i);
        }
    }
}

TEST_CASE("Clearing") {
    LinkedList<int> list{ 1, 2, 3, 4, 5 };
    list.clear();
    REQUIRE(list.size() == 0);
}

TEST_CASE("Popping") {
    LinkedList<int> list{ 4, 2, 8 };
    REQUIRE(list.front() == 4);
    list.pop_front();
    REQUIRE(list.front() == 2);
    REQUIRE(list.size() == 2);
    list.pop_front();
    REQUIRE(list.front() == 8);
    REQUIRE(list.size() == 1);
}
