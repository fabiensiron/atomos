#ifndef _STDARG_H
#define _STDARG_H

#define __va_rounded_size(TYPE) \
  (((sizeof (TYPE) + sizeof (int) -  1) / sizeof (int)) * sizeof (int))

typedef char* va_list;

#define va_start(AP, LASTARG) \
  (AP = ((char *) &(LASTARG) + __va_rounded_size(LASTARG))) /* need to do */

//void va_end (va_list); /* need to define */


#define va_arg(AP, TYPE) \
  (AP += __va_rounded_size(TYPE), \
   *((TYPE *)(AP - __va_rounded_size(TYPE)))) /* need to do */


#define va_end(AP) \
  ;

#endif /* _STDARG_H */
