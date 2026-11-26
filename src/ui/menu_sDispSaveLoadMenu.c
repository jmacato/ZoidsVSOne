#include "model_archive.h"

typedef struct SaveLoadWindow {
    s16 active;
    s16 anim;
} SaveLoadWindow;

extern SaveLoadWindow menudispslwindow[3];
extern ModelArchive *menu1p;
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void sSetAnim1(ModelArchive *archive, s32 model, HSD_JObj *joint, s32 animation);
extern s32 jobjAnim1(HSD_JObj *joint);
extern void jobjDispAll(HSD_JObj *joint);

void menu_sDispSaveLoadMenu(void)
{
    s32 idx = 24;
    s16 anim;
    s16 i;

    for (i = 0; i < 3; i++) {
        if (menudispslwindow[i].active == 1) {
            sSetAnim1(menu1p, 24, GetChild(menu1p->models[idx], 0, i, -1, -1, -1), menudispslwindow[i].anim);
            menudispslwindow[i].active = 2;
        }
        if (menudispslwindow[i].active == 2) {
            if (jobjAnim1(GetChild(menu1p->models[idx], 0, i, -1, -1, -1)) != 0) {
                menudispslwindow[i].active = 3;
                anim = menudispslwindow[i].anim;
                if (anim == 1 || anim == 6) {
                    if (anim == 1) {
                        menudispslwindow[i].anim = 2;
                        menudispslwindow[i].active = 2;
                    }
                    if (menudispslwindow[i].anim == 6) {
                        menudispslwindow[i].anim = 0;
                        menudispslwindow[i].active = 2;
                    }
                    sSetAnim1(menu1p, 24, GetChild(menu1p->models[idx], 0, i, -1, -1, -1), menudispslwindow[i].anim);
                    jobjAnim1(GetChild(menu1p->models[idx], 0, i, -1, -1, -1));
                } else if (anim == 0) {
                    menudispslwindow[i].active = 2;
                } else if (anim == 2) {
                    menudispslwindow[i].anim = 2;
                    menudispslwindow[i].active = 2;
                } else if (anim == 3) {
                    menudispslwindow[i].anim = 3;
                    menudispslwindow[i].active = 2;
                } else if (anim == 4) {
                    menudispslwindow[i].anim = 4;
                    menudispslwindow[i].active = 2;
                } else if (anim == 5) {
                    menudispslwindow[i].anim = 5;
                    menudispslwindow[i].active = 2;
                }
            }
        }
        if (menudispslwindow[i].active != 0)
            jobjDispAll(GetChild(menu1p->models[24], 0, i, -1, -1, -1));
    }
}
