#include "model_archive.h"

extern ModelArchive *menu1p;
extern s8 vsman;
extern s16 flag_VsEntryLoadButton[2][2];
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void sSetAnim1(ModelArchive *archive, s32 model, HSD_JObj *joint, s32 animation);
extern s32 jobjAnim1(HSD_JObj *joint);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

static inline s32 menuAnim1(HSD_JObj *jobj)
{
    s32 done = jobjAnim1(jobj);

    return done;
}

void menu_sDispVsEntryLoadButton(void)
{
    s32 model = 4;
    HSD_JObj *button;

    button = GetChild(menu1p->models[model], 0, vsman, -1, -1, -1);
    if (flag_VsEntryLoadButton[vsman][0] == 0)
        return;
    if (flag_VsEntryLoadButton[vsman][0] == 1) {
        flag_VsEntryLoadButton[vsman][0] = 2;
        sSetAnim1(menu1p, 4, button, flag_VsEntryLoadButton[vsman][1]);
    }
    if (flag_VsEntryLoadButton[vsman][0] == 2 && menuAnim1(button) != 0) {
        flag_VsEntryLoadButton[vsman][0] = 3;
        switch (flag_VsEntryLoadButton[vsman][1]) {
        case 0:
            flag_VsEntryLoadButton[vsman][1] = 0;
            flag_VsEntryLoadButton[vsman][0] = 2;
            break;
        case 1:
            flag_VsEntryLoadButton[vsman][1] = 2;
            flag_VsEntryLoadButton[vsman][0] = 2;
            break;
        case 2:
            flag_VsEntryLoadButton[vsman][1] = 2;
            flag_VsEntryLoadButton[vsman][0] = 2;
            break;
        case 3:
            flag_VsEntryLoadButton[vsman][1] = 3;
            flag_VsEntryLoadButton[vsman][0] = 2;
            break;
        case 5:
            flag_VsEntryLoadButton[vsman][0] = 0;
            break;
        default:
            flag_VsEntryLoadButton[vsman][0] = 2;
            break;
        }
        sSetAnim1(menu1p, 4, button, flag_VsEntryLoadButton[vsman][1]);
        menuAnim1(button);
    }
    HSD_JObjDispAll(button, 0, 7, 0);
}
