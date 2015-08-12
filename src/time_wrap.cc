//
//  timer.c
//  mynode
//
//  Created by kenvi.zhu on 15/8/3.
//
//

#include "time_wrap.h"

#include <sys/time.h>
#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/util.h>
#include <stdint.h>
#include "include/v8.h"
#include "mynode.h"
#include "time_wrap.h"
#include "env.h"
#include "env-inl.h"

using namespace v8;
using namespace mynode;

void Timer::Initialize(Handle<Object> target, Handle<Value> moduleName,
                       Handle<Context> context){
    Isolate* isolate = Isolate::GetCurrent();
    Local<FunctionTemplate> constructor = FunctionTemplate::New(isolate);
    constructor->SetClassName(String::NewFromUtf8(isolate, "Timer"));
    
    MYNODE_SET_METHOD(constructor, "now", now);
    
    target->Set(String::NewFromUtf8(isolate, "Timer"), constructor->GetFunction());
    
    
    
    
    // prototype
    
    target->Set(String::NewFromUtf8(isolate, "Timer"),
                constructor->GetFunction());
    
}

void Timer::now(const FunctionCallbackInfo<Value>& args) {
    struct timeval tv;
    evutil_gettimeofday(&tv, nullptr);
    uint64_t now = tv.tv_sec * 1000 + tv.tv_usec;
    tv.~timeval();
    args.GetReturnValue().Set(static_cast<double>(now));
    
}

MYNODE_MODULE_REGISTER(timer, mynode::Timer::Initialize, NULL, 1)
