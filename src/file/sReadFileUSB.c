#include "types.h"
extern s32 TEA_USBFileR2(void);
void *sReadFileUSB(char *name)
{
    return (void *)TEA_USBFileR2();
}
