#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <string>

class StringView {
   private:
    const char* begin_{nullptr};
    size_t size_{0};

   public:
    explicit StringView() = default;

    StringView(StringView& s) = default;

    explicit StringView(const std::string& s, size_t size) : begin_(s.data()), size_(size) {
    }

    explicit StringView(const std::string& s) : begin_(s.data()), size_(s.size()) {
    }

    explicit StringView(const char* s, size_t size) : begin_(s), size_(size) {
    }

    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    StringView(const char* s) : begin_(s), size_(std::strlen(s)) {
    }

    template <typename T>
    explicit StringView(T first, T last) : begin_(first), size_(std::distance(first, last)) {
    }

    explicit StringView(std::nullptr_t t) = delete;

    StringView(StringView&& a) = default;

    ~StringView() = default;

    StringView& operator=(const StringView& s) = default;

    StringView& operator=(StringView&& a) noexcept {
        begin_ = a.begin_;
        size_ = a.size_;
        return *this;
    }

    char operator[](uint32_t i) const {
        return *std::next(begin_, i);
    }

    [[nodiscard]] StringView Substr(uint32_t pos = 0, size_t size = std::string::npos) const {
        return StringView(std::next(this->begin_, pos), std::min(size_ - pos, size));
    }

    [[nodiscard]] const char* Data() const {
        return begin_;
    }

    [[nodiscard]] size_t Size() const {
        return this->size_;
    }

    [[nodiscard]] char At(uint32_t i) const {
        if (i < size_) {
            return (*this)[i];
        }
        throw std::out_of_range("bolbas");
    }

    [[nodiscard]] bool Empty() const {
        return size_ == 0;
    }

    [[nodiscard]] char Front() const {
        return *begin_;
    }

    [[nodiscard]] char Back() const {
        return this->At(size_ - 1);
    }
};
