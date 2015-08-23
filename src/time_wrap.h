//
//  timer.h
//  mynode
//
//  Created by kenvi.zhu on 15/8/3.
//
//

#ifndef __mynode__timer__
#define __mynode__timer__
#include <stdio.h>
#include <sys/time.h>
#include <include/v8.h>
#include "env-inl.h"
#include "env.h"
#include <event2/event.h>
#include "utils.h"
#include <stdint.h>
#include "handle_wrap.h"

namespace mynode{
    using namespace v8;
    
    const uint32_t kOnTimeout = 0;
    
    class TimeWrap: public HandleWrap
    {
    public:
        static void Initialize(Handle<Object> target, Handle<Value> unused,
                               Handle<Context> context);
        static void now(const FunctionCallbackInfo<Value>& args);
        void setTimeout(const FunctionCallbackInfo<Value>& args);
        void cb_func(const FunctionCallbackInfo<Value> &args);
        TimeWrap(Environment* env, v8::Handle<Object> object, handle_t* handle);
        static void OnTimeout(int fd, short event, void *params);
        
    private:
        static void New(const FunctionCallbackInfo<Value>& args);
        static void Start(const FunctionCallbackInfo<Value>& args);
        ~TimeWrap();
        
        handle_t handle__;
        
    };
    
    
}


#endif /* defined(__mynode__timer__) */
