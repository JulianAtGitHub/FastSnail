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

#include <string.h>

#include "FSArray.h"
#include "FSConfig.h"

FSArray::FSArray(unsigned long size)
:_size(size)
,_count(0)
{
    if (!_size) {
        _size = FSARRAY_DEFAULT_SIZE;
    }

    _array = (FSObject **)calloc(_size, c_FSObjectPoint_size);
}

FSArray::~FSArray(void) {
    for (unsigned long i = 0; i < _count; ++i) {
        FSObject *object = _array[i];
        if (object) {
            object->release();
        }
    }
    free(_array);
}

void FSArray::enlarge(void) {
    unsigned long size = _size << 1;
    FSObject **array = (FSObject **)calloc(size, c_FSObjectPoint_size);
    memcpy(array, _array, _size * c_FSObjectPoint_size);
    free(_array);
    _array = array;
    _size = size;
}

FSObject * FSArray::objectAt(unsigned long index) {
    if (index >= _count) {
        return NULL;
    }
    return _array[index];
}

FSObject * FSArray::push(FSObject *object) {
    if (object) {
        if (_size == _count) {
            enlarge();
        }
        _array[_count ++] = object;
        object->retain();
    }
    return object;
}

FSObject * FSArray::pop(void) {
    FSObject *object = NULL;
    if (_count > 0) {
        object = _array[-- _count];
        object->release();
    }
    return object;
}
