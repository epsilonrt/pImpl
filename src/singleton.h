/*
   Copyright (c) 2023, Pascal JEAN aka epsilonrt
   All rights reserved.

   SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef DOXYGEN
#define SINGLETON_I(Class) Class & i = Class::instance()
#endif // DOXYGEN

/**
   @brief Singleton class

   How to use:
   @code
   class Foo : public Singleton<Foo> {
    friend class Singleton<Foo>;
   public:
    // No need to define a constructor, destructor, copy constructor and assignment operator
    void bar() { ... }
   private:
    Foo() {}
   };
   @endcode

   @tparam T the class to be singleton
*/
template<typename T>
class Singleton {
  public:
    /**
       @brief Get the instance object

       @return T&  The unique instance
    */
    static T &instance();

    /**
       @brief Make the class non construction-copyable and non copyable
    */
    Singleton (const Singleton &) = delete;
    /**
       @brief Make the class non copyable
    */
    Singleton &operator= (const Singleton) = delete; // non copyable

  protected:
    Singleton() {}
};

template<typename T>
T &Singleton<T>::instance() {
  static T instance;
  return instance;
}

#ifdef DOXYGEN
/**
   @brief Define a reference \c i to the unique instance of a singleton class \c Class

   Allowing to use \c i instead of \c Class::instance() for more readability
*/
#define SINGLETON_I(Class)
#endif // DOXYGEN
