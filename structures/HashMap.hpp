#ifndef CS_124_TEAM_PROJECT_HASHMAP_HPP
#define CS_124_TEAM_PROJECT_HASHMAP_HPP

#include <vector>
#include <iostream>

template <typename PairKey, typename PairValue>
struct HashMapNode {
    PairKey key;
    PairValue value;
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
        int count = 0;
        int index = hashFunction(key) % capacity;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                return true;
            }
            index = (index + 1) % capacity;
            count++;
            if (count > capacity) {
                return false;
            }
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
        int count = 0;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                return table[index] -> value;
            }
            index = (index + 1) % capacity;
            count++;
            if (count > capacity) {
                break;
            }
        }
        return HashMapValue();
    }

    /**
     * Sets a key-value pair in the hash map. If the key already exists, it overwrites the value.
     * @param key
     * @param value
     */
    void set(HashMapKey key, HashMapValue value) {
        int count = 0;
        int index = hashFunction(key) % capacity;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                table[index] -> value = value;
                return;
            }
            index = (index + 1) % capacity;
            count++;
            if (count > capacity) {
                break;
            }
        }
        table[index] = new HashMapNode<HashMapKey, HashMapValue>{key, value};
        size++;
    }

    /**
     * Removes the key-value pair with the given key.
     * @param key
     */
    void remove(HashMapKey key) {
        int count = 0;
        int index = hashFunction(key) % capacity;
        while (table[index] != nullptr) {
            if (table[index] -> key == key) {
                delete table[index];
                table[index] = nullptr;
                size--;
                return;
            }
            index = (index + 1) % capacity;
            count++;
            if (count > capacity) {
                return;
            }
        }
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == nullptr) continue;
            delete table[i];
            table[i] = nullptr;
        }
    }
private:
    int (*hashFunction)(HashMapKey);
    int capacity = 0;
    int size = 0;
    std::vector<HashMapNode<HashMapKey, HashMapValue>*> table;
};


#endif