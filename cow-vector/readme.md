# COW Vector

The standard vector implements so-called _value semantics_. This means that when a vector is copied, all values stored in the vector are copied. This behavior is also called "deep copying".

Vector copy semantics are simple to understand but can be quite expensive. Therefore, when working with a vector, you need to write code carefully to avoid creating unnecessary vector copies where they are not needed.

Besides _value semantics_, two other approaches can be distinguished:
 - _reference semantics_ - when copying an object, its content is never copied but is always shared among all copies. This approach is sometimes called "shallow copy".
 - _cow semantics_. COW stands for "copy-on-write". In this approach, we initially make a shallow copy of the vector. If the user only reads the content of the copy and does not modify it, they do not notice the substitution, and we save performance costs. The moment the user attempts to modify the vector, we make a real "deep copy". Thus, copying occurs only when writing to the vector. Hence the name "copy-on-write".

COW semantics are used in string implementations at Yandex and Facebook.

## Implementation

To implement COW semantics, you will need to move all fields of your vector into a separate structure. Inside this structure, in addition to the usual fields, you need to store a reference counter.

```c++
struct State {
    int ref_count; // how many vectors share this State.

    // other fields
};

class COWVector {
private:
    State* state_;
};

```

By correctly maintaining ref_count, you will always know when to delete State or when to turn a shallow-copy into a deep-copy.

Note:
* You cannot use smart pointers here!

* Wherever you write new, disable clang-tidy with the line // NOLINT(cppcoreguidelines-owning-memory)