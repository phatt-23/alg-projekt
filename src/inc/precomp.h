#ifndef __precomp_h__
#define __precomp_h__

// includes from C++ stl
#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <cstdint>
#include <cassert>
#include <cstring>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <utility>
#include "colours.h"

#define __iot_def_out__ "iot_output.txt"
#define __buffer_len__  256

// flags and messages for debugging
#define __file_line__ printf("in " __itl__ __blu__ __bld__ __FILE__ __reset__ " at " __bld__ __blu__ __itl__ "%d" __reset__ " ", __LINE__);
#define __function__  printf("fn " __bld__ __grn__ __itl__ "%s" __reset__, __PRETTY_FUNCTION__);
#define __info__      printf(__bld__ __bg_wht__ __blk__"." __bg_blu__ __blk__ "info" __reset__ __bld__ __bg_wht__ __blk__ "." __reset__ " ");
#define __error__ printf(__bld__ __bg_wht__ __blk__ "{" __bg_red__ __blk__ "error" __reset__ __bld__ __bg_wht__ __blk__ "}" __reset__ " ");
#define __endl__      puts("");
#define __info_all__  __info__ __file_line__ __function__ printf(__bld__ " $" __reset__ " ");
#define __error_all__ __error__ __file_line__ __function__ printf(__bld__ " $" __reset__ " ");


#if 0 // 1 if debugging
    #define __decoder_dbg__     true
    #define __measurement_dbg__ true
    #define __interval_dbg__    true
#else // release
    #define __decoder_dbg__     false
    #define __measurement_dbg__ false
    #define __interval_dbg__    false
#endif


#endif//__precomp_h__
