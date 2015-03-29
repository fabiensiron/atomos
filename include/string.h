#ifndef _STRING_H
#define _STRING_H

#ifndef NULL
#define NULL ((void*) 0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

extern char* strcpy (char*, const char*);
extern int strcmp (const char*, const char*);
extern int strlen (const char*);

#endif
