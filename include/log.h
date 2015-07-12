#ifndef _LOG_H
#define _LOG_H

#include <include/stdio.h>

#define STATE_OK      0
#define STATE_FAILED  1
#define STATE_NOTHING 2

#define TYPE_HEXA     0
#define TYPE_STRING   8
#define TYPE_UINT     4

extern void klog (char* str_, u32 *arg_, u8 status_);

#endif /* _LOG_H */
