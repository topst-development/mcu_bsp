
MEMORY {

    // Reserve 0x8000 bytes for use by target-resident code or debug monitor
    dram_memory  : ORIGIN = 0x06000000,	LENGTH = 0x80000-0x680-DMA_NC_SIZE
    // Reserve 0x680 bytes for arm stack
    stack_memory  : ORIGIN = 0x06000000 + 0x80000 -DMA_NC_SIZE -0x680, LENGTH = 0x680
    // Reserve DMA_NC_SIZE bytes for non-cacheable area, The dma address is valid only physical address(0xC0000000), it can not use mirrored mem address(0x06000000)
    dma_memory  : ORIGIN = 0xC0000000 + 0x80000-DMA_NC_SIZE, LENGTH = DMA_NC_SIZE
    // S-NOR code area XIP
    flash_memory : ORIGIN = 0x08200000, LENGTH = 0x00200000 //64MByte
}

//
// Program layout for running out of RAM.
//
//

SECTIONS
{

//
// The text segment
//

    .picbase                                            : > flash_memory
    .text                                               :{ "startup.o(.text)" } > .
    .syscall                                            : > .
    .intercall                                          : > .
    .interfunc                                          : > .
    .fixaddr                                            : > .
    .fixtype                                            : > .
    .rodata                              		: > .
    .secinfo                                            : > .
    .ROM.data 	                     ALIGN(4)ROM(.data) : > .
    .ROM.bss 	                        ALIGN(4) NOLOAD : > .

//
// The data segment
//

    .pidbase                                  ALIGN(16) : > dram_memory
    .data                                       ALIGN(4):{vector.o(.text) *(.data)}> .
    .bss                                        ALIGN(0x20): > .
    .ghcovfz					  CLEAR : > .
    .ghcovcz					  CLEAR : > .
    .ghcovdz					  CLEAR : > .
//
// These special symbols mark the bounds of RAM and ROM memory.
//
    __ghs_romstart  = MEMADDR(flash_memory);
    __ghs_romend    = ADDR(.ROM.data);
    __ghs_ramstart  = ADDR(.data);
    __ghs_ramend    = ENDADDR(.bss);
    __ghs_bssstart = ADDR(.bss);
    __arm_stack = MEMADDR(stack_memory);
    __nc_dmastart = MEMADDR(dma_memory);
        
}
