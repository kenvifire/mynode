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

namespace mynode{
    using namespace v8;
    
    class Timer
    {
    public:
        static void Initialize(Handle<Object> target, Handle<Value> unused,
                               Handle<Context> context);
        static void now(const FunctionCallbackInfo<Value>& args);
        
    private:
        
    };
    
}


#endif /* defined(__mynode__timer__) */
