//
//  base-object.c
//  mynode
//
//  Created by Hannah Zhang on 15/8/23.
//
//

#include "base-object.h"
#include "env.h"
#include "include/v8.h"
#include <assert.h>
#include "utils.h"
#include "utils-inl.h"

namespace mynode{
    inline BaseObject::BaseObject( Environment* env, v8::Local<v8::Object> handle)
        : handle_(env->isolate(),handle),
          env_(env){
              assert(!handle.IsEmpty());
        
    }
    
    inline BaseObject::~BaseObject() {
        assert(handle_.IsEmpty());
    }
    
    inline Environment* BaseObject::env() const{
        return env_;
    }
    
    inline v8::Local<v8::Object> BaseObject::object() {
        return PersistentToLocal(env_->isolate(),handle_);
    }

    
}
