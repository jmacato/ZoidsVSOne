#include "game_camera.h"
#include "zoid.h"
#include "zoid_ai.h"

extern CameraState *camTmp;
extern s32 gameEndF;
extern u32 gameEndTm;
extern s32 camTypeB;
extern void sCameraCtrl(CameraState *camera);
extern void sCameraON(CameraState *camera);
extern void camOn(CameraState *camera);
extern void ZoidLen(void);
extern void ZoidAllAnim(void);
extern void ZoidAllMat(void);
extern void ZoidAllMove(void);
extern void sMissileMove(void);
extern void grdObjAnim(void);
extern void grdObjTest(void);
extern void psInterpretParticles(s32 a);
extern void psExecGenerator(s32 a);
extern void ZoidAllPutXZ(void);
extern void sWeaponMoveAll(void);
extern void ZoidWeaponActLoop(void);
extern void sLsrMove(void);
extern void ZoidZdCoObjBodyAll(void);
extern void ZoidCoObjAll(void);
extern void ZoidZdAll(void);
extern void sEffectAnimAll(void);
extern void ZoidAllSmoke(void);
extern void sCameraShadowAll(void);
extern s32 gameEnd(void);
extern void TeaBgm(s32 track);

void game1(void)
{
    s32 i;
    u8 frame_padding[8];

    camTmp = sCamera;
    if (gameEndF > 3)
        return;
    for (i = 0; i < 4; i++) {
        sCameraCtrl(&sCamera[i]);
    }
    ZoidAI();
    for (i = 0; i < 4; i++) {
        if (camTypeB == 0)
            sCameraON(&sCamera[i]);
        else
            camOn(&sCamera[i]);
    }
    camTmp = sCamera;
    ZoidLen();
    ZoidAllAnim();
    ZoidAllMat();
    ZoidAllMove();
    sMissileMove();
    grdObjAnim();
    grdObjTest();
    psInterpretParticles(0);
    psExecGenerator(0);
    ZoidAllPutXZ();
    ZoidAllMat();
    sWeaponMoveAll();
    ZoidWeaponActLoop();
    sLsrMove();
    ZoidZdCoObjBodyAll();
    ZoidCoObjAll();
    ZoidZdAll();
    sEffectAnimAll();
    ZoidAllSmoke();
    sCameraShadowAll();
    if (gameEnd() != 0 && gameEndF == 0)
        gameEndF = 1;
    if (gameEndF != 0) {
        gameEndTm++;
        if (gameEndTm > 300) {
            if (gameEndF == 1) {
                gameEndF = 2;
                TeaBgm(-1);
            }
        } else if (Zoid[0].field_1B90 != 0) {
            gameEndTm = 300;
        }
    } else {
        gameEndTm = 0;
    }
    if (gameEndF >= 4) {
        for (i = 0; i < 16; i++) {
            if (Zoid[i].joint != 0)
                Zoid[i].rumble_timer = 0;
        }
    }
}
