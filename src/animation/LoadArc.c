#pragma readonly_strings on
#include "model_archive.h"
#include "archive.h"
#include "jobj.h"
#include "fog.h"

extern s32 arc2;
extern void OSReport(const char *format, ...);
extern u32 strlen(const char *text);
extern char *strcpy(char *dst, const char *src);
extern s32 fexist(char *name);
extern HSD_Archive *sLoad(char *name, void **data);
extern struct HSD_LObj *LoadArcLight(ModelArchive *archive);
extern struct HSD_CObj *HSD_CObjLoadDesc(union HSD_CObjDesc *desc);

s32 LoadArc(ModelArchive *archive, char *name)
{
    char *base;
    char *p;
    s32 length;
    void *data;
    ModelAnimationTable *scene;

    (void)"LOADing\n";
    (void)"ZOIDS.VS";
    (void)"file error";
    (void)"\203f\203B\203X\203N\203J\203o\201[\202\252\212J\202\242\202\304\202\242\202\334\202\267\201B\203Q\201[\203\200\202\360\221\261\202\257\202\351\217\352\215\207\202\315\201A\n\203f\203B\203X\203N\203J\203o\201[\202\360\225\302\202\337\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"\203]\203C\203h\203o\201[\203T\203X\202\314\203f\203B\203X\203N\202\360\203Z\203b\203g\n\202\265\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"\202\261\202\314\203f\203B\203X\203N\202\315\203]\203C\203h\203o\201[\203T\203X\202\314\n\203f\203B\203X\203N\202\305\202\315\202\240\202\350\202\334\202\271\202\361\201B\n\203]\203C\203h\203o\201[\203T\203X\202\314\203f\203B\203X\203N\202\360\203Z\203b\203g\n\202\265\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"\203f\203B\203X\203N\202\360\223\307\202\337\202\334\202\271\202\361\202\305\202\265\202\275\201B\n\202\255\202\355\202\265\202\255\202\315\201A\226{\221\314\202\314\216\346\210\265\220\340\226\276\217\221\202\360\n\202\250\223\307\202\335\202\255\202\276\202\263\202\242\201B";
    (void)"\203G\203\211\201[\202\252\224\255\220\266\202\265\202\334\202\265\202\275\201B\n\226{\221\314\202\314\203p\203\217\201[\203{\203^\203\223\202\360\211\237\202\265\202\304\223d\214\271\202\360\n\202n\202e\202e\202\311\202\265\201A\226{\221\314\202\314\216\346\210\265\220\340\226\276\217\221\202\314\n\216w\216\246\202\311\217]\202\301\202\304\202\255\202\276\202\263\202\242\201B";
    (void)"PreOpen:";
    (void)"heap alloc ";
    (void)"\203\201\203\202\203\212\202\252\221\253\202\350\202\334\202\271\202\361";
    (void)"loading file (%s) ...";
    (void)"cannot open file\n";
    (void)"size[%d]..";
    (void)"cannot allocate memory\n";
    (void)"memAloc...[%X]....";
    (void)"cannot load file\n";
    (void)"archive load %s ";
    (void)"archive ok \n";
    (void)"not found. [%s]*************************\n";
    (void)"scene_data";
    (void)"LoadArc  -----%5d %s\n";
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
    archive->model_data = 0;
    archive->owned_data = 0;
    archive->models[0] = 0;
    if (!fexist(name)) {
        OSReport("not found. [%s]*************************\n", name);
        return 0;
    }
    archive->model_data = sLoad(name, &data);
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
    OSReport("LoadArc  -----%5d %s\n", arc2, name);
    arc2++;
    return 1;
}
