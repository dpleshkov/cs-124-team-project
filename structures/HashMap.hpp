#ifndef CS_124_TEAM_PROJECT_HASHMAP_HPP
#define CS_124_TEAM_PROJECT_HASHMAP_HPP

#include <vector>
#include <iostream>

template <typename PairKey, typename PairValue>
struct HashMapNode {
    PairKey key;
    PairValue value;
    HashMapNode<PairKey, PairValue> *next = nullptr;
};

template <typename HashMapKey, typename HashMapValue>
class HashMap {
public:
    /**
     * Constructor for the HashMap class. Accepts a pointer to a
     * hash function and a size for the hash table.
     * @param hashFunction
     * @param capacity
     */
    HashMap(int (*hashFunction)(HashMapKey), int capacity) {
        this -> hashFunction = hashFunction;
        this -> capacity = capacity;
        this -> size = 0;
        for (int i = 0; i < capacity; i++) {
            this -> table.push_back(nullptr);
        }
    }

    /**
     * Returns true if the hash map contains the given key.
     * @param key
     * @return true/false
     */
    bool exists(HashMapKey key) {
        int index = hashFunction(key) % capacity;
        auto current = table[index];
        while (current != nullptr) {
            if (current -> key == key) {
                return true;
            }
            current = current -> next;
        }
        return false;
    }

    /**
     * Returns the value associated with the given key, defaulting to
     * the default value of the value class if the key is not found.
     * @param key
     * @return
     */
    HashMapValue get(HashMapKey key) {
        int index = hashFunction(key) % capacity;
        auto current = table[index];
        while (current != nullptr) {
            if (current -> key == key) {
                return current -> value;
            }
            current = current -> next;
        }
        return HashMapValue();
    }

    /**
     * Sets a key-value pair in the hash map. If the key already exists, it overwrites the value.
     * @param key
     * @param value
     */
    void set(HashMapKey key, HashMapValue value) {
        int index = hashFunction(key) % capacity;
        auto current = table[index];
        table[index] = new HashMapNode<HashMapKey, HashMapValue>{key, value, current};
    }

    /**
     * Removes the key-value pair with the given key.
     * @param key
     */
    void remove(HashMapKey key) {
        int index = hashFunction(key) % capacity;
        auto current = table[index];
        HashMapNode<HashMapKey, HashMapValue>* last = nullptr;
        while (current != nullptr) {
            if (current -> key == key) {
                if (last != nullptr) {
                    last -> next = current -> next;
                    delete current;
                    return;
                } else {
                    table[index] = current -> next;
                }
            }
            last = current;
            current = current -> next;
        }
    }

    std::vector<HashMapKey> getKeys() {
        std::vector<HashMapKey> output;
        for (auto i : table) {
            auto current = i;
            while (current != nullptr) {
                output.push_back(current -> key);
                current = current -> next;
            }
        }
        return output;
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            while (table[i] != nullptr) {
                auto deleted = table[i];
                table[i] = table[i] -> next;
                delete deleted;
            }
        }
    }
private:
    int (*hashFunction)(HashMapKey);
    int capacity = 0;
    int size = 0;
    std::vector<HashMapNode<HashMapKey, HashMapValue>*> table;
};


#endif