# pimp
PImpl Idiom in C++ for platformio

When changes are made to a [header file](https://www.geeksforgeeks.org/difference-header-file-library/), all sources including it needs to be recompiled. In large projects and libraries, it can cause build time issues due to the fact that even when a small change to the implementation is made everyone has to wait some time until they compile their code. One way to solve this problem is by using the **PImpl Idiom**, which **hides the implementation in the headers and includes an interface file** that **compiles instantly**.

The PImpl Idiom **(Pointer to IMPLementation)** is a technique used for separating implementation from the interface. It minimizes header exposure and helps programmers to reduce build dependencies by moving the private data members in a separate class and accessing them through an [opaque pointer](https://www.geeksforgeeks.org/opaque-pointer/).

![](https://media.geeksforgeeks.org/wp-content/uploads/20190606163517/Header-and-Implementation-file-structure-within-the-PImpl-Idiom-2.jpg)

This library provides an implementation derived from the article [PImpl Idiom in C++ with Examples](https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/) and uses a [std::unique_ptr ](https://en.cppreference.com/w/cpp/memory/unique_ptr). Thus, this library can only be used on platforms with an STL implementation.

It is also very strongly inspired by the implementation of the library [Qt](https://wiki.qt.io/D-Pointer) which uses a **d** pointer to the private class and a **q** pointer to the public class.

## The public API

Here is a simplified example of the [Device](https://github.com/epsilonrt/libmodbuspp/blob/master/include/modbuspp/device.h) class from the [libmosbuspp](https://github.com/epsilonrt/libmodbuspp) library.

```cpp
#include <pimp.h>

  class Device  {
    public:
      Device ();
      virtual ~Device();
      virtual bool open();
      virtual void close();
      virtual bool isOpen() const;
      bool isConnected() const;

    protected:
      class Private;
      Device (Private &dd);
      std::unique_ptr<Private> d_ptr;

    private:
      PIMP_DECLARE_PRIVATE (Device)
  };
```

As can be seen above, only the prototypes of the methods needed to use the **Device** class are exposed to the user. The protected and private blocks only contain the elements necessary for the **Pimpl idiom**, this syntax will have to be added to each class wishing to use it.

## The implemantation

```cpp
  class Device::Private {

    public:
      Private (Device * q);
      virtual ~Private();
      virtual bool open();
      virtual void close();
      bool isConnected () const;

      Device * const q_ptr;
      bool isOpen;
      PIMP_DECLARE_PUBLIC (Device)
  };

  Device::Private::Private (Device * q) :
    q_ptr (q), isOpen (false) {}

  Device::Private::~Private() {}
```
