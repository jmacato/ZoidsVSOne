#include "zoid.h"
#include "aobj.h"

#define NULL 0

extern u32 zdsMotTBL[];
extern void HSD_JObjAnimAll(HSD_JObj *joint);
extern u32 HSD_AObjGetFlags(struct HSD_AObj *aobj);
extern void zdAnimEffect(ZoidState *zoid, s32 animation);
extern void setAnimFrameXor(HSD_JObj *joint, HSD_JObj *exclude, f32 frame);
extern void setAnimStopXor(HSD_JObj *joint, HSD_JObj *exclude);
extern void setAnimRateXor(HSD_JObj *joint, f32 rate, HSD_JObj *exclude);
extern void zdClearAnimRy(HSD_JObj *joint, u32 flags);
extern void zdSetXYZ(ZoidState *zoid);
extern void __assert(const char *file, s32 line, const char *expr);

static inline f32 HSD_AObjGetCurrentFrame(HSD_AObj *aobj)
{
    if (aobj == NULL)
        __assert("aobj.h", 149, "aobj");
    return aobj->current_frame;
}

static inline f32 HSD_JObjGetTranslationY(HSD_JObj *jobj)
{
    if (jobj == NULL)
        __assert("jobj.h", 1021, "jobj");
    return jobj->translation.y;
}

void ZoidAnim(ZoidState *zoid)
{
    u32 *motion = zdsMotTBL;
    s32 loop;
    u32 flags;
    f32 frame;
    s32 id;
    Vec3 pos;

    if (zoid != NULL && zoid->joint != NULL && zoid->animation_stopped == 0) {
        frame = HSD_AObjGetCurrentFrame(zoid->aobj);
        HSD_JObjAnimAll(zoid->joint);
        zoid->animation_stopped = 0;
        zoid->animation_frame = HSD_AObjGetCurrentFrame(zoid->aobj);
        zoid->animation_looped = 0;
        loop = 0;
        if (HSD_AObjGetFlags(zoid->aobj) & AOBJ_REWINDED) {
            zoid->animation_looped = 1;
            loop = 1;
            if (!(motion[zoid->current_animation] & 2))
                zdAnimEffect(zoid, zoid->current_animation);
        }
        if (loop != 0 && (motion[zoid->current_animation] & 2)) {
            setAnimFrameXor(zoid->joint, zoid->animation_exclusion, frame);
            setAnimStopXor(zoid->joint, zoid->animation_exclusion);
            setAnimRateXor(zoid->joint, 0.0f, zoid->animation_exclusion);
            HSD_JObjAnimAll(zoid->joint);
            zoid->animation_stopped = 1;
        }
        zoid->child_translation_y = HSD_JObjGetTranslationY(zoid->joint->child);
        if (zoid->ground_normal_count != 0)
            zoid->field_1A40 = 0;
        else
            zoid->field_1A40++;
        if (zoid->child_translation_y > 0.3)
            zoid->movement_flags = (zoid->movement_flags << 1) | 1;
        if (zoid->child_translation_y < 0.01)
            zoid->movement_flags = zoid->movement_flags << 1;
        zoid->movement_flags = (u8)zoid->movement_flags;
        if (motion[zoid->current_animation] & 0x80)
            zdClearAnimRy(zoid->joint, flags = motion[zoid->current_animation]);
        zdSetXYZ(zoid);
    }
}
