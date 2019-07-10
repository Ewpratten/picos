#include <kernel/uart.h>
#include <extras/stdio.h>
#include <extras/stdlib.h>
#include <kernel/memory/atag.h>
#include <kernel/video/gpu.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    // Input buffer
    char buf[256];

    // Declare as unused
    (void)r0;
    (void)r1;
    (void)atags;

    mem_init((atag_t *)atags);
    gpu_init();
    printf("GPU Initalized\n");
    uart_init();
    printf("UART Initalized\n");

    while (1)
    {
        memset(buf, 0, 256);
        gets(buf, 256);
        puts(buf);
        putc('\n');
    }
}
