#include "user_p.h"

// ----------------------------------------------------------------------------
User::Private::Private (User *q) : PimpClass::Private (q), age (0) {}

// ----------------------------------------------------------------------------
bool User::Private::checkParentAccess() const {
  PIMP_Q (const User);
  return q->name() == name && q->age() == age;
}

// ----------------------------------------------------------------------------
User::User() : PimpClass (*new Private (this)) {
}

// ----------------------------------------------------------------------------
User::User (Private &dd) : PimpClass (dd) {
}

// ----------------------------------------------------------------------------
User::User (const string_t &name, int age) : User() {
  PIMP_D (User);
  d->name = name;
  d->age = age;
}

// ----------------------------------------------------------------------------
string_t User::name() const {
  PIMP_D (const User);
  return d->name;
}

// ----------------------------------------------------------------------------
int User::age() const {
  PIMP_D (const User);
  return d->age;
}

// ----------------------------------------------------------------------------
void User::setAge (int age) {
  PIMP_D (User);
  d->age = age;
}

// ----------------------------------------------------------------------------
void User::setName (const string_t &name) {
  PIMP_D (User);
  d->name = name;
}

// ----------------------------------------------------------------------------
bool User::checkParentAccess() const {
  PIMP_D (const User);
  return d->checkParentAccess();
}
