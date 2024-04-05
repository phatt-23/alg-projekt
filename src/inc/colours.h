#ifndef __colours_h__
#define __colours_h__

#if __unix__ 

#define __reset__     "\x1b[0m"

#define __blk__       "\x1b[30m"
#define __red__       "\x1b[31m"
#define __grn__       "\x1b[32m"
#define __yel__       "\x1b[33m"
#define __blu__       "\x1b[34m"
#define __mag__       "\x1b[35m"
#define __cyn__       "\x1b[36m"
#define __wht__       "\x1b[37m"

#define __bg_blk__    "\x1b[40m"
#define __bg_red__    "\x1b[41m"
#define __bg_grn__    "\x1b[42m"
#define __bg_yel__    "\x1b[43m"
#define __bg_blu__    "\x1b[44m"
#define __bg_mag__    "\x1b[45m"
#define __bg_cyn__    "\x1b[46m"
#define __bg_wht__    "\x1b[47m"

#define __bld__        "\x1b[1m"
#define __itl__        "\x1b[3m"
#define __uln__        "\x1b[4m"

#endif//__unix__

#endif//__colours_h__
