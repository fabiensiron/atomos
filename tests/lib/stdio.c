#include <stdio.h>


union u_size {
  int i;
  unsigned int u;
  unsigned long l;
  char c;
  void* p;
};

static void putc_i (char c_) {
  char str[] = {c_, 0};
  write (str);
}

static void putc_s (char* s_) {
  for (int i = 0; s_[i] != 0; i++)
    putc_i (s_[i]);
} 

struct stack_t {
  char buff[100];
  int head;
};

static void push (char c_, struct stack_t *s_) {
  s_->buff[s_->head] = c_;
  s_->head++;
}

static char pop (struct stack_t *s_) {
  if (s_->head == 0)
    return 0;
  s_->head--;
  return s_->buff[s_->head];
}

static char digits[] = "0123456789abcdef";

static void putint_i (unsigned int i_, int base_) {
  if (i_ == 0) {
    putc_i ('0');
  } else {
    struct stack_t stack;
    stack.head = 0;
 /*   if (i_ < 0) {
      putc_i ('-'); 
      i_ *= -1;
    } */
    do {
      char loc_ = digits[i_%base_]; 
      push (loc_, &stack);
      i_ /= base_;
    } while (i_);

    do {
      char tmp = pop (&stack);
      putc_i (tmp);
    } while (stack.head > 0); 
  }
}

int vprintf (char* fmt_, va_list args_) {
  for (int i = 0; fmt_[i] != '\0'; i++) {
    if (fmt_[i] == '%') {
      union u_size u;
      u.l = va_arg(args_, unsigned long);
      switch (fmt_[i+1]) {
        case 'd':{
          putint_i(u.i,10);
          }break;
        case 'i': {
          putint_i(u.i,10);
          }break;
        case 's':{
          putc_s (u.p);
          }break;
        case 'c':{
          putc_i (u.c);
          }break;
        case 'x':{
          putc_s("0x");
          putint_i(u.u,16);
          }break;
      }

      i++;
    } else {
      putc_i (fmt_[i]);
    }
  }
  return 0;
}

extern int printf (char* fmt, ...) {
  int ret;
  va_list ap;

  va_start(ap,fmt);
  ret = vprintf (fmt, ap);
  va_end(ap);

  return ret;
}

