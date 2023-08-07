// PimplSingleton example - User class private header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class with a 
// singleton class in the private implementation.
// This example is in the public domain

#pragma once
#include <Arduino.h>
#include <pImpl.h>


// ----------------------------------------------------------------------------
// User class is a PimplClass with a private implementation.
class User : public PimplClass {
  public:
    // Default constructor
    User();
    // Constructor with parameters
    User (const String &name, int age);
    // Returns the name
    String name() const;
    // Returns the age
    int age() const;
    // Sets the age
    void setAge (int age);
    // Sets the name
    void setName (const String &name);
    // Checks the parent access from the private implementation
    bool checkParentAccess() const;
    // Checks if other user has the same engine
    bool checkHasSameEngine (User &other);
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
    DerivedUser (const String &name, int age, const String &address);
    // Returns the address
    String address() const;
    // Sets the address
    void setAddress (const String &address);
  protected:
    // Constructor with private implementation
    class Private;
    // This constructor must be used by derived classes
    DerivedUser (Private &dd);
  private:
    // Declare d_func() macro for private implementation access
    PIMPL_DECLARE_PRIVATE (DerivedUser)
};