#include "types.h"
extern s32 TEA_USBFileLenR2(void);
void *sReadFileLenUSB(char *name, s32 *size)
{
    return (void *)TEA_USBFileLenR2();
}
