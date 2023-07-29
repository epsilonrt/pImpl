# pimp
PImpl Idiom in C++ for platformio

When changes are made to a [header file](https://www.geeksforgeeks.org/difference-header-file-library/), all sources including it needs to be recompiled. In large projects and libraries, it can cause build time issues due to the fact that even when a small change to the implementation is made everyone has to wait some time until they compile their code. One way to solve this problem is by using the **PImpl Idiom**, which **hides the implementation in the headers and includes an interface file** that **compiles instantly**.

The PImpl Idiom **(Pointer to IMPLementation)** is a technique used for separating implementation from the interface. It minimizes header exposure and helps programmers to reduce build dependencies by moving the private data members in a separate class and accessing them through an [opaque pointer](https://www.geeksforgeeks.org/opaque-pointer/).

![](https://media.geeksforgeeks.org/wp-content/uploads/20190606163517/Header-and-Implementation-file-structure-within-the-PImpl-Idiom-2.jpg)

This library provides an implementation derived from the article [PImpl Idiom in C++ with Examples](https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/) and uses a [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr). Thus, this library can only be used on platforms with an STL implementation.

## d-pointers with pimp library

pimp is very strongly inspired by the implementation of the [Qt](https://wiki.qt.io/D-Pointer) library which uses a **d** pointer to the private class and a **q** pointer to the public class.

### PIMP_D and PIMP_Q

A side effect of the optimization that we did in the previous step is that the q-ptr and d-ptr are of type MyClass and MyClassPrivate. This means that the following won't work.

_myclass.cpp_

```cpp
void MyClass::setText(const String &text)
{
   // won't work! since d_ptr is of type MyClassPrivate even though
   // it points to MyClassPrivate object
   d_ptr->text = text;
}

// Hence, when accessing the d-pointer in a subclass, we need to static_cast to the appropriate type.

void MyClass::setText(const String &text)
{
    MyClassPrivate *d = static_cast<MyClassPrivate*>(d_ptr); // cast to our private type
    d->text = text;
}
```

As you can see, it's not pretty having static_cast all over the place. Instead, there are two macros defined in pimp.h which make it straighforward:

_pimp.h_

```cpp
#define PIMP_D(Class) Class::Private * const d = d_func()
#define PIMP_Q(Class) Class * const q = q_func()
```

The PIMP_D macro casts the d-ptr to the appropriate type and assigns it to a local variable d. The PIMP_Q macro casts the this pointer to the appropriate type and assigns it to a local variable q. The PIMP_Q macro is useful when you need to access the public members of the class from the private class. For example, if you need to call a public slot from a private function, you can use the PIMP_Q macro to get access to the public members.

_myclass.cpp_

```cpp
// With PIMP_D you can use the members of MyClassPrivate from MyClass
void MyClass::setText(const String &text)
{
    PIMP_D(MyClass);
    d->text = text;
}

// With PIMP_Q you can use the members of MyClass from MyClassPrivate
void MyClassPrivate::someHelperFunction()
{
    PIMP_Q(MyClass);
    q->selectAll();
}
```

### PIMP_DECLARE_PRIVATE and PIMP_DECLARE_PUBLIC

You can use PIMP_DECLARE_PRIVATE macro in the public class. The macro reads:

_pimp.h_

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

_myclass.h_

```cpp
class MyClass
{
private:
    PIMP_DECLARE_PRIVATE(MyClass)
};
```

The idea is that MyClass provides a function d_func() that allows access to its private internal class. The method itself is private (since the macro is inside a private section in myclass.h). The d_func() can however be invoked by friends (C++ friend) of MyClass. This is primarily useful for access of information by pimp classes which cannot get access of some MyClass information using public api. As a bizarre example, MyClass might keep track of how many times the user has clicked on a link. However, there is no public API to access this information. A pimp class might want to access this information and display it in a tooltip. The pimp class can then use d_func() to get access to the private information.

The d_func also has the advantage to enforce const-correctness: In a const member function of MyClass you need a PIMP_D(const MyClass) and thus you can only call const member functions in MyClassPrivate. With a naked d_ptr you could also call non-const functions.
