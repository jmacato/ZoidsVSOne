#include "types.h"

#define NULL 0

/* Softimage PIC image: skips the header, the channel packets and the RLE scanlines */
u8 *skipPicData(u8 *data)
{
    s32 alpha;
    s32 x2;
    u8 chained;
    s32 count;
    s32 run;
    s32 run2;
    s32 i2;
    s32 i;
    s32 x;
    s32 width;
    u32 magic;
    s32 height;
    s32 y;

    magic = *((u32 *)data)++;
    if (magic != 0x5380F634)
        return NULL;
    width = *(u16 *)(data + 88);
    height = *(u16 *)(data + 90);
    data += 100;
    alpha = 0;
    do {
        chained = data[0];
        alpha |= data[3];
        data += 4;
    } while (chained != 0);
    alpha &= 0x10;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x += run) {
            count = *data++;
            if (count == 128) {
                run = *(u16 *)data;
                data += 5;
            } else if (count > 127) {
                run = count - 127;
                data += 3;
            } else {
                run = count;
                run++;
                for (i = 0; i < run; i++)
                    data += 3;
            }
        }
        if (alpha != 0) {
            for (x2 = 0; x2 < width; x2 += run2) {
                count = *data++;
                if (count == 128) {
                    run2 = *(u16 *)data;
                    data += 3;
                } else if (count > 127) {
                    run2 = count - 127;
                    data += 1;
                } else {
                    run2 = count;
                    run2++;
                    for (i2 = 0; i2 < run2; i2++)
                        data += 1;
                }
            }
        }
    }
    return data;
}
