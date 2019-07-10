; linker info
.section ".text.boot"
.global _start

; Entrypoint
_start:
    ; Disable cores 2,3,4 (only use single core for kernel)
    mrc p15, #0, r1, c0, c0, #5
    and r1, r1, #3
    cmp r1, #0
    bne halt

    ; Set stack base to 0x8000, directly after the kernel
    mov sp, #0x8000

    ; Store the global memory start and end addrs
    ldr r4, =__bss_start
    ldr r9, =__bss_end

    ; Clear all global vars
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b       2f

1:
    stmia r4!, {r5-r8}

2:
    cmp r4, r9
    blo 1b

    ; Jump to start of kernel_main()
    ldr r3, =kernel_main
    blx r3

; Do nothing when kernel finishes
halt:
    wfe
    b halt