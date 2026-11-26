#include "dvd_file.h"
#include "archive.h"
#include "disk_error.h"

extern void OSReport(const char *, ...);
extern s32 dOpen;
extern s32 rCbkR;
extern void rCbk(s32 result, DVDFileInfo *file);
extern void *malloc2(u32 size);
extern void free(void *memory);
extern void *sReadFileLen(char *name, s32 *size);
extern s32 usbForce;
extern void *sReadFileUSB(char *name);
extern void *sReadFileLenUSB(char *name, s32 *size);

#pragma dont_inline on
static s32 chkVS3(void)
{
    DVDFileInfo file;
    if (!DVDOpen("ZOIDS.VS", &file))
        return 0;
    DVDClose(&file);
    return 1;
}

s32 sReadPre(void)
{
    if (dOpen == 0 && DVDCheckDisk())
        return 0;
    if (dOpen != 0) {
        DVDCheckDisk();
        OSReport("PreOpen:");
        if (DVDCheckDisk()) {
            OSReport("Cl:");
            if (!chkVS3()) {
                OSReport("V3n");
                while (DVDCheckDisk())
                    diskError3(DISK_ERROR_NO_DISK);
            } else {
                dOpen = 0;
                OSReport("V3a");
                return 0;
            }
        } else
            OSReport("Op:");
    }
    diskError(DISK_ERROR_NONE);
    OSReport("PreRet:");
    dOpen = 0;
    return 1;
}

s32 fileLen(char *name)
{
    DVDFileInfo file;
    s32 length;
    if (!DVDOpen(name, &file))
        return 0;
    length = file.length;
    DVDClose(&file);
    return length;
}

static s32 fReadO2(DVDFileInfo *file, void *memory, s32 length, s32 offset)
{
    s32 result;
    rCbkR = 0;
    OSReport("Syns");
    result = DVDReadAsyncPrio(file, memory, (length + 31) & ~31, offset, rCbk, 2);
    OSReport("Syne");
    if (result == 0) {
        OSReport("Synr");
        return -1;
    }
    for (;;) {
        s32 state;
        if (!DVDCheckDisk())
            diskError(DISK_ERROR_NONE);
        state = DVDGetCommandBlockStatus(&file->cb);
        if (state == DVD_STATE_END)
            break;
        if (state == DVD_STATE_BUSY)
            continue;
        if (state == DVD_STATE_WAITING)
            continue;
        diskError(DISK_ERROR_NONE);
    }
    return 1;
}

s32 fexist(char *name)
{
    sReadPre();
    return DVDConvertPathToEntrynum(name) != -1;
}

static s32 fReadO(DVDFileInfo *file, void *memory, s32 length)
{
    return fReadO2(file, memory, length, 0);
}

HSD_Archive *sArchiveLoad(char *name, void **data)
{
    s32 length;
    HSD_Archive *archive;
    void *memory;
    if (data != 0)
        *data = 0;
    OSReport("archive load %s ", name);
    if (!fexist(name)) {
        OSReport("where?\n");
        return 0;
    }
    memory = sReadFileLen(name, &length);
    if (memory == 0)
        return 0;
    if (data != 0)
        *data = memory;
    archive = malloc2(sizeof(HSD_Archive));
    if (archive == 0) {
        OSReport("lost \n");
        free(memory);
        if (data != 0)
            *data = 0;
        return 0;
    }
    OSReport("archive ok \n");
    HSD_ArchiveParse(archive, memory, length);
    return archive;
}

HSD_Archive *sLoad(char *name, void **data)
{
    sReadPre();
    return sArchiveLoad(name, data);
}

static void *sReadFile(char *name)
{
    sReadPre();
    return sReadFileLen(name, 0);
}

void *sReadFileU(char *name, s32 usb)
{
    if (usbForce != 0)
        usb = 1;
    if (usb != 0)
        return sReadFileUSB(name);
    return sReadFile(name);
}

void *sReadFileLenU(char *name, s32 usb, s32 *size)
{
    if (usbForce != 0)
        usb = 1;
    if (usb != 0)
        return sReadFileLenUSB(name, size);
    return sReadFileLen(name, size);
}
