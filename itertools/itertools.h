#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>

template <class Iterator>
class Sequence {
   public:
    Sequence(Iterator begin, Iterator end) : begin_{std::move(begin)}, end_{std::move(end)} {
    }

    [[nodiscard]] Iterator begin() const {  // NOLINT(readability-identifier-naming)
        return begin_;
    }

    [[nodiscard]] Iterator end() const {  // NOLINT(readability-identifier-naming)
        return end_;
    }

   private:
    Iterator begin_, end_;
};

template <class Iterator>
class RepeatIterator {
   public:
    RepeatIterator(
        Iterator begin, Iterator end,
        size_t count = 0)  // NOLINT(fuchsia-default-arguments-declarations)
        : begin_{begin}, it_{begin}, end_{end}, count_{count} {
    }

    RepeatIterator& operator++() {
        if (!(++it_ != end_)) {
            ++count_;
            it_ = begin_;
        }
        return *this;
    }

    auto operator*() const {
        return *it_;
    }

    bool operator==(const RepeatIterator& rhs) const = default;

   private:
    Iterator begin_, it_, end_;
    size_t count_;
};

auto Repeat(const auto& sequence, size_t n) {
    auto begin = sequence.begin();
    auto end = sequence.end();
    if (n && (begin != end)) {
        return Sequence{RepeatIterator{begin, end}, RepeatIterator{begin, end, n}};
    }
    return Sequence{RepeatIterator{end, end}, RepeatIterator{end, end}};
}

class RangeIterator {
   public:
    RangeIterator(int64_t it, int64_t step) : it_{it}, step_{step} {
    }

    RangeIterator& operator++() {
        it_ += step_;
        return *this;
    }

    int64_t operator*() const {
        return it_;
    }

    bool operator==(const RangeIterator& rhs) const {
        return it_ >= rhs.it_;
    }

   private:
    int64_t it_;
    int64_t step_;
};

inline auto Range(int64_t to) {
    auto a = RangeIterator{0, 1};
    auto b = RangeIterator{to, 1};
    return Sequence{a, b};
}

inline auto Range(int64_t from, int64_t to, int64_t step = 1) {
    auto a = RangeIterator{from, step};
    auto b = RangeIterator{to, step};
    return Sequence{a, b};
}

template <class Iter1, class Iter2>
class ZipIterator {
   public:
    ZipIterator(Iter1 it1, Iter2 it2)  // NOLINT(fuchsia-default-arguments-declarations)
        : it1_{it1}, it2_{it2} {
    }

    ZipIterator& operator++() {
        ++it1_;
        ++it2_;
        return *this;
    }

    auto operator*() const {
        return std::make_pair(*it1_, *it2_);
    }

    bool operator==(const ZipIterator& rhs) const {
        return it1_ == rhs.it1_ || it2_ == rhs.it2_;
    }

   private:
    Iter1 it1_;
    Iter2 it2_;
};

auto Zip(const auto& a, const auto& b) {
    return Sequence(ZipIterator(a.begin(), b.begin()), ZipIterator(a.end(), b.end()));
}

template <class Iter>
class GroupIterator {
   public:
    explicit GroupIterator(Iter it, Iter end) : it_{std::move(it)}, end_{std::move(end)} {
    }

    GroupIterator& operator++() {
        if (it_ != end_) {
            auto it1 = it_;
            while (it_ != end_ && *it1 == *it_) {
                ++it_;
            }
        }
        return *this;
    }

    auto operator*() const {
        auto next = it_;
        while (next != end_ && *next == *it_) {
            ++next;
        }
        return Sequence(it_, next);
    }

    bool operator==(const GroupIterator& rhs) const {
        return it_ == rhs.it_;
    }

   private:
    Iter it_;
    Iter end_;
};

auto Group(const auto& a) {
    return Sequence(GroupIterator(a.begin(), a.end()), GroupIterator(a.end(), a.end()));
}