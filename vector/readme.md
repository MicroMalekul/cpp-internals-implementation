# Vector

In this task, you will implement a simplified analogue of the `std::vector` template class.
The goal is to manage memory manually without relying on standard containers or smart pointers.

## Features

Your `Vector` class stores integers (or templated types) and supports the following operations:

* **Constructors**: Default, by size (filled with zeros), and via `std::initializer_list` (e.g., `Vector a = {1, 3, 5}`).
* **Rule of Five**: Copy constructor, Move constructor, Copy assignment, Move assignment, and Destructor.
* **Element Access**: `operator[]` (const and non-const).
* **Capacity Management**:
    * `Size()`: Returns the number of elements.
    * `Capacity()`: Returns the number of allocated memory cells.
    * `Reserve(n)`: Allocates memory for at least `n` elements.
* **Modifiers**:
    * `PushBack(val)`: Adds an element to the end. Performs reallocation (doubles capacity) if the vector is full.
    * `PopBack()`: Removes the last element (decreases size, capacity remains unchanged).
    * `Clear()`: Sets size to 0.
    * `Swap(other)`: Swaps contents with another vector.
* **Iterators**: Methods `begin()` and `end()` returning a custom `RandomAccessIterator`.

## Implementation Details

1.  **Memory Management**: You must use `new` and `delete[]` manually.
2.  **Iterators**: The `Vector::Iterator` must satisfy the [RandomAccessIterator](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator) requirements.
3.  **Reallocation Strategy**: When `PushBack` is called on a full vector, allocate a new array of size `max(1, capacity * 2)`, move elements, and delete the old array.

## Restrictions

* Do not use `std::vector` or `std::unique_ptr`/`std::shared_ptr`.
* Ensure exception safety (e.g., in `operator=`).