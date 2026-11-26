#include "jobj.h"
#include "model_archive.h"
#include "zoid.h"
#include "game_person_data.h"
#include "game_text.h"

#define NULL 0
#define JOBJ_MTX_INDEP_SRT 0x02000000
#define JOBJ_USER_DEF_MTX 0x800000
#define JOBJ_MTX_DIRTY 0x40

extern ModelArchive *dspPartner;
extern s32 sCamNN;
extern s32 gameEndF;
extern s32 dspPartnerMsgTm, dspPartnerMsg, dspPartnerMsgA, dspPartnerMsgB;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);

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

static inline void HSD_JObjSetScaleX(HSD_JObj *jobj, f32 value)
{
    if (jobj == NULL)
        __assert("jobj.h", 805, "jobj");
    jobj->scale.x = value;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT))
        HSD_JObjSetMtxDirty(jobj);
}

static inline HSD_JObj *menuGetChild(HSD_JObj *jobj, s32 a, s32 b, s32 c, s32 d, s32 e)
{
    HSD_JObj *child = GetChild(jobj, a, b, c, d, e);

    return child;
}

static inline HSD_JObj *dspPartnerModel(s32 i)
{
    HSD_JObj *jobj = dspPartner->models[i];

    return jobj;
}

void sDispPartner(void *enable)
{
    ZoidState *partner;
    HSD_JObj *root;
    HSD_JObj *bar;
    s32 next;
    s32 i;

    if (sCamNN != 1)
        return;
    if (dspPartner == 0)
        return;
    if (gameEndF > 3)
        return;
    partner = &Zoid[2];
    if (partner->joint == 0)
        return;
    if (enable == 0)
        return;
    root = dspPartnerModel(0);
    if (root == 0)
        return;
    if (dspPartnerMsgTm != 0)
        dspPartnerMsgTm--;
    else
        dspPartnerMsg = -1;
    if (dspPartnerMsg >= 8)
        dspPartnerMsg = -1;
    for (i = 0; i < 8; i++)
        HiddenParts(menuGetChild(root, 0, 0, i < 4 ? 0 : 1, i & 3, -1), dspPartnerMsgB != i);
    menuGetChild(root, 0, -1, 0, 0, -1);
    switch (dspPartnerMsgA) {
    case 0:
        if (dspPartnerMsg != dspPartnerMsgB) {
            if (dspPartnerMsg != -1) {
                SetAnimArc2(dspPartner, 0, dspPartnerMsg < 4 ? 1 : 4);
                dspPartnerMsgB = dspPartnerMsg;
                dspPartnerMsgA = 1;
            } else {
                dspPartnerMsgB = -1;
            }
        }
        break;
    case 2:
        if (dspPartnerMsg != dspPartnerMsgB) {
            SetAnimArc2(dspPartner, 0, dspPartnerMsgB < 4 ? 3 : 6);
            dspPartnerMsgA = 3;
        }
        break;
    }
    next = -1;
    if (jobjAnim(root) != 0) {
        switch (dspPartnerMsgA) {
        case 1:
            next = dspPartnerMsgB < 4 ? 2 : 5;
            dspPartnerMsgA = 2;
            break;
        case 3:
            dspPartnerMsgA = 0;
            next = 0;
            break;
        }
        if (next != -1) {
            SetAnimArc2(dspPartner, 0, next);
            jobjAnim(root);
        }
    }
    bar = menuGetChild(root, 0, 1, 0, -1, -1);
    if (bar != 0) {
        if (partner->max_health <= 0)
            partner->max_health = 100;
        HSD_JObjSetScaleX(bar, (f32)partner->health / (f32)partner->max_health);
    }
    jobjDispAll(root);
    sMakeMatrix(root);
    putAscJobj(menuGetChild(root, 0, 2, 0, -1, -1), 1, Tea_persondat[Zoid[2].person].name);
}
