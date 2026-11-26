#include "model_archive.h"
#include "jobj.h"

#pragma dont_inline on
HSD_JObj *CopyJoint(ModelArchive *archive)
{
    HSD_JObj *joint;
    ModelAnimation *model;
    HSD_AnimJoint *animation;
    HSD_MatAnimJoint *material;
    HSD_ShapeAnimJoint *shape;
    if (archive->animations->models == 0)
        return 0;
    joint = HSD_JObjLoadJoint(archive->animations->models[0]->joint);
    model = archive->animations->models[0];
    if (model->shape_animations != 0)
        shape = model->shape_animations[0];
    else
        shape = 0;
    if (model->material_animations != 0)
        material = model->material_animations[0];
    else
        material = 0;
    if (model->joint_animations != 0)
        animation = model->joint_animations[0];
    else
        animation = 0;
    HSD_JObjAddAnimAll(joint, animation, material, shape);
    return joint;
}

HSD_JObj *CopyJoint2(ModelArchive *archive, s32 model)
{
    if (archive == 0)
        return 0;
    if (archive->model_data == 0)
        return 0;
    if (archive->animations->models == 0)
        return 0;
    if (model >= archive->model_count)
        return 0;
    return HSD_JObjLoadJoint(archive->animations->models[model]->joint);
}

JointPose *stSearchJobj(HSD_JObj *joint, JointPose *pose, HSD_JObj *target)
{
    if (joint == 0)
        return 0;
    if (pose == 0)
        return 0;
    if (joint == target)
        return pose;
    joint = joint != 0 ? joint->child : 0;
    pose = pose->child;
    while (joint != 0 && pose != 0) {
        JointPose *found = stSearchJobj(joint, pose, target);
        if (found != 0)
            return found;
        joint = joint != 0 ? joint->next : 0;
        pose = pose->next;
    }
    return 0;
}
