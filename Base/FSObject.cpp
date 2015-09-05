/*****************************************************
 * Created by Julian on 8/6/15.
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
#include "FSObject.h"
#include "FSBase.h"
#include "FSAllocator.h"

const size_t FSOBJECT_POINT_SIZE = sizeof(FSObject);

void * FSObject::operator new (size_t size) {
    return g_fsAllocator->alloc(size);
}

void FSObject::operator delete (void* ptr) {
    g_fsAllocator->dealloc(ptr);
}

FSObject::FSObject(void)
:_retainCount(1) {

}

FSObject::~FSObject(void) {

}

FSObject * FSObject::retain(void) {
    ++ _retainCount;
    return this;
}

void FSObject::release(void) {
    if ((-- _retainCount) == 0) {
        delete this;
    }
}

