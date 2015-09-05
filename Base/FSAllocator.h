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

#include "FSConfig.h"

class FSAllocator {

public:
    class _FSBlock {
        void *_block;
        size_t _size;
        unsigned long _index;

    public:
        _FSBlock(size_t size);
        ~_FSBlock(void);

        inline void * block(void) { return _block; }
        inline size_t size(void) { return _size; }

        inline unsigned long index(void) { return _index; }
        inline void setIndex(unsigned long index) { _index = index; }
    };

    class _FSBlockArray {
        _FSBlock **_blocks;
        unsigned long _length;
        unsigned long _count;

        bool enlargeBlockArray(void);
    public:
        _FSBlockArray(void);
        ~_FSBlockArray(void);

        inline unsigned long count (void) { return _count; }

        void addBlock(_FSBlock *block);
        _FSBlock *removeBlock(void);
        _FSBlock *removeBlock(unsigned long index);
    };

private:
    unsigned int _arrayCount;
    _FSBlockArray **_blockArraies;
#ifdef FSALLOCATOR_DEBUG
    _FSBlockArray **_deliveredArraies;
#endif

protected:
    void enlarge(unsigned int multiple = 2);

public:
    FSAllocator(void);
    virtual ~FSAllocator(void);

    void *alloc(size_t size);
    void dealloc(void *block);
};


#endif //FASTSNAIL_FSALLOCATOR_H
