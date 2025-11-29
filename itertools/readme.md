# Itertools

In this task, you will implement several helper functions for working with sequences, similar to those found in Python.

Namely: `Range`, `Zip`, and `Group`.
Examples of what we want to achieve in the end:

```c++
std::vector first = {4, 4, 5};
std::list<std::string> second = {"aba", "caba"};

for (const auto& elem : Zip(first, second)) {
    // elem.first -> int
    // elem.second -> string
}

for (const auto& elem : Zip(second, Range(second.size()))) {
    // like enumerate
    // elem.first -> string
    // elem.second -> index: 0, 1, 2, ...
}

for (const auto& elem : Group(first)) {
    // elem groups equal elements
    for (const auto& val : elem) {
        // only equal elements here
    }
}
````

It is important that these functions do not create new containers, vectors, or the like. Everything is implemented via iterators; i.e., `Range(100'500)` does not create a vector containing a heap of elements, but rather returns an entity that can be iterated over (just like in Python 3).

Use `Sequence`, defined in `itertools.h`, as this entity. It is a class template containing a pair of iterators (pointing to the beginning and the end of the sequence). Its main purpose is to be returned as a result from a function, which can then be used in a range-based for loop (as in the examples above).

The `Range(from, to, step)` function must generate the sequence `from, from + step, ..., from + k * step`, where `k` is the largest integer such that `from + k * step < to`. Also implement abbreviated forms of `Range` with 1 and 2 arguments (see tests). Assume that `step` is positive.

The `Zip` function takes 2 sequences (each having `begin` and `end`) and generates a sequence of corresponding pairs. The function must truncate the resulting sequence to the length of the shortest input sequence, i.e.:

```c++
std::vector a = {1, 2, 3};
for (const auto& val : Zip(a, Range(1 << 30))) {
    // 3 iterations
}
```

The `Group` function returns a sequence of `Sequence` objects representing consecutive subsequences of equal elements (see tests). Use only the `==` operator for comparison.

All we want is for the range-based for loop to work, so you can implement the minimal interface for all iterators: constructor, prefix `++`, dereference, and `operator!=`.

### Notes

  * To avoid being overwhelmed by compilation errors, use `const` wherever possible. This task implies read-only operations on sequences.
  * You can use `auto` in the function return type to avoid writing out long types manually.
  * As an example, the implementation of the `Repeat` function is provided in the `itertools.h` file. With its help, you can iterate over a sequence `n` times in a single loop:

<!-- end list -->

```c++
std::list a = {1, 2, 3, 4};
for (auto x : Repeat(a, 3)) {
    // 12 iterations: {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4}
}
```

  * It is useful to check what the [range-based for](https://en.cppreference.com/w/cpp/language/range-for#Explanation) expands into.

<!-- end list -->
