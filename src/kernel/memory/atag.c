#include <kernel/memory/atag.h>

uint32_t get_mem_size(atag_t *tag)
{
#ifndef EMU_SWITCH
    while (tag->tag != NONE)
    {
        if (tag->tag == MEM)
        {
            return tag->mem.size;
        }
        tag = (atag_t *)(((uint32_t *)tag) + tag->tag_size);
    }
    return 0;
#else
    return 1024 * 1024 * 128;
#endif
}