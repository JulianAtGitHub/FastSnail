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

void * FSObject::_FSReference::operator new (size_t size) {
    return g_fsAllocator->alloc(size);
}

void FSObject::_FSReference::operator delete (void* ptr) {
    g_fsAllocator->dealloc(ptr);
}

void * FSObject::operator new (size_t size) {
    return g_fsAllocator->alloc(size);
}

void FSObject::operator delete (void* ptr) {
    g_fsAllocator->dealloc(ptr);
}

FSObject::FSObject(void)
:_referenceList(NULL)
,_retainCount(1)
{

}

FSObject::~FSObject(void) {
    _FSReference *element = NULL;
    while (_referenceList) {
        element = _referenceList;
        _referenceList = element->_next;
        delete element;
    }
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

void FSObject::link(FSObject **objRef) {
    if (!objRef) {
        return;
    }

    _FSReference *element = _referenceList;
    _FSReference *tail = NULL;
    while (element) {
        if (element->_reference == objRef) {
            return;
        } else {
            tail = element;
            element = element->_next;
        }
    }

    element = new _FSReference(objRef);
    *(element->_reference) = this;
    if (tail) {
        tail->_next = element;
    } else {
        _referenceList = element;
    }
}

void FSObject::separate(FSObject **objRef) {
    if (!objRef) {
        return;
    }

    _FSReference *previous = NULL;
    _FSReference *element = _referenceList;
    while (element) {
        if (element->_reference == objRef) {
            if (previous) {
                previous->_next = element->_next;
            } else {
                _referenceList = element->_next;
            }
            *(element->_reference) = NULL;
            delete element;
            return;
        } else {
            previous = element;
            element = element->_next;
        }
    }
}

