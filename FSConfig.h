/*****************************************************
 * Created by Julian on 8/10/15.
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

#ifndef FASTSNAIL_FSCONFIG_H
#define FASTSNAIL_FSCONFIG_H

#define FSALLOCATOR_DEBUG

/* pack size default value:
 * clang: 8 byte
 * gcc: 4 byte
 * cl(vc): 8 byte
 * */
#define FSALLOCATOR_PACK_SIZE 8

#define FSALLOCATOR_DEFAULT_ARRAY_LENGTH 64

#define FSALLOCATOR_MAX_BLOCK_SIZE  1024

#endif //FASTSNAIL_FSCONFIG_H
