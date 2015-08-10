//
//  utils.c
//  mynode
//
//  Created by kenvi.zhu on 15/8/9.
//
//

#include "utils.h"

template <class TypeName>
inline v8::Local<TypeName> StrongPersistentToLocal(
                                                   const v8::Persistent<TypeName>& persistent) {
    return *reinterpret_cast<v8::Local<TypeName>*>(
                                                   const_cast<v8::Persistent<TypeName>*>(&persistent));
}