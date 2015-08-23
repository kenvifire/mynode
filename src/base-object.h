//
//  base-object.h
//  mynode
//
//  Created by Hannah Zhang on 15/8/23.
//
//

#ifndef __mynode__base_object__
#define __mynode__base_object__

#include <stdio.h>
#include "include/v8.h"
#include "env.h"

namespace mynode {
    class BaseObject {
    public:
        BaseObject(Environment* env, v8::Local<v8::Object> handle);
        ~BaseObject();
        
        inline v8::Local<v8::Object> object();
        inline Environment* env() const;
    
    private:
        BaseObject();
        v8::Persistent<v8::Object> handle_;
        Environment* env_;
    };
}


#endif /* defined(__mynode__base_object__) */
