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

#ifndef FASTSNAIL_FSALLOCATOR_H
#define FASTSNAIL_FSALLOCATOR_H

#include "../FSConfig.h"

class FSAllocator {

    class _FSBlock {
        void *_block;
        size_t _size;
        _FSBlock *_previous;
        _FSBlock *_next;

    public:
        _FSBlock(size_t size);
        virtual ~_FSBlock(void);

        inline void * block(void) { return _block; }
        inline size_t size(void) { return _size; }

        inline _FSBlock * previous(void) { return _previous; }
        inline void setPrevious(_FSBlock *previous) { _previous = previous; }

        inline _FSBlock * next(void) { return _next; }
        inline void setNext(_FSBlock *next) { _next = next; }
    };

    /* pack size default value:
     * clang: 8 byte
     * gcc: 4 byte
     * cl(vc): 8 byte
     * */
    _FSBlock **_blockArray;
#ifdef FSALLOCATOR_DEBUG
    _FSBlock **_deliveredBlockArray;
#endif
    unsigned int _arraySize;

protected:
    void enlargeBlockArray(unsigned int multiple);

public:
    FSAllocator(void);
    virtual ~FSAllocator(void);

    void *alloc(size_t size);
    void dealloc(void *block);
};


#endif //FASTSNAIL_FSALLOCATOR_H
