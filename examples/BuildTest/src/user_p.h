#include <pimp_p.h>
#include "user.h"

#pragma once
class User::Private : public PimpClass::Private {
  public:
    Private (User *q);
    bool checkParentAccess() const;
    string_t name;
    int age;

  // private:
    PIMP_DECLARE_PUBLIC (User)
};