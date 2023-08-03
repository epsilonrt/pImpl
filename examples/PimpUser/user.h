// PimpUser example - User class header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimpUser class
// This example is compatible with Arduino, and is in the public domain

#pragma once
#include <pimp.h>
#include <Arduino.h>

// ----------------------------------------------------------------------------
// User class is a PimpClass with a private implementation.
class User : public PimpClass {
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
  protected:
    // Constructor with private implementation
    class Private;
    // This constructor must be used by derived classes
    User (Private &dd);
  private:
    // Declare d_func() macro for private implementation access
    PIMP_DECLARE_PRIVATE (User)
};