#include "model_archive.h"
#include "archive.h"
#include "object.h"
#include "jobj.h"
#include "lobj.h"

extern void sArchivePurge(HSD_Archive *archive);
extern void jobjUnrefAll(HSD_JObj *joint);
extern void free(void *memory);
extern s32 arc2;

static inline s32 decrement_reference(void *object)
{
    s32 result;
    u16 *count = &((HSD_Obj *)object)->reference_count;
    if ((result = (*count == (u16)-1)))
        return result;
    return (*count)-- == 0;
}

static inline void delete_object(void *object)
{
    if (object != 0) {
        ((HSD_Class *)object)->class_info->release((HSD_Class *)object);
        ((HSD_Class *)object)->class_info->destroy((HSD_Class *)object);
    }
}

static inline void unreference_object(void *object)
{
    if (object != 0 && decrement_reference(object))
        delete_object(object);
}

void PurgeArc(ModelArchive *archive)
{
    if (archive != 0 && archive->model_data != 0) {
        if (archive->lights != 0) {
            HSD_LObjRemoveAll(archive->lights);
            archive->lights = 0;
        }
        if (archive->camera != 0) {
            unreference_object((HSD_Obj *)archive->camera);
            archive->camera = 0;
        }
        if (archive->models[0] != 0) {
            HSD_JObjRemoveAnimAll(archive->models[0]);
            jobjUnrefAll(archive->models[0]);
            archive->models[0] = 0;
        }
        if (archive->fog != 0) {
            unreference_object((HSD_Obj *)archive->fog);
            archive->fog = 0;
        }
        if (archive->model_data != 0)
            sArchivePurge(archive->model_data);
        arc2--;
        OSReport("PurgeArc2 -----------------%5d %s\n", arc2, archive->name);
        archive->model_data = 0;
        if (archive->owned_data != 0)
            free(archive->owned_data);
        archive->owned_data = 0;
    }
}

void PurgeArc2(ModelArchive *archive)
{
    if (archive != 0 && archive->model_data != 0) {
        s32 model;
        if (archive->lights != 0) {
            HSD_LObjRemoveAll(archive->lights);
            archive->lights = 0;
        }
        if (archive->camera != 0) {
            unreference_object((HSD_Obj *)archive->camera);
            archive->camera = 0;
        }
        for (model = 0; model < archive->model_count; model++) {
            if (archive->models[model] != 0) {
                HSD_JObjRemoveAnimAll(archive->models[model]);
                HSD_JObjUnref(archive->models[model]);
                archive->models[model] = 0;
            }
        }
        if (archive->fog != 0) {
            unreference_object((HSD_Obj *)archive->fog);
            archive->fog = 0;
        }
        if (archive->model_data != 0)
            sArchivePurge(archive->model_data);
        archive->model_data = 0;
        arc2--;
        OSReport("PurgeArc2 -----------------%5d %s\n", arc2, archive->name);
        if (archive->owned_data != 0)
            free(archive->owned_data);
        archive->owned_data = 0;
        OSReport("fl ");
        free(archive);
        OSReport("free OK \n ");
    }
}
