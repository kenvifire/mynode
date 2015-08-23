//
//  handle_warp.h
//  mynode
//
//  Created by Hannah Zhang on 15/8/22.
//
//

#ifndef __mynode__handle_wrap__
#define __mynode__handle_wrap__

#include <stdio.h>

#include "env.h"
#include "include/v8.h"
#include <event2/event.h>
#include "base-object.h"

namespace mynode {
   
    struct handle_t{
        struct event* event_;
        void* data;
    };
    
    class HandleWrap : public BaseObject {
        public:
        struct handle_t* GetHandler() {return handle__;}
        
        HandleWrap(Environment* env,
                   v8::Handle<v8::Object> object,
                   handle_t* handle
                   );
        
        
        
        private:
        struct handle_t* handle__;
        
        
    };
}

#endif /* defined(__mynode__handle_wrap__) */
