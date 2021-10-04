#ifndef Util_H
#define Util_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/common.h"

using namespace v8;

namespace No {
    namespace Util {
        char * GetErrorByErrno();
        void Log(const char * str);
        Local<String> newStringToLcal(Isolate * isolate, const char * str, NewStringType type = NewStringType::kNormal);
        MaybeLocal<String> newString(Isolate * isolate, const char * str, NewStringType type= NewStringType::kNormal);
        // 设置对象的属性，属性为函数
        void setMethod(Isolate *isolate, Local<ObjectTemplate> recv, const char *name, FunctionCallback callback);
        void setObjectTemplateValue(Isolate *isolate, Local<ObjectTemplate> recv, const char *name, Local<Data> value);
        void setObjectValue(Isolate *isolate, Local<Object> recv, const char *name, Local<Value> value);
        class PersistentToLocal {
            public:
                template <typename TypeName>
                static Local<TypeName> Strong(const PersistentBase<TypeName>& persistent) {
                    return *reinterpret_cast<Local<TypeName>*>(
                        const_cast<PersistentBase<TypeName>*>(&persistent)
                    );
                };
        };
        template <typename T>
        struct KeyCompare {
            bool operator()(T* x, T* k) const {
                return x->id >= k->id;
            }
        };

        class IdGenerator {
            public:
                IdGenerator(uint64_t _id = 0): id(_id) {}
                uint64_t getNextId() {
                    return ++id;
                }
            private:
                uint64_t id;
        };
        void GetError(V8_ARGS);
        void Init(Isolate* isolate, Local<Object> target);
    }
}

#endif 
