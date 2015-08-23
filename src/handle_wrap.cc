//
//  handle_warp.cpp
//  mynode
//
//  Created by Hannah Zhang on 15/8/22.
//
//

#include "handle_wrap.h"
#include "include/v8.h"
#include "utils-inl.h"
#include "base-object.h"
#include "base-object.cc"

namespace mynode {
   
    using v8::Object;
    using v8::HandleScope;
    
    HandleWrap::HandleWrap(Environment* env,
           v8::Handle<Object> object,
           handle_t* handle)
        : BaseObject(env,object),
        handle__(handle){
            HandleScope scope(env->isolate());
            Wrap(object, this);
    }
}

