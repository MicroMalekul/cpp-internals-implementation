#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>

template<class T>
class Vector {
   public:
    class Iterator {
       public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(pointer ptr = nullptr) : ptr_(ptr) {
        }

        Iterator& operator++() {
            ptr_++;
            return *this;
        }

        Iterator operator++(int) {
            auto temp = *this;
            ptr_++;
            return temp;
        }

        Iterator& operator--() {
            ptr_--;
            return *this;
        }

        Iterator operator--(int) {
            auto temp = *this;
            ptr_--;
            return temp;
        }

        Iterator& operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }

        friend Iterator operator+(difference_type n, Iterator a) {
            Iterator temp = a;
            return temp += n;
        }

        Iterator operator+(difference_type n) const {
            Iterator temp = *this;
            return temp += n;
        }

        Iterator& operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }

        Iterator operator-(difference_type n) const {
            Iterator temp = *this;
            return temp -= n;
        }

        difference_type operator-(Iterator b) const {
            return ptr_ - b.ptr_;
        }

        reference operator[](difference_type n) {
            return *(ptr_ + n);
        }

        reference operator[](difference_type n) const {
            return *(ptr_ + n);
        }

        reference operator*() {
            return *ptr_;
        }

        Iterator operator->() {
            return *this;
        }

        reference operator*() const {
            return *ptr_;
        }

        Iterator operator->() const {
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }

        bool operator<(const Iterator& other) const {
            return ptr_ < other.ptr_;
        }

        bool operator<=(const Iterator& other) const {
            return ptr_ <= other.ptr_;
        }

        bool operator>(const Iterator& other) const {
            return ptr_ > other.ptr_;
        }

        bool operator>=(const Iterator& other) const {
            return ptr_ >= other.ptr_;
        }

       private:
        pointer ptr_;
    };

    [[nodiscard]] Iterator begin() const {
        return Iterator(arr_);
    }

    [[nodiscard]] Iterator end() const {
        auto* it = arr_;
        std::advance(it, size_);
        return Iterator(it);
    }

    Vector() : arr_(new T[0]) {
    }

    explicit Vector(size_t size) : capacity_(size), size_(size), arr_(new T[size]()) {
    }

    explicit Vector(size_t capacity, size_t size)
        : capacity_(capacity), size_(size), arr_(new T[capacity]()) {
    }

    Vector(std::initializer_list<T> arr)
        : capacity_(arr.size()), size_(arr.size()), arr_(new T[arr.size()]()) {
        std::copy(arr.begin(), arr.end(), arr_);
    }

    Vector(Vector& a) : capacity_(a.capacity_), size_(a.size_), arr_(new T[capacity_]) {
        std::copy(a.begin(), a.end(), arr_);
    }

    Vector(Vector&& a) noexcept : capacity_(a.capacity_), size_(a.size_), arr_(a.arr_) {
        a.arr_ = nullptr;
        a.size_ = 0;
        a.capacity_ = 0;
    }

    ~Vector() {
        delete[] arr_;
    }

    Vector& operator=(const Vector& a) {
        if (this == &a) {
            return *this;
        }
        delete[] arr_;
        capacity_ = a.capacity_;
        size_ = a.size_;
        arr_ = new T[capacity_];  // NOLINT(cppcoreguidelines-owning-memory)
        std::copy(a.begin(), a.end(), arr_);
        return *this;
    }

    Vector& operator=(Vector&& a) noexcept {
        if (this == &a) {
            return *this;
        }

        delete[] arr_;

        arr_ = a.arr_;
        size_ = a.size_;
        capacity_ = a.capacity_;

        a.arr_ = nullptr;
        a.size_ = 0;
        a.capacity_ = 0;

        return *this;
    }

    void Swap(Vector& b) {
        std::swap(arr_, b.arr_);
        std::swap(size_, b.size_);
        std::swap(capacity_, b.capacity_);
    }

    template <typename T1>
    T& operator[](T1 i) {
        auto* it = arr_;
        std::advance(it, i);
        return *it;
    }

    template <typename T1>
    T& operator[](T1 i) const {
        auto* it = arr_;
        std::advance(it, i);
        return *it;
    }

    [[nodiscard]] size_t Size() const {
        return size_;
    }

    [[nodiscard]] size_t Capacity() const {
        return capacity_;
    }

    void PushBack(T a) {
        if (size_ == capacity_) {
            Vector temp = Vector(capacity_ == 0 ? 1 : capacity_ * 2LL, size_);
            std::copy(begin(), end(), temp.arr_);
            this->Swap(temp);
        }

        *end() = a;
        size_++;

    }

    void PopBack() {
        if (size_ != 0) {
            size_--;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t a) {
        if (a > capacity_) {
            Vector temp(a, size_);
            std::copy(begin(), end(), temp.arr_);
            Swap(temp);
        }
    }

   private:
    size_t capacity_{0};
    size_t size_{0};
    T* arr_{};
};
