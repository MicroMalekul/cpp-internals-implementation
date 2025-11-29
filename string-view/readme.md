# String View

Implement the `StringView` class, a simplified analog of [std::string_view](http://en.cppreference.com/w/cpp/string/basic_string_view).

Unlike `std::string`, this class does not own the string; instead, it stores a pointer to its beginning and its size. This allows for creating "copies" of strings and extracting substrings at practically zero cost. However, it is important to understand that since `StringView` does not own the string but merely observes it, any changes to the underlying string will be visible through the `StringView`. At the same time, the `StringView` class itself cannot modify the string it observes.

You are not provided with the class interface; you must write it entirely from scratch. Implement the following:

* Default constructor.
* Copy constructor.
* Constructors (two) accepting `const std::string&` and a substring size (default `data.size()`). The first accepts only the string; the second accepts the string and the size.
* Constructors (two) accepting `const char*` — a pointer to a C-string. Use [strlen](http://en.cppreference.com/w/cpp/string/byte/strlen) to determine its length. The first accepts only the string pointer; the second accepts the pointer and the size.
* Template constructor accepting two arguments, `first` and `last`, of type `std::random_access_iterator`.
* Delete the constructor for `std::nullptr_t`.
* Assignment operator (`=`) accepting `const StringView&`.
* Constant operator `[i]`, allowing access to the character at position `i`. Since it is not possible to modify the string via the `StringView` class, a non-const operator `[i]` is not needed.
* Constant method `Substr`, similar to the std version. The first argument is the start position (default `0`), the second argument is the count of elements (default `std::string::npos`) ([std::string::npos](http://en.cppreference.com/w/cpp/string/basic_string/npos)).
* Constant method `Data`, returning a pointer to the beginning of the observed string.
* Constant method `Size`, returning the length of the observed string.
* Constant method `At`, used to access the character at position `i`. Must throw an `std::out_of_range` exception if the index is out of bounds.
* Constant method `Empty` — same as `std::string_view`.
* Constant method `Front` — same as `std::string_view`.
* Constant method `Back` — same as `std::string_view`.

You can find usage examples in the tests.
