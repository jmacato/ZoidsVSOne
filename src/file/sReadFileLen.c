#pragma readonly_strings on
#include "dvd_file.h"

extern void OSReport(const char *format, ...);
extern void debug11(void);
extern void dspLoadNow(void);
extern void *malloc2(u32 size);
extern void free(void *memory);
extern s32 fReadO(DVDFileInfo *file, void *memory, s32 length);

void *sReadFileLen(char *name, s32 *size)
{
    DVDFileInfo file;
    s32 length;
    void *memory;

    (void)"LOADing\n";
    (void)"ZOIDS.VS";
    (void)"file error";
    (void)"\203f\203B\203X\203N\203J\203o\201[\202\252\212J\202\242\202\304\202\242\202\334\202\267\201B\203Q\201[\203\200\202\360\221\261\202\257\202\351\217\352\215\207\202\315\201A\n\203f\203B\203X\203N\203J\203o\201[\202\360\225\302\202\337\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"\203]\203C\203h\203o\201[\203T\203X\202\314\203f\203B\203X\203N\202\360\203Z\203b\203g\n\202\265\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"\202\261\202\314\203f\203B\203X\203N\202\315\203]\203C\203h\203o\201[\203T\203X\202\314\n\203f\203B\203X\203N\202\305\202\315\202\240\202\350\202\334\202\271\202\361\201B\n\203]\203C\203h\203o\201[\203T\203X\202\314\203f\203B\203X\203N\202\360\203Z\203b\203g\n\202\265\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"\203f\203B\203X\203N\202\360\223\307\202\337\202\334\202\271\202\361\202\305\202\265\202\275\201B\n\202\255\202\355\202\265\202\255\202\315\201A\226{\221\314\202\314\216\346\210\265\220\340\226\276\217\221\202\360\n\202\250\223\307\202\335\202\255\202\276\202\263\202\242\201B";
    (void)"\203G\203\211\201[\202\252\224\255\220\266\202\265\202\334\202\265\202\275\201B\n\226{\221\314\202\314\203p\203\217\201[\203{\203^\203\223\202\360\211\237\202\265\202\304\223d\214\271\202\360\n\202n\202e\202e\202\311\202\265\201A\226{\221\314\202\314\216\346\210\265\220\340\226\276\217\221\202\314\n\216w\216\246\202\311\217]\202\301\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"PreOpen:";
    (void)"heap alloc ";
    (void)"\203\201\203\202\203\212\202\252\221\253\202\350\202\334\202\271\202\361";
    if (size != 0)
        *size = 0;
    debug11();
    dspLoadNow();
    OSReport("loading file (%s) ...", name);
    if (!DVDOpen(name, &file)) {
        OSReport("cannot open file\n", name);
        return 0;
    }
    length = file.length;
    OSReport("size[%d]..", length);
    if (length != 0) {
        memory = malloc2((length + 31) & ~31);
        if (memory == 0) {
            OSReport("cannot allocate memory\n");
            DVDClose(&file);
            return 0;
        }
        OSReport("memAloc...[%X]....", memory);
        if (fReadO(&file, memory, length) < 0) {
            OSReport("cannot load file\n");
            DVDClose(&file);
            free(memory);
            OSReport("error\n");
            return 0;
        }
    }
    DVDClose(&file);
    OSReport("Done\n");
    if (size != 0)
        *size = length;
    return memory;
}
