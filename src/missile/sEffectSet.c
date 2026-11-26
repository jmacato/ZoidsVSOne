#pragma readonly_strings on
#include "game_camera.h"
#include "missile.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern s32 efctNum;
extern s32 SE_TableList[];
extern s32 gameEndF;
extern CameraState *camTmp;
extern s32 sprintf(char *buffer, const char *format, ...);
extern HSD_JObj *CopyJoint(void *archive);
extern void LoadArcAnimModel(void *archive, HSD_JObj *joint, s32 model, s32 selected);
extern HSD_JObj *searchJobjJoint(void *archive, HSD_JObj *joint, char *name);
extern void sLsrSet(HSD_JObj *source, ModelArchive *archive);
extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern s32 camSe(CameraState *camera, s16 sound, f32 *point);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

#pragma force_active on
static const char sEffectPathFormat[14] = "effect/%s.dat";
static const char sEffectLightPath[17] = "effect/light.dat";
#pragma force_active off

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY))
        result = 1;
    return result;
}

#define HSD_JObjSetMtxDirty(jobj) \
    do { \
        if ((jobj) != NULL && !HSD_JObjMtxIsDirty(jobj)) \
            HSD_JObjSetMtxDirtySub(jobj); \
    } while (0)

static inline void HSD_JObjSetTranslateX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 952, "jobj");
    jobj->translation.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void sEffectSet(s32 type, s32 mode, f32 *position, HSD_JObj *source, struct ZoidState *zoid)
{
    HSD_JObj *root;
    ModelArchive *archive;
    HSD_JObj *start;
    Effect *effect;
    s32 i;
    s32 j;
    s32 se;
    s32 sound;
    char name[100];
    u8 pad_stack[16];

    if (type <= 0)
        return;
    if (type >= 110)
        return;
    archive = efctFile[type];
    if (archive == NULL)
        return;
    if (archive->model_data == NULL)
        return;
    start = searchJobjJoint(archive, archive->models[0], "start_joint");
    if (searchJobjJoint(archive, archive->models[0], "end_joint") == NULL)
        start = NULL;
    if (start != NULL) {
        sLsrSet(source, archive);
        return;
    }
    efctNum++;
    for (i = 0; i < 100; i++) {
        if (efctNum >= 100)
            efctNum = 0;
        effect = &sEffect[efctNum];
        if (effect->root == NULL)
            break;
        efctNum++;
    }
    if (i == 100)
        return;
    root = CopyJoint(archive);
    if (root == NULL)
        return;
    effect->a1_joint = searchJobjJoint(archive, archive->models[0], "a_1_joint");
    if (source != NULL) {
        for (i = 0; i < 18; i++) {
            sprintf(name, "te_%02d_joint", i);
            effect->joints[i].joint = searchJobjJoint(archive, root, name);
            effect->joints[i].position[0] = 0.01 + (source->matrix[0][3] + 0.01 * i);
            effect->joints[i].position[1] = 0.01 + (source->matrix[1][3] + 0.01 * i);
            effect->joints[i].position[2] = 0.01 + (source->matrix[2][3] + 0.01 * i);
        }
        for (i = 0; i < 60; i++) {
            for (j = 0; j < 3; j++)
                effect->history[i][j] = 0.01 + (source->matrix[j][3] + 0.01 * i);
        }
    }
    effect->root = root;
    effect->type = type;
    effect->archive = archive;
    effect->mode = mode;
    effect->source = source;
    effect->zoid = zoid;
    if (mode == 0) {
        effect->position[0] = position[0];
        effect->position[1] = position[1];
        effect->position[2] = position[2];
    }
    if ((u32)(mode - 1) <= 2) {
        for (i = 0; i < 3; i++) {
            effect->position[i] = source->matrix[i][3];
            for (j = 0; j < 4; j++)
                effect->root->matrix[i][j] = source->matrix[i][j];
        }
        HSD_JObjSetTranslateX(effect->root, effect->position[0]);
        sGlobal2Local(effect->root);
        sMakeMatrix(effect->root);
    }
    LoadArcAnimModel(archive, root, 0, 0);
    sound = Tea_effectdat[type].se;
    if (sound < 0)
        return;
    se = SE_TableList[sound];
    if (se < 0)
        return;
    if (gameEndF != 0)
        return;
    effect->se_voice = camSe(camTmp, sound, effect->position);
    effect->se_playing = 1;
    effect->se = se;
}
