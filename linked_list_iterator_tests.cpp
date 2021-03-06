//
// Created by adjsky on 3/5/21.
//

#include "catch.hpp"
#include "linked_list.hpp"

TEST_CASE("Linked list iterator") {
    SECTION("Nullptr iterators are the same") {
        LinkedListIterator<float> it{ nullptr };
        LinkedListIterator<float> it2{ nullptr };
        REQUIRE_FALSE(it != it2);
    }

    SECTION("Node data and data from iterator are the same") {
        auto node{ new Node<float>{ 5.0f, nullptr } };
        LinkedListIterator<float> it{ node };
        REQUIRE(node->data == *it);
    }

    SECTION("Two iterators constructed from the same node are the same") {
        auto node{ new Node<float>{ 5.0f, nullptr } };
        LinkedListIterator<float> it1{ node };
        LinkedListIterator<float> it2{ node };
        REQUIRE_FALSE(it1 != it2);
    }

    SECTION("Can modify value with non-const iterator") {
        auto node{ new Node<int>{ 5, nullptr } };
        LinkedListIterator<int> it{ node };
        *it = 4;
        REQUIRE(node->data == 4);
    }
}
