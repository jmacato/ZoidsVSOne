#include "zoid.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern void sGlobal2Local(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

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

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 980, "jobj");
    jobj->translation.z = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

extern ModelArchive *csrFile;
extern s32 csrDispON;
extern s32 csrNum;
extern void jobjAnim(HSD_JObj *joint);

void zdDispCursorSet(ZoidState *zoid, s32 slot)
{
    f32 matrix[3][4];
    s32 frame_padding[1];
    f32 (*source)[4];
    s32 i;
    s32 j;
    WeaponSlot *weapon;

    if (csrFile != 0 && zoid != 0 && zoid->joint != 0) {
        csrDispON = 0;
        if (slot >= 0) {
            weapon = &zoid->weapon_slots[slot];
            if (weapon->joint != 0) {
                csrDispON = 1;
                source = weapon->joint->matrix;
                if (csrNum != 0) {
                    SetAnimArc2(csrFile, 0, 0);
                    csrNum = 0;
                }
                jobjAnim(csrFile->models[0]);
                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 4; j++) {
                        matrix[i][j] = source[i][j];
                        csrFile->models[0]->matrix[i][j] = source[i][j];
                    }
                }
                sGlobal2Local(csrFile->models[0]);
                HSD_JObjSetTranslateX(csrFile->models[0], matrix[0][3]);
                HSD_JObjSetTranslateY(csrFile->models[0], matrix[1][3]);
                HSD_JObjSetTranslateZ(csrFile->models[0], matrix[2][3]);
                sMakeMatrix(csrFile->models[0]);
            }
        }
    }
}
