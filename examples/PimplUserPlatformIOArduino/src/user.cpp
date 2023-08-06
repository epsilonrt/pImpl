// PimplUser example - User class implementation
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class
// This example is compatible with Arduino, and is in the public domain

#include "user_p.h"

// ----------------------------------------------------------------------------
// User::Private implementation
// ----------------------------------------------------------------------------

// Constructor that is called by User class for creating the private implementation
// Initializes the private attributes
User::Private::Private (User *q) : PimplClass::Private (q), age (0) {}

// Checks the parent access from the private implementation
bool User::Private::checkParentAccess() const {
  PIMPL_Q (const User);
  return q->name() == name && q->age() == age;
}

// ----------------------------------------------------------------------------
// User class implementation
// ----------------------------------------------------------------------------

// Default constructor
// Call the protected constructor with private implementation
User::User() : PimplClass (*new Private (this)) {
}

// Protected constructor with private implementation
User::User (Private &dd) : PimplClass (dd) {
}

// Constructor with parameters
User::User (const String &name, int age) : User() {
  PIMPL_D (User);
  d->name = name;
  d->age = age;
}

// ----------------------------------------------------------------------------
// Public API
// ----------------------------------------------------------------------------

// Returns the name
String User::name() const {
  PIMPL_D (const User);
  return d->name;
}

// Returns the age
int User::age() const {
  PIMPL_D (const User);
  return d->age;
}

// Sets the age
void User::setAge (int age) {
  PIMPL_D (User);
  d->age = age;
}

// Sets the name
void User::setName (const String &name) {
  PIMPL_D (User);
  d->name = name;
}

// Checks the parent access from the private implementation
// for testing purpose
// call the private implementation method passing by the PIMPL_D(const User) macro
bool User::checkParentAccess() const {
  PIMPL_D (const User);
  return d->checkParentAccess();
}
