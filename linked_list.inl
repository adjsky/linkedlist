template <typename T>
LinkedList<T>::LinkedList() noexcept :
    head_{ nullptr },
    tail_{ nullptr },
    size_{ 0 }
{
}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> list) :
    head_{ nullptr },
    tail_{ nullptr },
    size_{ 0 }
{
    for (T value : list) {
        append(value);
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& another) :
    head_{ nullptr },
    tail_{ nullptr },
    size_{ 0 } // will be increased in append
{
    for (T value : another) {
        append(value);
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& another) {
    if (this != &another) {
        clear(); // clear data to prevent leaking
        for (T value : another) {
            append(value);
        }
    }
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& another) noexcept :
    head_{ another.head_ },
    tail_{ another.tail_ },
    size_{ another.size_ }
{
    another.head_ = nullptr;
    another.tail_ = nullptr;
    another.size_ = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& another) noexcept {
    if (this != &another) {
        head_ = another.head_;
        tail_ = another.tail_;
        size_ = another.size_;
        another.head_ = nullptr;
        another.tail_ = nullptr;
        another.size_ = 0;
    }
    return *this;
}

template <typename T>
void LinkedList<T>::append(T value) {
    auto node = new Node<T>{ value, nullptr };
    if (head_) {
        if (size_ == 1) {
            tail_ = node;
            head_->next = tail_;
        } else {
            tail_->next = node;
            tail_ = node;
        }
    } else {
        head_ = tail_ = node;
    }
    ++size_;
}

template <typename T>
void LinkedList<T>::prepend(T value) {
    auto node = new Node<T>{ value, nullptr };
    if (head_) {
        if (size_ == 1) {
            head_ = node;
            head_->next = tail_;
        } else {
            node->next = head_;
            head_ = node;
        }
    } else {
        head_ = tail_ = node;
    }
    ++size_;
}

template <typename T>
void LinkedList<T>::pop_front() {
    auto next{ head_->next };
    delete head_;
    head_ = next;
    --size_;
}

template <typename T>
typename LinkedList<T>::reference LinkedList<T>::front() {
    return head_->data;
}

template <typename T>
typename LinkedList<T>::const_reference LinkedList<T>::front() const {
    return head_->data;
}

template<typename T>
typename LinkedList<T>::reference LinkedList<T>::back() {
    return tail_->data;
}

template<typename T>
typename LinkedList<T>::const_reference LinkedList<T>::back() const {
    return tail_->data;
}

template <typename T>
typename LinkedList<T>::size_type LinkedList<T>::size() {
    return size_;
}

template<typename T>
void LinkedList<T>::clear() noexcept {
    if (auto current = head_; current != nullptr) {
        auto next = current->next;
        while (current) {
            delete current;
            current = next;
            if (next)
                next = next->next;
        }
    }
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() noexcept {
    return LinkedListIterator<T>(head_);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::begin() const noexcept {
    return LinkedListIterator<T>(head_);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() noexcept {
    return LinkedListIterator<T>(nullptr);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::end() const noexcept {
    return LinkedListIterator<T>(nullptr);
}
