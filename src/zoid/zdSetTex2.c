#include "types.h"

extern void MemCpy(u8 *source, u8 *destination, s32 size);
extern void DCFlushRange(void *memory, u32 size);
extern void GXInvalidateTexAll(void);
extern void OSReport(const char *format, ...);

s32 zdSetTex2(u8 *texture, u8 *image, s32 size)
{
    MemCpy(texture + 0x40, image, size);
    DCFlushRange(texture + 0x40, size);
    DCFlushRange(image, size);
    GXInvalidateTexAll();
    OSReport("imgsize=%d tsize=%d \n", size, size);
    return 1;
}
