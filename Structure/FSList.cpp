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

#include "FSList.h"

FSList::FSListElement::FSListElement(FSObject *object)
:_next(NULL)
{
    setObject(object);
}

FSList::FSListElement::~FSListElement(void) {
    setObject(NULL);
}

FSList::FSList(void)
:_count(0)
,_head(NULL)
,_tail(NULL)
{

}

FSList::~FSList(void) {

}

void FSList::attachToHead(FSObject *object) {
    if (!object) {
        return;
    }

    FSListElement *element = new FSListElement(object);

    if (_count) {
        element->setNext(_head);
        _head = element;
    } else {
        _head = element;
        _tail = element;
    }

    ++ _count;
}

void FSList::attachToTail(FSObject *object) {
    if (!object) {
        return;
    }

    FSListElement *element = new FSListElement(object);

    if (_count) {
        _tail->setNext(element);
        _tail = element;
    } else {
        _head = element;
        _tail = element;
    }

    ++ _count;
}

FSObject * FSList::detachFromHead(void) {
    
}

FSObject * FSList::detachFromTail(void) {

}
