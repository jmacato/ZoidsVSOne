#include "model_archive.h"
#include "lobj.h"

static inline void HSD_LObjSetNext(HSD_LObj *lobj, HSD_LObj *next)
{
    if (!lobj)
        __assert("lobj.h", 301, "lobj");
    lobj->next = next;
}

HSD_LObj *LoadArcLight(ModelArchive *archive)
{
    HSD_LObj *head = 0;
    if (archive->animations->lights != 0) {
        s32 i;
        HSD_LObj *tail = 0;
        for (i = 0; archive->animations->lights[i] != 0; i++) {
            HSD_LObj *light = HSD_LObjLoadDesc(archive->animations->lights[i]->light);
            if (archive->animations->lights[i]->animations != 0)
                HSD_LObjAddAnim(light, archive->animations->lights[i]->animations[0]);
            if (tail == 0)
                head = tail = light;
            else {
                HSD_LObjSetNext(tail, light);
                tail = light;
            }
        }
        HSD_LObjReqAnimAll(head, 0.0F);
    }
    return head;
}

HSD_LObj *LoadArc2Light(ModelArchive *archive, s32 selected)
{
    HSD_LObj *light;
    if (archive == 0)
        return 0;
    if (archive->animations == 0)
        return 0;
    if (archive->animations->lights == 0)
        return 0;
    light = HSD_LObjLoadDesc(archive->animations->lights[selected]->light);
    if (archive->animations->lights[selected]->animations != 0) {
        HSD_LObjAddAnim(light, archive->animations->lights[selected]->animations[0]);
        HSD_LObjReqAnimAll(light, 0.0F);
    }
    return light;
}

#pragma dont_inline on
static void SetAnimLight(ModelLightAnimation *model, HSD_LObj *light, s32 selected)
{
    s32 i;
    if (model != 0) {
        if (model->animations == 0) {
            OSReport("light anim TBL non \n");
            return;
        }
        for (i = 0; i < selected + 1; i++) {
            if (model->animations[i] == 0) {
                OSReport("light non anim  req=%d(in %d) \n", selected, i);
                return;
            }
        }
        HSD_LObjAddAnim(light, model->animations[selected]);
        HSD_LObjReqAnimAll(light, 0.0F);
    }
}

void LoadArcAnimLight2(ModelArchive *archive, HSD_LObj *light, s32 selected)
{
    if (archive != 0 && archive->animations != 0 && archive->animations->lights != 0 &&
        light != 0) {
        s32 i;
        HSD_LObj *current = light;
        ModelLightAnimation **models = archive->animations->lights;
        for (i = 0; models[i] != 0; i++) {
            SetAnimLight(models[i], current, selected);
            current = current == 0 ? 0 : current->next;
        }
    }
}
