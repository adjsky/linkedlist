//
// Created by adjsky on 3/5/21.
//

#ifndef LINKED_LIST_LINKED_LIST_HPP
#define LINKED_LIST_LINKED_LIST_HPP

#include <cstddef>
#include <initializer_list>

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
class ConstLinkedListIterator {
public:
    explicit ConstLinkedListIterator(Node<T>* node) noexcept : ptr_{ node } {}
    const T& operator*() const noexcept {
        return ptr_->data;
    }
    bool operator!=(const ConstLinkedListIterator<T>& another) const { return ptr_ != another.ptr_; }
    ConstLinkedListIterator& operator++() {
        if (this->ptr_ != nullptr)
            this->ptr_ = this->ptr_->next;
        return *this;
    }
    const T* operator->() const noexcept {
        return &ptr_->data;
    }

protected:
    Node<T>* ptr_;
};

template<typename T>
class LinkedListIterator : public ConstLinkedListIterator<T> {
public:
    explicit LinkedListIterator(Node<T>* node) noexcept : ConstLinkedListIterator<T>{ node } {}
    T& operator*() noexcept {
        return this->ptr_->data;
    }
    T* operator->() noexcept {
        return &this->ptr_->data;
    }
};

template <typename T>
class LinkedList {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = LinkedListIterator<T>;
    using const_iterator = ConstLinkedListIterator<T>;
    using size_type = std::size_t;
public:
    LinkedList() noexcept;
    LinkedList(std::initializer_list<T> list);
    ~LinkedList();

    LinkedList(const LinkedList& another);
    LinkedList& operator=(const LinkedList& another);

    LinkedList(LinkedList&& another) noexcept;
    LinkedList& operator=(LinkedList&& another) noexcept;

    void append(T value);
    void prepend(T value);
    void pop_front();
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    size_type size();
    void clear() noexcept;;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

private:
    Node<T>* head_;
    Node<T>* tail_;
    size_type size_;
};

#include "linked_list.inl"

#endif //LINKED_LIST_LINKED_LIST_HPP
