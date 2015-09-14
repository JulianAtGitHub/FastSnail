//
// Created by Julian on 8/21/15.
//

#ifndef FASTSNAIL_TESTFSOBJECT_H
#define FASTSNAIL_TESTFSOBJECT_H

#include <stdio.h>
#include "Base/FSObject.h"

class CTestFSObject : public FSObject {
    unsigned long m_l;

public:
    CTestFSObject():m_l(0) { }
};

void testFSObject(void) {

    printf("\ntest FSObject\n");

    FSObject *obj1 = new FSObject;
    obj1->retain();
    printf("obj1 retain count:%d\n", obj1->retainCount());
    obj1->release();
    obj1->release();

    CTestFSObject *obj2 = new CTestFSObject;
    printf("obj2 retain count:%d\n", obj1->retainCount());

    CTestFSObject *obj3 = obj2;
    obj2->link((FSObject **)&obj3);

    CTestFSObject *obj4 = obj2;
    obj2->link((FSObject **)&obj4);

    obj2->separate((FSObject **)&obj3);
    obj2->release();

}

#endif //FASTSNAIL_TESTFSOBJECT_H
