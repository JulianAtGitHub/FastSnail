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

#ifndef FASTSNAIL_FSDEFINE_H
#define FASTSNAIL_FSDEFINE_H

#include <stdlib.h>

#define fsAlloc(Type) calloc(1, sizeof(Type))

#define fsDealloc(Object) free(Object)

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif


#endif //FASTSNAIL_FSDEFINE_H
