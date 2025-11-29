# LRU Cache

In this task, you need to implement an "LRU cache". This is an associative container that evicts elements according to the Least Recently Used algorithm.
The interface is located in the `lru_cache.h` file.

As long as the cache size does not exceed the maximum, it works like a regular map:

 * The `Set()` method stores a new value corresponding to a key.
 * The `Get()` method returns false if nothing has been stored for the key. If a value corresponds to the key, `Get()` returns true and that value.

If, after `Set()`, the cache size exceeds `max_size`, the LRU algorithm is triggered, and the cache removes the key that was accessed least recently (in `Get()` or `Set()`).
The computational complexity of the `Get()` and `Set()` methods must be `O(1)` on average.