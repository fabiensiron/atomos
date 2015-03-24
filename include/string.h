#ifndef _STRING_H
#define _STRING_H

#ifndef NULL
#define NULL ((void*) 0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

extern char* reverse (const char*);
extern char* strcpy (char*, const char*);
extern char* strcat (char*, const char*);
extern int strcmp (const char*, const char*);
extern char* strchr (const char*, char);
extern int strspn (const char*, const char*);
extern char* strpbrk (const char*, const char*);
extern char* strstr (const char*, const char*);
extern int strlen (const char*);
extern char* strtok (char*, const char*);

#endif
