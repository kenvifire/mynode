//
//  evn-inl.h
//  mynode
//
//  Created by kenvi.zhu on 15/8/10.
//
//

#include "env.h"
#include "include/v8.h"

#ifndef mynode_env_inl_h
#define mynode_env_inl_h


namespace mynode{
    inline Environment* Environment:: GetCurrent(v8::Isolate* isolate){
        
    }
    inline Environment* Environment::GetCurrent(v8::Local<v8::Context> context){
        
    }
    
    inline Environment:: Environment(v8::Local<v8::Context> context)
        :isolate_(context->GetIsolate()){
        v8::HandleScope handle_scope(isolate());
        v8::Context::Scope context_scope(context);
        //set_binding_cache(v8::Object::New(isolate()));
    }
    
    
    inline v8::Local<v8::Object> binding_object_cache() const {
        return StrongPersistentToLocal(binding_object_cache_);
    }
   
    
    
    inline void Environment::set_binding_object_cache(v8::Local<v8::Object> value) {
        binding_object_cache_.Reset(isolate(), value);
    }
}

#endif
