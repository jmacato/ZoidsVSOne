#include "missile.h"
#include "jobj.h"


void sMissileSetAnim(Missile *missile, s32 selected)
{
    ModelAnimationTable *table;
    ModelAnimation *model;
    struct HSD_ShapeAnimJoint *shape;
    struct HSD_MatAnimJoint *material;
    struct HSD_AnimJoint *animation;

    if (missile == 0)
        return;
    if (missile->joint == 0)
        return;
    table = missile->archive->animations;
    if (table->models == 0)
        return;
    if (table->models[0]->joint_animations == 0)
        return;
    HSD_JObjRemoveAnimAll(missile->joint);
    model = table->models[0];
    if (model->shape_animations != 0)
        shape = model->shape_animations[selected];
    else
        shape = 0;
    if (model->material_animations != 0)
        material = model->material_animations[selected];
    else
        material = 0;
    if (model->joint_animations != 0)
        animation = model->joint_animations[selected];
    else
        animation = 0;
    HSD_JObjAddAnimAll(missile->joint, animation, material, shape);
    HSD_JObjReqAnimAll(missile->joint, 0.0f);
    missile->animation = selected;
}
