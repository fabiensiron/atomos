#ifndef _STDARG_H
#define _STDARG_H

typedef char* var_list;

#define va_start(AP, LASTARG) \
  (0) /* need to do */

void va_end (va_list); /* need to define */

#define va_end(AP)

#define va_arg(AP, TYPE) \
  (0) /* need to do */

#endif /* _STDARG_H */
