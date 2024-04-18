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

bool Cache::removeNode(std::string key) {
    Node* p = Cache::findNode(key);
    if(p == nullptr) {
        return false;
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
    delete p;
    return true;
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
    delete p;
    size--;
}

Cache::Node* Cache::findNode(std::string key) {
    if(linkedList == nullptr) {
        return nullptr;
    }
    Node* p = linkedList;
    while(p != nullptr) {
        if(p->key.compare(key) == 0) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

void Cache::add(std::string key, int value) {
    Cache::removeNode(key);
    insertNode(key, value);
    while(size > CACHE_SIZE) {
        Cache::removeTail();
    }
}

void Cache::add(std::string key, double value) {
    Cache::removeNode(key);
    insertNode(key, value);
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