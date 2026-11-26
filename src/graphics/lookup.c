#include "jobj.h"

#pragma dont_inline on
HSD_TObj *searchTObj(HSD_JObj *joint)
{
    HSD_DObj *object;
    HSD_MObj *material;
    HSD_TObj *texture;
    while (joint != 0) {
        object = HSD_JObjGetDObj(joint);
        while (object != 0) {
            material = object != 0 ? object->mobj : 0;
            {
                s32 has_material = material != 0;
                if (has_material && material->tobj != 0)
                    return material->tobj;
            }
            object = object != 0 ? object->next : 0;
        }
        if (joint->child != 0) {
            texture = searchTObj(joint->child);
            if (texture != 0)
                return texture;
        }
        joint = joint->next;
    }
    return 0;
}

HSD_TObj *searchTObjN(HSD_JObj *joint, s32 *index)
{
    HSD_DObj *object;
    HSD_MObj *material;
    HSD_TObj *texture;
    while (joint != 0) {
        object = HSD_JObjGetDObj(joint);
        while (object != 0) {
            material = object != 0 ? object->mobj : 0;
            {
                s32 has_material = material != 0;
                if (has_material) {
                    texture = material->tobj;
                    while (texture != 0) {
                        s32 selected = *index == 0;
                        if (selected)
                            return texture;
                        --*index;
                        texture = texture->next;
                    }
                }
            }
            object = object != 0 ? object->next : 0;
        }
        if (joint->child != 0) {
            texture = searchTObjN(joint->child, index);
            while (texture != 0) {
                if (*index == 0)
                    return texture;
                --*index;
                texture = texture->next;
            }
        }
        joint = joint->next;
    }
    return 0;
}

HSD_JObj *jobjWithAobj(HSD_JObj *joint)
{
    if (joint == 0)
        return 0;
    if (joint->animation != 0)
        return joint;
    for (joint = joint != 0 ? joint->child : 0; joint != 0;
         joint = joint != 0 ? joint->next : 0) {
        HSD_JObj *found = jobjWithAobj(joint);
        if (found != 0)
            return found;
    }
    return 0;
}
