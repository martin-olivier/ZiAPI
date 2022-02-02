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
        {"sources", new Node({
            new Node("/bin/ls"),
            new Node(10),
            new Node(nullptr),
            new Node(10.5)
            })
        },
        {"modules", new Node({
            {"directoryListing", new Node({
                {"root", new Node("/var/www")}
            })}
        })}
    }
);
```
#
## Data Types

### Undefined

example of a json containing an `undefined`

```json

```
transcription with our `Config.hpp`
```cpp
new ziapi::config::Node(ziapi::config::Undefined{})
```


### Null

example of a json containing a `null`

```json
null
```
transcription with our `Config.hpp`
```cpp
new ziapi::config::Node(nullptr)
```

### bool

example of a json containing a `bool`

```json
true
```
transcription with our `Config.hpp`
```cpp
new ziapi::config::Node(true)
```


### int

example of a json containing an `int`

```json
5
```
transcription with our `Config.hpp`
```cpp
new ziapi::config::Node(5)
```


### double

example of a json containing a `double`

```json
4.2
```

transcription with our `Config.hpp`
```cpp
new ziapi::config::Node(4.2)
```


### String

example of a json containing an `String`

```json
"Hello World!"
```
transcription with our `Config.hpp`
```cpp
new ziapi::config::Node("Hello World!")
```


### Array

example of a json containing an `Array`

```json
["Hello", "World", "!"]
```

transcription with our `Config.hpp`
```cpp
using Node = ziapi::config::Node;

new Node({
    new Node("Hello"),
    new Node("World"),
    new Node("!")
})
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

new Node({
    {"age", new Node(19)},
    {"first_name", new Node("Charlie")},
    {"last_name", new Node("Chou")},
    {"is_sexy", new Node(true)}
})
```

