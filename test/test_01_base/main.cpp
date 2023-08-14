//
// Unit Test for the class PimplClass
//
#include <unity.h>
#include <string.h>
#include "user.h"

void setUp (void) {
  // set stuff up here
}

void tearDown (void) {
  // clean stuff up here
}

void test_user_default_constructor (void) {
  User u;

  TEST_ASSERT_FALSE (u.isNull());
  TEST_ASSERT_EQUAL (u.age(), 0);
  TEST_ASSERT_EQUAL (strlen (u.name().c_str()), 0);
}

void test_user_parameter_constructor (void) {
  User u ("John Doe", 42);

  TEST_ASSERT_EQUAL (u.age(), 42);
  TEST_ASSERT_EQUAL (strcmp (u.name().c_str(), "John Doe"), 0);
}

void test_user_parent_access (void) {
  User u;

  TEST_ASSERT_TRUE (u.checkParentAccess());
}

void test_user_setters (void) {
  User u;

  u.setAge (42);
  TEST_ASSERT_EQUAL (u.age(), 42);
  u.setName ("John Doe");
  TEST_ASSERT_EQUAL (strcmp (u.name().c_str(), "John Doe"), 0);
  u.clear();
  TEST_ASSERT_EQUAL (u.age(), 0);
  TEST_ASSERT_EQUAL (strlen (u.name().c_str()), 0);
}

void test_duser_default_constructor (void) {
  DerivedUser u;

  TEST_ASSERT_EQUAL (u.age(), 0);
  TEST_ASSERT_EQUAL (strlen (u.name().c_str()), 0);
  TEST_ASSERT_EQUAL (strlen (u.address().c_str()), 0);
}

void test_duser_parameter_constructor (void) {
  DerivedUser u ("John Doe", 42, "Main Street");

  TEST_ASSERT_EQUAL (u.age(), 42);
  TEST_ASSERT_EQUAL (strcmp (u.name().c_str(), "John Doe"), 0);
  TEST_ASSERT_EQUAL (strcmp (u.address().c_str(), "Main Street"), 0);
}

void test_duser_parent_access (void) {
  DerivedUser u;

  TEST_ASSERT_TRUE (u.checkParentAccess());
}

void test_duser_setters (void) {
  DerivedUser u;

  u.setAge (42);
  TEST_ASSERT_EQUAL (u.age(), 42);
  u.setName ("John Doe");
  TEST_ASSERT_EQUAL (strcmp (u.name().c_str(), "John Doe"), 0);
  u.setAddress ("Main Street");
  TEST_ASSERT_EQUAL (strcmp (u.address().c_str(), "Main Street"), 0);
}

void test_duser_pointer (void) {
  DerivedUser u;
  User *p = &u;

  TEST_ASSERT_EQUAL (u.age(), p->age());
  TEST_ASSERT_EQUAL (strcmp (u.name().c_str(), p->name().c_str()), 0);
}


void test_all (void) {
  RUN_TEST (test_user_default_constructor);
  RUN_TEST (test_user_parameter_constructor);
  RUN_TEST (test_user_parent_access);
  RUN_TEST (test_user_setters);
  RUN_TEST (test_duser_default_constructor);
  RUN_TEST (test_duser_parameter_constructor);
  RUN_TEST (test_duser_parent_access);
  RUN_TEST (test_duser_setters);
  RUN_TEST (test_duser_pointer);
}

// ----------------------------------------------------------
// Unit Test Runner
// ----------------------------------------------------------

#ifndef ARDUINO
// ----------------------------------------------------------
// Native platform test
int main() {

  UNITY_BEGIN();    // IMPORTANT LINE!
  test_all();
  UNITY_END(); // stop unit testing
  return 0;
}

#else
// ----------------------------------------------------------
// Arduino platform test
void setup() {

  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay (2000);

  UNITY_BEGIN();    // IMPORTANT LINE!
  test_all();
  UNITY_END(); // stop unit testing
}

void loop() {
  // nothing to be done here.
}
#endif