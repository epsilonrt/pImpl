// PimplSingleton example for PlatformIO, Native platform
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class with a 
// singleton class in the private implementation.
// See user.h, user_p.h and user.cpp for more details
// This example is in the public domain

#include <iostream>
#include "user.h"

// user is a User object with a private implementation
// User::Private implementation has a singleton object Engine
// See user_p.h and user.cpp in this directory for more details
User user ("John Doe", 42);

// duser is a DerivedUser object with a private implementation
// Derived class is derived from User class
// DerivedUser::Private implementation should have the same instance 
// of the Engine singleton as the user object.
// See user_p.h and user.cpp in this directory for more details
DerivedUser duser ("Pascal JEAN, aka epsilonRT", 57, "Somewhere in France");

int main() {

  // check if the private implementation has access to the API class
  std::cout << "Parent Access: " << (duser.checkParentAccess() ? "Ok" : "Failed!") << std::endl;
  // check if the private implementations has access to the same singleton
  std::cout << "Singleton check: " << (duser.checkHasSameEngine(user) ? "Ok" : "Failed!") << std::endl;
  return 0;
}
