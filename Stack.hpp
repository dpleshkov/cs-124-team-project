#ifndef CS124_LAB3_STACK_HPP
#define CS124_LAB3_STACK_HPP

#include "Node.hpp"

template <typename StackNodeType>
class StackNode {
public:
    explicit StackNode(StackNodeType value) {
        this -> value = value;
    };
    StackNode<StackNodeType>* next = nullptr;
    StackNodeType value;
};

template<typename StackType>
class Stack {
public:
    /**
     * @return top element of the stack
     */
    StackType peek() {
        return head -> value;
    };

    /**
     * Removes top element of the stack
     */
    void pop() {
        auto* removed = head;
        head = head -> next;
        delete removed;
    };

    /**
     * Adds an element on top of the stack
     * @param item to be added
     */
    void push(StackType item) {
        auto* newNode = new StackNode<StackType>(item);
        if (head == nullptr) {
            head = newNode;
        } else {
            newNode -> next = head;
            head = newNode;
        }
    };

    /**
     * @return true if stack is empty
     */
    bool isEmpty() {
        return head == nullptr;
    }

    ~Stack() {
        while (head != nullptr) {
            auto* deleted = head;
            head = head -> next;
            delete deleted;
        }
    }
private:
    StackNode<StackType>* head = nullptr;
};

#endif