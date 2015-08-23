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
#include <assert.h>

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
    
    template <typename TypeName>
    void Wrap(v8::Local<v8::Object> object, TypeName* pointer) {
        object->SetAlignedPointerInInternalField(0, pointer);
    }
    
    template <class TypeName>
    inline v8::Local<TypeName> PersistentToLocal(
                                                 v8::Isolate* isolate,
                                                 const v8::Persistent<TypeName>& persistent) {
        if (persistent.IsWeak()) {
            return WeakPersistentToLocal(isolate, persistent);
        } else {
            return StrongPersistentToLocal(persistent);
        }
    }
    
    template <class TypeName>
    inline v8::Local<TypeName> WeakPersistentToLocal(
                                                     v8::Isolate* isolate,
                                                     const v8::Persistent<TypeName>& persistent) {
        return v8::Local<TypeName>::New(isolate, persistent);
    }
    
    template <typename TypeName>
    TypeName* Unwrap(v8::Local<v8::Object> object) {
        assert(!object.IsEmpty());
        assert(object->InternalFieldCount() > 0);
        void* pointer = object->GetAlignedPointerFromInternalField(0);
        return static_cast<TypeName*>(pointer);
    }
}


#endif
