#include "jobj.h"

#define JOBJ_HIDDEN 0x10
#define JOBJ_INSTANCE 0x1000
#define JOBJ_XLU 0x80000
#define JOBJ_ROOT_XLU 0x20000000
#define RENDER_XLU 0x40000000

extern void psKillJObjAllGenerator(HSD_JObj *joint);
extern void *malloc2(u32 size);
extern void ZeroMemory(void *memory, s32 size);
extern void free(void *memory);

#pragma dont_inline on
void jobjDisp(HSD_JObj *joint)
{
    if (joint != 0)
        HSD_JObjDisp(joint, 0, HSD_TRSP_ALL, 0);
}

void jobjDispAll(HSD_JObj *joint)
{
    if (joint != 0)
        HSD_JObjDispAll(joint, 0, HSD_TRSP_ALL, 0);
}

void jobjUnrefAll(HSD_JObj *joint)
{
    if (joint != 0) {
        HSD_JObjRemoveAnimAll(joint);
        psKillJObjAllGenerator(joint);
        HSD_JObjUnref(joint);
    }
}

void HiddenParts(HSD_JObj *joint, s32 hidden)
{
    if (joint != 0) {
        if (hidden != 0)
            HSD_JObjSetFlags(joint, JOBJ_HIDDEN);
        else
            HSD_JObjClearFlags(joint, JOBJ_HIDDEN);
    }
}

void HiddenPartsAll(HSD_JObj *joint, s32 hidden)
{
    if (joint != 0) {
        HiddenParts(joint, hidden);
        for (joint = joint != 0 ? joint->child : 0; joint != 0;
             joint = joint != 0 ? joint->next : 0) {
            HiddenPartsAll(joint, hidden);
        }
    }
}

MaterialPose *makeDobj(void)
{
    MaterialPose *pose = malloc2(sizeof(MaterialPose));
    ZeroMemory(pose, sizeof(MaterialPose));
    return pose;
}

JointPose *makeJobj(void)
{
    JointPose *pose = malloc2(sizeof(JointPose));
    ZeroMemory(pose, sizeof(JointPose));
    return pose;
}

void stCopyObj(HSD_JObj *joint, JointPose *pose)
{
    HSD_DObj *object;
    MaterialPose *material;
    s32 has_child;
    if (joint != 0) {
        object = HSD_JObjGetDObj(joint);
        if (object != 0) {
            material = makeDobj();
            pose->materials = material;
            for (;;) {
                object = object != 0 ? object->next : 0;
                if (object == 0)
                    break;
                material = material->next = makeDobj();
            }
        }
        if (joint->flags & JOBJ_INSTANCE)
            return;
        joint = joint != 0 ? joint->child : 0;
        has_child = joint != 0;
        if (has_child) {
            JointPose *child_pose = makeJobj();
            pose->child = child_pose;
            pose = child_pose;
            stCopyObj(joint, pose);
            while (joint != 0) {
                JointPose *next_pose;
                joint = joint != 0 ? joint->next : 0;
                if (joint != 0) {
                    next_pose = makeJobj();
                    pose->next = next_pose;
                    pose = next_pose;
                    stCopyObj(joint, pose);
                }
            }
        }
    }
}

void stCopyMatMobj(HSD_JObj *joint, JointPose *pose)
{
    HSD_DObj *object;
    MaterialPose *saved;
    if (joint != 0 && pose != 0) {
        pose->saved_flags = joint->flags;
        object = HSD_JObjGetDObj(joint);
        saved = pose->materials;
        while (object != 0 && saved != 0) {
            HSD_MObj *material = object->mobj;
            HSD_Material *values;
            saved->material = material;
            saved->alpha = 1.0F;
            if (material != 0)
                saved->render_mode = material->rendermode;
            else
                saved->render_mode = 0;
            values = 0;
            if (material != 0)
                values = material->mat;
            {
                s32 has_values = values != 0;
                if (has_values)
                    saved->alpha = values->alpha;
            }
            object = object != 0 ? object->next : 0;
            saved = saved->next;
        }
        if (joint->flags & JOBJ_INSTANCE)
            return;
        joint = joint != 0 ? joint->child : 0;
        pose = pose != 0 ? pose->child : 0;
        while (joint != 0 && pose != 0) {
            stCopyMatMobj(joint, pose);
            joint = joint != 0 ? joint->next : 0;
            pose = pose != 0 ? pose->next : 0;
        }
    }
}

void stCopyMatRet(HSD_JObj *joint, JointPose *pose)
{
    if (joint != 0 && pose != 0) {
        HSD_DObj *object;
        MaterialPose *saved;
        joint->flags = pose->saved_flags;
        object = HSD_JObjGetDObj(joint);
        saved = pose->materials;
        while (object != 0 && saved != 0) {
            HSD_MObj *material = saved->material;
            object->mobj = material;
            if (material != 0) {
                HSD_Material *values = material->mat;
                if (values != 0)
                    values->alpha = saved->alpha;
                material->rendermode = saved->render_mode;
            }
            object = object->next;
            saved = saved->next;
        }
        if (joint->flags & JOBJ_INSTANCE)
            return;
        joint = joint != 0 ? joint->child : 0;
        pose = pose != 0 ? pose->child : 0;
        while (joint != 0 && pose != 0) {
            stCopyMatRet(joint, pose);
            joint = joint->next;
            pose = pose->next;
        }
    }
}

void stCopyMatReset(HSD_JObj *joint, JointPose *pose)
{
    HSD_DObj *object;
    MaterialPose *saved;
    MaterialPose *next;
    if (joint != 0) {
        s32 has_pose = pose != 0;
        if (has_pose) {
            joint->flags = pose->saved_flags;
            pose->saved_flags = 0;
            object = HSD_JObjGetDObj(joint);
            saved = pose->materials;
            pose->materials = 0;
            while (object != 0 && saved != 0) {
                object->mobj = saved->material;
                object = object != 0 ? object->next : 0;
                next = saved->next;
                free(saved);
                saved = next;
            }
            if (joint->flags & JOBJ_INSTANCE)
                return;
            joint = joint != 0 ? joint->child : 0;
            pose = pose != 0 ? pose->child : 0;
            while (joint != 0 && pose != 0) {
                stCopyMatReset(joint, pose);
                joint = joint->next;
                pose = pose->next;
            }
        }
    }
}

void stMatSet(HSD_JObj *joint, JointPose *pose, f32 alpha)
{
    HSD_DObj *object = HSD_JObjGetDObj(joint);
    MaterialPose *saved = pose->materials;
    if (object == 0)
        return;
    while (object != 0) {
        HSD_MObj *material = object != 0 ? object->mobj : 0;
        s32 has_material = material != 0;
        if (has_material) {
            f32 original_alpha = saved->alpha;
            if (alpha == 1.0)
                material->rendermode = saved->render_mode;
            else
                material->rendermode |= RENDER_XLU;
            if (material->mat != 0)
                material->mat->alpha = alpha * original_alpha;
        }
        object = object != 0 ? object->next : 0;
        saved = saved->next;
    }
}
HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth,
                   s32 fifth)
{
    s32 stop = first == -1;
    if (stop)
        return joint;
    {
        s32 indices[6];
        s32 *index;
        indices[0] = first;
        indices[1] = second;
        indices[2] = third;
        indices[3] = fourth;
        indices[4] = fifth;
        indices[5] = -1;
        index = indices;
        for (;;) {
            s32 count;
            for (count = *index; count > 0; count--) {
                joint = joint != 0 ? joint->next : 0;
                if (joint == 0)
                    return 0;
            }
            if (*++index == -1)
                return joint;
            joint = joint != 0 ? joint->child : 0;
        }
    }
}

void stStJobjUnref(JointPose *pose)
{
    JointPose *next;
    while (pose != 0) {
        if (pose->child != 0)
            stStJobjUnref(pose->child);
        next = pose->next;
        free(pose);
        pose = next;
    }
}

void stSetFlag(HSD_JObj *joint, JointPose *pose, f32 alpha)
{
    if (joint != 0 && pose != 0) {
        if (alpha == 1.0)
            joint->flags = pose->saved_flags;
        else
            joint->flags |= JOBJ_ROOT_XLU | JOBJ_XLU;
        stMatSet(joint, pose, alpha);
        if (joint->flags & JOBJ_INSTANCE)
            return;
        joint = joint != 0 ? joint->child : 0;
        pose = pose != 0 ? pose->child : 0;
        while (joint != 0 && pose != 0) {
            stSetFlag(joint, pose, alpha);
            joint = joint->next;
            pose = pose->next;
        }
    }
}
