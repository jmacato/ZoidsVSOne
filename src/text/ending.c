#pragma auto_inline off
#pragma readonly_strings on
#include "jobj.h"
#include "zoid.h"
#include "video.h"
#include "game_mode.h"
#include "game_zoid_entry.h"
#include "model_archive.h"
#include "gx_tev.h"

typedef struct AsciiEntry {
    char text[80];
    f32 scroll_y;
} AsciiEntry;

extern AsciiEntry *sStr;
extern char *strcpy(char *destination, const char *source);

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern ModelArchive *textPos, *ending, *dspFilter;
extern HSD_JObj *j0, *j1;
extern f32 strConfUp;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void jobjDispAll(HSD_JObj *joint);
/* by value to match (the definition takes GXColor *; pointers drop the stack copies) */
extern void sPutFontRect(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);

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

static inline void HSD_JObjSetTranslateY(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 966, "jobj");
    jobj->translation.y = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

void setAscii(char *text)
{
    AsciiEntry *entry = sStr;
    s32 i;

    for (i = 0; i < 40; i++, entry++) {
        if (entry->text[0] == 0) {
            entry->scroll_y = 0.0f;
            strcpy(entry->text, text);
            if (entry->text[0] == 0)
                strcpy(entry->text, "  ");
            return;
        }
    }
}

void dispAscii(void)
{
    HSD_JObj *jobj;
    s32 i;
    AsciiEntry *entry;

    for (i = 0; i < 40; i++) {
        entry = &sStr[i];
        if (entry->text[0] == 0)
            continue;
        if (entry->text[0] == '!') {
            /* "!N" lines of epilogue/epilogue.txt show child joint N of credit.dat model 3 instead of text */
            jobj = GetChild(textPos->models[3], 0, entry->text[1] & 0xF, -1, -1, -1);
            HSD_JObjSetTranslateY(jobj, entry->scroll_y);
            jobjDispAll(jobj);
        } else {
            jobjCopyPos(GetChild(textPos->models[0], 0, -1, -1, -1, -1), j0);
            jobjCopyPos(GetChild(textPos->models[0], 0, 0, -1, -1, -1), j1);
            j0->matrix[1][3] += entry->scroll_y;
            j1->matrix[1][3] += entry->scroll_y;
            sPutFontRect(entry->text, j0, j1, (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);
        }
        entry->scroll_y += strConfUp;
        if (entry->scroll_y > 100.0f) {
            entry->text[0] = 0;
            entry->scroll_y = 0.0f;
        }
    }
}

extern s32 cOn, fOn;
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void HSD_LObjSetCurrentAll(struct HSD_LObj *);
extern void HSD_LObjSetupInit(struct HSD_CObj *);
extern void jobjDispAll(HSD_JObj *joint);
extern void VIWaitForRetrace(void);

#define JOBJ_USE_QUATERNION 0x20000

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 y)
{
    if (jobj == NULL)
        __assert("jobj.h", 696, "jobj");
    if (jobj->flags & JOBJ_USE_QUATERNION)
        __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotation[1] = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

extern s32 dOn;

void closeDisp(void)
{
    if (dOn != 0) {
        jobjDispAll(ending->models[0]);
        jobjDispAll(ending->models[1]);
        jobjDispAll(ending->models[2]);
        jobjDispAll(ending->models[3]);
        jobjDispAll(ending->models[4]);
        jobjCopyPos(ending->models[4], Zoid[0].joint);
        HSD_JObjSetRotationY(Zoid[0].joint, -1.5707963f);
        jobjDispAll(Zoid[0].joint);
    }
}

void closeDispAll(void)
{
    HSD_StartRender(HSD_RP_SCREEN);
    if (HSD_CObjSetCurrent(ending->camera) != 0) {
        HSD_LObjSetCurrentAll(ending->lights);
        HSD_LObjSetupInit(ending->camera);
        if (cOn == 0)
            closeDisp();
        HSD_CObjEndCurrent();
    }
    if (HSD_CObjSetCurrent(textPos->camera) != 0) {
        dispAscii();
        if (cOn != 0)
            closeDispC();
        if (fOn != 0)
            jobjDispAll(dspFilter->models[0]);
        HSD_CObjEndCurrent();
    }
    HSD_EndRender();
    HSD_VICopyXFB(HSD_RP_SCREEN);
    HSD_VISetXFBDrawDone();
    VIWaitForRetrace();
}

extern u8 *staff;
extern s32 strNextTm, strConfNext;
extern s32 fOn, cOn, dOn;
extern u8 *cpyCr(u8 *source, char *destination);
extern s32 jobjAnim(HSD_JObj *joint);
extern void ZoidAnim(ZoidState *zoid);
extern void ZoidToFly(ZoidState *zoid);
extern void sWeaponMoveAll(void), sWeaponDispAll(void);
extern void HSD_LObjAnimAll(struct HSD_LObj *lobj);
extern void sPadAll(void);

static inline void SetClearColor(GXColor c)
{
    HSD_VIData.current.vi.clear_clr = c;
}

void closeLoop(void)
{
    ZoidState *zoid;
    char text[256];
    s32 i;
    s32 running;
    u8 *line;

    if (sStr != 0 && textPos != 0 && ending != 0 && (zoid = Zoid, zoid->joint != 0) && staff != 0) {
        SetClearColor((GXColor){0, 0, 0, 0});
        HSD_VISetBlack(0);
        HSD_SetZSortMode(1, 1);
        line = staff;
        running = 1;
        do {
            if (*line != 0)
                strNextTm++;
            if (strNextTm >= strConfNext) {
                strNextTm = 0;
                line = cpyCr(line, text);
                setAscii(text);
                if (*line == 0) {
                    SetAnimArc2(dspFilter, 0, 3);
                    fOn = 1;
                }
            }
            if (*line == 0 && jobjAnim(dspFilter->models[0]) != 0) {
                SetAnimArc2(dspFilter, 0, 4);
                jobjAnim(dspFilter->models[0]);
                fOn = 1;
            }
            jobjAnim(ending->models[0]);
            jobjAnim(ending->models[1]);
            if (jobjAnim(ending->models[2]) != 0)
                running = 0;
            ZoidAnim(zoid);
            ZoidToFly(zoid);
            sWeaponMoveAll();
            sWeaponDispAll();
            HSD_LObjAnimAll(ending->lights);
            closeDispAll();
            sPadAll();
        } while (running != 0);
        SetAnimArc2(dspFilter, 0, 5);
        cOn = 1;
        do {
            closeDispAll();
            sPadAll();
        } while (jobjAnim(dspFilter->models[0]) == 0);
        fOn = 0;
        for (i = 0; i < 180; i++) {
            closeDispAll();
            sPadAll();
        }
        fOn = 1;
        SetAnimArc2(dspFilter, 0, 3);
        jobjAnim(dspFilter->models[0]);
        do {
            closeDispAll();
            sPadAll();
        } while (jobjAnim(dspFilter->models[0]) == 0);
        dOn = 0;
        for (i = 0; i < 60; i++) {
            closeDispAll();
            sPadAll();
        }
    }
}


extern void OSReport(const char *format, ...);
extern void debug11(void);
extern void TeaBgm(s16 track);
extern void ZoidInit(ZoidState *zoid, s16 type);
extern void ZoidPurge(ZoidState *zoid);
extern void *malloc(u32 size);
extern void free(void *ptr);
extern u8 *sReadFileLenU(char *name, s32 usb, s32 *length);
extern void LoadArcAnimLight2(ModelArchive *archive, struct HSD_LObj *lights, s32 animation);
extern struct HSD_AObj *getAnimAobj(HSD_JObj *joint);
extern void sAddAnimAll(HSD_JObj *joint, void *animations, s32 index);
extern void ZoidSetAnim(ZoidState *zoid, s32 animation);
extern s32 staffLen;
extern s32 strConfAll, strConfNextAll;

static inline f32 HSD_AObjGetEndFrame(HSD_AObj *aobj)
{
    f32 frame;

    if (aobj == 0)
        __assert("aobj.h", 171, "aobj");
    frame = aobj->end_frame;
    return frame;
}

void Epilogue(void)
{
    char text[256];
    u8 *line;
    s32 i;
    HSD_AObj *aobj;

    OSReport("epilogue start\n");
    debug11();
    cOn = 0;
    fOn = 0;
    dOn = 1;
    if (GameZoid[0].type < 0)
        GameZoid[0].type = 3;
    if (GameZoid[0].type > 99)
        GameZoid[0].type = 3;
    HSD_SetZSortMode(0, 0);
    TeaBgm(-1);
    if (GameMode.game_type == GAME_TYPE_BATTLE)
        TeaBgm(14);
    else
        TeaBgm(14);
    textPos = LoadArc2("epilogue/credit.dat");
    if (textPos == 0)
        OSReport("textPos credit.dat not found .\n");
    ending = LoadArc2("epilogue/ending.dat");
    if (ending == 0)
        OSReport("ending.dat not found\n");
    ZoidInit(&Zoid[0], GameZoid[0].type);
    sStr = malloc(3360); /* 40 AsciiEntry records */
    if (sStr == 0) {
        OSReport("StStr out of memory.\n");
    } else {
        for (i = 0; i < 40; i++)
            sStr[i].text[0] = 0;
    }
    staff = sReadFileLenU("epilogue/epilogue.txt", 0, &staffLen);
    if (staff != 0) {
        if (staffLen <= 0)
            staffLen = 1;
        staff[staffLen - 1] = 0;
        strConfAll = 0;
        for (line = staff; *line != 0; strConfAll++)
            line = cpyCr(line, text);
        OSReport("%d line(s) \n", strConfAll);
    } else {
        OSReport("staff text not found.\n");
    }
    strNextTm = 0;
    if (ending != 0) {
        OSReport("SetEndingAnime ");
        SetAnimArc2(ending, 0, 1);
        jobjAnim(ending->models[0]);
        SetAnimArc2(ending, 1, 1);
        jobjAnim(ending->models[1]);
        SetAnimArc2(ending, 2, 1);
        jobjAnim(ending->models[2]);
        OSReport("SetEndingLight ");
        LoadArcAnimLight2(ending, ending->lights, 1);
        OSReport("GetEndingAobj ");
        aobj = getAnimAobj(ending->models[2]);
        OSReport("AobjIs[%s] ", aobj ? "on" : "non");
        if (aobj != 0) {
            strConfNextAll = HSD_AObjGetEndFrame(aobj);
            strConfNext = strConfNextAll / strConfAll;
            OSReport("strn=%d ", strConfNext);
        }
    }
    if (Zoid[0].joint != 0) {
        OSReport("epi -anim ");
        sAddAnimAll(Zoid[0].joint, Zoid[0].animations, 4);
        ZoidSetAnim(&Zoid[0], 4);
    }
    j0 = HSD_JObjAlloc();
    j1 = HSD_JObjAlloc();
    if (dspFilter != 0) {
        SetAnimArc2(dspFilter, 0, 0);
        jobjAnim(dspFilter->models[0]);
    } else {
        OSReport("un Filter ");
    }
    closeLoop();
    TeaBgm(-1);
    HSD_JObjUnref(j1);
    HSD_JObjUnref(j0);
    if (staff != 0)
        free(staff);
    if (sStr != 0)
        free(sStr);
    if (Zoid[0].joint != 0)
        ZoidPurge(&Zoid[0]);
    if (ending != 0)
        PurgeArc2(ending);
    if (textPos != 0)
        PurgeArc2(textPos);
    HSD_StateInvalidate(-1);
}
