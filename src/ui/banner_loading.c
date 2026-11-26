#pragma readonly_strings on
#include "model_archive.h"

extern ModelArchive *menu_zoidp[100], *menu_personp[58];
extern s32 fexist(char *name);
extern s32 sprintf(char *destination, const char *format, ...);

void ttlMenuLoadZoidBanner(void)
{
    char filename[48];
    s16 i;
    for (i = 0; i < 100; i++) {
        sprintf(filename, "menu/picture/sz%02d.dat", i);
        if (menu_zoidp[i] == 0) {
            if (fexist(filename) == 1)
                menu_zoidp[i] = LoadArc2(filename);
            else {
                menu_zoidp[i] = 0;
                menu_zoidp[i] = LoadArc2("menu/picture/sz00.dat");
            }
        }
    }
}

void ttlMenuLoadPersonBanner(void)
{
    char filename[48];
    s16 i;
    for (i = 0; i < 58; i++) {
        sprintf(filename, "menu/picture/sp%02d.dat", i);
        if (menu_personp[i] == 0) {
            if (fexist(filename) == 1)
                menu_personp[i] = LoadArc2(filename);
            else {
                menu_personp[i] = 0;
                menu_personp[i] = LoadArc2("menu/picture/sp00.dat");
            }
        }
    }
}
