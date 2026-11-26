#include "zoid.h"
#include "zoid_collision.h"

extern s32 sprintf(char *buffer, const char *format, ...);
extern void OSReport(const char *format, ...);
extern void *HSD_ArchiveGetPublicAddress(struct HSD_Archive *archive, const char *name);
extern HSD_JObj *search_PARTS(HSD_JObj *joint, HSD_JObjDesc *description, HSD_JObjDesc *target);
extern void __assert(const char *file, s32 line, const char *message);

#pragma auto_inline off
HSD_JObj *searchJoint(ZoidState *zoid, const char *part)
{
    char name[256];
    HSD_JObjDesc *description;
    if (*part == 0)
        return 0;
    sprintf(name, "%s_%s", zoid->name, part);
    description = HSD_ArchiveGetPublicAddress(zoid->archive, name);
    if (description == 0) {
        OSReport("joint error [%s] \n ============", name);
        return 0;
    }
    return search_PARTS(zoid->joint, zoid->animations->models[0]->joint, description);
}
void searchJointFoot(ZoidState *zoid, FootJoint *foot, const char *part)
{
    foot->joint = searchJoint(zoid, part);
    if (foot->joint != 0) {
        zoid->foot_count++;
        foot->offset = foot->joint->translation.y;
    }
}


/* SDK reference: https://github.com/doldecomp/melee/blob/master/src/sysdolphin/baselib/jobj.h. */
static inline f32 HSD_JObjGetScaleX(HSD_JObj *joint)
{
    if (joint == 0) __assert("jobj.h", 899, "jobj");
    return joint->scale.x;
}
static inline f32 HSD_JObjGetScaleY(HSD_JObj *joint)
{
    if (joint == 0) __assert("jobj.h", 911, "jobj");
    return joint->scale.y;
}
static inline f32 HSD_JObjGetScaleZ(HSD_JObj *joint)
{
    if (joint == 0) __assert("jobj.h", 923, "jobj");
    return joint->scale.z;
}

#pragma auto_inline off
void searchJointCoObj(ZoidState *zoid, CoObj *object, const char *part, HSD_JObj *base_joint)
{
    HSD_JObj *joint;
    Vec3 scale;
    f32 minimum, maximum;
    object->health = 0;
    object->maximum_health = 0;
    joint = searchJoint(zoid, part);
    object->joint = joint;
    if (joint != 0) {
        object->maximum_health = 100;
        object->health = 100;
        scale.x = HSD_JObjGetScaleX(joint);
        scale.y = HSD_JObjGetScaleY(joint);
        scale.z = HSD_JObjGetScaleZ(joint);
        minimum = scale.x;
        maximum = scale.x;
        if (scale.x < scale.y)
            maximum = scale.y;
        if (maximum < scale.z)
            maximum = scale.z;
        if (scale.x > scale.y)
            minimum = scale.y;
        if (minimum > scale.z)
            minimum = scale.z;
        object->minimum_scale = minimum;
        object->maximum_scale = maximum;
        object->base_joint = base_joint;
    }
}
