#include <kernel/uart.h>
#include <extras/stdio.h>
#include <extras/stdlib.h>
#include <kernel/memory/atag.h>
#include <kernel/memory/mem.h>
#include <kernel/video/gpu.h>
#include <kernel/timer.h>
#include <kernel/io/sdcard.h>
#include <extras/string.h>

#include <kernel/ubasic/ubasic.h>

void console(void){
    printf("READY\n");

    char program[8192];
    char buf[128];

    long line = 10;

    while (1){
        printf("[%d] ", line);

        // Clear the buffer
        memset(buf, 0, 128);

        // Read the next line of code to the program from buf
        gets(buf, 128);

        // Check if "run" is inputted
        if (strncmp(buf, "run", 3) == 0){
            // Run the program
            ubasic_init(program);

            line = 10;

            do {
                ubasic_run();
            } while (!ubasic_finished());

            // Clear the program for next use
            memset(program, 0, 8192);
        } else {
            // Append line to program
            strcat(program, short_itoa(line, 10));
            strcat(program, " ");
            strcat(program, buf);
            strcat(program, "\n");
            line += 10;
        }
    }
}

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
    timer_init();
    printf("Timer Initalized\n");

#ifndef NO_SDCARD
    if (sd_init())
    {
        printf("EMMC Initalized\n");
    }
    else
    {
        printf("EMMC FAILED Initialization! FS functions may not work\n");
    }
#else
    printf("EMMC disabled at compile time. Skipping\n");
#endif

    printf("uBASIC Loaded with debug flag: %d", getDebugFlag());

    // printf("-- Welcome to PICOS --\n");
    printf("\n\n\
     ____ ___ ____ ___  ____  \n\
    |  _ \\_ _/ ___/ _ \\/ ___| \n\
    | |_) | | |  | | | \\___ \\ \n\
    |  __/| | |__| |_| |___) |\n\
    |_|  |___\\____\\___/|____/ \n\n\n");

    console();

    printf("STOP\n");
    while (1)
    {
        // memset(buf, 0, 256);
        // gets(buf, 256);
        // puts(buf);
        // putc('\n');
    }
}
