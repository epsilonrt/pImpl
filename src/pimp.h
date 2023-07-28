/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#pragma once

#include <memory>

/*
 * Internal: Pointer to implementation
 * "Pointer to implementation" or "pImpl" is a C++ programming technique that
 * removes implementation details of a class from its object representation by
 * placing them in a separate class, accessed through an opaque pointer.
 * This technique is used to construct C++ library interfaces with stable
 * ABI and to reduce compile-time dependencies.
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

/* ========================================================================== */
