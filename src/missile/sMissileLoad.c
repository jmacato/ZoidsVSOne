#include "types.h"
#include "model_archive.h"

extern s32 sprintf(char *buffer, const char *format, ...);
extern void OSReport(const char *format, ...);

void *sMissileLoad(char *name)
{
    char path[256];
    sprintf(path, "missile/%s.dat", name);
    OSReport("mis loa now // %s\n", path);
    return LoadArc2(path);
}
