//
// Created by Emma on 2015/8/2.
//

#include <stdio.h>

#include "Base/FSObject.h"

int main (int argc, char **argv) {
    printf("Hello FastSnail!");

    /* test fsObject */
    fsObject *object = fsObject_create();
    object = fsObject_release(object);

    return 0;
}
