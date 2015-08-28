#include <include/log.h>

#define LOG_STATE_OFFSET 60

static void fake_sleep () {
  for (int i = 0; i < 10000000; i++)
    ;
}

extern void _klog (char* str_, u32 *arg_, u8 status_) {

    static int number = 0;
    u8 state = status_ & 0x03;
    u8 type = status_ & 0x0c; 
    
    struct text_color_t tmp_color = text_color; 

    kprintf ("[0%i] %s", number, str_);

    if (arg_ != NULL) {
      switch (type) {
        case TYPE_STRING:
          kprintf (": %s", arg_);
          break;
        case TYPE_UINT:
          kprintf (": %i", *arg_);
          break;
        default:
          kprintf (": %x", *arg_);
          break;
      }
    }

    struct cursor_t tmp_cursor = get_cursor ();

    set_cursor (tmp_cursor.r, LOG_STATE_OFFSET);
    
    switch (state) {
      case STATE_OK:
        set_fg_color (GREEN);
        kprintf ("[OK]");
        break;
      case STATE_FAILED:
        set_fg_color (RED);
        kprintf ("[FAILED]");
        break;
    }

  
    kprintf ("\n");

    fake_sleep ();

    set_bg_color (tmp_color.bg); 
    set_fg_color (tmp_color.fg);

    number++;
}

