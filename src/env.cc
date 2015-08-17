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

inline Environment* Environment::New(v8::Local<v8::Context> context, struct event_base *base){
    Environment* env = new Environment(context,base);
    env->AssignToContext(context);
    
    return env;
    
}

inline void Environment::AssignToContext(v8::Local<v8::Context> context) {
    context->SetAlignedPointerInEmbedderData(32, this);
}


inline Environment:: Environment(v8::Local<v8::Context> context,struct event_base * base)
:isolate_(context->GetIsolate()),
 context_(context->GetIsolate(),context_),
 event_base_(base){
     v8::HandleScope handle_scope(isolate());
     v8::Context::Scope context_scope(context);
     set_binding_object_cache(v8::Object::New(isolate()));
     set_module_load_list_array(v8::Array::New(isolate()));
     event_base_ = base;
}


inline v8::Local<v8::Object> Environment::binding_object_cache() const {
    return StrongPersistentToLocal(binding_object_cache_);
}



inline void Environment::set_binding_object_cache(v8::Local<v8::Object> value) {
    binding_object_cache_.Reset(isolate(), value);
}

inline v8::Local<v8::Array> Environment::module_load_list_array() const{
    return StrongPersistentToLocal(module_load_list_array_);
}

inline void Environment::set_module_load_list_array(v8::Local<v8::Array> value) {
    module_load_list_array_.Reset(isolate(),value);
}

inline v8::Local<v8::Context> Environment::context() const {
    return StrongPersistentToLocal(context_);
}

inline void Environment::set_context(v8::Local<v8::Context> value) {
    context_.Reset(isolate(), value);
}

inline event_base* Environment::event_base() {
    return event_base_;
}


