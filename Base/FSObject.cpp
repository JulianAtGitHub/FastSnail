//
// Created by Julian on 8/6/15.
//

#include "FSObject.h"

FSObject::FSObject(void)
:_retainCount(1) {

}

FSObject::~FSObject(void) {

}

unsigned int FSObject::retainCount(void) {
    return _retainCount;
}

FSObject * FSObject::retain(void) {
    ++_retainCount;
    return this;
}

void FSObject::release(void) {

}

