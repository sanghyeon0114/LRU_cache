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

    head = nullptr;
    size = 0;
}

// int를 cache에 추가한다
void Cache::add(std::string key, int value) {
    if(size == 1 && head->key.compare(key) == 0) {
        head->type = INT;
        head->ivalue = value;
        return;
    }
    Node *pre = nullptr, *cur = head;
    bool isDelete = false;
    while(cur != nullptr) {
        if(cur->key.compare(key) == 0) {
            Node *p = cur;
            if(pre == nullptr) {
                head = head->next;
            } else if(cur->next == nullptr) {
                pre->next = nullptr;
            }
            delete p;
            isDelete = true;
            break;
        }
        pre = cur;
        cur = cur->next;
    }

    if(size == CACHE_SIZE) {
        Node *p = head;
        head = head->next;
        delete p;
    } else if(!isDelete) {
        size++;
    }

    Cache::Node *node = new Cache::Node;
    node->key = key;
    node->type = INT;
    node->ivalue = value;

    if(head == nullptr) {
        head = node;
        return;
    }
    Node *p;
    for(p = head; p->next != nullptr; p = p->next);
    p->next = node;
}

// double을 cache에 추가한다
void Cache::add(std::string key, double value) {
    if(size == 1 && head->key.compare(key) == 0) {
        head->type = DOUBLE;
        head->dvalue = value;
        return;
    }
    Node *pre = nullptr, *cur = head;
    bool isDelete = false;
    while(cur != nullptr) {
        if(cur->key.compare(key) == 0) {
            Node *p = cur;
            if(pre == nullptr) {
                head = head->next;
            } else if(cur->next == nullptr) {
                pre->next = nullptr;
            }
            delete p;
            isDelete = true;
            break;
        }
        pre = cur;
        cur = cur->next;
    }

    if(size == CACHE_SIZE) {
        Node *p = head;
        head = head->next;
        delete p;
    } else if(!isDelete) {
        size++;
    }

    Cache::Node *node = new Cache::Node;
    node->key = key;
    node->type = DOUBLE;
    node->dvalue = value;

    if(head == nullptr) {
        head = node;
        return;
    }
    Node *p;
    for(p = head; p->next != nullptr; p = p->next);
    p->next = node;
}

// key에 해당하는 value를 cache에서 가져온다
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, int &value) {
    Node *cur = head;
    while(cur != nullptr) {
        if(cur->key == key && cur->type == INT) {
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
        if(cur->key == key && cur->type == DOUBLE) {
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
    
    if(head != nullptr) {
        result.append("(");
        result.append(head->key);
        result.append(": ");
        if(head->type == INT) {
            result.append(std::to_string(head->ivalue));
        } else if(head->type == DOUBLE) {
            result.append(std::to_string(head->dvalue));
        }
        result.append(") ");
    }

    Node *cur = head;
    while(cur != nullptr) {
        result.append("[");
        result.append(cur->key);
        result.append(": ");
        if(cur->type == INT) {
            result.append(std::to_string(cur->ivalue));
        } else if(cur->type == DOUBLE) {
            result.append(std::to_string(cur->dvalue));
        }
        result.append("]");
        cur = cur->next;
        if(cur != nullptr) {
            result.append(" -> ");
        }
    }

    return result;
}