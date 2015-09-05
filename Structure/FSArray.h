/*****************************************************
 * Created by Julian on 8/21/15.
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

#ifndef FASTSNAIL_FSARRAY_H
#define FASTSNAIL_FSARRAY_H

#include "Base/FSBase.h"
#include "Base/FSObject.h"

class FSArray : public FSObject {
    FSObject **_array;
    unsigned long _size;
    unsigned long _count;

protected:
    void enlarge(void);

public:
    FSArray(unsigned long size = 0);
    virtual ~FSArray(void);

    inline unsigned long count(void) { return _count; }

    FSObject * objectAt(unsigned long index);

    FSObject * push(FSObject *object);
    FSObject * pop(void);
};


#endif //FASTSNAIL_FSARRAY_H
