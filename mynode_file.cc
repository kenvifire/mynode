//
//  mynode_file.cpp
//  mynode
//
//  Created by Hannah Zhang on 15/9/5.
//
//

#include "mynode_file.h"
#include "env.h"


namespace mynode {
    using v8::HandleScope;
    using v8::FunctionCallbackInfo;
    using v8::Value;
    using v8::Handle;
    using v8::Object;
    using v8::Context;
    
    
    static void Access(const FunctionCallbackInfo<Value>& args) {;
        Environment* env = Environment::GetCurrent(args.GetIsolate());
        HandleScope scope(env->isolate());
        
        int mode = static_cast<int>(args[1]->Int32Value());
        
        if (args[2]->IsObject()) {
            //
            printf("async call");
        }else {
            printf("sync call");
        }
        
    }
    
    void InitFs(Handle<Object> target,
                Handle<Value> unused,
                Handle<Context> context,
                void *priv) {
        Environment * env = Environment::GetCurrent(context);
        
        MYNODE_SET_METHOD(target, "access", Access);
    }
}
MYNODE_MODULE_REGISTER(file, mynode::InitFs, NULL, 1)
