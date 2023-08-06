// PimplUser example - User class header
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class
// This example is compatible with PlatformIO for native platform, and is in the public domain

#pragma once
#include <pImpl.h>
#include <string>

// ----------------------------------------------------------------------------
// User class is a PimplClass with a private implementation.
class User : public PimplClass {
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
    PIMPL_DECLARE_PRIVATE (User)
};