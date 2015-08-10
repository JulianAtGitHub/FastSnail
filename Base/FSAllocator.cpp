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

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#include "FSAllocator.h"

#pragma mark - implement FSAllocator::_FSBlock

FSAllocator::_FSBlock::_FSBlock(size_t size)
:_block(NULL)
,_size(size)
,_previous(NULL)
,_next(NULL)
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

#pragma mark - implement FSAllocator

FSAllocator::FSAllocator(void) {
    _arraySize = (FSALLOCATOR_MAX_BLOCK_SIZE >> 2) + 1;
    _blockArray = (_FSBlock **)calloc(_arraySize, sizeof(FSAllocator::_FSBlock *));
#ifdef FSALLOCATOR_DEBUG
    _deliveredBlockArray = (_FSBlock **)calloc(_arraySize, sizeof(FSAllocator::_FSBlock *));
#endif
}

FSAllocator::~FSAllocator(void) {
    for (unsigned int index = 0; index < _arraySize; ++index) {
        if (_blockArray[index]) {
            _FSBlock *head = _blockArray[index];
            _FSBlock *element = NULL;
            while (head) {
                element = head;
                head = element->next();
                delete element;
            }
        }
    }

#ifdef FSALLOCATOR_DEBUG

#endif
}

void FSAllocator::enlargeBlockArray(unsigned int multiple) {
    if (multiple > 0 ) {
        unsigned int newArraySize = _arraySize * multiple;

        _FSBlock **blockArray = (_FSBlock **)calloc(newArraySize, sizeof(FSAllocator::_FSBlock *));
        memcpy(blockArray, _blockArray, _arraySize * sizeof(FSAllocator::_FSBlock *));
        free((void *)_blockArray);
        _blockArray = blockArray;

#ifdef FSALLOCATOR_DEBUG
        _FSBlock **deliveredBlockArray = (_FSBlock **)calloc(newArraySize, sizeof(FSAllocator::_FSBlock *));
        memcpy(deliveredBlockArray, _deliveredBlockArray, _arraySize * sizeof(FSAllocator::_FSBlock *));
        free((void *)_deliveredBlockArray);
        _deliveredBlockArray = deliveredBlockArray;
#endif

        _arraySize = newArraySize;
    }
}

void * FSAllocator::alloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    unsigned int index = (unsigned int)(size >> 2);
    if (index >= _arraySize) {
        enlargeBlockArray( (unsigned int)ceilf((index + 1)/(float)_arraySize) );
    }
    _FSBlock *fsBlock = NULL;
    if (_blockArray[index]) {
        fsBlock = _blockArray[index];
        _blockArray[index] = fsBlock->next();
        fsBlock->setPrevious(NULL);
        fsBlock->setNext(NULL);
        if (_blockArray[index]) {
            _blockArray[index]->setPrevious(NULL);
        }
    } else {
        fsBlock = new _FSBlock((index + 1) << 2);
    }

#ifdef FSALLOCATOR_DEBUG
    _FSBlock *head = _deliveredBlockArray[index];
    if (head) {
        head->setPrevious(fsBlock);
        fsBlock->setNext(head);
    }
    _deliveredBlockArray[index] = fsBlock;
#endif

    return fsBlock->block();
}

void FSAllocator::dealloc(void *block) {
    if (block == NULL) {
        return;
    }

    block = (void *)((uintptr_t)block - FSALLOCATOR_PACK_SIZE);
    _FSBlock **address = (_FSBlock **)block;
    _FSBlock *fsBlock = address[0];
    unsigned int index = (unsigned int)(fsBlock->size() >> 2) - 1;

#ifdef FSALLOCATOR_DEBUG
    _FSBlock *element = _deliveredBlockArray[index];
    while (element) {
        if (element == fsBlock) {
            if (element == _deliveredBlockArray[index]) {
                _deliveredBlockArray[index] = element->next();
            }
            if (element->previous()) {
                element->previous()->setNext(element->next());
            }
            if (element->next()) {
                element->next()->setPrevious(element->previous());
            }
            break;
        }
        element = element->next();
    }
#endif

    fsBlock->setNext(NULL);
    fsBlock->setPrevious(NULL);
    _FSBlock *head = _blockArray[index];
    if (head) {
        head->setPrevious(fsBlock);
        fsBlock->setNext(head);
    }
    _blockArray[index] = fsBlock;
}
