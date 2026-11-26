#pragma readonly_strings on
#include "dvd_file.h"
#include "video.h"
#include "fog.h"
#include "disk_error.h"

extern HSD_Fog *fogG;
extern s32 dOpen;
extern u8 adr[];
extern void sbk(s32 result, DVDFileInfo *file);
extern void OSReport(const char *format, ...);
extern void VIWaitForRetrace(void);
extern void HSD_FogSet(HSD_Fog *fog);
extern s32 DVDCheckDisk(void);
extern s32 DVDGetDriveStatus(void);
extern s32 DVDGetCommandBlockStatus(DVDCommandBlock *block);
extern void sPadAll(void);
extern void TEA_VoiceOff(void);
extern s32 strncmp(const char *a, const char *b, u32 n);

static inline void setEraseColor(GXColor color)
{
    GXColor erase = color;
    HSD_VIData.current.vi.clear_clr = erase;
}

void diskError(s32 mode)
{
    DVDFileInfo file;
    s32 state;
    DVDDiskID *id;

    (void)"LOADing\n";
    dOpen = 0;
    HSD_VISetBlack(0);
    HSD_VICopyXFB(HSD_RP_SCREEN);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
    HSD_VICopyXFB(HSD_RP_SCREEN);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
    for (;;) {
        diskError2(mode);
        DVDCancelAll();
        OSReport("D-");
        if (DVDConvertPathToEntrynum("ZOIDS.VS") == -1) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D3");
            continue;
        }
        if (!DVDOpen("ZOIDS.VS", &file)) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D4");
            continue;
        }
        if (!DVDReadAsyncPrio(&file, adr, 32, 0, sbk, 2)) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D6");
            continue;
        }
        for (;;) {
            DVDCheckDisk();
            state = DVDGetCommandBlockStatus(&file.cb);
            OSReport("%d.", state);
            if (state == DVD_STATE_END)
                break;
            if (state == DVD_STATE_BUSY)
                continue;
            if (state == DVD_STATE_WAITING)
                continue;
            if (state == DVD_STATE_NO_DISK)
                diskError2(DISK_ERROR_NO_DISK);
            else if (state == DVD_STATE_WRONG_DISK)
                diskError2(DISK_ERROR_WRONG_DISK);
            break;
        }
        DVDClose(&file);
        if (!DVDCheckDisk()) {
            OSReport("D/");
            mode = DISK_ERROR_COVER_OPEN;
            DVDClose(&file);
            continue;
        }
        mode = 0;
        id = DVDGetCurrentDiskID();
        if (id == 0)
            mode = 1;
        if (id != 0 && strncmp(id->gameName, "GZOJ", 4) != 0)
            mode = 1;
        if (id != 0 && strncmp(id->company, "DA", 2) != 0)
            mode = 1;
        if (mode != 0) {
            OSReport("Din");
            mode = DISK_ERROR_WRONG_DISK;
            continue;
        }
        if (!DVDOpen("ZOIDS.VS", &file)) {
            mode = DISK_ERROR_WRONG_DISK;
            OSReport("D7");
            continue;
        }
        break;
    }
    DVDCancelAll();
    DVDClose(&file);
    TEA_VoiceOff();
    OSReport("Dh");
    setEraseColor((GXColor){ 0, 0, 0, 0 });
    HSD_FogSet(0);
    HSD_StartRender(HSD_RP_SCREEN);
    HSD_EndRender();
    HSD_VICopyXFB(HSD_RP_SCREEN);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
    sPadAll();
    DVDGetDriveStatus();
    if (fogG != 0)
        HSD_FogSet(fogG);
    if (fogG != 0)
        HSD_VIData.current.vi.clear_clr = fogG->color;
}
