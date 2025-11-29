#include "lru_cache.h"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <concepts>
#include <cstdint>
#include <random>
#include <ranges>
#include <string>
#include <vector>

class RandomGenerator {
public:
    explicit RandomGenerator(int32_t seed) : gen_(seed) {}

    template <typename T>
    T genInt() {
        std::uniform_int_distribution<T> dist;
        return dist(gen_);
    }

private:
    std::mt19937 gen_;
};


TEST_CASE("Check class") {
    STATIC_CHECK_FALSE(std::copy_constructible<LruCache>);
    STATIC_CHECK_FALSE(std::move_constructible<LruCache>);
    STATIC_CHECK_FALSE(std::assignable_from<LruCache, const LruCache&>);
    STATIC_CHECK_FALSE(std::assignable_from<LruCache, LruCache&&>);
}

TEST_CASE("set and get") {
    LruCache cache(10);
    std::string value;

    cache.set("a", "1");
    cache.set("b", "2");
    cache.set("c", "3");

    REQUIRE(cache.get("a", &value));
    REQUIRE(value == "1");
    REQUIRE(cache.get("b", &value));
    REQUIRE(value == "2");
    REQUIRE(cache.get("c", &value));
    REQUIRE(value == "3");

    REQUIRE(!cache.get("d", &value));

    cache.set("c", "4");
    REQUIRE(cache.get("c", &value));
    REQUIRE(value == "4");
}

TEST_CASE("Eviction") {
    LruCache cache(2);
    std::string value;

    cache.set("a", "1");
    cache.set("b", "2");
    cache.set("c", "3");

    REQUIRE_FALSE(cache.get("a", &value));
    REQUIRE(cache.get("b", &value));
    REQUIRE(cache.get("c", &value));

    cache.set("b", "4");
    cache.set("c", "5");
    cache.set("b", "6");

    cache.set("e", "7");
    REQUIRE_FALSE(cache.get("c", &value));
    REQUIRE(cache.get("b", &value));
    REQUIRE(cache.get("e", &value));

    cache.get("b", &value);
    cache.set("f", "8");
    REQUIRE_FALSE(cache.get("e", &value));
    REQUIRE(cache.get("b", &value));
    REQUIRE(cache.get("f", &value));
}

TEST_CASE("Stress 1") {
    constexpr auto kSize = 1000;
    constexpr auto kEnd = 100 * kSize;

    LruCache cache(kSize);
    std::string value;
    for (auto i : std::views::iota(0, kSize)) {
        auto key = std::to_string(i);
        cache.set(key, key);
        if (!cache.get(key, &value)) {
            FAIL("Can't set " << key);
        } else if (value != key) {
            FAIL(value << " != " << key);
        }
    }

    for (auto i : std::views::iota(kSize, kEnd)) {
        auto key = std::to_string(i);
        cache.set(key, "foo");
        auto old_key = std::to_string(i - kSize);
        if (cache.get(old_key, &value)) {
            FAIL(old_key << " was not deleted");
        }
    }
}

TEST_CASE("Stress 2") {
    LruCache cache(100);
    std::string value;
    RandomGenerator rnd{431'234};

    for (auto i = 0; i < 100'000; ++i) {
        auto key = std::to_string(rnd.genInt<uint32_t>() % 500);
        if (rnd.genInt<uint32_t>() % 2 != 0U) {
            cache.set(key, "foo");
        } else {
            cache.get(key, &value);
        }
    }
}

TEST_CASE("Stress 3") {
    constexpr auto kSize = 100'000;
    constexpr auto kRange = std::views::iota(0, kSize);

    std::mt19937 gen{31'134};  // NOLINT(cert-msc32-c,cert-msc51-cpp)
    std::vector v(kRange.begin(), kRange.end());
    std::ranges::shuffle(v, gen);

    LruCache cache(kSize);
    for (auto i : v) {
        cache.set(std::to_string(i), "foo");
    }

    std::ranges::shuffle(v, gen);
    std::string value;
    for (auto i : v) {
        auto key = std::to_string(i);
        if (!cache.get(key, &value)) {
            FAIL(key << " not found");
        }
    }

    for (auto i : std::views::iota(0, kSize)) {
        cache.set(std::to_string(i + kSize), "foo");
        auto old_key = std::to_string(v[i]);
        if (cache.get(old_key, &value)) {
            FAIL(old_key << " was not deleted");
        }
    }

    for (auto i : std::views::iota(kSize, 2 * kSize)) {
        auto key = std::to_string(i);
        if (!cache.get(key, &value)) {
            FAIL(key << " not found");
        }
    }
}
