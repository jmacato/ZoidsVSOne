#include "archive.h"
#include "os_alloc.h"

extern s32 HSD_GetHeap(void);
extern s32 usrHeap;
extern s32 dbgAlloc;

#pragma dont_inline on
static void debugFilePurge(void *memory)
{
    /* The shipped debug hook only checks its pointer and returns. */
    if (memory == 0)
        return;
}

void sArchivePurge(HSD_Archive *archive)
{
    if (archive != 0) {
        HSD_ArchiveFreeAll(archive);
        debugFilePurge(archive);
        dbgAlloc--;
    }
}

void free(void *memory)
{
    if (memory != 0) {
        dbgAlloc--;
        if (usrHeap == -1)
            OSFreeToHeap(HSD_GetHeap(), memory);
        else
            OSFreeToHeap(usrHeap, memory);
        debugFilePurge(memory);
    }
}
