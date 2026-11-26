#include "types.h"

extern char menusaveloadfilename[];
extern char menusaveloadcommentname[];
extern char *strcpy(char *dst, const char *src);

void ttlMenuSaveDataSetFileName(void)
{
    strcpy(menusaveloadfilename, "ZOIDSVS.TEA");
    strcpy(menusaveloadcommentname, "\203v\203\214\203C\203f\201[\203^\201@\201@                                 ");
}
