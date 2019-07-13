#ifndef _EXTRAS_FILE_H
#define _EXTRAS_FILE_H

#include <stdio.h>

#define _IO_getc_unlocked(_fp) \
       (_IO_BE ((_fp)->_IO_read_ptr >= (_fp)->_IO_read_end, 0) \
    ? __uflow (_fp) : *(unsigned char *) (_fp)->_IO_read_ptr++)

int fgetc(FILE *fp);

#endif