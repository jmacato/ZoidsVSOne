#pragma readonly_strings on
#include "game_mode.h"
#include "map_info.h"
#include "game_pad.h"
#include "zoid.h"
#include "zoid_ai.h"
#include "game_camera.h"
#include "gx_tev.h"
#include "initialize.h"
#include "os_reset.h"
#include "video.h"
#include "fog.h"
#include "perf.h"
#include "os_time.h"

extern HSD_Fog *fogG;
extern ModelArchive *Sky;
extern MapInfo mgI;
extern s32 gameTime;
extern s32 vsyncN;
extern CameraState *camTmp;
extern s32 sCamNS2;
extern s32 VsMode;
extern s32 VsTime;
extern s32 VsTimeTBL[];
extern s16 TEA_SEVOL;
extern PadState *sPad1;
extern PadState *sPad2;
extern PadState *sPad3;
extern PadState *sPad4;
extern void OSReport(const char *format, ...);
extern s32 sprintf(char *dst, const char *format, ...);
extern s32 fexist(char *path);
extern void putErr(char *message);
extern void sMissileEpilogue(void);
extern void sEffectEpilogue(void);
extern s32 HSD_Rand(void);
extern void LoadStageNow(s32 stage);
extern void ZoidInitAll(void);
extern void ZoidCalcAll(void);
extern void testLocate(s32 index);
extern f32 sColPosY(f32 *position, u16 *selector);
extern void zdCoStartPos(ZoidState *zoid);
extern void ZoidAmbientSetSkyAll(void);
extern void sDispLoadParts(s32 count);
extern void sCameraSetShadowAll(void);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void sEffectPrologue(void);
extern void sMissilePrologue(void);
extern void sLsrPrologue(void);
extern u32 VIGetRetraceCount(void);
extern void TEA_VoiceOn(u8 voice, s32 type);
extern void IntSePrologue(void);
extern void sPadAll(void);
extern void game1(void);
extern void voiceSet(s32 win);
extern s32 gameWin(void);
extern void *OSAllocFromHeap(s32 heap, u32 size);
extern void HSD_Free(void *ptr);
extern void draw1(s32 first_camera);
extern void sPutFontAllNn(void);
extern void VIWaitForRetrace(void);
extern void IntSeClear(void);
extern void HSD_AudioSFXKeyOffAll(void);
extern void sDispPauseProc(void);
extern void TeaBgm(s16 track);
extern s32 putBP(void);
extern void TEA_SeKeyOn(s32 id, u8 vol, s32 a, s32 b);
extern void sLsrEpilogue(void);
extern void sMissilePurgeAll(void);
extern void sDispPurgeParts(void);
extern void sWeaponUnMountAll(ZoidState *zoid);
extern void ZoidPurgeAll(void);
extern void PurgeStageData(void);
extern void psKillAllGenerator(void);
extern void psKillAllParticle(void);

#pragma force_active on
static u8 aram_block[64];
GameModeState GameMode;
s32 bp[12];
void *dspLoad = 0;
s32 normLineDEBUG = 0;
s32 ctrlZoid = 0;
static s32 AreaIn;
static s32 vOn44;
static s32 lastGame;
s32 winF;
s32 gameEndF;
s32 gameEndTm;
s32 gameContinueTm;
s32 pause;
s32 bpTm[2];
s32 gametime;
#pragma force_active off


extern s32 calcEndVsMan(void);
extern f64 __frsqrte(f64);

static inline f32 sqrtf(f32 x)
{
    static const f64 _half = 0.5;
    static const f64 _three = 3.0;
    volatile f32 y;

    if (x > 0.0f) {
        f64 guess = __frsqrte((f64)x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

#pragma dont_inline on
s32 calcEndBattle(void)
{
    ZoidState *first = &Zoid[0];
    s32 player_slot = first->slot;
    s32 i;
    s32 opponent_alive = 0;

    for (i = 0; i < 16; i++) {
        ZoidState *zoid = &Zoid[i];
        if (zoid->joint != 0 && zoid->slot != player_slot && zoid->death_started == 0)
            opponent_alive = 1;
    }
    if (first->death_started == 0) {
        if (opponent_alive != 0)
            return GAME_RESULT_NONE;
        return GAME_RESULT_WIN;
    }
    if (opponent_alive != 0)
        return GAME_RESULT_LOSE;
    return GAME_RESULT_DRAW;
}

#pragma push
#pragma dont_inline off
static s32 calcEndMission(void)
{
    s32 unused[2];
    s16 hp;
    ZoidState *zoid;
    s32 i;
    f32 dz;
    s32 alive;
    s16 type;
    s32 slot;
    f32 dx;

    zoid = &Zoid[0];
    slot = zoid->slot;
    if (zoid->death_started != 0)
        return GAME_RESULT_LOSE;
    switch (mgI.clear_condition) {
    case MISSION_CLEAR_DESTROY_ALL:
    case 1:
    case 4:
        for (i = 0, alive = 0; i < 16; i++) {
            zoid = &Zoid[i];
            if (zoid->joint != 0 && zoid->slot != slot && zoid->death_started == 0)
                alive++;
        }
        if (alive == 0)
            return GAME_RESULT_WIN;
        break;
    case MISSION_CLEAR_TARGET_HEALTH:
        type = mgI.target_type;
        hp = mgI.target_health;
        for (i = 0, alive = 0; i < 16; i++) {
            zoid = &Zoid[i];
            if (zoid->joint != 0 && zoid->slot != slot && zoid->type == type) {
                alive++;
                if (zoid->health <= hp)
                    return GAME_RESULT_WIN;
            }
        }
        break;
    case MISSION_CLEAR_AREA:
        dx = zoid->position[0] - mgI.area_x;
        dz = zoid->position[2] - mgI.area_z;
        if (sqrtf(dx * dx + dz * dz) < mgI.area_radius)
            AreaIn = 1;
        if (AreaIn != 0)
            return GAME_RESULT_WIN;
        break;
    case MISSION_CLEAR_KILLS:
        i = 0;
        alive = i;
        for (; i < 16; i++) {
            zoid = &Zoid[i];
            if (zoid->joint != 0 && zoid->slot == slot)
                alive += zoid->kills;
        }
        if (alive >= mgI.required_kills)
            return GAME_RESULT_WIN;
        break;
    }
    return GAME_RESULT_NONE;
}
#pragma pop

s32 calcEnd(void)
{
    switch (GameMode.game_type) {
    case GAME_TYPE_BATTLE:
        return calcEndBattle();
    case GAME_TYPE_VS:
        return calcEndVsMan();
    case GAME_TYPE_3:
        return calcEndVsMan();
    case GAME_TYPE_MISSION:
        return calcEndMission();
    default:
        return calcEndBattle();
    }
}

#pragma dont_inline off



s32 putBP(void)
{
    s32 i;
    s32 j;
    s32 count;
    s32 done = 0;

    if (bpTm[0] == 0)
        return 0;
    if (bpTm[0] < 60) {
        bpTm[0]++;
    } else {
        count = 0;
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (bp[i + 6] < bp[i]) {
                    bp[i + 6]++;
                    if (sPad1->a != 0)
                        bp[i + 6] = bp[i];
                    count++;
                }
            }
        }
        if (count == 0)
            done = 1;
    }
    if (done != 0) {
        bpTm[1]++;
        if (bpTm[1] > 60)
            return 1;
    }
    return 0;
}

/* unreferenced, keeps the unit's .rodata layout */
#pragma force_active on
static const char sTex1BKaPath[15] = "tex/1_B_KA.DTX";
static const char sVoiceReportFormat[21] = "chara =%d , vc =%d \n";
#pragma force_active off

static void game0(void)
{
    char path[84];
    u8 unused[84];
    void *ptrs[1024];
    u8 unused2[28];
    u32 tick;
    s32 prevbp;
    s32 cnt5;
    s32 now;
    s32 stage;
    s32 ok;
    s32 i;
    s32 n;
    s32 m;
    s32 bpcnt;
    s32 skip;
    s32 drawn;
    u32 last;
    u32 prev;
    ZoidState *zoid;
    CameraState *camera;
    s32 j;
    ZoidState *z2;
    ZoidControlData *ctrl;
    s32 f;
    f32 scale;
    f32 x;
    f32 y;

    skip = 0;
    drawn = 0;
    gameEndTm = 0;
    gameEndF = 0;
    sMissileEpilogue();
    sEffectEpilogue();
    OSReport("#\203Q\201[\203\200\203X\203^\201[\203g!! \n");
    vOn44 = 0;
    HSD_Rand();
    if (GameMode.game_type == GAME_TYPE_BATTLE)
        GameMode.map_no = mgI.map_no;
    if (GameMode.game_type == GAME_TYPE_MISSION)
        GameMode.map_no = mgI.map_no;
    stage = GameMode.map_no;
    ok = 1;
    sprintf(path, "stage/st%02d.dat", stage);
    if (fexist(path) == 0)
        ok = 0;
    sprintf(path, "stage/skymap%02d.dat", stage);
    if (fexist(path) == 0)
        ok = 0;
    if (ok == 0) {
        sprintf(path, "stage not found %d ", stage);
        putErr(path);
        OSReport("%s \n", path);
        stage = 3;
    }
    LoadStageNow(stage);
    if (fogG != 0)
        HSD_VIData.current.vi.clear_clr = fogG->color;
    ZoidInitAll();
    ZoidCalcAll();
    for (i = 1; i < 16; i++)
        Zoid[i].slot = i & 1;
    if (GameMode.game_type == GAME_TYPE_VS || GameMode.game_type == GAME_TYPE_3) {
        testLocate(0);
        testLocate(1);
        testLocate(2);
        testLocate(3);
    }
    for (i = 0; i < 16; i++) {
        if (Zoid[i].joint != 0) {
            Zoid[i].heading = 3.1415926f;
            Zoid[i].position[1] = 100.0f + sColPosY(Zoid[i].position, 0);
            Zoid[i].position[1] = 1.0f + sColPosY(Zoid[i].position, 0);
            zdCoStartPos(&Zoid[i]);
            zdCoStartPos(&Zoid[i]);
        }
    }
    ZoidAmbientSetSkyAll();
    for (i = 0; i < 16; i++)
        aiPrologue(i);
    sCameraPurge();
    if (GameMode.game_type == GAME_TYPE_VS)
        sCamNN = 2;
    else
        sCamNN = 1;
    if (sCamNN == 2) {
        sCamNS2 = VsMode == 0;
        if (sCamNS2 != 0) {
            sCameraSetHalf2(&sCamera[0], 1);
            sCameraSetHalf2(&sCamera[1], 0);
        } else {
            sCameraSetHalf(&sCamera[0], 1);
            sCameraSetHalf(&sCamera[1], 0);
        }
        sCamera[0].lights = Sky->lights;
        sCamera[1].lights = Sky->lights;
        sCameraTargetZoid(&sCamera[0], &Zoid[0]);
        sCameraTargetZoid(&sCamera[1], &Zoid[1]);
        sDispLoadParts(2);
    } else {
        sCameraSetNormal(&sCamera[0]);
        sCamera[0].lights = Sky->lights;
        sCameraTargetZoid(&sCamera[0], &Zoid[0]);
        sDispLoadParts(1);
    }
    for (j = 0; j < 4; j++) {
        camera = &sCamera[j];
        if (camera->cobj != 0 && (zoid = camera->zoid) != 0) {
            camera->relative_origin.x = 100.0f + zoid->position[0];
            camera->field_19C.x = 100.0f + zoid->position[0];
            camera->eye.x = 100.0f + zoid->position[0];
            camera->relative_origin.y = 100.0f + zoid->position[1];
            camera->field_19C.y = 100.0f + zoid->position[1];
            camera->eye.y = 100.0f + zoid->position[1];
            camera->relative_origin.z = 100.0f + zoid->position[2];
            camera->field_19C.z = 100.0f + zoid->position[2];
            camera->eye.z = 100.0f + zoid->position[2];
        }
    }
    sCameraSetShadowAll();
    HSD_VISetBlack(0);
    ZoidSetAnim(&Zoid[0], 3);
    ZoidSetAnim(&Zoid[1], 3);
    ZoidSetAnim(&Zoid[2], 3);
    ZoidSetAnim(&Zoid[3], 3);
    ZoidSetAnim(&Zoid[4], 4);
    ZoidSetAnim(&Zoid[5], 4);
    ZoidSetAnim(&Zoid[6], 5);
    ZoidSetAnim(&Zoid[7], 5);
    sEffectPrologue();
    sMissilePrologue();
    sLsrPrologue();
    for (i = 0; i < 16; i++) {
        zoid = &Zoid[i];
        if (zoid->joint != 0) {
            ctrl = zoid->control;
            zoid->weapon_mount = -1;
            f = 0;
            if (ctrl != 0 && ctrl->field_0140[0] == 2)
                f = 1;
            zoid->selected_weapon_mount = f;
        }
    }
    last = VIGetRetraceCount();
    winF = GAME_RESULT_NONE;
    tick = last;
    TEA_VoiceOn(Zoid[0].person, 2);
    gameTime = 36180;
    if (GameMode.game_type == GAME_TYPE_VS || GameMode.game_type == GAME_TYPE_3) {
        if (VsTimeTBL[VsTime] == -1)
            gameTime = -1;
        else
            gameTime = VsTimeTBL[VsTime] * 3600 + 60;
    }
    GameMode.win = 0;
    gameEndF = 0;
    bpcnt = 0;
    GameMode.gametime = 0;
    cnt5 = 0;
    gametime = 0;
    bpTm[0] = 0;
    bpTm[1] = 0;
    prevbp = 0;
    AreaIn = 0;
    gameContinueTm = 1200;
    IntSePrologue();
    scale = 20.0f;
    while (1) {
        static s32 bak = -1;

        HSD_PerfInitStat();
        HSD_PerfSetStartTime();
        vsyncN++;
        sPadAll();
        camTmp = sCamera;
        game1();
        if (bak != gameEndF)
            OSReport("gameEndF=%d\n", gameEndF);
        bak = gameEndF;
        if (gameEndF == 0) {
            gametime++;
        } else {
            Zoid[0].rumble_timer = 0;
            Zoid[1].rumble_timer = 0;
            sPad1->rumble = 0;
            sPad2->rumble = 0;
        }
        if (gameEndF == 6)
            voiceSet(winF);
        if (gameEndF == 5) {
            cnt5++;
            if (cnt5 > 300)
                gameEndF = 6;
        }
        if (gameEndF == 4) {
            winF = gameWin();
            OSReport("gameEndF=4-5 winF=%d \n", winF);
            gameEndF = 5;
            voiceSet(winF);
        }
        HSD_PerfSetCPUTime();
        camTmp = sCamera;
        prev = tick;
        tick = VIGetRetraceCount();
        if (normLineDEBUG != 0) {
            static char str[0x100];
            n = tick - prev;
            if (n < 0)
                n = 0;
            for (i = 0; i < n * 4; i++)
                str[i] = ' ';
            str[n * 4] = 0;
        }
        if (normLineDEBUG != 0) {
            static char str0[0x100];
            static char str1[0x100];
            static char strS[0x100];
            static char strF0[0x100];
            static char strF1[0x100];
            y = HSD_PerfLastStat.draw_time;
            x = HSD_PerfLastStat.cpu_time;
            (void)(x == HSD_PerfLastStat.draw_time);
            n = x * scale;
            m = y * scale;
            for (i = 0; i < n; i++)
                str0[i] = ' ';
            str0[i] = 0;
            for (i = 0; i < m; i++)
                str1[i] = ' ';
            str1[i] = 0;
            for (i = 0; i < (s32)scale; i++)
                strS[i] = ' ';
            strS[i] = 0;
            sprintf(strF0, "C %8f", x);
            sprintf(strF1, "D %8f", y);
        }
        for (i = 0; i < 1024; i++)
            ptrs[i] = 0;
        for (n = 0; n < 1024; n++) {
            ptrs[n] = OSAllocFromHeap(HSD_GetHeap(), 0x10000);
            if (ptrs[n] == 0)
                break;
        }
        m = n << 6;
        for (i = 0; i < 1024; i++) {
            if (ptrs[i] != 0)
                HSD_Free(ptrs[i]);
        }
        if (m >= 0x6000)
            m -= 0x6000;
        {
            static char str[0x32];
            sprintf(str, "memory %4dM.%4dK byte(s)", m / 1024, m & 0x3FF);
        }
        pause = 0;
    loop:
        (void)(i == (s32)&HSD_PerfLastStat);
        now = VIGetRetraceCount();
        if (skip > 100)
            skip--;
        if (now - last < 1 || drawn > 0) {
            camTmp = &sCamera[0];
            draw1(1);
            for (now = 1; now < 4; now++) {
                camTmp = &sCamera[now];
                draw1(0);
            }
            sPutFontAllNn();
            HSD_VICopyXFB(HSD_RP_SCREEN);
            HSD_VISetXFBDrawDone();
            if (VIGetRetraceCount() - last < 2)
                VIWaitForRetrace();
            drawn = 0;
        } else {
            skip = 200;
            drawn++;
        }
        IntSeClear();
        last = now;
        HSD_PerfSetDrawTime();
        HSD_PerfSetTotalTime();
        if (gameEndF < 2) {
            if (sPad1->pressed_start != 0) {
                if (pause == 0)
                    pause = 1;
                else if (pause == 1)
                    pause = 0;
            }
            if (GameMode.game_type == GAME_TYPE_VS && sPad2->pressed_start != 0) {
                if (pause == 0)
                    pause = 2;
                else if (pause == 2)
                    pause = 0;
            }
        }
        if (pause != 0) {
            HSD_AudioSFXKeyOffAll();
            sDispPauseProc();
            HSD_PerfInitStat();
            HSD_PerfSetStartTime();
            vsyncN++;
            Zoid[0].rumble_timer = 0;
            Zoid[1].rumble_timer = 0;
            sPad1->rumble = 0;
            sPad2->rumble = 0;
            sPad3->rumble = 0;
            sPad4->rumble = 0;
            Zoid[0].rumble_timer = 0;
            Zoid[1].rumble_timer = 0;
            sPadAll();
            HSD_PerfSetCPUTime();
            putErr("pause");
            goto loop;
        }
        if (gameEndF == 12)
            break;
        if (gameEndF == 8) {
            HSD_AudioSFXKeyOffAll();
            switch (GameMode.game_type) {
            case GAME_TYPE_BATTLE:
                if (winF == GAME_RESULT_DRAW || winF == GAME_RESULT_LOSE) {
                    sPad1->pressed_a = 0;
                    gameContinueTm = 1200;
                    gameEndF = 9;
                    GameMode.win = 3;
                    TeaBgm(-1);
                    sPadAll();
                } else {
                    TeaBgm(-1);
                    gameEndF = 11;
                    GameMode.win = 2;
                    for (i = 0; i < 6; i++) {
                        bp[i] = 0;
                        bp[i + 6] = 0;
                    }
                    if (gameTime > 0)
                        bp[0] = gameTime / 60 * 10;
                    if (bp[0] > 9999)
                        bp[0] = 9999;
                    bp[1] = Zoid[0].health;
                    if (Zoid[2].joint != 0)
                        bp[2] = Zoid[2].health;
                    else
                        bp[2] = Zoid[0].max_health;
                    bp[3] = Zoid[0].field_1BDC;
                    bp[4] = Zoid[0].field_1BE0;
                    bp[5] = 0;
                }
                break;
            case GAME_TYPE_MISSION:
                TeaBgm(-1);
                gameEndF = 12;
                GameMode.win = winF == GAME_RESULT_WIN ? 2 : 3;
                break;
            default:
                gameEndF = 12;
                GameMode.win = winF == GAME_RESULT_WIN ? 2 : 3;
                break;
            }
        }
        if (gameEndF == 9) {
            OSReport("gameEndF=9 tm=%d pA=%s \n", gameContinueTm, sPad1->pressed_a ? "On" : "Of");
            gameContinueTm--;
            if (gameContinueTm <= 0) {
                gameContinueTm = 0;
                gameEndF = 12;
            }
            if (sPad1->left != 0 || sPad1->right != 0) {
                if (sPad1->left != 0)
                    GameMode.win = 3;
                else
                    GameMode.win = 0;
            }
            if (sPad1->pressed_a != 0) {
                gameContinueTm = 0;
                gameEndF = 10;
            }
        }
        if (gameEndF == 11) {
            if (GameMode.game_type == GAME_TYPE_BATTLE) {
                if (GameMode.win == 2) {
                    if (putBP() != 0) {
                        if (GameMode.map != 11)
                            TEA_VoiceOn(15, 97);
                        gameEndF = 13;
                    } else {
                        bpcnt++;
                        if (bpcnt > 15 && prevbp != bp[11]) {
                            bpcnt = 0;
                            TEA_SeKeyOn(543, TEA_SEVOL, 64, 64);
                            OSReport("b");
                            prevbp = bp[11];
                        }
                    }
                    GameMode.bp_earned = bp[11];
                } else {
                    gameEndF = 12;
                }
            } else {
                gameEndF = 12;
            }
        }
        if (gameEndF == 13) {
            bpTm[1]++;
            if (bpTm[1] > 480)
                gameEndF = 12;
        }
    }
    VIWaitForRetrace();
    VIWaitForRetrace();
    VIWaitForRetrace();
    GameMode.gametime = gametime / 60;
    i = 0;
    sPad1->rumble = 0;
    sPad2->rumble = 0;
    sPad3->rumble = 0;
    sPad4->rumble = 0;
    for (i = 0; i < 16; i++)
        aiEpilogue(i);
    sEffectEpilogue();
    sLsrEpilogue();
    sMissilePurgeAll();
    sMissileEpilogue();
    sDispPurgeParts();
    sCameraPurge();
    for (i = 0; i < 16; i++) {
        z2 = &Zoid[i];
        if (z2->joint != 0)
            sWeaponUnMountAll(z2);
        z2++;
    }
    ZoidPurgeAll();
    PurgeStageData();
    HSD_AudioSFXKeyOffAll();
    psKillAllGenerator();
    psKillAllParticle();
}

#pragma force_active on
static u8 fixt[0x5A88];
#pragma force_active off


extern void *dspFilter;
extern HSD_JObj *jobjFilter[3];
extern s32 sCamNN2, sZoidHG;

extern void debugFileUnPurgeList(void);
extern void ascPrologue(void);
extern void ascEpilogue(void);
extern HSD_JObj *CopyJoint2(void *arc, s32 index);
extern void ZoidPrologue(void);
extern void ZoidEpilogue(void);
extern void GameZoidInit(void);
extern void sWeaponPrologue(void);
extern void sWeaponEpilogue(void);
extern void zDispCursorPrologue(void);
extern void zDispCursorEpilogue(void);
extern void HSD_SetZSortMode(s32 a, s32 b);
extern void HSD_StateInvalidate(s32 state);
extern void HSD_FogSet(HSD_Fog *fog);
extern void ttlMain(void);
extern void loadMapInfo(void);
extern void Epilogue(void);
extern void waitV(s32 n);
extern void jobjUnrefAll(HSD_JObj *jobj);
extern s32 sReadPre(void);
extern void chkVS(void);
extern void HSD_AudioStreamStop(s32 a);



static void gameBgm(s32 game_type, s32 map)
{
    TeaBgm(-1);
    if (map < 0)
        return;
    if (game_type == GAME_TYPE_BATTLE) {
        s32 tracks[16] = {1, 2, 3, 4, 6, 1, 2, 3, 4, 6, 1, 12, 1, 1, 1, 1};
        if (map >= 12)
            return;
        TeaBgm(tracks[map]);
    }
    if (game_type == GAME_TYPE_VS)
        TeaBgm(3);
    if (game_type == GAME_TYPE_3)
        TeaBgm(18);
    if (game_type == GAME_TYPE_MISSION) {
        s32 tracks[86] = {
            17, 17, 3, 30, 16, 16, 34, 34, 34, 34, 31, 30, 32, 16, 17, 31,
            17, 30, 30, 17, 16, 31, 34, 32, 34, 30, 31, 32, 30, 16, 30, 32,
            17, 34, 31, 35, 35, 35, 35, 30, 30, 30, 35, 35, 35, 16, 16, 34,
            34, 34, 30, 30
        };
        if (map == 100)
            return;
        if (map > 70)
            map = 70;
        if (tracks[map] >= 0)
            TeaBgm(tracks[map]);
    }
}

typedef struct HSD_PadQueue { u8 data[52]; } HSD_PadQueue;
extern GXRenderModeObj GXNtsc480IntDf;
extern void *memcpy(void *dst, const void *src, u32 n);
extern void *menu_saveloadiconp, *menu_yesnop;
extern s32 dspLoadF;
extern void *OSGetArenaLo(void);
extern void *OSGetArenaHi(void);
extern void *OSInitAlloc(void *lo, void *hi, s32 heaps);
extern void OSSetArenaLo(void *lo);
extern void sFileInit(void);
extern u32 OSGetPhysicalMemSize(void);
extern void *mallocF(u32 size);
extern void HSD_GetVersion(s32 *a, s32 *b, s32 *c, s32 *d);
extern void debug11(void);
extern void HSD_PadInit(s32 n, HSD_PadQueue *queue, s32 a, s32 b);
extern void sPadInit(void);
extern void sFontInit(void);
extern void sFontUn(void);
extern void TEA_SoundInit(void);
extern void TEA_SoundDefLoad(void);
extern void configGet(void);
extern void TEA_defstatusload(void);
extern void TEA_mcInit(void);
extern void TEA_USBInit(void);
extern u32 OSGetSoundMode(void);
extern void sndOutputMode(s32 mode);
extern void sCameraInit(void);
extern void sCameraUn(void);
extern void initPtcl(void);
extern void readPtcl(const char *name);
extern void forgetPtcl(void);
extern void TEA_AudioSeqStop(void);
extern void TEA_AudioSeqFree(void);
extern void TEA_SoundSfxPop(void);
extern void sndQuit(void);
extern void OSSetCurrentHeap(s32 heap);

static inline void setClear(GXColor color)
{
    HSD_VIData.current.vi.clear_clr = color;
}

static void mainLoop(void)
{
    void *arc;

    setClear((GXColor){ 0, 0, 0, 0 });
    OSReport("game loop start ================================\n================================\n===========================\n=====================================\n");
    if ((arc = LoadArc2("debug/c_.dat")) != 0)
        PurgeArc2(arc);
    debugFileUnPurgeList();
    TeaBgm(-1);
    ascPrologue();
    dspFilter = LoadArc2("filter/filter.dat");
    jobjFilter[0] = CopyJoint2(dspFilter, 0);
    jobjFilter[1] = CopyJoint2(dspFilter, 0);
    jobjFilter[2] = CopyJoint2(dspFilter, 0);
    ZoidPrologue();
    GameZoidInit();
    sCamNN = 1;
    sCamNN2 = 2;
    sWeaponPrologue();
    zDispCursorPrologue();
    sZoidHG = 1;
    HSD_SetZSortMode(0, 0);
    HSD_StateInvalidate(-1);
    sZoidHG = 1;
    lastGame = 0;
    OSReport("GameMode.gametime=%d\n", GameMode.gametime);
    debugFileUnPurgeList();
    if (fogG != 0)
        HSD_FogSet(0);
    ttlMain();
    debugFileUnPurgeList();
    TeaBgm(-1);
    debugFileUnPurgeList();
    HSD_VISetBlack(0);
    OSReport("type=%d , stg=%d \n", GameMode.game_type, GameMode.map);
    if (GameMode.game_type == GAME_TYPE_BATTLE)
        loadMapInfo();
    GameMode.bp_earned = 0;
    HSD_SetZSortMode(1, 1);
    zDispCursorEpilogue();
    TeaBgm(-1);
    HSD_StateInvalidate(-1);
    sZoidHG = 0;
    if (GameMode.game_type == GAME_TYPE_MISSION) {
        if (GameMode.map == 100)
            lastGame = 1;
        OSReport("epilogue?---------------\n");
    }
    OSReport("GameStartMain\n");
    if ((arc = LoadArc2("debug/c_.dat")) != 0)
        PurgeArc2(arc);
    debugFileUnPurgeList();
    VIWaitForRetrace();
    VIWaitForRetrace();
    VIWaitForRetrace();
    if (lastGame != 0) {
        Epilogue();
        OSReport("the end of the mission \n");
    } else {
        gameBgm(GameMode.game_type, GameMode.map);
        game0();
    }
    if (GameMode.game_type == GAME_TYPE_BATTLE && GameMode.map == 11 && winF == GAME_RESULT_WIN) {
        Epilogue();
        GameMode.win = 2;
    }
    waitV(3);
    GameMode.field_2C = 0;
    TeaBgm(-1);
    waitV(3);
    sWeaponEpilogue();
    ZoidEpilogue();
    jobjUnrefAll(jobjFilter[2]);
    jobjFilter[2] = 0;
    jobjUnrefAll(jobjFilter[1]);
    jobjFilter[1] = 0;
    jobjUnrefAll(jobjFilter[0]);
    jobjFilter[0] = 0;
    PurgeArc2(dspFilter);
    dspFilter = 0;
    ascEpilogue();
    HSD_VISetBlack(0);
    sReadPre();
    chkVS();
    HSD_AudioStreamStop(0);
    OSReport("stream off \n");
    sReadPre();
    TeaBgm(-1);
    OSReport("audio off \n");
    sReadPre();
    HSD_AudioSFXKeyOffAll();
    OSReport("key off\n");
    waitV(3);
}

/* unreferenced, keeps the unit's .rodata layout */
#pragma force_active on
static const char sTestSeparator[70] = "-------------------------------------test---------------------------\n";
#pragma force_active off

#pragma dont_inline on
static void init_alloc(s32 heaps)
{
    void *lo = OSGetArenaLo();
    void *hi = OSGetArenaHi();
    lo = OSInitAlloc(lo, hi, heaps);
    OSSetArenaLo(lo);
}

void main(void)
{
    static HSD_PadQueue queue[10];
    u8 unused[24];
    GXRenderModeObj rmode;
    OSCalendarTime td;
    s32 major;
    s32 minor;
    s32 build;
    s32 rev;
    s32 again;

    init_alloc(2);
    memcpy(&rmode, &GXNtsc480IntDf, sizeof(GXRenderModeObj));
    HSD_SetInitParameter(HSD_INIT_XFB_MAX_NUM, 2);
    HSD_SetInitParameter(HSD_INIT_RENDER_MODE_OBJ, &rmode);
    HSD_Init();
    sFileInit();
    if (OSGetPhysicalMemSize() == 0x3000000) {
        OSReport("dev mem alloc \n");
        mallocF(0x1800000);
    }
    HSD_GetVersion(&major, &minor, &build, &rev);
    OSReport("ver %d %d %d %d \n", major, minor, build, rev);
    OSTicksToCalendarTime(OSGetTime(), &td);
    OSReport("NowTime %d/%d/%d %02d:%02d:%02d \n", td.year, td.mon, td.mday, td.hour, td.min, td.sec);
    debug11();
    HSD_PadInit(10, queue, 0, 0);
    sPadInit();
    VIWaitForRetrace();
    sPadAll();
    VIWaitForRetrace();
    sPadAll();
    HSD_VISetBlack(0);
    VIWaitForRetrace();
    sPadAll();
    VIWaitForRetrace();
    sPadAll();
    sFontInit();
    OSReport("--------------test-----------ok--------\n");
    dspLoad = LoadArc2("menu/loading/loading.dat");
    OSReport("load ok=================\n");
    sReadPre();
    TEA_SoundInit();
    sReadPre();
    TEA_SoundDefLoad();
    configGet();
    sReadPre();
    TEA_defstatusload();
    if (OSGetResetCode() == 0x8800)
        GameMode.field_2C = 2;
    OSReport("resetcode=%X \n", OSGetResetCode());
    TEA_mcInit();
    TEA_USBInit();
    if (OSGetSoundMode() == 0) {
        OSReport("mono !!--------------------------\n");
        sndOutputMode(0);
    }
    again = 0;
    while (1) {
        if (again != 0) {
            sFontInit();
            dspLoad = LoadArc2("menu/loading/loading.dat");
            TEA_SoundDefLoad();
        }
        sCameraInit();
        menu_saveloadiconp = LoadArc2("menu/saveload/mc/icon.dat");
        OSReport("icon ok\n");
        menu_yesnop = LoadArc2("menu/caution/caution.dat");
        dspLoadF = 0;
        do {
            HSD_ObjDumpStat();
            initPtcl();
            readPtcl("ptcl/Zoid_eff");
            mainLoop();
            waitV(3);
            forgetPtcl();
            OSReport("forget partcle \n");
            HSD_AudioSFXKeyOffAll();
            TeaBgm(-1);
            waitV(3);
            TEA_AudioSeqStop();
            TEA_AudioSeqFree();
        } while (GameMode.game_type != GAME_TYPE_BATTLE || GameMode.win != 0);
        OSReport("IPL put pri \n ");
        HSD_VISetBlack(1);
        HSD_StartRender(HSD_RP_SCREEN);
        HSD_EndRender();
        HSD_VICopyXFB(HSD_RP_SCREEN);
        HSD_VISetXFBDrawDone();
        waitV(3);
        OSResetSystem(OS_RESET_RESTART, 0x8800, 0);
        PurgeArc2(menu_yesnop);
        PurgeArc2(menu_saveloadiconp);
        sCameraUn();
        OSReport("bye cam \n");
        TeaBgm(-1);
        OSReport("bgm -1 \n");
        TEA_SoundSfxPop();
        OSReport("bgm pop\n");
        PurgeArc2(dspLoad);
        sFontUn();
        HSD_AudioSFXKeyOffAll();
        TeaBgm(-1);
        waitV(10);
        OSReport("a");
        TEA_AudioSeqStop();
        OSReport("b");
        TEA_AudioSeqFree();
        OSReport("c");
        OSReport("d");
        OSReport("e");
        OSReport("f");
        OSReport("a");
        waitV(10);
        sndQuit();
        debugFileUnPurgeList();
        HSD_ClearHeap();
        again = 1;
        OSSetCurrentHeap(HSD_GetHeap());
        OSReport("----- clearheap !!!! --------------------\n");
    }
}
