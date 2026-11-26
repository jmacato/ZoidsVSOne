#pragma readonly_strings on
#include "model_archive.h"
#include "archive.h"
#include "jobj.h"
#include "fog.h"

extern u32 strlen(const char *text);
extern char *strcpy(char *dst, const char *src);
extern HSD_Archive *TEA_USBFileArchiveLoad(char *name, void **data);
extern struct HSD_LObj *LoadArcLight(ModelArchive *archive);
extern struct HSD_CObj *HSD_CObjLoadDesc(union HSD_CObjDesc *desc);

s32 LoadArcUSB(ModelArchive *archive, char *name)
{
    char *base;
    char *p;
    s32 length;
    void *data;
    ModelAnimationTable *scene;

    p = name;
    base = name;
    for (; *p != 0; p++) {
        if (*p == '/')
            base = p + 1;
    }
    length = strlen(base);
    strcpy(archive->name, base);
    if (length > 4)
        archive->name[length - 4] = 0;
    archive->owned_data = 0;
    archive->model_data = TEA_USBFileArchiveLoad(name, &data);
    if (archive->model_data != 0)
        archive->owned_data = data;
    HSD_ArchiveLoadDepends(archive->model_data, 0, 0, 0);
    HSD_ArchiveResolveReference(archive->model_data, 0);
    archive->animations = HSD_ArchiveGetPublicAddress(archive->model_data, "scene_data");
    archive->lights = LoadArcLight(archive);
    scene = archive->animations;
    if (scene->models != 0) {
        ModelAnimation *model;
        archive->models[0] = HSD_JObjLoadJoint(scene->models[0]->joint);
        model = archive->animations->models[0];
        HSD_JObjAddAnimAll(archive->models[0],
                           model->joint_animations ? *model->joint_animations : 0,
                           model->material_animations ? *model->material_animations : 0,
                           model->shape_animations ? *model->shape_animations : 0);
    }
    archive->camera = HSD_CObjLoadDesc(*archive->animations->camera);
    scene = archive->animations;
    if (scene->fog != 0 && *scene->fog != 0)
        archive->fog = HSD_FogLoadDesc(*scene->fog);
    return 1;
}
