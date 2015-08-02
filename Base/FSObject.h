/*****************************************************
 * Created by Julian on 2015/8/2.
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

#ifdef __cplusplus
extern "C" {
#endif

struct fsObject;
typedef struct fsObject fsObject;

void * fsObject_create(void);

void * fsObject_retain(void *object);

void * fsObject_release(void *object);

unsigned int fsObject_referenceCount(void *object);

#ifdef __cplusplus
}
#endif

#endif //FASTSNAIL_FSOBJECT_H
