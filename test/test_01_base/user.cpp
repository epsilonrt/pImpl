// PimplUser example - User class implementation
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class
// This example is compatible with PlatformIO for native platform, and is in the public domain

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
User::User (const string_t &name, int age) : User() {
  PIMPL_D (User);
  d->name = name;
  d->age = age;
}

// ----------------------------------------------------------------------------
// Public API
// ----------------------------------------------------------------------------

// Returns the name
string_t User::name() const {
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
void User::setName (const string_t &name) {
  PIMPL_D (User);
  d->name = name;
}

// Clear or reset the object
void User::clear() {
  if (isNull()) {

    d_ptr.reset (new Private (this));
  }
  else {
    PIMPL_D (User);

    d->name = "";
    d->age = 0;
  }
}

// Checks the parent access from the private implementation
// for testing purpose
// call the private implementation method passing by the PIMPL_D(const User) macro
bool User::checkParentAccess() const {
  PIMPL_D (const User);
  return d->checkParentAccess();
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
DerivedUser::DerivedUser (const string_t &name, int age, const string_t &address) : User (*new Private (this)) {
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
string_t DerivedUser::address() const {
  PIMPL_D (const DerivedUser);
  return d->address;
}

// Sets the address
void DerivedUser::setAddress (const string_t &address) {
  PIMPL_D (DerivedUser);
  d->address = address;
}

