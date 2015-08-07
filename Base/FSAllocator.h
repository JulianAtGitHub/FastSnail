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


class FSAllocator {

    class _FSBlock {
        void *_block;
        unsigned long _size;
        _FSBlock *_previous;
        _FSBlock *_next;

    public:
        _FSBlock(unsigned long size);
        virtual ~_FSBlock(void);

        inline unsigned long size(void) { return _size; }

        inline _FSBlock * previous(void) { return _previous; }
        inline void setPrevious(_FSBlock *previous) { _previous = previous; }

        inline _FSBlock * next(void) { return _next; }
        inline void setNext(_FSBlock *next) { _next = next; }
    };

    class _FSBlockChain {
        unsigned long _blockSize;
        _FSBlock *_chainRoot;

    public:
        _FSBlockChain(unsigned long blockSize);
        virtual ~_FSBlockChain(void);

        inline unsigned long blockSize(void) { return _blockSize; }

        _FSBlock * borrowBlock(void);
        bool returnBlock(_FSBlock *block);
    };

    _FSBlockChain *_blockChain;
    unsigned int _chainCount;

public:
    FSAllocator(void);
    virtual ~FSAllocator(void);

};


#endif //FASTSNAIL_FSALLOCATOR_H
