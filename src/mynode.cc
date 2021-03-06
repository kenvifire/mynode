// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "include/libplatform/libplatform.h"
#include "include/v8.h"
#include "time_wrap.h"
#include "mynode.h"
#include "env.h"
#include "env.cc"
#include "utils.h"
#include "utils-inl.h"
#include "mynode_constants.h"

using namespace v8;


namespace mynode {
    
   static mynode_module* modlist_builtin;
    
    
    
    

    MaybeLocal<String> ReadFile(Isolate* isolate, const char* name);
    void ReportException(Isolate* isolate, TryCatch* try_catch);
    bool ExecuteString(Isolate* isolate, Local<String> source,
                       Local<Value> name, bool print_result,
                       bool report_exception);
    void Load(const FunctionCallbackInfo<Value>& args );
    int RunMain(Isolate* isolate, int argc, char* argv[]);
    void Require(const FunctionCallbackInfo<Value>& args);
    void LoadScript(const FunctionCallbackInfo<Value>& args);
    void RunScript(const FunctionCallbackInfo<Value> & args);
    void LoadModule(const FunctionCallbackInfo<Value> & args);
    Environment* CreateEnvironment(v8::Isolate* isolate,
                                   v8::Handle<v8::Context> context,
                                   int argc,
                                   const char* const* argv,
                                   struct event_base* base
                                   );
    static void Binding(const FunctionCallbackInfo<Value> & args);

    class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
    public:
        virtual void* Allocate(size_t length) {
            void* data = AllocateUninitialized(length);
            return data == NULL ? data : memset(data, 0, length);
        }
        virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
        virtual void Free(void* data, size_t) { free(data); }
    };

    const char* ToCString (String::Utf8Value& value) {
        return *value ? *value : "<string conversion failed>";
    }

    void Print(const FunctionCallbackInfo<Value>& args) {
        bool first = true;

        for (int i = 0 ; i < args.Length(); i++) {
            HandleScope handle_scope(args.GetIsolate());

            if(first){
                first = false;
            } else {
                printf(" ");
            }

            String::Utf8Value str(args[i]);
            const char* cstr = ToCString(str);

            printf("%s", cstr);
        }
        printf("\n");
        fflush(stdout);

    }
    


    Local<Context> CreateContext(Isolate* isolate){

        Local<ObjectTemplate> global = ObjectTemplate::New(isolate);

        global->Set(String::NewFromUtf8(isolate, "print",NewStringType::kNormal).ToLocalChecked(),
                    FunctionTemplate::New(isolate, Print));

        global->Set(String::NewFromUtf8(isolate, "loadFile",NewStringType::kNormal).ToLocalChecked(),
                    FunctionTemplate::New(isolate, Load));
        
        global->Set(String::NewFromUtf8(isolate, "require",NewStringType::kNormal).ToLocalChecked(),
                    FunctionTemplate::New(isolate, Require));

        global->Set(String::NewFromUtf8(isolate, "loadScript",NewStringType::kNormal).ToLocalChecked(),
                    FunctionTemplate::New(isolate, LoadScript));
        
        global->Set(String::NewFromUtf8(isolate, "runScript",NewStringType::kNormal).ToLocalChecked(),
                    FunctionTemplate::New(isolate, RunScript));
        
        
        global->Set(String::NewFromUtf8(isolate, "binding",NewStringType::kNormal).ToLocalChecked(),
                    FunctionTemplate::New(isolate, Binding));
        
        
        
        return Context::New(isolate, NULL, global);

    }
    
    void LoadModule(const FunctionCallbackInfo<Value>& args) {
        HandleScope hadle_scope(args.GetIsolate());
        
        if(args.Length() < 1) {
            args.GetIsolate()->ThrowException(String::NewFromUtf8(args.GetIsolate(), "no module name",
                                                                  NewStringType::kNormal).ToLocalChecked());
            return;
        }
        
          
    }

    void Load(const FunctionCallbackInfo<Value>& args ) {
        for (int i = 0; i < args.Length(); i++) {
            HandleScope handle_scope(args.GetIsolate());
            String::Utf8Value file(args[i]);

            if (*file == NULL) {
                args.GetIsolate()->ThrowException(
                    String::NewFromUtf8(args.GetIsolate(), "Error loading file",
                                        NewStringType::kNormal).ToLocalChecked());
                return;

            }

            Local<String> source;

            if (!ReadFile(args.GetIsolate(), *file).ToLocal(&source)) {
                args.GetIsolate()->ThrowException(
                    String::NewFromUtf8(args.GetIsolate(), "Error loading file",
                                        NewStringType::kNormal).ToLocalChecked());
                return;
            }

            if (ExecuteString(args.GetIsolate(), source, args[i], false, false)) {
                args.GetIsolate()->ThrowException(
                    String::NewFromUtf8(args.GetIsolate(), "Error executing file",
                                        NewStringType::kNormal).ToLocalChecked());
            }

        }
    }

    bool ExecuteString(Isolate* isolate, Local<String> source,
                       Local<Value> name, bool print_result,
                       bool report_exception) {

        HandleScope handle_scope(isolate);
        TryCatch try_catch(isolate);
        ScriptOrigin origin(name);
        Local<Context> context(isolate->GetCurrentContext());
        Local<Script> script;

        if(!Script::Compile(context, source, &origin).ToLocal(&script)) {

            if(report_exception)
                ReportException(isolate, &try_catch);
            return  false;
        }else {
            Local<Value> result;
            if (!script->Run(context).ToLocal(&result)) {
                assert(try_catch.HasCaught());

                if (report_exception)
                    ReportException(isolate, &try_catch);
                return false;
            } else {
                assert(!try_catch.HasCaught());
                if (print_result && !result->IsUndefined()) {
                    String::Utf8Value str(result);
                    const char* cstr = ToCString(str);
                    printf("%s\n",cstr);
                }
                return true;
            }

        }
    }

    MaybeLocal<String> ReadFile(Isolate* isolate, const char* name) {
        FILE* file = fopen(name, "rb");
        if( file == NULL) return MaybeLocal<String>();

        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        rewind(file);

        char* chars = new char[size +1];
        chars[size] = '\0';

        for (size_t i = 0; i < size; ) {
            i += fread(&chars[i], 1, size - i, file);
            if (ferror(file)) {
                fclose(file);
                return MaybeLocal<String>();
            }
        }
        fclose(file);

        MaybeLocal<String> result = String::NewFromUtf8(isolate, chars, NewStringType::kNormal,
                                                        static_cast<int>(size));
        delete[] chars;
        return result;

    }

    void ReportException(Isolate* isolate, TryCatch* try_catch) {
        HandleScope handle_scope(isolate);
        String::Utf8Value exception(try_catch->Exception());
        const char* exception_string = ToCString(exception);
        Local<Message> message = try_catch->Message();

        if (message.IsEmpty()) {
            fprintf(stderr, "%s\n",exception_string);
        }else {
            String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
            Local<Context> context(isolate->GetCurrentContext());
            const char* filename_string = ToCString(filename);
            int linenum = message->GetLineNumber(context).FromJust();
            fprintf(stderr, "%s:%i:%s\n",filename_string,linenum,exception_string);

            String::Utf8Value sourceline(
                                         message->GetSourceLine(context).ToLocalChecked());
            const char* sourceline_string = ToCString(sourceline);
            fprintf(stderr, "%s\n",sourceline_string);

            int start = message->GetStartColumn(context).FromJust();
            for (int i = 0; i < start; i++) {
                fprintf(stderr, " ");
            }

            int end = message->GetEndColumn(context).FromJust();
            for (int i = start; i < end; i++) {
                fprintf(stderr, "^");
            }

            fprintf(stderr, "\n");
            String::Utf8Value stack_trace(
                try_catch->StackTrace(context).ToLocalChecked());
            if (stack_trace.length() > 0) {
                const char* stack_trace_string = ToCString(stack_trace);
                fprintf(stderr, "%s\n",stack_trace_string);
            }

        }

    }



    int Start(int argc, char* argv[]) {
        // Initialize V8.
        V8::InitializeICU();
        Platform* platform = platform::CreateDefaultPlatform();
        V8::InitializePlatform(platform);
        V8::Initialize();

        // Create a new Isolate and make it the current one.
        ArrayBufferAllocator allocator;
        Isolate::CreateParams create_params;
        create_params.array_buffer_allocator = &allocator;
        Isolate* isolate = Isolate::New(create_params);
        {
            Isolate::Scope isolate_scope(isolate);

            // Create a stack-allocated handle scope.
            HandleScope handle_scope(isolate);

            // Create a new context.
            Local<Context> context = CreateContext(isolate);
            Environment* env = CreateEnvironment(isolate, context, argc, argv,event_base_new());

            // Enter the context for compiling and running the hello world script.
            Context::Scope context_scope(context);

            RunMain(isolate, argc, argv);
            
            //event_base_dispatch(env->event_base());
            event_base_loop(env->event_loop(), EVLOOP_NO_EXIT_ON_EMPTY);

            // Create a string containing the JavaScript source code.
            //Local<String> source =
            //String::NewFromUtf8(isolate, "print('hello world')",
             //                   NewStringType::kNormal).ToLocalChecked();

            // Compile the source code.
            //Local<Script> script = Script::Compile(context, source).ToLocalChecked();

            // Run the script to get the result.
            //Local<Value> result = script->Run(context).ToLocalChecked();

            // Convert the result to an UTF8 string and print it.
            //String::Utf8Value utf8(result);
            printf("**********");
        }

        // Dispose the isolate and tear down V8.
        isolate->Dispose();
        V8::Dispose();
        V8::ShutdownPlatform();
        delete platform;
        return 0;
    }

    int RunMain(Isolate* isolate, int argc, char* argv[]) {
        for (int i = 1; i< argc; i++) {
            const char* str = argv[i];
            Local<String> file_name =
            String::NewFromUtf8(isolate, str,NewStringType::kNormal).ToLocalChecked();

            Local<String> source;

            if(!ReadFile(isolate, str).ToLocal(&source)) {
                fprintf(stderr, "Error reading %s\n", str);
                continue;
            }

            if( !ExecuteString(isolate, source, file_name, false, true))
                return 1;

        }
    }
    
    
    void Require(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);
        
        if (args.Length() < 1) {
            isolate->ThrowException(Exception::TypeError(
                                                         String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }
        const char* file_name = *String::Utf8Value(args[0]->ToString(isolate));
        Local<String> source;
        if(!ReadFile(isolate, file_name).ToLocal(&source)){
            fprintf(stderr, "Error reading %s\n", file_name);
            return;
        }
       
        TryCatch try_catch(isolate);
        ScriptOrigin origin(args[0]->ToString(isolate));
        Local<Context> context(isolate->GetCurrentContext());
        Local<Script> script;
        
        if(Script::Compile(context, source, &origin).ToLocal(&script)) {
            Local<Value> result;
            if (!script->Run(context).ToLocal(&result)) {
                assert(try_catch.HasCaught());
                ReportException(isolate, &try_catch);
                return;
            } else {
                assert(!try_catch.HasCaught());
                if (!result->IsUndefined()) {
                    args.GetReturnValue().Set(result);
                }
            }
            
        }
        return;
        
    }
    
    
    void LoadScript(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);
        
        if (args.Length() < 1) {
            isolate->ThrowException(Exception::TypeError(
                                                         String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }
        const char* file_name = *String::Utf8Value(args[0]->ToString(isolate));
        Local<String> source;
        if(!ReadFile(isolate, file_name).ToLocal(&source)){
            fprintf(stderr, "Error reading %s\n", file_name);
            return;
        }
        
        args.GetReturnValue().Set(source);
        
    }
    
    
    
    void RunScript(const FunctionCallbackInfo<Value> &  args) {
        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);
        
        if (args.Length() < 1) {
            isolate->ThrowException(Exception::TypeError(
                                                         String::NewFromUtf8(isolate, "no source")));
            return;
        }
        
        ScriptOrigin origin(args[0]->ToString(isolate));
        Local<Context> context(isolate->GetCurrentContext());
        Local<Script> script;
        Local<String> source;
        source = args[0]->ToString(isolate);
        TryCatch try_catch(isolate);

        
        if(Script::Compile(context, source, &origin).ToLocal(&script)) {
            Local<Value> result;
            if (!script->Run(context).ToLocal(&result)) {
                assert(try_catch.HasCaught());
                ReportException(isolate, &try_catch);
                return;
            } else {
                assert(!try_catch.HasCaught());
                if (!result->IsUndefined()) {
                    args.GetReturnValue().Set(result);
                }
            }
            
        }
        return;
        
    }
    
    extern "C" void mynode_module_register(void *m) {
        struct mynode_module* mp = reinterpret_cast<struct mynode_module*>(m);
        
        mp->nm_link = modlist_builtin;
        modlist_builtin = mp;
    }
    
    struct mynode_module* get_builttin_module(const char* name) {
        struct mynode_module* mp;
        
        for (mp = modlist_builtin; mp != NULL; mp=mp->nm_link) {
            if(strcmp(mp->nm_modname, name) == 0) {
                break;
            }
        }
        
        //assert(mp != NULL);
        return (mp);
    }
  
    static void Binding(const FunctionCallbackInfo<Value> & args) {
        HandleScope handle_scope(args.GetIsolate());
        Isolate* isolate = args.GetIsolate();
        Environment* env = Environment::GetCurrent(args.GetIsolate());
        
        Local<String> module = args[0]->ToString();
        
        Local<Object> cache = env->binding_object_cache();
        Local<Object> exports;
        
        if(cache->Has(module)) {
            exports = cache->Get(module)->ToObject();
            args.GetReturnValue().Set(exports);
            return;
        }
        
        char buff[1024];
        unsigned char* modulename = new unsigned char[module->Utf8Length()];
        module->WriteOneByte(modulename);
        snprintf(buff, sizeof(buff), "binding %s", modulename);
        
        Local<Array> modules = env->module_load_list_array();
        uint32_t len = modules->Length();
        modules->Set(len, OneByteString(isolate, buff));
       
        
        mynode_module* load_module = get_builttin_module((char*)modulename);
        
        if(load_module != NULL) {
            exports = Object::New(env->isolate());
            
            Local<Value> unused = Undefined(env->isolate());
            load_module->nm_context_register_func(exports,unused,
                                                  env->context(),
                                                  load_module->nm_priv);
            cache->Set(module, exports);
           
            args.GetReturnValue().Set(exports);
            
        } else if(!strcmp((char*)modulename, "constants")) {
            exports = Object::New(env->isolate());
            DefineConstants(exports);
            cache->Set(module, exports);
            args.GetReturnValue().Set(exports);
        }
        
        
        
        
    }
    Environment* CreateEnvironment(v8::Isolate* isolate,
                                   v8::Handle<v8::Context> context,
                                   int argc,
                                   const char* const* argv,
                                    struct event_base* base
                                   ){
        HandleScope handle_scope(isolate);
        Context::Scope context_scope(context);
        Environment *env = Environment::New(context,base);
        return env;
    }


}
