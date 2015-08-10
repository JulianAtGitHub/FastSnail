//
// Created by Julian on 8/10/15.
//

#ifndef FASTSNAIL_TESTFSALLOCATOR_H
#define FASTSNAIL_TESTFSALLOCATOR_H

#include <stdlib.h>
#include <time.h>
#include <new>

#include "../Base/FSAllocator.h"

class CTestFSAllocator {
    unsigned int m_ui;
    unsigned short m_us;
    long m_l;
    char m_c;
    void *m_p;

public:
    CTestFSAllocator():m_ui(0),m_us(0),m_l(0),m_c(0),m_p(NULL){}

    unsigned int get_ui() { return m_ui; }
    unsigned short get_us() { return m_us; }
    long get_l() { return m_l; }
    char get_c() { return m_c; }
    void * get_p() { return m_p; }

    void set_ui(unsigned int ui) { m_ui = ui; }
    void set_us(unsigned short us) { m_us = us; }
    void set_l(long l) { m_l = l; }
    void set_c(char c) { m_c = c; }
    void set_p(void *p) { m_p = p; }
};

void testFSAllocator (void) {

    clock_t t_begin, t_end;
    const unsigned int instanceCount = 90000000;
    const float time_per_clock = 1.0/CLOCKS_PER_SEC;

    t_begin = clock();
    for (unsigned int i = 0; i < instanceCount; ++i) {
        CTestFSAllocator * instance = new CTestFSAllocator();
        delete instance;
    }
    t_end = clock();
    printf("operator new and delete cost time:%f\n", (t_end - t_begin)*time_per_clock);

    FSAllocator *allocator = new FSAllocator();

    t_begin = clock();
    for (unsigned int i = 0; i < instanceCount; ++i) {
        void *block = allocator->alloc(sizeof(CTestFSAllocator));
        CTestFSAllocator *instance = new (block) CTestFSAllocator;
        allocator->dealloc(instance);
    }
    t_end = clock();
    printf("use FSAllocator cost time:%f\n", (t_end - t_begin)*time_per_clock);

    delete allocator;
    printf("FSAllocator tested!\n");
}

#endif //FASTSNAIL_TESTFSALLOCATOR_H
