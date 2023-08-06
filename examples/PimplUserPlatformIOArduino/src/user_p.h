// PimplUser example - User class private header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class
// This example is compatible with Arduino, and is in the public domain

#pragma once
#include <pImpl_p.h>
#include "user.h"

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
    // Declare q_func() macro for API class access
    PIMPL_DECLARE_PUBLIC (User)
};