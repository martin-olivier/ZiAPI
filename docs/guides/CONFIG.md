# Managing your configuration

In this guide we will learn how to use our configuration, to setup all of your modules easily.

## The `Node` object

First, let's take a look at the definition of `ziapi::config::Node`.

```cpp
using NodeVariant = std::variant<Undefined, Null, bool, int, double, String, Array, Dict>;

struct Node : public NodeVariant { /* ... */ }
```

So here we can see that our `struct Node` inherits from a `std::variant` of a lot of types.
The `std::variant` declines all the possible data types available in JSON, YAML, XML, etc.

Let's look at a simple example:

Imagine you have a configuration file of the following form:

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

Or its YAML equivalent

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

You could represent it using a `ziapi::config::Node` like so

```cpp
using Node = ziapi::config::Node;
using Dict = ziapi::config::Dict;
using Array = ziapi::config::Array;

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

// Or using helper static methods

auto obj = Node::MakeDict({
    {"sources", Node::MakeArray({ "/bin/ls", 10, nullptr, 10.5 })},
    {"modules", Node::MakeDict({
        {"directoryListing", Node::MakeDict({
            {"root", "/var/www"}
        })}
    })}
})
```
### More informations about Dict and Array helper functions
```cpp
// You can also give the helper methods a vector representing your array or dictionnary
// The helper functions will automatically transform your contained Nodes into shared_ptr   

std::vector<std::pair<std::string, Node>> dictionnary_vector;
// ... Fill the dictionnary vector
Node dictionnary_node = Node::MakeDict(dictionnary_vector)

std::vector<Node> array_vector;
// ... Fill the array vector
Node array_node = Node::MakeArray(array_vector)


// You can of course build them from the Node base types
// In this case, you're responsible of giving the values as shared_ptr and converting the final variable as a Node

Dict dictionnary;
dictionnary["modules_count"] = std::make_shared<Node>(10);
Node dictionnary_node(dictionnary);

Array arr;
arr.emplace_back(std::make_shared("/bin/ls"));
Node array_node(arr);
```

## Data Types

### `Undefined`

The `Undefined` data type represents an empty configuration, much like an empty file.

```cpp
ziapi::config::Node(ziapi::config::Undefined{})
```

### `Null`

The `Null` data type represents a boolean value. So the following JSON:

```json
null
```

Would translate to

```cpp
ziapi::config::Node(nullptr)
```

### `bool`

The `bool` data type represents a boolean value. So the following JSON:

```json
true
```

Would translate to

```cpp
ziapi::config::Node(true)
```

### `int`

The `int` data type represents an integer value. So the following JSON:

```json
5
```

Would translate to

```cpp
ziapi::config::Node(5)
```

### `double`

The `double` data type represents a floating point value. So the following JSON:

```json
4.2
```

Would translate to

```cpp
ziapi::config::Node(4.2)
```

### `String`

The `String` data type represents a string value. So the following JSON:

```json
"Hello World!"
```

Would translate to

```cpp
ziapi::config::Node("Hello World!")
```


### `Array`

The `Array` data type represents an array of values. So the following JSON:

```json
["Hello", "World", "!"]
```

Would translate to

```cpp
ziapi::config::Array arr({
    std::make_shared<ziapi::config::Node>("Hello"),
    std::make_shared<ziapi::config::Node>("World"),
    std::make_shared<ziapi::config::Node>("!")
});

ziapi::config::Node arr_node(arr);
```

Which is equivalent to

```c++
auto array_node = ziapi::config::Node::MakeArray({ "Hello", "World", "!" }); 
// vector<Node> can also be passed as a parameter
```

### `Dict`

The `Dict` data type represents a dictionary of values. So the following JSON:

```json
{
    "age": 19,
    "first_name": "Charlie",
    "last_name": "Chou",
    "is_sexy": true
}
```

Would translate to

```cpp
ziapi::config::Dict dict({
    {"age", std::make_shared<ziapi::config::Node>(19)},
    {"first_name", std::make_shared<ziapi::config::Node>("Charlie")},
    {"last_name", std::make_shared<ziapi::config::Node>("Chou")},
    {"is_sexy", std::make_shared<ziapi::config::Node>(true)}
})

ziapi::config::Node node_dict(dict);
```

Which is equivalent to

```c++
auto node_dict = ziapi::config::Node::MakeDict({
    {"age", 19},
    {"first_name", "Charlie"},
    {"last_name", "Chou"},
    {"is_sexy", true},
}) // vector<std::string, Node> can also be passed as a parameter
```