#include "cached_runner.h"

// TODO: 필요한 함수 구현
#include "task_runner.h"

CachedRunner::CachedRunner(Cache &cache) {
    this->cache = &cache;
    hitCount = 0;
    missCount = 0;
}

// 파일의 숫자를 전부 곱하여 반환한다
double CachedRunner::multiply(std::string filename) {
    std::string key = "multiply(";
    key.append(filename);
    key.append(")");

    double value;
    if(cache->get(key, value)) {
        hitCount++;
    } else {
        missCount++;
        value = TaskRunner::multiply(filename);
    }
    cache->add(key, value);
    return value;
}

// 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
int CachedRunner::palindrome(std::string filename) {
    std::string key = "palindrome(";
    key.append(filename);
    key.append(")");

    int value;
    if(cache->get(key, value)) {
        hitCount++;
    } else {
        missCount++;
        value = TaskRunner::palindrome(filename);
    }
    cache->add(key, value);
    return value;
}

// 캐시에 히트한 횟수를 반환한다
int CachedRunner::hits() {
    return hitCount;
}

// 캐시에 미스한 횟수를 반환한다
int CachedRunner::misses() {
    return missCount;
}