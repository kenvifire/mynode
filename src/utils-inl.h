//
//  utils-inl.h
//  mynode
//
//  Created by kenvi.zhu on 15/8/12.
//
//

#ifndef mynode_utils_inl_h
#define mynode_utils_inl_h

#include "utils.h"

namespace mynode {
    template <class TypeName>
    inline v8::Local<TypeName> StrongPersistentToLocal(
                                                       const v8::Persistent<TypeName>& persistent) {
        return *reinterpret_cast<v8::Local<TypeName>*>(
                                                       const_cast<v8::Persistent<TypeName>*>(&persistent));
    }
    
    inline v8::Local<v8::String> OneByteString(v8::Isolate* isolate,
                                           const char* data,
                                           int length ){
    return v8::String::NewFromOneByte(isolate,
                                      reinterpret_cast<const uint8_t*>(data),
                                      v8::String::kNormalString,
                                        length);
    }
}


#endif
