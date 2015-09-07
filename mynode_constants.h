//
//  mynode_constants.h
//  mynode
//
//  Created by Hannah Zhang on 15/9/7.
//
//

#ifndef __mynode__mynode_constants__
#define __mynode__mynode_constants__

#include <stdio.h>
#include "mynode.h"
#include "include/v8.h"
namespace mynode {
    void DefineConstants(v8::Handle<v8::Object> target);
}

#endif /* defined(__mynode__mynode_constants__) */
