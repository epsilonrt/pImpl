# pimp
PImpl Idiom in C++ for platformio

When changes are made to a [header file](https://www.geeksforgeeks.org/difference-header-file-library/), all sources including it needs to be recompiled. In large projects and libraries, it can cause build time issues due to the fact that even when a small change to the implementation is made everyone has to wait some time until they compile their code. One way to solve this problem is by using the **PImpl Idiom**, which **hides the implementation in the headers and includes an interface file** that **compiles instantly**.

The PImpl Idiom **(Pointer to IMPLementation)** is a technique used for separating implementation from the interface. It minimizes header exposure and helps programmers to reduce build dependencies by moving the private data members in a separate class and accessing them through an [opaque pointer](https://www.geeksforgeeks.org/opaque-pointer/).

![](https://media.geeksforgeeks.org/wp-content/uploads/20190606163517/Header-and-Implementation-file-structure-within-the-PImpl-Idiom-2.jpg)

This library provides an implementation derived from the article [PImpl Idiom in C++ with Examples](https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/) and uses a [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr). 

Thus, this library **can only be used on platforms with an STL implementation** as it is the case for the [Arduino](https://www.arduino.cc/) frameworks for [ESP32](https://www.espressif.com/en/products/socs/esp32) and [ESP8266](https://www.espressif.com/en/products/socs/esp8266), [STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html), [Teensy 3 and more)[https://www.pjrc.com/teensy/] (but not for [AVR](https://www.microchip.com/design-centers/8-bit/avr-mcus) based platforms) and as well as for the [mbed](https://www.mbed.com/en/) framework, and for native PC, Linux, and Mac...

## The d-pointer

pimp is very strongly inspired by the implementation of the [Qt](https://www.qt.io/) library which uses a **d** pointer to the private class (implemantation) and a **q** pointer to the public class (API). The explanations below are taken from the [D-Pointer](https://wiki.qt.io/D-Pointer) page of the Qt wiki.

The trick is to keep the size of all public classes of a library constant by only storing a single pointer. This pointer points to a private/internal data structure that contains all the data. The size of this internal structure can shrink or grow without having any side-effect on the application because the pointer is accessed only in the library code and from the application's point of view the size of the object never changes - it's always the size of the pointer. This pointer is called the d-pointer.

The spirit of this pattern is outlined in the code below (all code in this article doesn't have destructors, of course you should add them in real code).

**widget.h**

```cpp
 /* 
  Since d_ptr is an unique pointer and is never referended in header file (it would cause a compile error) 
  Widget::Private doesn't have to be included, but forward-declared instead.
  The definition of the class can be written in widget.cpp or in a separate file, say widget_p.h 
 */
 
 class Widget
 {
     // ...
     Rect geometry() const;
     // ... 
 
 private:
     Class Private;
     std::unique_ptr<Private> d_ptr;
 };
```

**widget_p.h** which is the private header file of the widget class

```cpp
/* widget_p.h (_p means private) */
struct Widget::Private
{
    Rect geometry;
    std::string stylesheet;
};
```

**widget.cpp**

```cpp
// With this #include, we can access Widget::Private.
#include "widget_p.h"

Widget::Widget() : d_ptr(new Private)
{
    // Creation of private data
}

Rect Widget::geometry() const
{
    // The d-ptr is only accessed in the library code
    return d_ptr->geometry;
}
```

Next, there's an example of a child class based on Widget.

**label.h**

```cpp
class Label : public Widget
{
    // ...
    std::string text();

private:
     Class Private;
    // Each class maintains its own d-pointer
     std::unique_ptr<Private> d_ptr;
};
```

**label.cpp**

```cpp
// Unlike Widget::Private, the author decided Label::Private
// to be defined in the source file itself
struct Label::Private
{
    std::string text;
};

Label::Label() : d_ptr(new Private)
{
}

std::string Label::text()
{
    return d_ptr->text;
}
```

With the above structure, CuteApp never accesses the d-pointer directly. And since the d-pointer is only ever accessed in WidgetLib and WidgetLib is recompiled for every release, the Private class can freely change with no impact on CuteApp.

**Other benefits of d-pointer**  
It's not all about binary compatibility. The d-pointer has other benefits:

* Hide implementation details - We can ship WidgetLib with just the header files and the binaries. The .cpp files can be closed source.  
* The header file is clean of implementation details and can serve as the API reference.  
* Since the header files needed for implementation are moved from the header file into the implementation (source) file, compiles are much faster.  

It is indeed true that the above benefits appear trivial ;-) 

### The q-pointer

So far, we have only seen the d-pointer as a C-style data structure. In reality, it contains private methods (helper functions). For example, Label::Private might have a getLinkTargetFromPoint() helper function that is required to find the link target when the mouse is clicked. In many cases, these helper methods require access to the public class i.e some functions from Label or from its base class Widget. For example, a helper method, setTextAndUpdateWidget() might want to call Widget::update() which is a public method to schedule a redraw the Widget. So, the Widget::Private stores a pointer to the public class called the q-pointer. Modifying the code above for the q-pointer, we get:

**widget.h**

```cpp

class Widget::Private;

class Widget
{
    // ...
    Rect geometry() const;
    // ...
private:
     Class Private;
     std::unique_ptr<Private> d_ptr;
};
```

**widget_p.h**

```cpp
struct Widget::Private
{
    // Constructor that initializes the q-ptr
    Private(Widget *q) : q_ptr(q) { }
    Widget * const q_ptr; // q-ptr points to the API class
    Rect geometry;
    std::string stylesheet;
};
```

**widget.cpp**

```cpp
#include "widget_p.h"
// Create private data.
// Pass the 'this' pointer to initialize the q-ptr
Widget::Widget() : d_ptr(new Private(this))
{
}

Rect Widget::geometry() const
{
    // the d-ptr is only accessed in the library code
    return d_ptr->geometry;
}
```

Next, another class based on Widget.

**label.h**

```cpp
class Label : public Widget
{
    // ...
    std::string text() const;

private:
     Class Private;
     std::unique_ptr<Private> d_ptr;
};
```

**label.cpp**

```cpp
// Unlike Widget::Private, the author decided Label::Private
// to be defined in the source file itself
struct Label::Private
{
    Private(Label *q) : q_ptr(q) { }
    Label * const q_ptr;
    std::string text;
};

Label::Label() : d_ptr(new Private(this))
{
}

std::string Label::text()
{
    return d_ptr->text;
}
```

### Inheriting d-pointers for optimization

In the above code, creating a single Label results in the memory allocation for Label::Private and Widget::Private. If we were to employ this strategy, the situation becomes quite worse for classes like QListWidget - it is 6 levels deep in the class inheritance hierarchy and it would result in upto 6 memory allocations!

This is solved by having an inheritance hierarchy for our private classes and having the class getting instantiated pass on a the d-pointer all the way up.

Notice that when inheriting d-pointers, the declaration of the private class has to be in a separate file, for example widget_p.h. It's no longer possible to declare it in the widget.cpp file.

**widget.h**

```cpp
class Widget
{
public:
    Widget();
    // ...
protected:
    // only subclasses may access the below
    // allow subclasses to initialize with their own concrete Private
    Class Private;
    Widget(Private &dd);
    std::unique_ptr<Private> d_ptr;
};
```

**widget_p.h**

```cpp
struct Widget::Private
{
    Private(Widget *q) : q_ptr(q) { } // constructor that initializes the q-ptr
    Widget * const q_ptr; // q-ptr that points to the API class
    Rect geometry;
    std::string stylesheet;
};
```

**widget.cpp**

```cpp
Widget::Widget() : d_ptr(new Private(this))
{
}

Widget::Widget(Private &dd) : d_ptr(&dd)
{
}
```

**label.h**

```cpp
class Label : public Widget
{
public:
    Label();
    // ...
protected:
    Class Private;
    Label(Private &dd); // allow Label subclasses to pass on their Private
    // notice how Label does not have a d_ptr! It just uses Widget's d_ptr.
};
```

**label.cpp**

```cpp
#include "widget_p.h"

class Label::Private : public Widget::Private
{
  public:
    std::string text;
};

Label::Label()
 : Widget(*new Private) // initialize the d-pointer with our own Private
{
}

Label::Label(Label::Private &dd) : Widget(dd)
{
}
```

Do you see the beauty? When we now create a Label object, it will create a Label::Private (which subclasses Widget::Private). It passes on the concrete d-pointer to Widget's protected constructor! Now, when a Label object is created, there is only one memory allocation. Label also has a protected constructor that can be used by its subclasses to provide their own private classes.

## d-pointers with pimp library

### PIMP_D and PIMP_Q

A side effect of the optimization that we did in the previous step is that the q-ptr and d-ptr are of type Widget and Widget::Private. This means that the following won't work.

**label.cpp**

```cpp
void Label::setText(const std::string &text)
{
   // won't work! since d_ptr is of type Label::Private even though it points to Widget::Private object
   d_ptr->text = text;
}

// Hence, when accessing the d-pointer in a subclass, we need to static_cast to the appropriate type.

void Label::setText(const std::string &text)
{
    Private *d = static_cast<Private*>(d_ptr); // cast to our private type
    d->text = text;
}
```

As you can see, it's not pretty having static_cast all over the place. Instead, there are two macros defined in pimp.h which make it straighforward:

**pimp.h**

```cpp
#define PIMP_D(Class) Class::Private * const d = d_func()
#define PIMP_Q(Class) Class * const q = q_func()
```

The PIMP_D macro casts the d-ptr to the appropriate type and assigns it to a local variable d. The PIMP_Q macro casts the this pointer to the appropriate type and assigns it to a local variable q. The PIMP_Q macro is useful when you need to access the public members of the class from the private class. For example, if you need to call a public slot from a private function, you can use the PIMP_Q macro to get access to the public members.

**label.cpp**

```cpp
// With PIMP_D you can use the members of Label::Private from Label
void Label::setText(const std::string &text)
{
    PIMP_D(Label);
    d->text = text;
}

// With PIMP_Q you can use the members of Label from Label::Private
void Label::Private::someHelperFunction()
{
    PIMP_Q(Label);
    q->selectAll();
}
```

### PIMP_DECLARE_PRIVATE and PIMP_DECLARE_PUBLIC

You may use **PIMP_DECLARE_PRIVATE** macro in the public class. The macro reads:

**pimp.h**

```cpp
#define PIMP_DECLARE_PRIVATE(Class)\
  inline Class::Private* d_func() {\
    return reinterpret_cast<Class::Private*>(d_ptr.get());\
  }\
  inline const Class::Private* d_func() const {\
    return reinterpret_cast<const Class::Private *>(d_ptr.get());\
  }\
  friend class Class::Private;
```

This macro can be used this way:

**label.h**

```cpp
class Label
{
public:
    Label();
    // ...
protected:
    Class Private;
    Label(Private &dd);
private:
    PIMP_DECLARE_PRIVATE(Label)
};
```

The idea is that Label provides a function d_func() that allows access to its private internal class. The method itself is private (since the macro is inside a private section in label.h). The d_func() can however be invoked by **friends** (C++ friend) of Label. 

The d_func also has the advantage to enforce const-correctness: In a const member function of MyClass  you need a PIMP_D(const MyClass) and thus you can only call const member functions in MyClass::Private. With a naked d_ptr you could also call non-const functions.
