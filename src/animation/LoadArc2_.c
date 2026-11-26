#pragma readonly_strings on
#include "model_archive.h"
#include "archive.h"
#include "jobj.h"
#include "fog.h"

extern s32 arc2;
extern HSD_Archive *TEA_USBFileArchiveLoad(char *name, void **data);
extern void *malloc2(u32 size);
extern void free(void *memory);
extern void sArchivePurge(HSD_Archive *archive);
extern void putErr(const char *message);
extern void ZeroMemory(void *address, u32 size);
extern void sMakeMatrix(HSD_JObj *joint);
extern void setAnimRate(HSD_JObj *joint, f32 rate);
extern void OSReport(const char *format, ...);
extern u32 strlen(const char *text);
extern char *strcpy(char *dst, const char *src);
extern s32 fexist(char *name);
extern HSD_Archive *sLoad(char *name, void **data);
extern struct HSD_LObj *LoadArcLight(ModelArchive *archive);
extern struct HSD_CObj *HSD_CObjLoadDesc(union HSD_CObjDesc *desc);

ModelArchive *LoadArc2_(char *name, s32 usb)
{
    char *p;
    s32 count;
    ModelAnimationTable *scene;
    char *base;
    s32 length;
    s32 i;
    HSD_JObj *joint;
    s32 size;
    HSD_Archive *model_data;
    ModelArchive *archive;
    void *data;

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
    (void)"LoadArc2 -----%5d %s\n";
    data = 0;
    if (usb) {
        model_data = TEA_USBFileArchiveLoad(name, &data);
    } else {
        if (!fexist(name)) {
            OSReport("not found. [%s]*************************\n", name);
            return 0;
        }
        model_data = sLoad(name, &data);
    }
    if (model_data == 0)
        return 0;
    OSReport("LoadArc2 -----%5d %s\n", arc2, name);
    arc2++;
    HSD_ArchiveLoadDepends(model_data, 0, 0, 0);
    HSD_ArchiveResolveReference(model_data, 0);
    scene = HSD_ArchiveGetPublicAddress(model_data, "scene_data");
    count = 0;
    if (scene->models != 0) {
        while (scene->models[count] != 0)
            count++;
    }
    size = count * 4 + sizeof(ModelArchive);
    archive = malloc2(size);
    if (archive == 0) {
        if (data != 0)
            free(data);
        if (model_data != 0)
            sArchivePurge(model_data);
        putErr("\203\201\203\202\203\212\202\252\221\253\202\350\202\334\202\271\202\361");
        return 0;
    }
    ZeroMemory(archive, size);
    archive->owned_data = data;
    archive->animations = scene;
    archive->model_data = model_data;
    archive->model_count = count;
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
    if (scene->models != 0) {
        for (i = 0; i < count; i++) {
            joint = HSD_JObjLoadJoint(scene->models[i]->joint);
            if (joint != 0) {
                ModelAnimation *model = scene->models[i];
                HSD_JObjAddAnimAll(joint,
                                   model->joint_animations ? *model->joint_animations : 0,
                                   model->material_animations ? *model->material_animations : 0,
                                   model->shape_animations ? *model->shape_animations : 0);
                archive->models[i] = joint;
                sMakeMatrix(joint);
                HSD_JObjReqAnimAll(joint, 0.0f);
                setAnimRate(joint, 1.0f);
            }
        }
    }
    archive->lights = LoadArcLight(archive);
    archive->camera = HSD_CObjLoadDesc(*scene->camera);
    if (scene->fog != 0 && *scene->fog != 0)
        archive->fog = HSD_FogLoadDesc(*scene->fog);
    return archive;
}
