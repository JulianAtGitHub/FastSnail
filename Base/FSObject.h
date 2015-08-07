//
// Created by Julian on 8/6/15.
//

#ifndef FASTSNAIL_FSOBJECT_H
#define FASTSNAIL_FSOBJECT_H

class FSObject {
    unsigned int _retainCount;

public:
    FSObject(void);
    virtual ~FSObject(void);

    unsigned int retainCount(void);
    FSObject * retain(void);
    void release(void);
};

#endif //FASTSNAIL_FSOBJECT_H
