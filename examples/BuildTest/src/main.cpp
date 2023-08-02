

#include "user.h"

User user ("John Doe", 42);

#ifndef ARDUINO
//-----------------------------------------------------------------------------
#include <iostream>
int main() {
  std::cout << "Parent Access: " << (user.checkParentAccess() ? "Ok" : "Failed!") << std::endl;
  std::cout << "User name: " <<  user.name() << std::endl;
  std::cout << "User age: " <<  user.age() << std::endl;
  return 0;
}
#else
//-----------------------------------------------------------------------------
void setup() {
  Serial.begin (115200);
  while (!Serial);
  Serial.println ("\nParent Access: " + String (user.checkParentAccess() ? "Ok" : "Failed!"));
  Serial.println ("User name: " + user.name());
  Serial.println ("User age: " + String (user.age()));
}
void loop() {
}
#endif