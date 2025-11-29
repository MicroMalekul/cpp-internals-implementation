#ifndef LRU_CACHE_H

#define LRU_CACHE_H
#include <cstddef>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>

class LruCache {
public:
    explicit LruCache(size_t max_size) : max_size_(max_size) {}

    LruCache(const LruCache &) = delete;
    ~LruCache() = default;
    LruCache(LruCache &&) = delete;
    LruCache &operator=(const LruCache &) = delete;
    LruCache &operator=(const LruCache &&) = delete;

    void set(const std::string &key, const std::string &value);

    bool get(const std::string &key, std::string *value);

private:
    std::list<std::pair<std::string, std::string>> lru_;
    std::unordered_map<std::string,
                       std::list<std::pair<std::string, std::string>>::iterator>
        data_;
    size_t max_size_{0};
};
#endif