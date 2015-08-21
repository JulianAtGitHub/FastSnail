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

#include <stdlib.h>

#include "FastSnail.h"
#include "Base/FSBase.h"
#include "Base/FSAllocator.h"

FSAllocator *g_fsAllocator = NULL;

bool FSInitialize(void) {
    g_fsAllocator = new FSAllocator();
    return true;
}
