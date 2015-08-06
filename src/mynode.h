//
//  mynode.h
//  mynode
//
//  Created by Hannah Zhang on 15/7/11.
//
//

#ifndef mynode_mynode_h
#define mynode_mynode_h

#include "include/v8.h"

namespace mynode {
    int Start(int argc, char* argv[]);
    
    template <typename TypeName>
    inline void MYNODE_SET_METHOD(const TypeName& recv,
                                  const char* name,
                                  v8::FunctionCallback callback) {
        
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::HandleScope handle_scope(isolate);
        v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate,callback);
        
        v8::Local<v8::Function> fn = t->GetFunction();
        v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, name);
        fn->SetName(fn_name);
        recv->Set(fn_name, fn);
    }
    
    #define MYNODE_SET_METHOD mynode::MYNODE_SET_METHOD
   
    inline void MYNODE_SET_PROTOTYPE_METHOD(v8::Handle<v8::FunctionTemplate> recv,
                                          const char* name,
                                          v8::FunctionCallback callback) {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::HandleScope handle_scope(isolate);
        v8::Handle<v8::Signature> s = v8::Signature::New(isolate,recv);
        v8::Local<v8::FunctionTemplate> t =
            v8::FunctionTemplate::New(isolate,callback,v8::Handle<v8::Value>(),s);
        v8::Local<v8::Function> fn = t->GetFunction();
        recv->PrototypeTemplate()->Set(v8::String::NewFromUtf8(isolate, name),fn);
        v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, name);
        fn->SetName(fn_name);
    }
    
    #define MYNODE_SET_PROTOTYPE_METHOD mynode::MYNODE_SET_PROTOTYPE_METHOD
    
}

#endif
