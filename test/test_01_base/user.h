// PimplUser example - User class header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class
// This example is compatible with PlatformIO for native platform, and is in the public domain

#pragma once
#include <pImpl.h>
#ifdef ARDUINO
#include <Arduino.h>
typedef String string_t;
#else
#include <string>
typedef std::string string_t;
#endif

// ----------------------------------------------------------------------------
// User class is a PimplClass with a private implementation.
class User : public PimplClass {
  public:
    // Default constructor
    User();
    // Constructor with parameters
    User (const string_t &name, int age);
    // Returns the name
    string_t name() const;
    // Returns the age
    int age() const;
    // Sets the age
    void setAge (int age);
    // Sets the name
    void setName (const string_t &name);
    // Checks the parent access from the private implementation
    bool checkParentAccess() const;
  protected:
    // Constructor with private implementation
    class Private;
    // This constructor must be used by derived classes
    User (Private &dd);
  protected:
    // Declare d_func() macro for private implementation access
    PIMPL_DECLARE_PRIVATE (User)
};

// ----------------------------------------------------------------------------
// DerivedUser class is a User class with a private implementation.
class DerivedUser : public User {
  public:
    // Default constructor
    DerivedUser();
    // Constructor with parameters
    DerivedUser (const string_t &name, int age, const string_t &address);
    // Returns the address
    string_t address() const;
    // Sets the address
    void setAddress (const string_t &address);
  protected:
    // Constructor with private implementation
    class Private;
    // This constructor must be used by derived classes
    DerivedUser (Private &dd);
  private:
    // Declare d_func() macro for private implementation access
    PIMPL_DECLARE_PRIVATE (DerivedUser)
};