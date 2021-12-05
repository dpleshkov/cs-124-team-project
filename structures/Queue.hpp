#ifndef CS124_TEAM_PROJECT_QUEUE_H
#define CS124_TEAM_PROJECT_QUEUE_H

template <typename QueueNodeType>
class QueueNode {
public:
    explicit StackNode(QueueNodeType value) {
        this -> value = value;
    };
    QueueNode<QueueNodeType>* next = nullptr;
    QueueNodeType value;
};

template<typename QueueType>
class Queue {
public:
    /**
     * @return the element at the front of the queue
     */
    QueueType peek() {
        return head -> value;
    };

    /**
     * Advances the queue
     */
    void dequeue() {
        if (head == nullptr) return;
        Node<QueueType>* removed = head;
        if (tail == removed) {
            tail = nullptr;
        }
        head = head -> next;
        delete removed;
    };

    /**
     * Adds an item to the queue
     * @param item to add
     */
    void enqueue(QueueType item) {
        auto* newNode = new QueueNode<QueueType>(item);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail -> next = newNode;
            tail = tail -> next;
        }
    };

    /**
     * @return true if queue is empty
     */
    bool isEmpty() {
        return head == nullptr;
    }

    ~Queue() {
        while (head != nullptr) {
            auto* deleted = head;
            head = head -> next;
            delete deleted;
        }
    }
private:
    QueueNode<QueueType>* head = nullptr;
    QueueNode<QueueType>* tail = nullptr;
};


#endif