// PimplSingleton example for PlatformIO, Native platform
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class with a
// singleton class in the private implementation.
// See user.h, user_p.h and user.cpp for more details
// This example is in the public domain

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

void setup() {
  Serial.begin (115200);
  // delay (2000);
  while(!Serial);

  // check if the private implementation has access to the API class
  Serial.println ("\nParent Access: " + String (duser.checkParentAccess() ? "Ok" : "Failed!"));
  // check if the private implementations has access to the same singleton
  Serial.println ("Singleton check: " + String (duser.checkHasSameEngine (user) ? "Ok" : "Failed!"));
}

void loop() {
}
