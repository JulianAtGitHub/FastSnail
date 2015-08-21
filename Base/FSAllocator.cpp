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

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "FSAllocator.h"

static size_t s_blockPointSize = sizeof(FSAllocator::_FSBlock *);
static size_t s_blockArrayPointSize = sizeof(FSAllocator::_FSBlockArray *);

#pragma mark - implement FSAllocator::_FSBlock

FSAllocator::_FSBlock::_FSBlock(size_t size)
:_block(NULL)
,_size(size)
,_index(0)
{
    if (_size > 0) {
        void *block = malloc(_size + FSALLOCATOR_PACK_SIZE);
        _block = (void *)((uintptr_t)block + FSALLOCATOR_PACK_SIZE);
        _FSBlock **address = (_FSBlock **)block;
        *address = this;
    }
}

FSAllocator::_FSBlock::~_FSBlock(void) {
    if (_block) {
        void *block = (void *)((uintptr_t)_block - FSALLOCATOR_PACK_SIZE);
        free(block);
    }
}

#pragma mark - implement FSAllocator::_FSBlockArray

FSAllocator::_FSBlockArray::_FSBlockArray(void)
:_length(FSALLOCATOR_DEFAULT_ARRAY_LENGTH)
,_count(0)
{
    _blocks = (_FSBlock **)calloc(_length, s_blockPointSize);
}

FSAllocator::_FSBlockArray::~_FSBlockArray(void) {
    if (_blocks) {
        free(_blocks);
    }
}

void FSAllocator::_FSBlockArray::enlargeBlockArray(void) {
    unsigned long newLength = _length << 1;
    void *blocks = calloc(newLength, s_blockPointSize);
    memcpy(blocks, _blocks, _length * s_blockPointSize);
    free(_blocks);
    _blocks = (_FSBlock **)blocks;
    _length = newLength;
}

void FSAllocator::_FSBlockArray::addBlock(_FSBlock *block) {
    if (block) {
        if (_count == _length) {
            enlargeBlockArray();
        }
        block->setIndex(_count);
        _blocks[_count ++] = block;
    }
}
FSAllocator::_FSBlock * FSAllocator::_FSBlockArray::removeBlock(void) {
    _FSBlock *block = NULL;
    if (_count > 0) {
        block = _blocks[-- _count];
        _blocks[_count] = 0;
    }
    return block;
}
FSAllocator::_FSBlock * FSAllocator::_FSBlockArray::removeBlock(unsigned long index) {
    _FSBlock *block = NULL;
    if (index < _count) {
        _FSBlock *tail = _blocks[-- _count];
        _blocks[_count] = 0;
        block = _blocks[index];
        _blocks[index] = tail;
        tail->setIndex(index);
    }
    return block;
}

#pragma mark - implement FSAllocator

FSAllocator::FSAllocator(void) {
    _arrayCount = (FSALLOCATOR_MAX_BLOCK_SIZE >> 2);
    _blockArraies = (_FSBlockArray **)calloc(_arrayCount, s_blockArrayPointSize);
#ifdef FSALLOCATOR_DEBUG
    _deliveredArraies = (_FSBlockArray **)calloc(_arrayCount, s_blockArrayPointSize);
#endif
}

FSAllocator::~FSAllocator(void) {
    _FSBlockArray *blockArray = NULL;
    _FSBlock *block = NULL;
    for (unsigned int index = 0; index < _arrayCount; ++index) {
        blockArray = _blockArraies[index];
        if (blockArray) {
            while ((block = blockArray->removeBlock()) != NULL) {
                delete block;
            }
        }
        delete blockArray;
    }

#ifdef FSALLOCATOR_DEBUG
    for (unsigned int index = 0; index < _arrayCount; ++index) {
        blockArray = _deliveredArraies[index];
        delete blockArray;
    }
#endif
}

void FSAllocator::enlarge(unsigned int multiple) {
    if (multiple > 1 ) {
        unsigned int arrayCount = _arrayCount * multiple;

        _FSBlockArray **blockArraies = (_FSBlockArray **)calloc(arrayCount, s_blockArrayPointSize);
        memcpy(blockArraies, _blockArraies, _arrayCount * s_blockArrayPointSize);
        free((void *) _blockArraies);
        _blockArraies = blockArraies;

#ifdef FSALLOCATOR_DEBUG
        _FSBlockArray **deliveredArraies = (_FSBlockArray **)calloc(arrayCount, s_blockArrayPointSize);
        memcpy(deliveredArraies, _deliveredArraies, _arrayCount * s_blockArrayPointSize);
        free((void *) _deliveredArraies);
        _deliveredArraies = deliveredArraies;
#endif

        _arrayCount = arrayCount;
    }
}

void * FSAllocator::alloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    unsigned int index = (unsigned int)((size - 1) >> 2);
    if (index >= _arrayCount) {
        enlarge( (unsigned int)ceilf( (index + 1)/(float)_arrayCount) );
    }

    _FSBlock *block = NULL;
    _FSBlockArray *blockArray = _blockArraies[index];
    if ( !blockArray || !(blockArray->count()) ) {
        block = new _FSBlock((index + 1) << 2);
    } else {
        block = blockArray->removeBlock();
    }

#ifdef FSALLOCATOR_DEBUG
    blockArray = _deliveredArraies[index];
    if (!blockArray) {
        blockArray = new _FSBlockArray();
        _deliveredArraies[index] = blockArray;
    }
    blockArray->addBlock(block);
#endif

    return block->block();
}

void FSAllocator::dealloc(void *block) {
    if (block == NULL) {
        return;
    }

    block = (void *)((uintptr_t)block - FSALLOCATOR_PACK_SIZE);
    _FSBlock **address = (_FSBlock **)block;
    _FSBlock *fsBlock = address[0];
    unsigned int index = (unsigned int)(fsBlock->size() >> 2) - 1;

    _FSBlockArray *blockArray = NULL;
#ifdef FSALLOCATOR_DEBUG
    blockArray = _deliveredArraies[index];
    if (blockArray) {
        blockArray->removeBlock(fsBlock->index());
    }
#endif

    blockArray = _blockArraies[index];
    if (!blockArray) {
        blockArray = new _FSBlockArray();
        _blockArraies[index] = blockArray;
    }
    blockArray->addBlock(fsBlock);
}
