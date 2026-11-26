#include "types.h"

extern void *sReadFileU(char *name, s32 mode);
extern void free(void *memory);

s32 chkVS(void)
{
    free(sReadFileU("ZOIDS.VS", 0));
    return 0;
}
