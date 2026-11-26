#include "model_archive.h"
#include "game_mode.h"

typedef struct SaveLoadAnim {
    s16 state;
    s16 anim;
} SaveLoadAnim;

extern ModelArchive *menu_saveloadp;
extern s32 menusaveloadDataSelect;
extern SaveLoadAnim menusaveloadDatamainanm;
extern SaveLoadAnim menusaveloadDataNoanm;
extern s16 menusaveloadslot;
extern s16 menuSLPos[5];
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern s32 jobjAnim(HSD_JObj *joint);
extern void jobjDisp(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);
extern void menu_sDispSaveLoadDataNo(s32 data, s16 slot);

void menu_sDispSaveLoadDataWindow(void)
{
    s16 model;
    s32 i;
    s32 frame_padding[4];

    model = 5;
    if (menusaveloadDataSelect == 0)
        return;
    if (menusaveloadDatamainanm.state == 0)
        return;
    if (menusaveloadDatamainanm.state == 1) {
        SetAnimArc2(menu_saveloadp, model, menusaveloadDatamainanm.anim);
        menusaveloadDatamainanm.state = 2;
    }
    if (menusaveloadDatamainanm.state == 2) {
        if (jobjAnim(menu_saveloadp->models[model]) != 0) {
            menusaveloadDatamainanm.state = 3;
            switch (menusaveloadDatamainanm.anim) {
            case 0:
                menusaveloadDatamainanm.anim = 1;
                menusaveloadDatamainanm.state = 2;
                break;
            case 2:
                menusaveloadDatamainanm.state = 0;
                return;
            default:
                menusaveloadDatamainanm.state = 2;
                break;
            }
            SetAnimArc2(menu_saveloadp, model, menusaveloadDatamainanm.anim);
            jobjAnim(menu_saveloadp->models[model]);
        }
    }
    jobjDisp(GetChild(menu_saveloadp->models[model], 0, -1, -1, -1, -1));
    jobjDisp(GetChild(menu_saveloadp->models[model], 0, 0, -1, -1, -1));
    jobjDisp(GetChild(menu_saveloadp->models[model], 0, 0, menusaveloadslot, -1, -1));
    jobjDispAll(GetChild(menu_saveloadp->models[model], 0, 1, -1, -1, -1));
    if (GameMode.game_type == GAME_TYPE_BATTLE)
        model = 7;
    else if (GameMode.game_type == GAME_TYPE_MISSION)
        model = 6;
    if (menusaveloadDatamainanm.anim != 1)
        return;
    if (menusaveloadDataNoanm.state == 0)
        return;
    if (menusaveloadDataNoanm.state == 1) {
        SetAnimArc2(menu_saveloadp, model, menusaveloadDataNoanm.anim);
        menusaveloadDataNoanm.state = 2;
    }
    if (menusaveloadDataNoanm.state == 2) {
        if (jobjAnim(menu_saveloadp->models[model]) != 0) {
            menusaveloadDataNoanm.state = 3;
            switch (menusaveloadDataNoanm.anim) {
            case 0:
                menusaveloadDataNoanm.anim = 1;
                menusaveloadDataNoanm.state = 2;
                break;
            case 2:
                menusaveloadDataNoanm.state = 0;
                return;
            default:
                menusaveloadDataNoanm.state = 2;
                break;
            }
            SetAnimArc2(menu_saveloadp, model, menusaveloadDataNoanm.anim);
            jobjAnim(menu_saveloadp->models[model]);
        }
    }
    for (i = 0; i < 4; i++)
        menu_sDispSaveLoadDataNo(i + menuSLPos[2], i);
}
