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

#ifndef FASTSNAIL_FSLIST_H
#define FASTSNAIL_FSLIST_H

#include "Base/FSObject.h"

class FSList : public FSObject {

public:
    class FSListElement : public FSObject {
        FSListElement *_previous;
        FSObject *_object;
        FSListElement *_next;

    public:
        FSListElement(FSObject *object);
        virtual ~FSListElement(void);

        inline void setPrevious(FSListElement *previous) {
            if (_previous) { _previous->release(); }
            _previous = previous;
            if (previous) { previous->retain(); }
        }
        inline FSListElement *previous(void) { return _previous; }

        inline void setNext(FSListElement *next) {
            if (_next) { _next->release(); }
            _next = next;
            if (next) { next->retain(); }
        }
        inline FSListElement *next(void) { return _next; }

        inline void setObject(FSObject *object) {
            if (_object) { _object->release(); }
            _object = object;
            if (object) { object->retain(); }
        }
        inline FSObject *object(void) { return _object; }
    };

private:
    unsigned long _count;
    FSListElement *_head;
    FSListElement *_tail;

protected:
    FSListElement * elementAt(unsigned long index);

public:
    FSList(void);
    virtual ~FSList(void);

    inline unsigned long count(void) { return _count; }

    void attachToHead(FSObject *object);
    void attachToTail(FSObject *object);

    FSObject * detachFromHead(void);
    FSObject * detachFromTail(void);

    FSObject * objectAt(unsigned long index);
};


#endif //FASTSNAIL_FSLIST_H
