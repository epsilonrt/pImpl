#include <pimp.h>

#ifdef ARDUINO
#include <Arduino.h>
typedef String string_t;
#else
#include <string>
typedef std::string string_t;
#endif

#pragma once
class User : public PimpClass {
  public:
    User();
    User (const string_t &name, int age);
    string_t name() const;
    int age() const;
    void setAge (int age);
    void setName (const string_t &name);
    bool checkParentAccess() const;
  protected:
    class Private;
    User (Private &dd);
  private:
    PIMP_DECLARE_PRIVATE (User)
};