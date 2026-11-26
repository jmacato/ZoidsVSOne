#include "jobj.h"
#include "zoid.h"

#pragma dont_inline on

typedef struct AnimationContext {
    HSD_JObj *joint;
    JointPose *pose;
    HSD_JObjDesc *description;
    HSD_AnimJoint *animation;
    HSD_MatAnimJoint *material;
    HSD_ShapeAnimJoint *shape;
} AnimationContext;

typedef char AnimationContextSizeCheck[sizeof(AnimationContext) == 24 ? 1 : -1];

extern void MemCpy(u8 *source, u8 *destination, s32 size);

s32 sGetAnimJoint(AnimationContext *context, HSD_JObj *target)
{
    AnimationContext child;
    while (context->joint != 0 && context->description != 0) {
        if (context->joint == target)
            return 1;
        if (context->description->child != 0) {
            MemCpy((u8 *)context, (u8 *)&child, sizeof(child));
            child.joint = child.joint ? child.joint->child : 0;
            child.pose = child.pose ? child.pose->child : 0;
            child.description = child.description ? child.description->child : 0;
            child.animation = child.animation ? child.animation->child : 0;
            child.material = child.material ? child.material->child : 0;
            child.shape = child.shape ? child.shape->child : 0;
            if (sGetAnimJoint(&child, target)) {
                MemCpy((u8 *)&child, (u8 *)context, sizeof(child));
                return 1;
            }
        }
        context->joint = context->joint ? context->joint->next : 0;
        context->pose = context->pose ? context->pose->next : 0;
        context->description = context->description ? context->description->next : 0;
        context->animation = context->animation ? context->animation->next : 0;
        context->material = context->material ? context->material->next : 0;
        context->shape = context->shape ? context->shape->next : 0;
    }
    return 0;
}

extern void zdHSD_JObjAddAnimAll(HSD_JObj *joint, JointPose *pose, s32 number,
                                HSD_AnimJoint *animation, HSD_MatAnimJoint *material,
                                HSD_ShapeAnimJoint *shape);
extern void setAnimRateXor(HSD_JObj *joint, HSD_JObj *excluded, f32 rate);

void ZoidSetAnimAllPoint(ZoidState *zoid, HSD_JObj *joint, s32 number)
{
    AnimationContext context;
    if (zoid != 0 && zoid->joint != 0 && joint != 0) {
        ModelAnimationTable *table = zoid->animations;
        if (table->models != 0 &&
            table->models[0]->joint_animations != 0) {
            context.joint = zoid->joint;
            context.pose = zoid->pose;
            context.description = table->models[0]->joint;
            context.animation = table->models[0]->joint_animations[number];
            context.material = 0;
            context.shape = 0;
            if (table->models[0]->material_animations != 0)
                context.material = table->models[0]->material_animations[number];
            if (table->models[0]->shape_animations != 0)
                context.shape = table->models[0]->shape_animations[number];
            if (sGetAnimJoint(&context, joint)) {
                zdHSD_JObjAddAnimAll(joint, context.pose, number, context.animation,
                                    context.material, context.shape);
                HSD_JObjReqAnimAll(joint, 0.f);
                {
                    f32 rate = 1.f;
                    setAnimRateXor(joint, zoid->animation_exclusion, rate);
                }
            }
        }
    }
}
