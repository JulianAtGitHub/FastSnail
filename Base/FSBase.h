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

#ifndef FASTSNAIL_FSBASE_H
#define FASTSNAIL_FSBASE_H

#include <assert.h>

class FSAllocator;

extern FSAllocator *g_fsAllocator;

#ifdef __cplusplus
extern "C" {
#endif

extern void FSLog(const char *format, ...);

#ifdef __cplusplus
}
#endif

#define FSAssert(condition, format, ...) \
    FSLog(format, ##__VA_ARGS__); \
    assert(condition)

#endif //FASTSNAIL_FSBASE_H
