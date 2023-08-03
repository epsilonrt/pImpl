// PimpUser example - User class header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimpUser class
// This example is compatible with PlatformIO for native platform, and is in the public domain

#pragma once
#include <pimp.h>
#include <string>

// ----------------------------------------------------------------------------
// User class is a PimpClass with a private implementation.
class User : public PimpClass {
  public:
    // Default constructor
    User();
    // Constructor with parameters
    User (const std::string &name, int age);
    // Returns the name
    std::string name() const;
    // Returns the age
    int age() const;
    // Sets the age
    void setAge (int age);
    // Sets the name
    void setName (const std::string &name);
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