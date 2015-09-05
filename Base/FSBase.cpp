/*****************************************************
 * Created by Julian on 9/5/15.
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

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "FSBase.h"

#ifdef __cplusplus
extern "C" {
#endif

static const unsigned int s_log_buff_size = 10240;
static char *s_log_buff = NULL;

void FSLog(const char *format, ...) {
    if(format) {
        if (!s_log_buff) {
            s_log_buff = (char *)malloc((s_log_buff_size + 1) * sizeof(char));
        }
        va_list ap;
        va_start(ap, format);
        vsnprintf(s_log_buff, s_log_buff_size, format, ap);
        va_end(ap);
        printf("FastSnail: %s\n", s_log_buff);
    }
}

#ifdef __cplusplus
}
#endif