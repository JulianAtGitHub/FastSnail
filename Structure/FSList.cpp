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
,_previous(NULL)
{
    setObject(object);
}

FSList::FSListElement::~FSListElement(void) {
    setObject(NULL);
    setPrevious(NULL);
    setNext(NULL);
}

FSList::FSList(void)
:_count(0)
,_head(NULL)
,_tail(NULL)
{

}

FSList::~FSList(void) {
    while (_count) {
        FSListElement *element = _head;
        _head = element->next();
        _head->setPrevious(NULL);
        element->setNext(NULL);
        element->release();
        -- _count;
    }
}

FSList::FSListElement * FSList::elementAt(unsigned long index) {
    FSListElement *element = NULL;
    if (index < _count) {
        element = _head;
        for (unsigned long i = 0; i < index ; ++i) {
            element = element->next();
        }
    }

    return element;
}

void FSList::attachToHead(FSObject *object) {
    if (!object) {
        return;
    }

    FSListElement *element = new FSListElement(object);

    if (_count) {
        element->setNext(_head);
        _head->setPrevious(element);
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
        element->setPrevious(_tail);
        _tail->setNext(element);
        _tail = element;
    } else {
        _head = element;
        _tail = element;
    }

    ++ _count;
}

FSObject * FSList::detachFromHead(void) {
    FSObject *object = NULL;
    if (_count) {
        FSListElement *element = _head;
        _head = element->next();
        if (_head) {
            element->setNext(NULL);
            _head->setPrevious(NULL);
        } else {
            _tail = NULL;
        }
        object = element->object();
        element->release();
        -- _count;
    }

    return object;
}

FSObject * FSList::detachFromTail(void) {
    FSObject *object = NULL;
    if (_count) {
        FSListElement *element = _tail;
        _tail = element->previous();
        if (_tail) {
            element->setPrevious(NULL);
            _tail->setNext(NULL);
        } else {
            _head = NULL;
        }
        object = element->object();
        element->release();
        -- _count;
    }

    return object;
}

FSObject * FSList::objectAt(unsigned long index) {
    FSListElement *element = elementAt(index);
    return (element ? element->object() : NULL);
}
