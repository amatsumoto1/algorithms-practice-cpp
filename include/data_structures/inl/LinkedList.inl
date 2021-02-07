#include <exception>

namespace DataStructures {

template<typename T>
LinkedList<T>::LinkedList()
    : head_(nullptr),
      size_(0)
{}

template<typename T>
LinkedList<T>::~LinkedList() {
    while (head_ != nullptr) {
        Node* current = head_->next_;
        delete head_;
        head_ = current;
    }
}

template<typename T>
int LinkedList<T>::GetSize() const {
    return size_;
}

template<typename T>
T& LinkedList<T>::operator[] (int index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head_;
    for (int i = 0; i < index; i++) {
        current = current->next_;
    }

    return current->value_;
}

template<typename T>
void LinkedList<T>::AddFront(T value) {
    head_ = new Node(value, head_);
    size_++;
}

template<typename T>
void LinkedList<T>::Append(T value) {
    if (head_ == nullptr) {
        head_ = new Node(value);
    }
    else {
        Node* current = head_;
        while (current->next_ != nullptr) {
            current = current->next_;
        }
        current->next_ = new Node(value);
    }
    size_++;
}

template<typename T>
bool LinkedList<T>::Insert(T value, int index) {
    if (index > size_ + 1 || index < 0) {
        return false;
    }
    
    if (index == 0) {
        AddFront(value);
        return true;
    }

    Node* current = head_;
    for (int i = 0; i < index -1; i++) {
        current = current->next_;
    }
    current->next_ = new Node(value, current->next_);
    size_++;
    return true;
}

template<typename T>
bool LinkedList<T>::Contains(T value) const {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }

    return false;
}

template<typename T>
T LinkedList<T>::PopFront() {
    if (size_ == 0) {
        throw std::out_of_range("Cannot remove first item from empty list.");
    }

    Node* temp = head_;
    T retVal = head_->value_;
    head_ = head_->next_;
    size_--;
    delete temp;
    return retVal;
}

template<typename T>
bool LinkedList<T>::Remove(T value) {
    if (head_ != nullptr && head_->value_ == value) {
        Node* temp = head_;
        head_ = temp->next_;
        delete temp;
        size_--;
        return true;
    }

    Node* current = head_;
    while (current != nullptr && current->next_ != nullptr) {
        if (current->next_->value_ == value) {
            Node* temp = current->next_;
            current->next_ = temp->next_;
            delete temp;
            size_--;
            return true;
        }
        current = current->next_;
    }
    return false;
}

template<typename T>
bool LinkedList<T>::RemoveAt(int index) {
    if (index >= size_ || index < 0) {
        return false;
    }

    if (index == 0) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    else {
        Node* current = head_;
        for (int i = 0; i < index-1; i++) {
            current = current->next_;
        }
        Node* temp = current->next_;
        current->next_ = temp->next_;
        delete temp;
    }

    size_--;
    return true;
}

}