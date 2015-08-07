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

#include "FSAllocator.h"

#pragma mark - implement FSAllocator::_FSBlock

FSAllocator::_FSBlock::_FSBlock(unsigned long size)
:_block(NULL)
,_size(size)
,_previous(NULL)
,_next(NULL)
{
    FSAllocator::_FSBlock **block = (FSAllocator::_FSBlock **)malloc(sizeof(FSAllocator::_FSBlock *) + size);
    if (block) {
        blocks[0] = this;
        _block = blocks[1];
    }
}

FSAllocator::_FSBlock::~_FSBlock(void) {
    if (_block) {
        FSAllocator::_FSBlock **block = (FSAllocator::_FSBlock **)_block;
        block--;
        free(block);
    }
}

#pragma mark - implement FSAllocator::_FSBlockChain

FSAllocator::_FSBlockChain::_FSBlockChain(unsigned long blockSize)
:_blockSize(blockSize)
,_chainRoot(NULL)
{

}

FSAllocator::_FSBlockChain::~_FSBlockChain(void) {
    FSAllocator::_FSBlock *lastBlock = _chainRoot;
    while (lastBlock != NULL) {
        lastBlock = lastBlock->next();
        delete lastBlock;
    }
}

FSAllocator::_FSBlock * FSAllocator::_FSBlockChain::borrowBlock(void) {
    FSAllocator::_FSBlock *block = NULL;
    if (_chainRoot == NULL) {
        block = new FSAllocator::_FSBlock(_blockSize);
    } else {
        block = _chainRoot;
        _chainRoot = block->next();
        block->setPrevious(NULL);
        block->setNext(NULL);
    }
    return block;
}

bool FSAllocator::_FSBlockChain::returnBlock(FSAllocator::_FSBlock *block) {
    if (block == NULL || _blockSize != block->size()) {
        return false;
    }

    if (_chainRoot == NULL) {
        _chainRoot = block;
        _chainRoot->setPrevious(NULL);
        _chainRoot->setNext(NULL);
    } else {
        FSAllocator::_FSBlock *lastBlock = _chainRoot;
        while (lastBlock->next() != NULL) {
            lastBlock = lastBlock->next();
        }
        lastBlock->setNext(block);
        block->setPrevious(lastBlock);
        block->setNext(NULL);
    }

    return true;
}

#pragma mark - implement FSAllocator

FSAllocator::FSAllocator(void)
:_blockChain(NULL)
,_chainCount(0)
{

}

FSAllocator::~FSAllocator(void) {

}
