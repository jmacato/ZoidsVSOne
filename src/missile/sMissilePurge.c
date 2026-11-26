#include "missile.h"
#include "jobj.h"

#define HSD_OBJECT_METHOD(o) (((HSD_Class *)(o))->class_info)

extern s32 misALL;
extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern void jobjUnrefAll(HSD_JObj *joint);
extern void TEA_VidOff(u32 voice);

static inline s32 ref_DEC(void *obj)
{
    s32 ret = (u64)(((HSD_Obj *)obj)->reference_count == (u16)0xFFFF);

    if (ret)
        return ret;
    return ((HSD_Obj *)obj)->reference_count-- == 0;
}

void sMissilePurge(Missile *missile)
{
    HSD_Obj *obj;

    if (missile != 0 && missile->flags != 0) {
        misALL--;
        if (missile->joint != 0) {
            setAnimRate(missile->joint, 0.0f);
            HSD_JObjRemoveAnimAll(missile->joint);
            jobjUnrefAll(missile->joint);
            missile->joint = 0;
        }
        if (missile->se_playing != 0) {
            missile->se_playing = 0;
            TEA_VidOff(missile->se_voice);
        }
        if ((obj = (HSD_Obj *)missile->light) != 0) {
            if (obj != 0) {
                if (ref_DEC(obj)) {
                    if (obj != 0) {
                        HSD_OBJECT_METHOD(obj)->release((HSD_Class *)obj);
                        HSD_OBJECT_METHOD(obj)->destroy((HSD_Class *)obj);
                    }
                }
            }
        }
        missile->light = 0;
        missile->flags = 0;
    }
}
