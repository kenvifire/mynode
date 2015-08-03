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

using namespace v8;
using namespace mynode;

void Timer::now(const FunctionCallbackInfo<Value>& args) {
    struct timeval tv;
    evutil_gettimeofday(&tv, nullptr);
    uint32_t now = tv.tv_sec * 1000 + tv.tv_usec;
    tv.~timeval();
    args.GetReturnValue().Set(now);
    
}