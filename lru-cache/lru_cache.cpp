#include "lru_cache.h"

void LruCache::set(const std::string &key, const std::string &value) {
    if (data_.size() >= max_size_) {
        data_.erase(data_.find(lru_.front().first));
        lru_.pop_front();
    }
    lru_.emplace_back(key, value);
    if (data_.find(key) != data_.end()) {
        lru_.erase(data_[key]);
    }
    data_[key] = std::prev(lru_.end());
}

bool LruCache::get(const std::string &key, std::string *value) {
    if (data_.find(key) == data_.end()) {
        return false;
    }
    *value = data_[key]->second;
    lru_.push_back(*data_[key]);
    lru_.erase(data_[key]);
    data_[key] = std::prev(lru_.end());
    return true;
}