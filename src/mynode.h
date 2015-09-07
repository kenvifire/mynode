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
    
    extern "C" void mynode_module_register(void *mod);
   
    class Environment;
   
    
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
    
    typedef void (*addon_register_func)(
        v8::Handle<v8::Object> exports,
        v8::Handle<v8::Value> module,
        v8::Handle<v8::Context> context,
        void * priv);
    typedef void (*addon_context_register_func) (
        v8::Handle<v8::Object> exports,
        v8::Handle<v8::Value> module,
        v8::Handle<v8::Context> context,
        void * priv);
    
    
    struct mynode_module {
        int nm_version;
        unsigned int nm_flags;
        void* nm_dso_handle;
        const char* nm_filename;
        mynode::addon_register_func nm_register_func;
        mynode::addon_context_register_func nm_context_register_func;
        const char* nm_modname;
        void* nm_priv;
        struct mynode_module* nm_link;
    };
    
    
    #define MYNODE_C_CTOR(fn)                                      \
        static void fn(void) __attribute__((constructor));         \
        static void fn(void)
    
    #define MYNODE_STRINGFY(n) #n
    
    
    
    #define MYNODE_MODULE_REGISTER(modname, regfunc, priv, flags ) \
      extern "C" {                                                 \
         static mynode::mynode_module _module =                    \
         {                                                         \
            1,                                                      \
            flags,                                                  \
            NULL,                                                   \
            __FILE__,                                               \
            NULL,                                                   \
            (mynode::addon_context_register_func) (regfunc),        \
            MYNODE_STRINGFY(modname),                               \
            priv,                                                   \
            NULL                                                    \
         };                                                         \
         MYNODE_C_CTOR(_register_ ## modname) {                     \
             mynode_module_register(&_module);                       \
         }                                                          \
        }
    
#define MYNODE_DEFINE_CONSTANT(target, constant)                    \
    do {                                                            \
    v8::Isolate* isolate = v8::Isolate::GetCurrent();               \
    v8::Local<v8::String> constant_name =                           \
        v8::String::NewFromUtf8(isolate, #constant);                \
    v8::Local<v8::Number> constant_value =                          \
        v8::Number::New(isolate, static_cast<double>(constant));    \
    v8::PropertyAttribute constant_attributes =                     \
        static_cast<v8::PropertyAttribute>(v8::ReadOnly | v8::DontDelete);\
    (target)->ForceSet(constant_name,constant_value,constant_attributes); \
    }                                                                          \
while (0);



    
    
}

#endif
