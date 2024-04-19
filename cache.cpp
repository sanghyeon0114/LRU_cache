#include "cache.h"
#include <sstream>

Cache::Cache() {
    linkedList = nullptr;
    size = 0;
}

Cache::~Cache()
{
    Node *cur = linkedList;
    Node *p;

    while(cur != nullptr) {
        p = cur;
        cur = cur->next;
        delete p;
    }

    linkedList = nullptr;
    size = 0;
}

void Cache::insertNode(std::string key, int value) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->type = INT;
    newNode->ivalue = value;
    size++;
    Cache::hashTable.addHashNode(newNode);
    if(linkedList == nullptr) {
        linkedList = newNode;
        newNode->pre = nullptr;
        newNode->next = nullptr;
        return;
    }
    linkedList->pre = newNode;
    newNode->pre = nullptr;
    newNode->next = linkedList;
    linkedList = newNode;
}

void Cache::insertNode(std::string key, double value) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->type = DOUBLE;
    newNode->dvalue = value;
    size++;
    Cache::hashTable.addHashNode(newNode);
    if(linkedList == nullptr) {
        linkedList = newNode;
        newNode->pre = nullptr;
        newNode->next = nullptr;
        return;
    }
    linkedList->pre = newNode;
    newNode->pre = nullptr;
    newNode->next = linkedList;
    linkedList = newNode;
}

void Cache::insertNode(Cache::Node* newNode) {
    size++;
    if(linkedList == nullptr) {
        linkedList = newNode;
        newNode->pre = nullptr;
        newNode->next = nullptr;
        return;
    }
    linkedList->pre = newNode;
    newNode->pre = nullptr;
    newNode->next = linkedList;
    linkedList = newNode;
}

Cache::Node* Cache::removeNode(std::string key) {
    Node* p = Cache::findNode(key);
    if(p == nullptr) {
        return nullptr;
    }
    size--;
    if(p->pre == nullptr) {
        if(p->next == nullptr) {
            linkedList = nullptr;
        } else {
            linkedList = p->next;
            linkedList->pre = nullptr;
        }
    } else {
        if(p->next == nullptr) {
            p->pre->next = nullptr;
        } else {
            p->pre->next = p->next;
            p->next->pre = p->pre;
        }
    }
    return p;
}

void Cache::removeTail() {
    if(linkedList == nullptr) {
        return;
    }
    Node* p;
    for(p = linkedList; p->next != nullptr; p = p->next);
    
    if(p->pre == nullptr) {
        linkedList = nullptr;
    } else {
        p->pre->next = nullptr;
    }
    Cache::hashTable.removeHashNode(p);
    delete p;
    size--;
}

Cache::Node* Cache::findNode(std::string key) {
    Cache::Node* p = hashTable.getHashNode(key);
    return p;
}

void Cache::add(std::string key, int value) {
    Cache::Node* p = Cache::removeNode(key);
    if(p == nullptr) {
        insertNode(key, value);
    } else {
        insertNode(p);
    }
    while(size > CACHE_SIZE) {
        Cache::removeTail();
    }
}

void Cache::add(std::string key, double value) {
    Cache::Node* p = Cache::removeNode(key);
    if(p == nullptr) {
        insertNode(key, value);
    } else {
        insertNode(p);
    }
    while(size > CACHE_SIZE) {
        Cache::removeTail();
    }
}

bool Cache::get(std::string key, int &value) {
    Node *p = Cache::findNode(key);
    if(p != nullptr && p->type == INT) {
        value = p->ivalue;
        return true;
    }
    return false;
}

bool Cache::get(std::string key, double &value) {
    Node *p = Cache::findNode(key);
    if(p != nullptr && p->type == DOUBLE) {
        value = p->dvalue;
        return true;
    }
    return false;
}

std::string Cache::toString() {
    std::string result;
    Node *p = linkedList;
    while(p != nullptr) {
        result.append("[");
        result.append(p->key);
        result.append(": ");
        if(p->type == INT) {
            result.append(std::to_string(p->ivalue));
        } else if(p->type == DOUBLE) {
            std::stringstream value;
            value << std::scientific << p->dvalue;
            result.append(value.str());
        }
        result.append("]");
        p = p->next;
        if(p != nullptr) {
            result.append(" -> ");
        }
    }
    result.append("\n");
    return result;
}

// Enhanced Start.
Cache::HashTable::HashTable() {
    for(int i = 0; i < HASH_SIZE; i++) {
        hashNode[i] = nullptr;
    }
}

Cache::HashTable::~HashTable() {
    for(int i = 0; i < HASH_SIZE; i++) {
        HashNode *hp = hashNode[i];
        while(hp != nullptr) {
            HashNode *cur = hp;
            hp = hp->next;
            delete cur;
        }
    }
}

int Cache::HashTable::hashFunction(std::string key) {
    int sum = 0;
    for(int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum % HASH_SIZE;
}

Cache::HashTable::HashNode* Cache::HashTable::newHashNode(Node* node) {
    HashNode* hp = new HashNode;
    hp->node = node;
    hp->next = nullptr;

    return hp;
}

Cache::Node* Cache::HashTable::getHashNode(std::string key) {
    int index = Cache::HashTable::hashFunction(key);
    HashNode* hp = hashNode[index];
    while(hp != nullptr) {
        if(hp->node != nullptr && hp->node->key.compare(key) == 0) {
            return hp->node;
        }
        hp = hp->next;
    }

    return nullptr;
}

void Cache::HashTable::addHashNode(Node* node) {
    if(node == nullptr) {
        return;
    }

    int index = Cache::HashTable::hashFunction(node->key);
    if(hashNode[index] == nullptr) {
        hashNode[index] = newHashNode(node);
    } else {
        HashNode* hp;
        for(hp = hashNode[index]; hp->next != nullptr; hp = hp->next);
        hp->next = newHashNode(node);
    }
}

void Cache::HashTable::removeHashNode(Node* node) {
    if(node == nullptr) {
        return;
    }

    int index = Cache::HashTable::hashFunction(node->key);
    HashNode *pre = nullptr, *hp = hashNode[index];
    while(hp != nullptr) {
        if(hp->node != nullptr && hp->node->key.compare(node->key) == 0) {
            if(pre == nullptr) {
                if(hp->next == nullptr) {
                    hashNode[index] = nullptr;
                } else {
                    hashNode[index] = hp->next;
                }
                delete hp;
            } else {
                if(hp->next == nullptr) {
                    pre->next = nullptr;
                } else {
                    pre->next = hp->next;
                }
                delete hp;
            }
            return;
        }
        pre = hp;
        hp = hp->next;
    }
}
// Enhanced End.