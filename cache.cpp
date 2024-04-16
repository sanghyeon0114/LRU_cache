#include "cache.h"

// TODO: 필요한 함수 구현

Cache::Cache() {

}
  
// int를 cache에 추가한다
void Cache::add(std::string key, int value) {

}

// double을 cache에 추가한다
void Cache::add(std::string key, double value) {

}
  
// key에 해당하는 value를 cache에서 가져온다
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, int &value) {
    return true;
}

// key에 해당하는 value를 cache에서 가져온다.
// 타입과 key가 동일한 원소가 없다면 false를 반환한다.
bool Cache::get(std::string key, double &value) {
    return true;
}

// 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
// 다음과 같이 표현된 문자열을 반환한다
// [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
std::string Cache::toString() {
    return "";
}