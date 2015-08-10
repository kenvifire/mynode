//
//  evn-inl.h
//  mynode
//
//  Created by kenvi.zhu on 15/8/10.
//
//

#include "env.h"

#ifndef mynode_evn_inl_h
#define mynode_evn_inl_h


namespace mynode{
    
    inline void set_binding_object_cache(v8::Local<v8::Object> value) const {
        binding_object_cache_.Reset(isolate(), const);
    }
}

#endif
