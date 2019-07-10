#include <kernel/uart.h>
#include <extras/stdio.h>
#include <extras/stdlib.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    // Input buffer
    char buf[256];
    
    // Declare as unused
    (void)r0;
    (void)r1;
    (void)atags;

    uart_init();
    puts("Hello, kernel World!\r\n");

    while (1)
    {
        gets(buf, 256);
        puts(buf);
        putc('\n');
    }
}
