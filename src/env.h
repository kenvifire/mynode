//
//  env.h
//  mynode
//
//  Created by kenvi.zhu on 15/8/9.
//
//

#ifndef __mynode__env__
#define __mynode__env__

#include <stdio.h>
#include "include/v8.h"
#include "utils.h"

namespace mynode {
    class Environment {
    private:
        v8::Isolate* const isolate_;
        v8::Context context_;
        v8::Persistent<v8::Object> binding_object_cache_;
    public:
        static inline Environment* GetCurrent(v8::Isolate* isolate);
        static inline Environment* GetCurrent(v8::Local<v8::Context> context);
        
        static inline Environment* New(v8::Local<v8::Context> context);
        
        // property methods
        inline v8::Isolate* isolate() const {
            return isolate_;
        }
        
        inline v8::Local<v8::Object> binding_object_cache() const {
            return StrongPersistentToLocal(binding_object_cache_);
        }
        
     
        
    };
}

#endif /* defined(__mynode__env__) */
