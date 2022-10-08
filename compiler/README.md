# BisonParser

## **Structure of the Parser**
------
- The ideea behind the AST in this case will be that everything will be an expression for simplification purposes. We will also have an **identifier** which will be an **ENUM (undefined, function, paramater, variable)**.

**Structure of the identifier**:

```c++
struct identifer {
    id_type type = id_type::undefined;
    std::size_t index = 0;
    std::string name;
};
```

**and the enum:**

```c++
#define ENUM_IDENTIFIERS(o) \
        o(undefined)                              /* undefined */ \
        o(function)                               /* a pointer to givenfunction */ \
        o(parameter)                              /* one of the function params */ \
        o(variable)                               /* a local variable */
#define o(n) n,
enum class id_type {  ENUM_IDENTIFIERS(o) };
#undef o
```

