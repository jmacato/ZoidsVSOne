#include "jobj.h"
#include "model_archive.h"

extern void setAnimRate(HSD_JObj *joint, f32 rate);

#pragma dont_inline on
void SetAnimModel(ModelAnimation *model, HSD_JObj *joint, s32 selected)
{
    HSD_AnimJoint *animation = 0;
    HSD_MatAnimJoint *material;
    HSD_ShapeAnimJoint *shape;
    s32 i;
    HSD_AnimJoint **list = model->joint_animations;

    if (list != 0) {
        for (i = selected + 1; i > 0; i--) {
            HSD_AnimJoint *entry = *list;
            animation = entry;
            if (entry == 0)
                break;
            list++;
        }
    }
    if (model->shape_animations != 0)
        shape = model->shape_animations[selected];
    else
        shape = 0;
    if (model->material_animations != 0)
        material = model->material_animations[selected];
    else
        material = 0;
    HSD_JObjAddAnimAll(joint, animation, material, shape);
    HSD_JObjReqAnimAll(joint, 0.0F);
    setAnimRate(joint, 1.0F);
}

void LoadArcAnimModel(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 selected)
{
    if (archive != 0 && archive->animations != 0 &&
        archive->animations->models != 0 && joint != 0) {
        SetAnimModel(archive->animations->models[model], joint, selected);
    }
}

void LoadArcAnimModel2(ModelArchive *archive, HSD_JObj *joint, s32 model, s32 selected)
{
    if (archive != 0 && archive->animations != 0) {
        ModelAnimation **models = archive->animations->models;
        if (archive->model_count > model && models != 0 && joint != 0) {
            SetAnimModel(models[model], joint, selected);
        }
    }
}

void SetAnimArc2(ModelArchive *archive, s32 model, s32 selected)
{
    if (archive != 0 && archive->model_count > model && archive->models[model] != 0) {
        HSD_JObjRemoveAnimAll(archive->models[model]);
        LoadArcAnimModel2(archive, archive->models[model], model, selected);
    }
}

void sAddAnimAll(HSD_JObj *joint, ModelAnimationTable *table, s32 selected)
{
    HSD_ShapeAnimJoint *shape;
    HSD_MatAnimJoint *material;
    HSD_AnimJoint *animation;
    if (joint != 0 && table != 0) {
        ModelAnimation **models = table->models;
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
        HSD_JObjAddAnimAll(joint, animation, material, shape);
    }
}
