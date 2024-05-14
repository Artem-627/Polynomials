//
// Created by artem627 on 4/30/24.
//
#pragma once

#include <cstdint>
#include <stdexcept>

template<typename T>
class List {
public:
    struct Node {
        T *data;
        Node *prev = nullptr;
        Node *next = nullptr;

        explicit Node(T const &data_) {
            data = new T(data_);
            prev = nullptr;
            next = nullptr;
        }
    };

    List() {
        head = nullptr;
        tail = nullptr;
    };

    explicit List(T const &other) {
        head = nullptr;
        tail = nullptr;
        for (auto curr_node = other.head; curr_node != nullptr; curr_node = curr_node->next) {
            pushBack(*curr_node->data);
        }
    }

    List(std::vector<T> const &src_vector) {
        head = nullptr;
        tail = nullptr;
        for (auto curr_node : src_vector) {
            pushBack(curr_node);
        }
    }

    explicit List(T &&other) {
        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
    }

    ~List() {
        auto curr_node = head;
        while (curr_node != nullptr) {
            delete curr_node->data;
            delete curr_node;
            curr_node = curr_node->next;
        }
    }


    void pushFront(T const &data) {
        if (head == nullptr && head == nullptr) {
            head = new Node(data);
            tail = head;
        } else {
            Node *new_node = new Node(data);
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    void pushBack(T const &data) {
        if (head == nullptr && head == nullptr) {
            head = new Node(data);
            tail = head;
        } else {
            Node *new_node = new Node(data);
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
    }

    void popFront() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        if (head == tail) {
            delete head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            auto new_head = head->next;
            delete head->data;
            delete head;
            head = new_head;
            head->prev = nullptr;
        }
    }

    void popBack() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        if (head == tail) {
            delete head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            auto new_tail = tail->prev;
            delete tail->data;
            delete tail;
            tail = new_tail;
            tail->next = nullptr;
        }
    }


    [[nodiscard]]
    std::uint32_t getSize() const {
        std::uint32_t size = 0;
        auto curr_node = head;
        while (curr_node != nullptr) {
            ++size;
            curr_node = curr_node->next;
        }
        return size;
    }

    void remove(std::uint32_t const &index) {
        if (this->head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node* curr_node = this->head;
        for (int i = 0; i < index; ++i) {
            if (curr_node->next == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            curr_node = curr_node->next;
        }
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            if (curr_node->next != nullptr) {
                curr_node->next->prev = curr_node->prev;
                if (curr_node == head) {
                    head = curr_node->next;
                }
            }
            if (curr_node->prev != nullptr) {
                curr_node->prev->next = curr_node->next;
                if (curr_node == tail) {
                    tail = curr_node->prev;
                }
            }
        }

        delete curr_node->data;
        delete curr_node;
    }


    void sort() {
        if (head == nullptr) {
            return;
        }
        partition();
    }

    T &operator[](std::uint32_t const &index) {
        if (this->head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        auto curr_node = this->head;
        for (int i = 0; i < index; ++i) {
            if (curr_node->next == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            curr_node = curr_node->next;
        }
        return *curr_node->data;
    }

    bool operator==(List<T> const &other) const {
        if (getSize() != other.getSize()) {
            return 0;
        }
        auto this_iter = head;
        auto other_iter = other.head;
        while (this_iter != nullptr && other_iter != nullptr) {
            if (*this_iter->data != *other_iter->data) {
                return 0;
            }
            this_iter = this_iter->next;
            other_iter = other_iter->next;
        }

        return 1;
    }

private:
    Node *head = nullptr;
    Node *tail = nullptr;

    void partition() {
        List<T> less;
        List<T> equal;
        List<T> more;

        T pivot = *head->data;

        Node* curr_node = head;

        while (curr_node != nullptr) {
            if (*curr_node->data < pivot) {
                less.pushBack(*curr_node->data);
            } else if (*curr_node->data > pivot) {
                more.pushBack(*curr_node->data);
            } else {
                equal.pushBack(*curr_node->data);
            }
            curr_node = curr_node->next;
        }

        if (less.getSize() != 0) {
            less.sort();
        }
        if (more.getSize() != 0) {
            more.sort();
        }

        less.join(equal);
        if (more.getSize() != 0) {
            less.join(more);
        }

        head = less.head;
        tail = less.tail;

        less.head = nullptr;
        less.tail = nullptr;
    }

    void join(List<T> &other) {
        if (head == nullptr) {
            head = other.head;
            tail = other.tail;
        } else {
            tail->next = other.head;
            other.head->prev = tail;
            tail = other.tail;
        }

        other.head = nullptr;
        other.tail = nullptr;
    }
};

