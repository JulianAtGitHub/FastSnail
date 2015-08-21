//
// Created by Julian on 8/21/15.
//

#ifndef FASTSNAIL_TESTFSOBJECT_H
#define FASTSNAIL_TESTFSOBJECT_H

#include "../Base/FSObject.h"

class CTestFSObject : public FSObject {
    unsigned long m_l;

public:
    CTestFSObject():m_l(0) { }
};

void testFSObject(void) {

    printf("\ntest FSObject\n");

    FSObject *obj1 = new FSObject;
    obj1->retain();
    obj1->release();
    obj1->release();

    CTestFSObject *obj2 = new CTestFSObject;
    obj2->release();

}

#endif //FASTSNAIL_TESTFSOBJECT_H
