
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <node.h>
#include <v8.h>
#include <nan.h>
#include "api.h"

using namespace v8;

IP2LocationWrap::IP2LocationWrap(char *db, enum IP2Location_mem_type mtype) {
  loc = IP2Location_open(db);
  IP2Location_open_mem(loc, mtype);
}

IP2LocationWrap::~IP2LocationWrap() {
  IP2Location_close(loc);
}

void IP2LocationWrap::Init(Handle<Object> target) {
  NanScope();
  Local<FunctionTemplate> t = NanNew<FunctionTemplate>(New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  NODE_SET_PROTOTYPE_METHOD(t, "queryCountryShort", GetCountryShort);
  NODE_SET_PROTOTYPE_METHOD(t, "queryCountryLong", GetCountryLong);
  NODE_SET_PROTOTYPE_METHOD(t, "queryRegion", GetRegion);
  NODE_SET_PROTOTYPE_METHOD(t, "queryCity", GetCity);
  NODE_SET_PROTOTYPE_METHOD(t, "queryISP", GetISP);
  NODE_SET_PROTOTYPE_METHOD(t, "query", GetAll);
  target->Set(NanNew<v8::String>("IP2Location"), t->GetFunction());
}

NAN_METHOD(IP2LocationWrap::New) {
  NanScope();
  char *db;
  char *mtype_str;
  enum IP2Location_mem_type mtype = IP2LOCATION_CACHE_MEMORY;

  v8::String::Utf8Value v8_db(args[0]->ToString());
  v8::String::Utf8Value v8_mtype_str(args[1]->ToString());
  db = *v8_db;
  mtype_str = *v8_mtype_str;

  if (strcmp("use_cache", mtype_str) == 0) {
    mtype = IP2LOCATION_CACHE_MEMORY;
  } else if (strcmp("use_shared_memory", mtype_str) == 0) {
    mtype = IP2LOCATION_SHARED_MEMORY;
  } else if (strcmp("use_file_io", mtype_str) == 0) {
    mtype = IP2LOCATION_FILE_IO;
  }

  IP2LocationWrap *locwrap = new IP2LocationWrap(db, mtype);
  locwrap->Wrap(args.This());
  NanReturnValue(args.This());
}

NAN_METHOD(IP2LocationWrap::GetCountryShort) {
  NanScope();
  IP2LocationWrap *locwrap = ObjectWrap::Unwrap<IP2LocationWrap>(args.This());
  v8::String::Utf8Value v8_ip(args[0]->ToString());
  IP2LocationRecord * record = IP2Location_get_country_short(locwrap->loc, *v8_ip);
  Local<String> ret = NanNew<String>(record->country_short);
  IP2Location_free_record(record);
  NanReturnValue(ret);
}

NAN_METHOD(IP2LocationWrap::GetCountryLong) {
  NanScope();
  IP2LocationWrap *locwrap = ObjectWrap::Unwrap<IP2LocationWrap>(args.This());
  v8::String::Utf8Value v8_ip(args[0]->ToString());
  IP2LocationRecord * record = IP2Location_get_country_long(locwrap->loc, *v8_ip);
  Local<String> ret = NanNew<String>(record->country_long);
  IP2Location_free_record(record);
  NanReturnValue(ret);
}

NAN_METHOD(IP2LocationWrap::GetRegion) {
  NanScope();
  IP2LocationWrap *locwrap = ObjectWrap::Unwrap<IP2LocationWrap>(args.This());
  v8::String::Utf8Value v8_ip(args[0]->ToString());
  IP2LocationRecord * record = IP2Location_get_region(locwrap->loc, *v8_ip);
  Local<String> ret = NanNew<String>(record->region);
  IP2Location_free_record(record);
  NanReturnValue(ret);
}

NAN_METHOD(IP2LocationWrap::GetCity) {
  NanScope();
  IP2LocationWrap *locwrap = ObjectWrap::Unwrap<IP2LocationWrap>(args.This());
  v8::String::Utf8Value v8_ip(args[0]->ToString());
  IP2LocationRecord * record = IP2Location_get_city(locwrap->loc, *v8_ip);
  Local<String> ret = NanNew<String>(record->city);
  IP2Location_free_record(record);
  NanReturnValue(ret);
}

NAN_METHOD(IP2LocationWrap::GetISP) {
  NanScope();
  IP2LocationWrap *locwrap = ObjectWrap::Unwrap<IP2LocationWrap>(args.This());
  v8::String::Utf8Value v8_ip(args[0]->ToString());
  IP2LocationRecord * record = IP2Location_get_isp(locwrap->loc, *v8_ip);
  Local<String> ret = NanNew<String>(record->isp);
  IP2Location_free_record(record);
  NanReturnValue(ret);
}

NAN_METHOD(IP2LocationWrap::GetAll) {
  NanScope();
  IP2LocationWrap *locwrap = ObjectWrap::Unwrap<IP2LocationWrap>(args.This());
  v8::String::Utf8Value v8_ip(args[0]->ToString());
  IP2LocationRecord * record = IP2Location_get_all(locwrap->loc, *v8_ip);

  Local<Object> res = NanNew<Object>();
  res->Set(NanNew<String>("countryShort"), NanNew<String>(record->country_short));
  res->Set(NanNew<String>("countryLong"), NanNew<String>(record->country_long));
  res->Set(NanNew<String>("region"), NanNew<String>(record->region));
  res->Set(NanNew<String>("city"), NanNew<String>(record->city));
  res->Set(NanNew<String>("isp"), NanNew<String>(record->isp));
  res->Set(NanNew<String>("latitude"), NanNew<Number>(record->latitude));
  res->Set(NanNew<String>("longitude"), NanNew<Number>(record->longitude));
  res->Set(NanNew<String>("domain"), NanNew<String>(record->domain));
  res->Set(NanNew<String>("zipcode"), NanNew<String>(record->zipcode));
  res->Set(NanNew<String>("timezone"), NanNew<String>(record->timezone));
  res->Set(NanNew<String>("netspeed"), NanNew<String>(record->netspeed));
  res->Set(NanNew<String>("iddcode"), NanNew<String>(record->iddcode));
  res->Set(NanNew<String>("areacode"), NanNew<String>(record->areacode));
  res->Set(NanNew<String>("weatherstationcode"), NanNew<String>(record->weatherstationcode));
  res->Set(NanNew<String>("weatherstationname"), NanNew<String>(record->weatherstationname));
  res->Set(NanNew<String>("mcc"), NanNew<String>(record->mcc));
  res->Set(NanNew<String>("mnc"), NanNew<String>(record->mnc));
  res->Set(NanNew<String>("mobilebrand"), NanNew<String>(record->mobilebrand));
  res->Set(NanNew<String>("elevation"), NanNew<Number>(record->elevation));
  res->Set(NanNew<String>("usagetype"), NanNew<String>(record->usagetype));
  IP2Location_free_record(record);
  NanReturnValue(res);
}

NODE_MODULE(ip2location, IP2LocationWrap::Init)