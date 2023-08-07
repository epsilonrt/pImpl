// PimplSingleton example - User class private header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class with a 
// singleton class in the private implementation.
// This example is in the public domain
#pragma once
#include <pImpl_p.h>
#include "user.h"

// Engine class is a singleton
// for showing how to use a singleton with PimplClass
class Engine : public Singleton<Engine> {
    friend class Singleton<Engine>;
  public:
    int foo;
    static const int bar = 42;
  private:
    Engine();
};

// Private implementation of User class
// This class is not exported and is only used by User class
// It is derived from PimplClass::Private to allow access to the API class with PIMPL_Q() macro
class User::Private : public PimplClass::Private {
  public:
    // Constructor call by User class for creating the private implementation
    Private (User *q);
    // Checks the parent access from the private implementation
    bool checkParentAccess() const;
    // Private attributes
    String name;
    int age;
    Engine & engine; // Singleton
    // Declare q_func() macro for API class access
    PIMPL_DECLARE_PUBLIC (User)
};

class DerivedUser::Private : public User::Private {
  public:
    // Constructor call by DerivedUser class for creating the private implementation
    Private (DerivedUser *q);
    // Private attributes
    String address;
    // Declare q_func() macro for API class access
    PIMPL_DECLARE_PUBLIC (DerivedUser)
};