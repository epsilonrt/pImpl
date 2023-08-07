// PimplSingleton example - User class private header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class with a 
// singleton class in the private implementation.
// This example is in the public domain

#include "user_p.h"

// ----------------------------------------------------------------------------
// Engine class implementation
// ----------------------------------------------------------------------------
Engine::Engine() : foo (bar) {}

// ----------------------------------------------------------------------------
// User::Private implementation
// ----------------------------------------------------------------------------

// Constructor that is called by User class for creating the private implementation
// Initializes the private attributes
User::Private::Private (User *q) : PimplClass::Private (q), age (0), engine (Engine::instance()) {}

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

// Checks if other user has the same engine
bool User::checkHasSameEngine (User &u) {
  PIMPL_D (const User);
  User::Private *other = u.d_func();

  // check if all instances have the same engine instance
  if (&d->engine != &other->engine) {
    return false;
  }

  // check if foo are initialized with bar value
  if (d->engine.foo != d->engine.bar) {
    return false;
  }
  // check if all instances have the same foo value
  if (d->engine.foo != other->engine.foo) {
    return false;
  }

  d->engine.foo = 0; // change foo value with this instance
  // check if all instances have the same foo value
  if (d->engine.foo != other->engine.foo) {
    return false;
  }

  other->engine.foo = 7; // change foo value with other instance
  // check if all instances have the same foo value
  if (d->engine.foo != other->engine.foo) {
    return false;
  }

  return true;
}

// ----------------------------------------------------------------------------
// DerivedUser::Private implementation
// ----------------------------------------------------------------------------
// Constructor that is called by DerivedUser class for creating the private implementation
// Initializes the private attributes
DerivedUser::Private::Private (DerivedUser *q) : User::Private (q) {}

// ----------------------------------------------------------------------------
// DerivedUser class implementation
// ----------------------------------------------------------------------------
// Default constructor
// Call the protected constructor with private implementation
DerivedUser::DerivedUser() : User (*new Private (this)) {}

// Constructor with parameters
DerivedUser::DerivedUser (const String &name, int age, const String &address) : User (*new Private (this)) {
  PIMPL_D (DerivedUser);
  d->name = name;
  d->age = age;
  d->address = address;
}

// Protected constructor with private implementation
DerivedUser::DerivedUser (Private &dd) : User (dd) {}

// ----------------------------------------------------------------------------
// Public API
// ----------------------------------------------------------------------------
// Returns the address
String DerivedUser::address() const {
  PIMPL_D (const DerivedUser);
  return d->address;
}

// Sets the address
void DerivedUser::setAddress (const String &address) {
  PIMPL_D (DerivedUser);
  d->address = address;
}

