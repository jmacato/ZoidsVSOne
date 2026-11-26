#pragma readonly_strings on
#include "zoid.h"
#include "aobj.h"

extern u32 zdsMotTBL[];
extern void __assert(const char *file, u32 line, const char *condition);
extern void zdAnimEffect(ZoidState *zoid, s32 animation);
extern void zdClearAtkTouch(ZoidState *zoid);
extern void zdAddAnimRy(ZoidState *zoid);
extern void sAddAnimAllXor(ZoidState *zoid, s32 animation);
extern HSD_AObj *getAnimAobjXor(HSD_JObj *joint, HSD_JObj *excluded);
extern void HSD_JObjReqAnimAll(HSD_JObj *joint, f32 frame);
extern void setAnimRateXor(HSD_JObj *joint, f32 rate, HSD_JObj *excluded);
extern void ZoidAnim(ZoidState *zoid);

static inline f32 HSD_AObjGetEndFrame(HSD_AObj *aobj)
{
    if (aobj == 0)
        __assert("aobj.h", 171, "aobj");
    return aobj->end_frame;
}

#pragma push
#pragma opt_common_subs off
void ZoidSetAnim(ZoidState *zoid, s32 animation)
{
    HSD_AObj *aobj;
    s32 frame_padding[2];

    if (zoid == 0)
        return;
    if (zoid->joint != 0) {
        zdAnimEffect(zoid, animation);
        zdClearAtkTouch(zoid);
        if (zdsMotTBL[zoid->current_animation] & 8)
            zdAddAnimRy(zoid);
        zoid->interpolation_remaining = 15;
        zoid->interpolation_duration = 15;
        zoid->field_1A40 = 0;
        zoid->current_animation = animation;
        if (zoid->animations->models != 0 && zoid->animations->models[0]->joint_animations != 0) {
            sAddAnimAllXor(zoid, animation);
            zoid->aobj = getAnimAobjXor(zoid->joint, zoid->animation_exclusion);
            aobj = zoid->aobj;
            zoid->animation_end_frame = HSD_AObjGetEndFrame(aobj);
            zoid->animation_stopped = 0;
            HSD_JObjReqAnimAll(zoid->joint, 0.0f);
            setAnimRateXor(zoid->joint, 1.0f, zoid->animation_exclusion);
            ZoidAnim(zoid);
        }
    }
}
#pragma pop
