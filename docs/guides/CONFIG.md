# Managing your configuration

In this guide we will learn how to use our configuration, to setup all of your modules easily.

## `Node` class

First, let's take a look at the `Node` definition

```cpp
using NodeVariant = std::variant<Undefined, Null, bool, int, double, String, Array, Dict>;

struct Node : public NodeVariant { /* ... */ }
```

So here we can see that our `struct Node` inherits from a `std::variant` of a lot of types.
The `std::variant` declines all the possible data types available in JSON, YAML, XML, etc.

Let's look at a simple example:

Imagine you have something like
```json
{
    "sources": ["/bin/ls", 10, null, 10.5],
    "modules": {
        "directoryListing": {
            "root": "/var/www"
        }
    }
}
```
or
```yaml
sources:
  - "/bin/ls"
  - 10
  - null
  - 10.5
modules:
  directoryListing:
    root: /var/www
```
You could generate it like so
```cpp
using Node = ziapi::config::Node;

Node obj(
    {
        {"sources", std::make_shared<Node>({
            std::make_shared<Node>("/bin/ls"),
            std::make_shared<Node>(10),
            std::make_shared<Node>(nullptr),
            std::make_shared<Node>(10.5)
            })
        },
        {"modules", std::make_shared<Node>({
            {"directoryListing", std::make_shared<Node>({
                {"root", std::make_shared<Node>("/var/www")}
            })}
        })}
    }
);
// or

auto obj = Node::MakeDict({
    {"sources", Node::MakeArray({ "/bin/ls", 10, nullptr, 10.5 })},
    {"modules", Node::MakeDict({
        {"directoryListing", Node::MakeDict({
            {"root", "/var/www"}
        })}
    })}
})

```
#
## Data Types

### Undefined

example of a json containing an `undefined`

```json

```
transcription with our `Config.hpp`
```cpp
ziapi::config::Node(ziapi::config::Undefined{})
```


### Null

example of a json containing a `null`

```json
null
```
transcription with our `Config.hpp`
```cpp
ziapi::config::Node(nullptr)
```

### bool

example of a json containing a `bool`

```json
true
```
transcription with our `Config.hpp`
```cpp
ziapi::config::Node(true)
```


### int

example of a json containing an `int`

```json
5
```
transcription with our `Config.hpp`
```cpp
ziapi::config::Node(5)
```


### double

example of a json containing a `double`

```json
4.2
```

transcription with our `Config.hpp`
```cpp
ziapi::config::Node(4.2)
```


### String

example of a json containing an `String`

```json
"Hello World!"
```
transcription with our `Config.hpp`
```cpp
ziapi::config::Node("Hello World!")
```


### Array

example of a json containing an `Array`

```json
["Hello", "World", "!"]
```

transcription with our `Config.hpp`
```cpp
using Node = ziapi::config::Node;

Node({
    std::make_shared<Node>("Hello"),
    std::make_shared<Node>("World"),
    std::make_shared<Node>("!")
});

// or

Node::MakeArray({ "Hello", "World", "!" });
```n

### Dict

example of a json containing a `Dict`

```json
{
    "age": 19,
    "first_name": "Charlie",
    "last_name": "Chou",
    "is_sexy": true
}
```

transcription with our `Config.hpp`
```cpp
using Node = ziapi::config::Node;

Node({
    {"age", std::make_shared<Node>(19)},
    {"first_name", std::make_shared<Node>("Charlie")},
    {"last_name", std::make_shared<Node>("Chou")},
    {"is_sexy", std::make_shared<Node>(true)}
})

// or

Node::MakeDict({
    {"age", 19},
    {"first_name", "Charlie"},
    {"last_name", "Chou"},
    {"is_sexy", true},
})

```

