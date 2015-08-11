//
//  utils.h
//  mynode
//
//  Created by kenvi.zhu on 15/8/9.
//
//

#ifndef mynode_utils_h
#define mynode_utils_h

#include "include/v8.h"

namespace mynode {
    template <class TypeName>
    inline v8::Local<TypeName> StrongPersistentToLocal(
        const v8::Persistent<TypeName>& persistent);
    
    inline v8::Local<v8::String> OneByteString(v8::Isolate* isolate,
                                               const char* data,
                                               int length = -1);
}
#endif
