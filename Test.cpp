//
// Created by Julian on 8/6/15.
//

#include <stdio.h>

#include "FastSnail.h"
#include "Test/TestFSAllocator.h"
#include "Test/TestFSObject.h"

int main (int argc, char **argv) {

    FSInitialize();

    printf("Hello FastSnail!\nLet's do some test!\n");

    testFSAllocator();

    testFSObject();

    return 0;
}