//
//  env.c
//  mynode
//
//  Created by kenvi.zhu on 15/8/9.
//
//

#include "env.h"
#include "include/v8.h"

using namespace mynode;

inline Environment* Environment:: GetCurrent(v8::Isolate* isolate){
    return GetCurrent(isolate->GetCurrentContext());
    
}
inline Environment* Environment::GetCurrent(v8::Local<v8::Context> context){
    return static_cast<Environment*>(context->GetAlignedPointerFromEmbedderData(32));
    
}

inline Environment* Environment::New(v8::Local<v8::Context> context){
    Environment* env = New(context);
    env->AssignToContext(context);
    
    return env;
    
}

inline void Environment::AssignToContext(v8::Local<v8::Context> context) {
    context->SetAlignedPointerInEmbedderData(32, this);
}


inline Environment:: Environment(v8::Local<v8::Context> context)
:isolate_(context->GetIsolate()){
    v8::HandleScope handle_scope(isolate());
    v8::Context::Scope context_scope(context);
    set_binding_object_cache(v8::Object::New(isolate()));
}


inline v8::Local<v8::Object> Environment::binding_object_cache() const {
    return StrongPersistentToLocal(binding_object_cache_);
}



inline void Environment::set_binding_object_cache(v8::Local<v8::Object> value) {
    binding_object_cache_.Reset(isolate(), value);
}







