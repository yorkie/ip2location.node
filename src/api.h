
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <v8.h>
#include <nan.h>
#include "IP2Location.h"

using namespace v8;
using namespace node;

class IP2LocationWrap : public ObjectWrap {
public:
  IP2LocationWrap(char * db, enum IP2Location_mem_type mtype);
  ~IP2LocationWrap();

  static void Init(Handle<Object> target);
  static NAN_METHOD(New);
  static NAN_METHOD(GetCountryShort);
  static NAN_METHOD(GetCountryLong);
  static NAN_METHOD(GetRegion);
  static NAN_METHOD(GetCity);
  static NAN_METHOD(GetISP);
  static NAN_METHOD(GetAll);

private:
  IP2Location *loc;
};

#endif