# C++ Internals Implementation (2024)

This repository contains a collection of educational C++ projects designed to explore the internal workings of standard library containers, memory management patterns, and iterator logic.

Each folder represents an isolated task focusing on a specific concept in modern C++ development.

## Project Structure

* **`string-view/`**: A simplified implementation of `std::string_view`
* **`vector/`**: A manual implementation of a dynamic array (similar to `std::vector`)
* **`cow-vector/`**: A vector implementation utilizing the **Copy-On-Write (COW)** optimization technique
* **`itertools/`**: A library of Python-like iterator adaptors (`Range`, `Zip`, `Group`).
* **`lru-cache/`**: An implementation of a Least Recently Used (LRU) cache policy with O(1) complexity

## Prerequisites

* C++ Compiler supporting C++20.
* CMake (Version 3.14 or higher).

## How to Build

This project is structured as a CMake monorepo. You can build all tasks at once or target specific directories.

1.  **Configure the project:**
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

2.  **Build all targets:**
    ```bash
    cmake --build .
    ```

3.  **Run Tests:**
    Each project includes a `test.cpp` file using the Catch2 testing framework.
    ```bash
    ctest --output-on-failure

    
