/*****************************************************
 * Created by Julian on 2015/8/2.
 *      /^\    /^\
 *     {  O}  {  O}
 *      \ /    \ /
 *      //     //       _------_
 *     //     //     ./~        ~-_
 *    / ~----~/     /              \
 *  /         :   ./       _---_    ~-
 * |  \________) :       /~     ~\   |
 * |        /    |      |  :~~\  |   |
 * |       |     |      |  \___-~    |
 * |        \ __/`\______\.        ./
 *  \                     ~-______-~\.
 *  .|                                ~-_
 * /_____________________________________~~____
 *
*****************************************************/

#include "FSDefine.h"

#include "FSObject.h"

struct fsObject {
    unsigned int _reference_count;
};

void * fsObject_create(void) {
    fsObject *self = (fsObject *)fsAlloc(fsObject);
    self->_reference_count = 1;
    return (void *)self;
}

void * fsObject_retain(void *object) {
    fsObject *self = (fsObject *)object;
    self->_reference_count += 1;
    return (void *)self;
}

void * fsObject_release(void *object) {
    fsObject *self = (fsObject *)object;
    self->_reference_count -= 1;
    if (self->_reference_count == 0) {
        fsDealloc(self);
        self = 0;
    }
    return (void *)self;
}

unsigned int fsObject_referenceCount(void *object) {
    fsObject *self = (fsObject *)object;
    return self->_reference_count;
}