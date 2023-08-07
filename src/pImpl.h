/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#pragma once
#include <memory>
#include "./singleton.h"

#ifndef DOXYGEN
#define PIMPL_D(Class) Class::Private * const d = d_func()
#define PIMPL_Q(Class) Class * const q = q_func()
#define PIMPL_DECLARE_PRIVATE(Class)\
  inline Class::Private* d_func() {\
    return reinterpret_cast<Class::Private*>(d_ptr.get());\
  }\
  inline const Class::Private* d_func() const {\
    return reinterpret_cast<const Class::Private *>(d_ptr.get());\
  }\
  friend class Class::Private;
#define PIMPL_DECLARE_PUBLIC(Class) \
  inline Class* q_func() { return reinterpret_cast<Class *>(q_ptr); } \
  inline const Class* q_func() const { return reinterpret_cast<const Class *>(q_ptr); } \
  friend class Class;
#endif

/**
 * @brief PimplClass
 * 
 * PimplClass is the base class for the pImpl idiom.
 * 
 * The pImpl idiom is used to hide the private implementation of a class from clients.
 * It also enables binary compatibility between releases.
 * 
 * There is no public constructor, only subclasses may be instantiated.
 * This prevents the instantiation of the base class.
 */
class PimplClass {
  public:
    /**
     * @brief Destroy the PimplClass object
     * 
     * Using a unique_ptr that points to a private class that is not fully defined 
     * requires not using the default destructor implementation.
     * Must be virtual to allow subclasses to be deleted through a pointer to the base class.
     */
    virtual ~PimplClass ();
  
  protected:
    /**
     * @brief The private class
     * 
     * The private class encapsulates all data and methods that are hidden from the user.
     * Allow subclasses to initialize with their own concrete Private class.
     * It is defined in the pImpl_p.h file.
     */
    class Private;

    /**
     * @brief Construct a new PimplClass object
     * 
     * This constructor must be used by subclasses to initialize the private class.
     * 
     * @param dd reference to the private class
     */
    PimplClass (Private &dd);

    /**
     * @brief The private class pointer
     * 
     * The private class pointer is a unique_ptr that points to the private class. 
     * unique_ptr is used to ensure that the private class is deleted when the API class is deleted.
     * Thus the private class is deleted when the last reference to the API class is deleted, no matter how it is deleted.
     */
    std::unique_ptr<Private> d_ptr;
};

#ifdef DOXYGEN
/**
 * @brief PIMPL_D
 * 
 * Provides a d pointer to the private class, use d_func() to access it which is defined in PIMPL_DECLARE_PRIVATE.
 * If you want to access the private class from a const method, use const_cast as in the following example:
 * @code
 * void MyClass::foo() const
 * {
 *   PIMPL_D(const MyClass);
 *   d->bar();
 * }
 * @endcode
 * 
 * @param Class the API class name
 */
#define PIMPL_D(Class)

/**
 * @brief PIMPL_Q
 * 
 * Provides a q pointer to the API class, use q_func() to access it which is defined in PIMPL_DECLARE_PUBLIC.
 * If you want to access the API class from a const method, use const_cast as in the following example:
 * @code
 * void MyClass::Private::foo() const
 * {
 *   PIMPL_Q(const MyClass);
 *   q->bar();
 * }
 * @endcode
 * 
 * @param Class the API class name
 */
#define PIMPL_Q(Class)

/**
 * @brief PIMPL_DECLARE_PRIVATE
 * 
 * Provides d_func() to access the private class, must be added in the private section of the API class, as in the following example:
 * @code
 * class MyClass : public PimplClass {
 *  PIMPL_DECLARE_PRIVATE(MyClass)
 * public:
 *  void foo();
 * };
 * @endcode
 * 
 * @param Class the API class name
 */
#define PIMPL_DECLARE_PRIVATE(Class)

/**
 * @brief PIMPL_DECLARE_PUBLIC
 * 
 * Provides q_func() to access the API class, must be added in the public section of the private class, as in the following example:
 * @code
 * class MyClass::Private : public PimplClass::Private {
 *  PIMPL_DECLARE_PUBLIC(MyClass)
 * public:
 *  void foo();
 * };
 * @endcode
 * 
 * @param Class the API class name
 */
#define PIMPL_DECLARE_PUBLIC(Class)
#endif

