/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/
#include <memory>

#pragma once

#ifdef DOXYGEN
/**
 * @brief PIMP_D
 * 
 * Provides a d pointer to the private class, use d_func() to access it which is defined in PIMP_DECLARE_PRIVATE.
 * If you want to access the private class from a const method, use const_cast as in the following example:
 * @code
 * void MyClass::foo() const
 * {
 *   PIMP_D(const MyClass);
 *   d->bar();
 * }
 * @endcode
 * 
 * @param Class the API class name
 */
#define PIMP_D(Class)

/**
 * @brief PIMP_Q
 * 
 * Provides a q pointer to the API class, use q_func() to access it which is defined in PIMP_DECLARE_PUBLIC.
 * If you want to access the API class from a const method, use const_cast as in the following example:
 * @code
 * void MyClass::Private::foo() const
 * {
 *   PIMP_Q(const MyClass);
 *   q->bar();
 * }
 * @endcode
 * 
 * @param Class the API class name
 */
#define PIMP_Q(Class)

/**
 * @brief PIMP_DECLARE_PRIVATE
 * 
 * Provides d_func() to access the private class, must be added in the private section of the API class, as in the following example:
 * @code
 * class MyClass : public PimpClass {
 *  PIMP_DECLARE_PRIVATE(MyClass)
 * public:
 *  void foo();
 * };
 * 
 * @param Class the API class name
 */
#define PIMP_DECLARE_PRIVATE(Class)

/**
 * @brief PIMP_DECLARE_PUBLIC
 * 
 * Provides q_func() to access the API class, must be added in the public section of the private class, as in the following example:
 * @code
 * class MyClass::Private : public PimpClass::Private {
 *  PIMP_DECLARE_PUBLIC(MyClass)
 * public:
 *  void foo();
 * };
 */
#define PIMP_DECLARE_PUBLIC(Class)
#else
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
#endif

/**
 * @brief PimpClass is the base class for the pimpl idiom
 * 
 * The pimpl idiom is used to hide the private implementation of a class from clients.
 * It also enables binary compatibility between releases.
 */
class PimpClass {
  public:
    /**
     * @function PimpClass
     * @brief Default constructor
     * There is no public constructor, only subclasses may be instantiated.
     * This prevents the instantiation of the base class.
     */

    /**
     * @brief Destroy the Pimp Class object
     * 
     * Using a unique_ptr that points to a private class that is not fully defined 
     * requires not using the default destructor implementation.
     * Must be virtual to allow subclasses to be deleted through a pointer to the base class.
     */
    virtual ~PimpClass ();
  
  protected:
    /**
     * @brief The private class
     * 
     * The private class encapsulates all data and methods that are hidden from the user.
     * Allow subclasses to initialize with their own concrete Private class.
     * It is defined in the pimp_p.h file.
     */
    class Private;

    /**
     * @brief Construct a new Pimp Class object
     * 
     * This constructor must be used by subclasses to initialize the private class.
     * 
     * @param dd reference to the private class
     */
    PimpClass (Private &dd);

    /**
     * @brief The private class pointer
     * 
     * The private class pointer is a unique_ptr that points to the private class. 
     * unique_ptr is used to ensure that the private class is deleted when the API class is deleted.
     * Thus the private class is deleted when the last reference to the API class is deleted, no matter how it is deleted.
     */
    std::unique_ptr<Private> d_ptr;
};
