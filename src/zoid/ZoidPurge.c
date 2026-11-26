#pragma readonly_strings on
#include "zoid.h"

extern void OSReport(const char *format, ...);
extern void sWeaponUnMountAll(ZoidState *zoid);
extern void ZoidCopyMatReset(ZoidState *zoid);
extern void stStJobjUnref(JointPose *pose);
extern void jobjUnrefAll(HSD_JObj *joint);
extern void free(void *memory);
extern void sArchivePurge(struct HSD_Archive *archive);
extern void ZeroMemory(void *dst, u32 size);

void ZoidPurge(ZoidState *zoid)
{
    s32 i;

    if (zoid == 0)
        return;
    if (zoid->name[0] == 0)
        return;
    OSReport("zoid purge! [%s] \n", zoid);
    sWeaponUnMountAll(zoid);
    ZoidCopyMatReset(zoid);
    if (zoid->pose != 0) {
        stStJobjUnref(zoid->pose);
        zoid->pose = 0;
    }
    if (zoid->joint != 0) {
        jobjUnrefAll(zoid->joint);
        zoid->joint = 0;
    }
    if (zoid->ai != 0) {
        free(zoid->ai);
        zoid->ai = 0;
    }
    if (zoid->control != 0) {
        free(zoid->control);
        zoid->control = 0;
    }
    if (zoid->archive != 0) {
        sArchivePurge(zoid->archive);
        zoid->archive = 0;
    }
    if (zoid->archive_data != 0)
        free(zoid->archive_data);
    zoid->archive_data = 0;
    ZeroMemory(zoid, sizeof(ZoidState));
    for (i = 0; i < 16; i++) {
        if (zoid == &Zoid[i])
            zoid->index = i;
    }
}
