#include "joint.h"
#include "model_archive.h"
#include "ground_object.h"

extern GroundObject obj[50];
extern ModelArchive *GroundObj[6];
extern s32 objNow;
extern void jobjUnrefAll(HSD_JObj *joint);
extern void ZeroMemory(void *address, u32 size);

void GroundObjPurge(void)
{
    s32 i;
    for (i = 0; i < 50; i++) {
        if (obj[i].joint != 0)
            jobjUnrefAll(obj[i].joint);
        obj[i].joint = 0;
        ZeroMemory(&obj[i], sizeof(GroundObject));
    }
    for (i = 0; i < 6; i++) {
        if (GroundObj[i] != 0) {
            PurgeArc2(GroundObj[i]);
            GroundObj[i] = 0;
        }
    }
    objNow = 0;
}
