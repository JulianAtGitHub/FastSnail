//
// Created by Julian on 8/6/15.
//

#ifndef FASTSNAIL_FSOBJECT_H
#define FASTSNAIL_FSOBJECT_H

#include <stdlib.h>

class FSObject {
    unsigned int _retainCount;

public:
    static void * operator new (size_t size);
    static void operator delete (void* ptr);

    FSObject(void);
    virtual ~FSObject(void);

    inline unsigned int retainCount(void) { return _retainCount; }
    FSObject * retain(void);
    void release(void);
};

#endif //FASTSNAIL_FSOBJECT_H
