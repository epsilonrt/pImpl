// PimplUser example for PlatformIO, Native platform
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimplUser class
// See user.h, user_p.h and user.cpp for more details
// This example is in the public domain


#include <iostream>
#include "user.h"

User user ("John Doe", 42);

int main() {
  // check if the private implementation has access to the API class
  std::cout << "Parent Access: " << (user.checkParentAccess() ? "Ok" : "Failed!") << std::endl;
  // print the user name and age
  std::cout << "User name: " <<  user.name() << std::endl;
  std::cout << "User age: " <<  user.age() << std::endl;
  // change the user name and age
  user.setName ("Pascal JEAN, aka epsilonRT");
  user.setAge (57);
  // print the user name and age
  std::cout << "User name: " <<  user.name() << std::endl;
  std::cout << "User age: " <<  user.age() << std::endl;
  return 0;
}
