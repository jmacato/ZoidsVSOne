#include "model_archive.h"

extern ModelArchive *menu1p;
extern s16 flag_VsFarmEntryButton[2];
extern s32 jobjAnim(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

static inline s32 sFarmAnim(s32 model)
{
    s32 ret;
    s32 done = jobjAnim(menu1p->models[model]);

    sMakeMatrix(menu1p->models[model]);
    ret = done;
    return ret;
}

void menu_sDispVsFarmEntryButton(void)
{
    s32 model = 3;

    if (flag_VsFarmEntryButton[0] == 0)
        return;
    if (flag_VsFarmEntryButton[0] == 1) {
        flag_VsFarmEntryButton[0] = 2;
        SetAnimArc2(menu1p, 3, flag_VsFarmEntryButton[1]);
    }
    if (flag_VsFarmEntryButton[0] == 2) {
        if (sFarmAnim(model) != 0) {
            flag_VsFarmEntryButton[0] = 3;
            switch (flag_VsFarmEntryButton[1]) {
            case 0:
                flag_VsFarmEntryButton[1] = 1;
                flag_VsFarmEntryButton[0] = 2;
                break;
            case 5:
                flag_VsFarmEntryButton[0] = 0;
                break;
            default:
                flag_VsFarmEntryButton[0] = 2;
                break;
            }
            SetAnimArc2(menu1p, 3, flag_VsFarmEntryButton[1]);
            jobjAnim(menu1p->models[model]);
        }
    }
    HSD_JObjDispAll(GetChild(menu1p->models[model], 0, 0, -1, -1, -1), 0, 7, 0);
}
