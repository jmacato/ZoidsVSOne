#include "jobj.h"
#include "zoid.h"

#define JOBJ_INSTANCE 0x1000

#pragma dont_inline on
extern void zdHSD_JObjAddAnim(HSD_JObj *joint, JointPose *pose, s32 number,
                             HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                             HSD_ShapeAnimJoint *shape);
void zdHSD_JObjAddAnimAll(HSD_JObj *joint, JointPose *pose, s32 number,
                         HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                         HSD_ShapeAnimJoint *shape)
{
    if (joint != 0) {
        zdHSD_JObjAddAnim(joint, pose, number, animation, material, shape);
        joint = joint ? joint->child : 0;
        animation = animation ? animation->child : 0;
        pose = pose ? pose->child : 0;
        material = material ? material->child : 0;
        shape = shape ? shape->child : 0;
        while (joint != 0 && animation != 0) {
            zdHSD_JObjAddAnimAll(joint, pose, number, animation, material, shape);
            joint = joint->next;
            animation = animation ? animation->next : 0;
            pose = pose ? pose->next : 0;
            material = material ? material->next : 0;
            shape = shape ? shape->next : 0;
        }
    }
}
void HSD_JObjAddAnimAllXor(HSD_JObj *joint, JointPose *pose, s32 number,
                          HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                          HSD_ShapeAnimJoint *shape, HSD_JObj *excluded)
{
    if (joint != 0) {
        if (excluded == 0) {
            HSD_JObjRemoveAnimAll(joint);
            HSD_JObjAddAnimAll(joint, animation, material, shape);
            return;
        }
        zdHSD_JObjAddAnim(joint, pose, number, animation, material, shape);
        if (joint->flags & JOBJ_INSTANCE)
            return;
        joint = joint->child;
        pose = pose ? pose->child : 0;
        animation = animation ? animation->child : 0;
        material = material ? material->child : 0;
        shape = shape ? shape->child : 0;
        while (joint != 0) {
            if (joint != excluded)
                HSD_JObjAddAnimAllXor(joint, pose, number, animation, material, shape, excluded);
            joint = joint->next;
            pose = pose ? pose->next : 0;
            animation = animation ? animation->next : 0;
            material = material ? material->next : 0;
            shape = shape ? shape->next : 0;
        }
    }
}
void sAddAnimAllXor(ZoidState *zoid, s32 selected)
{
    HSD_ShapeAnimJoint *shape;
    HSD_MatAnimJoint *material;
    HSD_AnimJoint *animation;
    if (zoid != 0 && zoid->joint != 0 && zoid->animations != 0) {
        ModelAnimation **models = zoid->animations->models;
        HSD_AnimJoint **animations = models[0]->joint_animations;
        HSD_MatAnimJoint **materials = models[0]->material_animations;
        HSD_ShapeAnimJoint **shapes = models[0]->shape_animations;
        if (shapes != 0)
            shape = shapes[selected];
        else
            shape = 0;
        if (materials != 0)
            material = materials[selected];
        else
            material = 0;
        if (animations != 0)
            animation = animations[selected];
        else
            animation = 0;
        HSD_JObjAddAnimAllXor(zoid->joint, zoid->pose, selected, animation, material, shape,
                              zoid->animation_exclusion);
    }
}
