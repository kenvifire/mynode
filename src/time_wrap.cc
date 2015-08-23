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
#include "env.cc"
#include <assert.h>
#include "utils.h"
#include "utils-inl.h"
#include "handle_wrap.h"
#include "base-object.h"
#include "base-object.cc"

using namespace v8;
using namespace mynode;

void TimeWrap::Initialize(Handle<Object> target, Handle<Value> moduleName,
                       Handle<Context> context){
    Isolate* isolate = Isolate::GetCurrent();
    Local<FunctionTemplate> constructor = FunctionTemplate::New(isolate);
    constructor->SetClassName(String::NewFromUtf8(isolate, "Timer"));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
    constructor->Set(String::NewFromUtf8(isolate, "kOnTimeout"),
                     Integer::New(isolate, kOnTimeout));
    
    MYNODE_SET_METHOD(constructor, "now", now);
    MYNODE_SET_PROTOTYPE_METHOD(constructor, "start", Start);
    
    
    // prototype
    
    target->Set(String::NewFromUtf8(isolate, "Timer"),
                constructor->GetFunction());
    
}



void TimeWrap::now(const FunctionCallbackInfo<Value>& args) {
    Environment* env = Environment::GetCurrent(args.GetIsolate());
    struct timeval tv;
    evutil_gettimeofday(&tv, nullptr);
    uint64_t now = tv.tv_sec * 1000 + tv.tv_usec;
    tv.~timeval();
    args.GetReturnValue().Set(static_cast<double>(now));
    
}

void TimeWrap::New(const FunctionCallbackInfo<Value>& args){
    assert(args.IsConstructCall());
    HandleScope handle_scope(args.GetIsolate());
    Environment* env = Environment::GetCurrent(args.GetIsolate());
    handle_t handle;
    new TimeWrap(env,args.This(),&handle);
}

TimeWrap::TimeWrap(Environment* env, v8::Handle<Object> object, handle_t* handle)
    : HandleWrap(env,object,handle)
{
    
}

void TimeWrap::OnTimeout(int fd, short event, void *params) {
    TimeWrap * wrap = static_cast<TimeWrap*>(params);
    Environment * env = wrap->env();
    HandleScope handle_scope(env->isolate());
    Context::Scope context_scope(env->context());
    v8::Handle<v8::Value> cb_v = wrap->object()->Get(kOnTimeout);
    
    Local<Object> context = wrap->object();
    
    Local<Value> ret = cb_v.As<Function>()->Call(context, 0, NULL);
}

void TimeWrap::Start(const FunctionCallbackInfo<Value>& args) {
    TimeWrap* wrap = Unwrap<TimeWrap>(args.Holder());
    int32_t s = args[0]->IntegerValue();
    int32_t ms = args[1]->IntegerValue();
    
    struct timeval tv = {s,ms};
    struct event* ev = event_new(wrap->env()->event_base(),-1,0,OnTimeout,wrap);
    
}

TimeWrap::~TimeWrap(){
    
}

//void Timer::setTimeout(const FunctionCallbackInfo<Value>& args) {
//    Environment* env = Environment::GetCurrent(args.GetIsolate());
//    
//    int time = args[0]->Int32Value();
//    
//    struct timeval timeout;
//    timeout.tv_sec = time / 1000;
//    timeout.tv_usec = time % 1000;
//    
//    //struct event* ev = event_new(env->event_base(),-1,0,Timer::cb_func,NULL);
//    //event_add(ev, &time);
//    
//}
//
//void Timer::cb_func(const FunctionCallbackInfo<Value> &args){
//    Environment* env = Environment::GetCurrent(args.GetIsolate());
//    HandleScope scope(env->isolate());
//    
//    Local<Function> cb = Local<Function>::Cast(args[0]);
//    const unsigned argc = 1;
//    Local<Value> argv[argc] = { String::NewFromUtf8(env->isolate(), "hello world") };
//    cb->Call(env->context(), argc, argv);
//    
//}



MYNODE_MODULE_REGISTER(timer, mynode::TimeWrap::Initialize, NULL, 1)
