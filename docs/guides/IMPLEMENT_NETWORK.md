# Implement a Network module

In this guide we will learn how to implement a Network module which is a type of module that allows us to handle incoming requests and send back responses.

## `INetworkModule` interface

Let's look at the definition of the `INetworkModule` interface.

```c++
class INetworkModule {
public:
    virtual void Run(http::IRequestOutputQueue &requests, http::IResponseInputQueue &responses) = 0;

    virtual void Terminate() = 0;
};
```

We have two methods to implement, let's go!

## Create a network module

Okay, let's create our own class which inherits from `INetworkModule`.

```c++
#include "ziapi/Module.hpp"

class MyNetwork : public ziapi::INetworkModule {
public:
    void Run(http::IRequestOutputQueue &requests, http::IResponseInputQueue &responses) override;

    void Terminate() override;

private:
    Array<Client> clients;
    bool mustStop = false; // do a constructor, it's pseudo-code
};
```

First, let's implement the `Run()` method. It should contain the main loop on all the clients and handle incoming data, and / or send back responses back. It's pseudo-code, just to understand the purpose of the method.

```c++
void MyNetwork::Run(http::IRequestOutputQueue &requests, http::IResponseInputQueue &responses)
{
    Socket mainSocket = CreateSocket();

    while (true) {
        // Check for a new client
        if (mainSocket.HasNewConnection()) {
            clients.append(mainSocket.Accept());
        }
        // Trigger key to stop the server
        if (keyPressed("q")) {
            mustStop = true;
        }
        if (mustStop) {
            mainSocket.destroy();
            return;
        }
        // For each client, read incoming data
        for (int i = 0; i < clients.Size(); ++i) {
            if (clients[i].HasData()) {
                requests.Push(clients[i].GetData());
            }
        }
        // For each response, send data
        for (int i = 0; i < responses.Size(); ++i) {
            auto response = responses.Pop();

            // send the response to the right client
        }
        sleep(1);
    }
}
```

To end, let's implement `Terminate`. It should stop the running loop and may be useful in order to join threads.

```c++
void MyNetwork::Terminate()
{
    shouldStop = true;
    // join threads if there is
    // wait for modules to stop
}
```

The network module is now complete !