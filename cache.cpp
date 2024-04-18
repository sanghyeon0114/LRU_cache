#include "cache.h"

// TODO: 필요한 함수 구현

Cache::Cache() {
    head = nullptr;
    size = 0;
}

Cache::~Cache()
{
    Node *cur = head;
    Node *p;

    while(cur != nullptr) {
        p = cur;
        cur = cur->next;
        delete p;
    }

    head = tail = nullptr;
    size = 0;
}

// int를 cache에 추가한다
void Cache::add(std::string key, int value) {
    if(size == CACHE_SIZE) {
        return;
    }
    size++;
    Cache::Node *node = new Cache::Node;
    node->key = key;
    node->type = INT;
    node->ivalue = value;

    if(head == nullptr) {
        head = tail = node;
        node->next = nullptr;
        return;
    }
    tail->next = node;
    node->next = nullptr;
    tail = tail->next;
}

// double을 cache에 추가한다
void Cache::add(std::string key, double value) {
    if(size == CACHE_SIZE) {
        return;
    }
    size++;
    Cache::Node *node = new Cache::Node;
    node->key = key;
    node->type = DOUBLE;
    node->dvalue = value;

    if(head == nullptr) {
        head = tail = node;
        node->next = nullptr;
        return;
    }
    tail->next = node;
    node->next = nullptr;
    tail = tail->next;
}

// key에 해당하는 value를 cache에서 가져온다
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, int &value) {
    Node *cur = head;
    while(cur != nullptr) {
        if(cur->key == key && cur->type == Type::INT) {
            value = cur->ivalue;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// key에 해당하는 value를 cache에서 가져온다.
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, double &value) {
    Node *cur = head;
    while(cur != nullptr) {
        if(cur->key == key && cur->type == Type::DOUBLE) {
            value = cur->dvalue;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
// 다음과 같이 표현된 문자열을 반환한다
// [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
std::string Cache::toString() {
    std::string result;
    Node *cur = head;
    while(true) {
            result.append("[");
            result.append(cur->key);
            result.append(": ");
        if(cur->type == Type::INT) {
            result.append(std::to_string(cur->ivalue));
        } else if(cur->type == Type::DOUBLE) {
            result.append(std::to_string(cur->dvalue));
        }
        result.append("]");
        cur = cur->next;
        if(cur != nullptr) {
            result.append(" -> ");
        } else {
            break;
        }
    }
    return result;
}