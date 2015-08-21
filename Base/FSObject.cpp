//
// Created by Julian on 8/6/15.
//

#include "FSObject.h"
#include "FSBase.h"

void * FSObject::operator new (size_t size) {
    return g_fsAllocator->alloc(size);
}

void FSObject::operator delete (void* ptr) {
    g_fsAllocator->dealloc(ptr);
}

FSObject::FSObject(void)
:_retainCount(1) {

}

FSObject::~FSObject(void) {

}

FSObject * FSObject::retain(void) {
    ++ _retainCount;
    return this;
}

void FSObject::release(void) {
    if ((-- _retainCount) == 0) {
        delete this;
    }
}

