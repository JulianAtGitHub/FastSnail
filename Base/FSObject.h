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

#ifndef FASTSNAIL_FSOBJECT_H
#define FASTSNAIL_FSOBJECT_H

#include <stdlib.h>

class FSObject {

public:
    struct _FSReference {
        static void * operator new (size_t size);
        static void operator delete (void* ptr);

        _FSReference *_next;
        FSObject **_reference;

        _FSReference(FSObject **ref):_next(NULL) ,_reference(ref) { }
    };

private:
    _FSReference *_referenceList;
    unsigned int _retainCount;

public:
    static void * operator new (size_t size);
    static void operator delete (void* ptr);

    FSObject(void);
    virtual ~FSObject(void);

    /* string reference */
    inline unsigned int retainCount(void) { return _retainCount; }
    FSObject * retain(void);
    void release(void);

    /* weak reference */
    void link(FSObject **objRef);
    void separate(FSObject **objRef);
};

#endif //FASTSNAIL_FSOBJECT_H
