#include "zoid.h"
#include "model_archive.h"
#include "game_pad.h"
#include "game_mode.h"

extern ModelArchive *dspPause;
extern s32 pBak;
extern s32 pause;
extern volatile s32 menuRet;
extern s32 gameTime;
extern PadState *sPad1, *sPad2;
extern s32 jobjAnim(HSD_JObj *joint);

static inline HSD_JObj *GetPauseModel(s32 i)
{
    HSD_JObj *jobj = dspPause->models[i];
    return jobj;
}

void sDispPauseProc(void)
{
    HSD_JObj *root;
    HSD_JObj *cursor;
    HSD_JObj *select;
    PadState *pad;
    ZoidState *zoid;

    if (dspPause == 0)
        return;
    root = GetPauseModel(0);
    cursor = dspPause->models[7];
    select = dspPause->models[8];
    if (root == 0)
        return;
    if (pBak != pause) {
        SetAnimArc2(dspPause, 0, 0);
        if (cursor != 0)
            SetAnimArc2(dspPause, 7, 0);
        if (select != 0)
            SetAnimArc2(dspPause, 8, 0);
        jobjAnim(root);
        pBak = pause;
        menuRet = 0;
    }
    pad = sPad1;
    if (pause == 2)
        pad = sPad2;
    if (pad->start != 0)
        return;
    if (pad->pressed_down != 0 || pad->pressed_up != 0)
        menuRet = 1 - menuRet;
    if (pad->pressed_a == 0)
        return;
    if (menuRet == 1) {
        if (GameMode.game_type == GAME_TYPE_VS) {
            if (pause != 0) {
                zoid = &Zoid[pause];
                zoid[-1].health = 0;
                zoid[-1].knockback[0] = 2.0f;
                zoid[-1].requested_action = ZOID_ACTION_DMG3_0;
            }
        } else {
            Zoid[0].health = 0;
            Zoid[0].knockback[0] = 2.0f;
            Zoid[0].requested_action = ZOID_ACTION_DMG3_0;
        }
        gameTime = 0;
    }
    pause = 0;
}
