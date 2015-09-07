//
//  mynode_file.h
//  mynode
//
//  Created by Hannah Zhang on 15/9/5.
//
//

#ifndef __mynode__mynode_file__
#define __mynode__mynode_file__

#include <stdio.h>
#include "mynode.h"
#include "include/v8.h"

namespace mynode {
    void InitFs(v8::Handle<v8::Object> target,
                v8::Handle<v8::Value> unused,
                v8::Handle<v8::Context> context,
                void *priv);
    
}

#endif /* defined(__mynode__mynode_file__) */
