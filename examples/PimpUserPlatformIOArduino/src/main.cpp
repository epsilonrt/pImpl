
// PimpUser example for PlatformIO, Arduino platform
// Created by Pascal JEAN aka epsilonRT, August 2023
// This example shows how to use the PimpUser class
// See user.h, user_p.h and user.cpp for more details
// This example is compatible with Arduino, and is in the public domain

// Define the API User class
#include "user.h"

// Create an instance of User class
User user ("John Doe", 42);


void setup() {
  Serial.begin (115200);
  while (!Serial);
  // check if the private implementation has access to the API class
  Serial.println ("\nParent Access: " + String (user.checkParentAccess() ? "Ok" : "Failed!"));
  // print the user name and age
  Serial.println ("User name: " + user.name());
  Serial.println ("User age: " + String (user.age()));
  // change the user name and age
  user.setName ("Pascal JEAN, aka epsilonRT");
  user.setAge (57);
  // print the user name and age
  Serial.println ("User name: " + user.name());
  Serial.println ("User age: " + String (user.age()));
}

void loop() {
}
