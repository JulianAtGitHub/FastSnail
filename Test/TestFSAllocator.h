//
// Created by Julian on 8/10/15.
//

#ifndef FASTSNAIL_TESTFSALLOCATOR_H
#define FASTSNAIL_TESTFSALLOCATOR_H

#include "../Base/FSAllocator.h"

void testFSAllocator (void) {
    FSAllocator *allocator = new FSAllocator();

    void *b1 = allocator->alloc(20);
    void *b2 = allocator->alloc(35);
    void *b3 = allocator->alloc(35);
    allocator->dealloc(b1);
    allocator->dealloc(b3);
    allocator->dealloc(b2);

    delete allocator;

    printf("FSAllocator tested!");
}

#endif //FASTSNAIL_TESTFSALLOCATOR_H
