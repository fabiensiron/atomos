#ifndef _LOG_H
#define _LOG_H

#include <include/stdio.h>
#include <include/config.h>
#include <include/time.h>

#ifdef DEBUG
# define klog(str_,arg_,status_) do{_klog(str_,arg_,status_);}while(0)
#else
# define klog(str_,arg_,status_)
#endif

#define STATE_OK      0
#define STATE_FAILED  1
#define STATE_NOTHING 2

#define TYPE_HEXA     0
#define TYPE_STRING   8
#define TYPE_UINT     4

#define SIZE_U32      16
#define SIZE_U16      32  
#define SIZE_U8       64  


extern void _klog (char* str_, u32 *arg_, u8 status_);

#endif /* _LOG_H */
