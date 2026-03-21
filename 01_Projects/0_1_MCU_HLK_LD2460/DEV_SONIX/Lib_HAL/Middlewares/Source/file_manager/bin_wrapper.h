#ifndef __BIN_WRAPPER_H__
#define __BIN_WRAPPER_H__

#include "file_wrapper.h"
#include "File_Bin.h"

//=============================================================================
//                  Structure Declaration
//=============================================================================
typedef struct _BIN_RES_T
{
    FIL    *fp;
    uint8_t mode;
    uint8_t is_eof;
} BIN_RES_T;

extern TYPE_WRAPPER BIN_Wrapper;

#endif /* __BIN_WRAPPER_H__ */
