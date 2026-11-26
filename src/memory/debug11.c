#include "types.h"

extern s32 HSD_GetHeap(void);
extern void *OSAllocFromHeap(s32 heap, u32 size);
extern void HSD_Free(void *ptr);
extern void OSReport(const char *format, ...);

void debug11(void)
{
    void *blocks[1024];
    s32 count;
    s32 i;
    u8 frame_padding[4];

    for (i = 0; i < 1024; i++) {
        blocks[i] = 0;
    }
    for (count = 0; count < 1024; count++) {
        blocks[count] = OSAllocFromHeap(HSD_GetHeap(), 0x10000);
        if (blocks[count] == 0)
            break;
    }
    count *= 64;
    for (i = 0; i < 1024; i++) {
        if (blocks[i] != 0)
            HSD_Free(blocks[i]);
        blocks[i] = 0;
    }
    OSReport("%4dM %4dK byte(s)\n", count / 1024, count & 1023);
}
