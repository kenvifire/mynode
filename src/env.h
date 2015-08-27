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
#include <event2/event.h>

namespace mynode {
#ifndef NODE_ISOLATE_SLOT
#define NODE_ISOLATE_SLOT 3
#endif
    class Environment {
        
    private:
        class IsolateData {
        public:
            static inline IsolateData* GetOrCreate(v8::Isolate* isolate,
                                                   struct event_base* loop);
            static inline IsolateData* Get(v8::Isolate* isolate);
            inline struct event_base* event_loop() const;
            inline v8::Isolate* isolate() const;
            
            inline explicit IsolateData(v8::Isolate* isolate, struct event_base* loop);
        private:
            struct event_base* const event_loop_;
            v8::Isolate* const isolate_;
        };
        
        IsolateData* isolate_data;
        v8::Persistent<v8::Context> context_;
        v8::Persistent<v8::Object> binding_object_cache_;
        v8::Persistent<v8::Array> module_load_list_array_;
        inline Environment(v8::Local<v8::Context> context,struct event_base* event_base);
        
        
  
    public:
        static inline Environment* GetCurrent(v8::Isolate* isolate);
        static inline Environment* GetCurrent(v8::Local<v8::Context> context);
        
        static inline Environment* New(v8::Local<v8::Context> context, struct event_base* base);
        
        inline void AssignToContext(v8::Local<v8::Context> context);
        
        // property methods
        inline v8::Isolate* isolate() const {
            return isolate_data->isolate();
        }
        
        inline v8::Local<v8::Object> binding_object_cache() const ;
       
        inline void set_binding_object_cache(v8::Local<v8::Object> value) ;
       
        inline v8::Local<v8::Array> module_load_list_array() const;
        
        inline void set_module_load_list_array(v8::Local<v8::Array> value);
        
        inline v8::Local<v8::Context> context() const;
        
        inline void set_context(v8::Local<v8::Context> value);
        
        inline event_base* event_loop();
        
  
     
        
    };
    
   
}

#endif /* defined(__mynode__env__) */
