/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#include <memory>

#pragma once

/*
   Internal: Pointer to implementation
   "Pointer to implementation" or "pImpl" is a C++ programming technique that
   removes implementation details of a class from its object representation by
   placing them in a separate class, accessed through an opaque pointer.
   This technique is used to construct C++ library interfaces with stable
   ABI and to reduce compile-time dependencies.
*/
#define PIMP_D(Class) Class::Private * const d = d_func()
#define PIMP_Q(Class) Class * const q = q_func()
#define PIMP_DECLARE_PRIVATE(Class)\
  inline Class::Private* d_func() {\
    return reinterpret_cast<Class::Private*>(d_ptr.get());\
  }\
  inline const Class::Private* d_func() const {\
    return reinterpret_cast<const Class::Private *>(d_ptr.get());\
  }\
  friend class Class::Private;
#define PIMP_DECLARE_PUBLIC(Class) \
  inline Class* q_func() { return reinterpret_cast<Class *>(q_ptr); } \
  inline const Class* q_func() const { return reinterpret_cast<const Class *>(q_ptr); } \
  friend class Class;

class PimpClass {
  public:
    // no public constructor, only subclasses may be instantiated

    // default destructor, not default destructor because of the unique_ptr is used :
    // https://en.cppreference.com/w/cpp/memory/unique_ptr
    // std::unique_ptr may be constructed for an incomplete type T, such as to 
    // facilitate the use as a handle in the pImpl idiom. If the default deleter 
    // is used, T must be complete at the point in code where the deleter is 
    // invoked, which happens in the destructor, move assignment operator, 
    // and reset member function of std::unique_ptr. 
    virtual ~PimpClass ();
  protected:
    // only subclasses may access the below
    // allow subclasses to initialize with their own concrete Private
    class Private;

    PimpClass (Private &dd);
    std::unique_ptr<Private> d_ptr;
};
