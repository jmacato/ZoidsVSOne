#pragma readonly_strings on
#include "map_info.h"

extern void ZeroMemory(void *dst, u32 size);
extern void MemCpy(void *src, void *dst, u32 size);
extern s32 sprintf(char *buffer, const char *format, ...);
extern void *sReadFileU(char *name, s32 usb);
extern void free(void *memory);

static u8 adr[64];
MapInfo mgI;

MapInfo *rdMapInfo(s32 mode, s32 number)
{
    char name[256];
    void *data;

    (void)adr;
    ZeroMemory(&mgI, sizeof(MapInfo));
    sprintf(name, "menu/map_info_dat/%s%03d.mg", mode == 0 ? "B" : "M", number);
    data = sReadFileU(name, 0);
    if (data == 0)
        return 0;
    MemCpy(data, &mgI, sizeof(MapInfo));
    free(data);
    return &mgI;
}
