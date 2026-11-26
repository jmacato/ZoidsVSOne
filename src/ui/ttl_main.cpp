extern "C" {
#include "model_archive.h"
#include "game_save.h"
#include "matrix.h"
#include "game_camera.h"
#include "lobj.h"
#include "zoid.h"
#include "game_zoid_data.h"
#include "game_part_data.h"
#include "game_mode.h"
#include "game_pad.h"
#include "missile.h"
#include "video.h"
#include "menu_message.h"
#include "map_info.h"
#include "game_text.h"
#include "ttl_main_bss.h"

extern s16 menuwepdispnum;
extern u8 menuZoidBattleModeSingleTeam;
extern s32 menuanmend;
extern void sSetAnim1(ModelArchive *archive, s32 model, HSD_JObj *joint, s32 animation);
extern s16 menumode;
extern s8 menucuranm;
extern void HSD_JObjDisp(HSD_JObj *joint, Mtx mtx, u32 flags, u32 rendermode);
extern s32 jobjAnim(HSD_JObj *joint);
extern void menu_sDispBattleEntryPersonListDisp(s16 person, s16 slot);
extern void menu_sDispBattleEntryZoidListDisp(s16 zoid, s16 slot);
extern s8 menuZoidBattleStage;
extern void jobjDispAll(HSD_JObj *joint);
extern void menu_sDispBattleEntryZoidStatusKind(s32 group, s32 kind, s32 value);
extern HSD_JObj *GetChild(HSD_JObj *joint, s32 first, s32 second, s32 third, s32 fourth, s32 fifth);
extern void jobjCopyPos(HSD_JObj *source, HSD_JObj *target);
extern void HSD_JObjDispAll(HSD_JObj *joint, s32 mtx, u32 flags, s32 rendermode);

extern char menudispyesnostr1[180];
extern char menudispyesnostr2[180];
extern SaveLoadWindow menudispslwindow[3];
extern s32 menudispwinstr[45];
extern s16 menutitleguide[8];
extern TitleAnim menutitleanm[20];
extern s16 menuSLPos[5];
extern s32 menu_SlotDataOn[5];
extern s32 menusaveloadSlotButtonanm[3];
extern s16 menusaveloadfilename[15];
extern s32 menusaveloadcommentname[17];
extern u8 menufarmanm[20];
extern u8 menumodeanm[20];
extern u8 menufarmanmold[20];
extern ButtonAnim menubackanm[20];
extern s16 menufarmst[20];
extern s16 menufarmmh[20];
extern s16 menufarmsl[20];
extern s16 menufarmcl[20];
extern s16 menufarmmn[20];
extern s16 menusetst[20];
extern s16 menusetsl[20];
extern s16 menusetmh[20];
extern ButtonAnim menusetbtanm[12];
extern s16 menusetcl[20];
extern s16 menusetmn[20];

extern s16 ttl_GetMountNo(s16 zoid, s16 slot);
extern void ZoidWeaponPurge(ZoidState *zoid);
extern void sWeaponMount(s32 slot, ZoidState *zoid, s32 weapon, s32 mode);
extern ModelArchive *menu_back1p, *menu1p;
extern void ZoidPurge(ZoidState *zoid);
extern HSD_LObj *ttlLight;
extern CameraState *menucam;
extern HSD_LightDesc infinite_light;
extern void TEA_THP_Play(char *filename, s32 loop);
extern void VIWaitForRetrace(void);
extern void sPadAll(void);
extern void sPadInit(void);
extern void ttlMenuPurgeParts(void);
extern void ttlMenuPurgeBack(void);
typedef struct SaveFileTable {
    s16 value[10];
} SaveFileTable;

extern s16 MemCardKeepBlock;
extern s32 ZoidFileBroken;
extern s32 TEA_mcFileMountExist(s32 channel, char *name);
extern s32 VolSe, VolBgm, VolVoice, rumble, VsTime, VsMode;
extern void menu_sDispStart(void);
extern s32 jobjAnim1(HSD_JObj *joint);
extern s32 sprintf(char *buffer, const char *format, ...);
extern void menu_sDispBattleSetLButtonEtc(void);
extern void menu_sDispBattleSetZoidStatusKind(s32 index, s32 value);
extern s32 ZoidInitC(ZoidState *zoid, s32 type, s32 color);
extern s32 menudemoend;
extern s16 menudemop, menudemoC, menudemomsg, menudemobg, menudemobgm, menudemovno;
extern s16 menudemokeywait, menudemojmp, menudemocur, menudemoselect;
extern s16 menudemocha[6];
extern s16 menudemofase[2];
extern s16 menudemoselmsg[2];
extern s16 menudemoseljmp[2];
extern s32 MenuDemoSkipFlag;
extern void TeaBgm(s32 track);
extern void TEA_AudioSeqVol(s32 a, s32 b);
extern void menu_MissionDemoLoadScrFile(s16 stage);
extern s32 menu_MissionDemoScrPlay1(void);
extern void SeRetDemo(void);
extern void menu_sDispMissionDemo(void);
extern s32 menudemoanmend[2];
extern s32 menudemocharain;
extern s32 vsyncN;
extern void HSD_StartRender(s32 pass), HSD_EndRender(void);
extern s32 HSD_CObjSetCurrent(struct HSD_CObj *);
extern void HSD_CObjEndCurrent(void);
extern void GXSetCullMode(s32);
extern void debugmenudraw(void);
extern void menu_sDispMissionDemoBack(void);
extern void menu_sDispMissionDemoPerson(s16 side);
extern void menu_sDispMissionDemoMsgArea(void);
extern void menu_sDispMissionDemoMsgCursor(void);
extern void menu_sDispMissionDemoSelectMenu(void);
extern PadState *sPad1, *sPad2;
extern void SeSelectB(void);
extern s32 menu_SlotOn;
extern s32 MemCardStatus[2];
extern s32 menudispyesnoflag;
extern void configClear(void);
extern void ttlMenuLoadYesNo(void);
extern void clrYesNoMsg(void);
extern s32 TeaMemCardChk(void);
extern s32 TEA_mcChkSlot(s32 channel);
extern s32 TEA_mcChkSector(s32 channel);
extern s32 TEA_mcMsgYesNo(s32 channel, s32 message);
extern s32 TEA_mcMsgYesNoNotChkSlot(s32 channel, s32 message);
extern s32 TEA_mcUnMount(s32 channel);
extern s32 TEA_mcMountNoChk(s32 channel);
extern s32 TEA_mcBadEncFormatEnc(s32 channel);
extern s32 TEA_mcChkIoErr(s32 channel);
extern s32 TEA_mcChkBroken(s32 channel);
extern s32 ttlMenuSaveLoadexistenceDataStartNew0(void);
extern s32 ttlMenuSaveLoadexistenceData0(s32 mode);
extern s32 MemCardFreeSize;
extern s32 MemCardFreeDir;
extern s32 CARDFreeBlocks(s32 channel, s32 *bytes, s32 *files);
extern s16 menusaveloadslot;
extern s32 flag_saveok;
extern void ttlMenuSaveDataSetFileName(s32 slot, s32 mode);
extern void TEA_mcMsgDisp(s32 channel, s32 message);
extern void TEA_mcMsgNoChkSlot(s32 channel, s32 message);
extern s32 TEA_mcSaveFile0(s32 slot, s32 number, s32 record);
extern char *strcpy(char *dst, const char *src);
extern s32 TEA_mcLoadFile0(s32 slot, s32 number, s32 record);
extern void menu_MissionDemo(void);
extern void configSet(void);
extern void menu_sDispSetButton(void);
extern void menu_sDispBattleFarm(void);
extern void menu_sDispBattleEntry(void);
extern void menu_sDispMisFarm(void);
extern void menu_sDispVsFarm(void);
extern void menu_sDispVsEntry(void);
extern void *sReadFileU(char *name, s32 mode);
extern void *memcpy(void *destination, const void *source, u32 size);
extern void free(void *memory);
extern char *rdMapInfo(s32 mode, s32 number);




#pragma readonly_strings on
void ttlMenuLoadParts(s32 mode)
{
    ttlMenuPurgeParts();
    switch (mode) {
    case 0:
        break;
    case 4:
        menu1p = LoadArc2("menu/battle_menu/farm/farm.dat");
        break;
    case 5:
        menu1p = LoadArc2("menu/battle_menu/battle_entry.dat");
        break;
    case 6:
        menu1p = LoadArc2("menu/title/title.dat");
        break;
    case 7:
        menu1p = LoadArc2("menu/vs_menu/vs_menu.dat");
        break;
    default:
        break;
    }
}

void ttlMenuLoadBack(s32 mode)
{
    ttlMenuPurgeBack();
    switch (mode) {
    case 0:
        break;
    case 3:
        menu_back1p = LoadArc2("menu/vs_menu/bglogo.dat");
        break;
    case 4:
        menu_back1p = LoadArc2("menu/garage/ngarage.dat");
        break;
    case 5:
        menu_back1p = LoadArc2("menu/garage00.dat");
        break;
    case 6:
        if (GameMode.country == 0)
            menu_back1p = LoadArc2("menu/garage/ngarage.dat");
        if (GameMode.country == 1)
            menu_back1p = LoadArc2("menu/garage/kgarage.dat");
        if (GameMode.country == 2)
            menu_back1p = LoadArc2("menu/garage/tgarage.dat");
        break;
    default:
        break;
    }
}
#pragma readonly_strings off

void ttlMenuAllPurge(void)
{
    s32 frame_padding[2];
    s16 i;

    ZoidPurge(&Zoid[1]);
    ZoidPurge(&Zoid[0]);
    for (i = 0; i < 100; i++) {
        if (menu_zoidp[i] != 0) {
            PurgeArc2(menu_zoidp[i]);
            menu_zoidp[i] = 0;
        }
    }
    for (i = 0; i < 58; i++) {
        if (menu_personp[i] != 0) {
            PurgeArc2(menu_personp[i]);
            menu_personp[i] = 0;
        }
    }
    if (menu_back1p != 0) {
        PurgeArc2(menu_back1p);
        menu_back1p = 0;
    }
    if (menu1p != 0) {
        PurgeArc2(menu1p);
        menu1p = 0;
    }
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
}

void ttlMenuAllPurgeMission(void)
{
    s32 frame_padding[2];
    s16 i;

    ZoidPurge(&Zoid[1]);
    ZoidPurge(&Zoid[0]);
    for (i = 0; i < 100; i++) {
        if (menu_zoidp[i] != 0) {
            PurgeArc2(menu_zoidp[i]);
            menu_zoidp[i] = 0;
        }
    }
    for (i = 0; i < 58; i++) {
        if (menu_personp[i] != 0) {
            PurgeArc2(menu_personp[i]);
            menu_personp[i] = 0;
        }
    }
    if (menu_back1p != 0) {
        PurgeArc2(menu_back1p);
        menu_back1p = 0;
    }
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
    HSD_VIWaitXFBFlush();
}

void ttl_WeaponAllUnMount(s16 slot)
{
    s16 i;
    s32 frame_padding[2];

    (void)Tea_partsdat;
    (void)Tea_bulletdat;
    (void)Tea_persondat;
    (void)Tea_effectdat;
    (void)TXT_Menu_dat;
    (void)menudemo;
    (void)menuZoidMountPointDsip;
    (void)menuwepdispmount;
    (void)menudispyesnostr1;
    (void)menudispyesnostr2;
    (void)menudispslwindow;
    (void)menudispwinstr;
    (void)menutitleguide;
    (void)menutitleanm;
    (void)menuSLPos;
    (void)menu_SlotDataOn;
    (void)menusaveloadSlotButtonanm;
    (void)menusaveloadfilename;
    (void)menusaveloadcommentname;
    (void)menufarmanm;
    (void)menumodeanm;
    (void)menufarmanmold;
    (void)menubackanm;
    (void)menufarmst;
    (void)menufarmmh;
    (void)menufarmsl;
    (void)menufarmcl;
    (void)menufarmmn;
    (void)menusetst;
    (void)menusetsl;
    (void)menusetmh;
    (void)menusetbtanm;
    (void)menusetcl;
    (void)menusetmn;
    for (i = 0; i < 10; i++) {
        if (IveSave[0].zoid_weapons[slot][i] != -1)
            ttl_GetMountNo(IveSave[0].owned_zoids[slot], i);
    }
    ZoidWeaponPurge(&Zoid[0]);
    for (i = 0; i < 28; i++)
        menuwepdispmount[i] = -1;
    menuwepdispnum = 0;
}

void ttlMovie(char *path)
{
    s32 i;

    if (ttlLight != 0)
        HSD_LObjRemoveAll(ttlLight);
    ttlLight = 0;
    TEA_THP_Play(path, 0);
    PSMTXTrans(dspMtx, 0.0f, 0.0f, 0.0f);
    menucam = &sCamera[0];
    sCameraSetNormal(menucam);
    ttlLight = HSD_LObjLoadDesc(&infinite_light);
    menucam->lights = ttlLight;
    HSD_VISetBlack(0);
    for (i = 0; i < 10; i++) {
        sPadAll();
        VIWaitForRetrace();
        HSD_VICopyXFB(HSD_RP_SCREEN);
        HSD_VISetXFBDrawDone();
    }
    sPadAll();
    sPadInit();
}

void menuPartsShopListZoid(s16 category, s16 zoid)
{
    s16 found;
    s16 i;
    s16 j;

    found = 0;
    for (i = 0; i < 450; i++) {
        IveSave[0].list_flag[i] = -1;
        IveSave[0].list_parts[i] = -1;
    }
    IveSave[0].list_count = 0;
    for (i = 0; i < 450; i++) {
        if (IveSave[0].shop_flags[i] != 0 && Tea_partsdat[i].category == category && Tea_partsdat[i].field_50 != 0) {
            if (Tea_partsdat[i].zoids[0] == -1) {
                found = 1;
            } else {
                for (j = 0; j < 12; j++) {
                    if (zoid == Tea_partsdat[i].zoids[j]) {
                        found = 1;
                        break;
                    }
                }
            }
            if (found != 0) {
                found = 0;
                IveSave[0].list_parts[IveSave[0].list_count] = i;
                IveSave[0].list_flag[IveSave[0].list_count] = i;
                IveSave[0].list_count++;
            }
        }
    }
}

void menuPartsHaveListZoid(s16 category, s16 zoid)
{
    s16 found;
    s16 part;
    s16 i;
    s16 j;

    found = 0;
    for (i = 0; i < 450; i++) {
        IveSave[0].list_flag[i] = -1;
        IveSave[0].list_parts[i] = -1;
    }
    IveSave[0].list_count = 0;
    for (i = 0; i < 450; i++) {
        part = IveSave[0].owned_parts[i];
        if (part > 0) {
            if (category == Tea_partsdat[part].category) {
                if (zoid == -1)
                    found = 1;
                if (Tea_partsdat[part].zoids[0] == -1) {
                    found = 1;
                } else {
                    for (j = 0; j < 12; j++) {
                        if (zoid == Tea_partsdat[part].zoids[j]) {
                            found = 1;
                            break;
                        }
                    }
                }
                if (found != 0) {
                    found = 0;
                    IveSave[0].list_parts[IveSave[0].list_count] = part;
                    IveSave[0].list_flag[IveSave[0].list_count] = i;
                    IveSave[0].list_count++;
                }
            }
        }
    }
}

void menuZoidPartsCopy(s16 srcSave, s16 srcSlot, s16 dstSave, s16 dstSlot)
{
    s16 i;

    IveSave[dstSave].zoid_colors[dstSlot] = IveSave[srcSave].zoid_colors[srcSlot];
    IveSave[dstSave].owned_zoids[dstSlot] = IveSave[srcSave].owned_zoids[srcSlot];
    for (i = 0; i < 28; i++)
        IveSave[dstSave].zoid_weapons[dstSlot][i] = IveSave[srcSave].zoid_weapons[srcSlot][i];
    for (i = 0; i < 3; i++)
        IveSave[dstSave].contract_subparts[dstSlot][i] = IveSave[srcSave].contract_subparts[srcSlot][i];
    IveSave[dstSave].contract_options[dstSlot] = IveSave[srcSave].contract_options[srcSlot];
}

void menu_sDispSaveLoadMenuSet(s16 select)
{
    s32 index;
    s16 i;
    s16 normal;
    s16 active;

    active = 0;
    switch (select) {
    case -1:
        normal = 0;
        break;
    case -2:
        menudispslwindow[0].anim = 6;
        menudispslwindow[0].active = 1;
        menudispslwindow[1].anim = 6;
        menudispslwindow[1].active = 1;
        menudispslwindow[2].anim = 6;
        menudispslwindow[2].active = 1;
        return;
    case -3:
        menudispslwindow[0].anim = 1;
        menudispslwindow[0].active = 1;
        menudispslwindow[1].anim = 1;
        menudispslwindow[1].active = 1;
        menudispslwindow[2].anim = 1;
        menudispslwindow[2].active = 1;
        return;
    default:
        normal = 2;
        active = 3;
        break;
    }
    index = select % 3;
    for (i = 0; i < 3; i++) {
        if (index == i && select >= 0) {
            menudispslwindow[i].anim = active;
            menudispslwindow[i].active = 1;
        } else {
            menudispslwindow[i].anim = normal;
            menudispslwindow[i].active = 1;
        }
    }
}

void menu_sDispBattleEntryPersonPartnerZoidPic(void)
{
    HSD_JObj *source;
    HSD_JObj *target;
    s16 person;
    s32 frame_padding[6];

    person = IveSave[0].selected_person;
    if (person != -1) {
        source = GetChild(menu1p->models[6], 0, 0, 1, -1, -1);
        target = GetChild(menu_personp[person]->models[0], 0, 0, -1, -1, -1);
        jobjCopyPos(source, target);
        HSD_JObjDispAll(target, 0, 7, 0);
    }
    source = GetChild(menu1p->models[6], 0, 0, 2, -1, -1);
    target = GetChild(menu_zoidp[IveSave[0].selected_zoid]->models[0], 0, 0, -1, -1, -1);
    if (target != 0) {
        jobjCopyPos(source, target);
        HSD_JObjDispAll(target, 0, 7, 0);
    }
    if (menuZoidBattleModeSingleTeam == 1) {
        person = IveSave[0].partner_person;
        if (person != -1) {
            source = GetChild(menu1p->models[6], 0, 1, 1, -1, -1);
            target = GetChild(menu_personp[person]->models[0], 0, 0, -1, -1, -1);
            jobjCopyPos(source, target);
            HSD_JObjDispAll(target, 0, 7, 0);
        }
        source = GetChild(menu1p->models[6], 0, 1, 2, -1, -1);
        target = GetChild(menu_zoidp[IveSave[0].partner_zoid]->models[0], 0, 0, -1, -1, -1);
        if (target != 0) {
            jobjCopyPos(source, target);
            HSD_JObjDispAll(target, 0, 7, 0);
        }
    }
}

void menu_sDispBattleEntryPersonZoidStatus(void)
{
    s32 idx = 6;
    s16 zoid;
    s32 frame_padding[4];

    jobjDispAll(GetChild(menu1p->models[idx], 0, 0, 0, -1, -1));
    if (menuZoidBattleStage == -1 || menuZoidBattleModeSingleTeam == 1)
        jobjDispAll(GetChild(menu1p->models[idx], 0, 1, 0, -1, -1));
    putAscJobj(GetChild(menu1p->models[idx], 0, 0, 0, 0, -1), 1, Tea_persondat[IveSave[0].selected_person].name);
    if (menuZoidBattleModeSingleTeam == 1)
        putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), 1, Tea_persondat[IveSave[0].partner_person].name);
    zoid = IveSave[0].selected_zoid;
    if (zoid != -1)
        putAscJobj(GetChild(menu1p->models[idx], 0, 0, 0, 1, -1), 1, Tea_zoiddat[zoid].name);
    if (menuZoidBattleModeSingleTeam == 1) {
        zoid = IveSave[0].partner_zoid;
        if (zoid != -1)
            putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 1, -1), 1, Tea_zoiddat[zoid].name);
    }
    if (IveSave[0].selected_zoid >= 0) {
        menu_sDispBattleEntryZoidStatusKind(0, 0, Tea_zoiddat[IveSave[0].selected_zoid].health);
        menu_sDispBattleEntryZoidStatusKind(0, 1, Tea_zoiddat[IveSave[0].selected_zoid].armor);
        menu_sDispBattleEntryZoidStatusKind(0, 2, Tea_zoiddat[IveSave[0].selected_zoid].field_0056);
    }
    if (menuZoidBattleModeSingleTeam == 1 && IveSave[0].partner_zoid != -1) {
        menu_sDispBattleEntryZoidStatusKind(1, 0, Tea_zoiddat[IveSave[0].partner_zoid].health);
        menu_sDispBattleEntryZoidStatusKind(1, 1, Tea_zoiddat[IveSave[0].partner_zoid].armor);
        menu_sDispBattleEntryZoidStatusKind(1, 2, Tea_zoiddat[IveSave[0].partner_zoid].field_0056);
    }
}

void menu_sDispBattleEntryPilotZoidList(void)
{
    s32 idx = 6;
    HSD_JObj *target;
    HSD_JObj *source;
    s16 i;
    s32 frame_padding[2];

    if (menumode < 5)
        return;
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, -1, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 0, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 1, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 2, -1, -1), 0, 7, 0);
    if (menumode == 5 || menumode == 6) {
        menu_sDispBattleEntryPersonListDisp(IveSave[0].selected_person, 0);
        if (menuZoidBattleModeSingleTeam == 1)
            menu_sDispBattleEntryPersonListDisp(IveSave[0].partner_person, 1);
    }
    if (menumode == 7 || menumode == 8) {
        for (i = 0; i < menufarmmh[menumode]; i++)
            menu_sDispBattleEntryZoidListDisp(IveSave[0].owned_zoids[i + menufarmst[menumode]], i);
    }
    if (menucuranm == 1) {
        SetAnimArc2(menu1p, 7, 0);
        menucuranm = 2;
    }
    if (menucuranm == 2) {
        if (jobjAnim(menu1p->models[7]) != 0)
            menucuranm = 3;
    } else if (menucuranm == 3) {
        SetAnimArc2(menu1p, 7, 0);
        jobjAnim(menu1p->models[7]);
        menucuranm = 2;
    }
    source = GetChild(menu1p->models[6], 0, 2, 4, menufarmsl[menumode], -1);
    target = GetChild(menu1p->models[7], 0, 1, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDisp(target, 0, 7, 0);
}

void menu_BattleSet_EntryPersonPartnerExit(void)
{
    s16 i;

    if (menumode == 2) {
        for (i = 0; i < 3; i++) {
            if (i == menufarmcl[2])
                menufarmanm[i] = 4;
            else
                menufarmanm[i] = 1;
        }
        if (menuZoidBattleStage == -1)
            return;
        if (menuZoidBattleModeSingleTeam != 0)
            return;
        menufarmanm[1] = 7;
    } else if (menumode == 3) {
        menufarmanm[0] = 5;
        menufarmanm[1] = 3;
        if (menuZoidBattleStage == -1)
            return;
        if (menuZoidBattleModeSingleTeam != 0)
            return;
        menufarmanm[1] = 7;
    } else if (menumode == 4) {
        menufarmanm[1] = 5;
        menufarmanm[0] = 3;
    } else if (menumode == 0) {
        menufarmanm[1] = 7;
        menufarmanm[0] = 7;
        menufarmanm[2] = 7;
    } else {
        menufarmanm[2] = 7;
    }
}

void menu_sDispMissionDemo(void)
{
    s32 frame_padding[6];

    HSD_StartRender(0);
    if (HSD_CObjSetCurrent(menudemo[0]->camera) != 0) {
        HSD_LObjSetCurrentAll(menudemo[0]->lights);
        HSD_LObjSetupInit(menudemo[0]->camera);
        GXSetCullMode(0);
        if (menudemoend == 1) {
            menu_sDispMissionDemoBack();
            menu_sDispMissionDemoPerson(1);
            menu_sDispMissionDemoPerson(0);
            if (menudemoanmend[0] == 1 && menudemoanmend[1] == 1)
                menudemocharain = 1;
            menu_sDispMissionDemoMsgArea();
            menu_sDispMissionDemoMsgCursor();
            menu_sDispMissionDemoSelectMenu();
        }
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}

void ttlMenuLoadZoid(void)
{
    s16 i;

    for (i = 1; i < 16; i++)
        GameZoid[i].type = -1;
    GameZoid[0].type = IveSave[0].selected_zoid;
    GameZoid[1].type = IveSave[0].partner_zoid;
    GameZoid[0].person = IveSave[0].selected_person;
    GameZoid[1].person = IveSave[0].partner_person;
    GameZoid[0].color = IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot];
    if (IveSave[0].partner_zoid_slot != -1)
        GameZoid[1].color = IveSave[0].zoid_colors[IveSave[0].partner_zoid_slot];
    ZoidInitC(&Zoid[0], GameZoid[0].type, GameZoid[0].color);
    if (GameMode.game_type == GAME_TYPE_VS)
        ZoidInitC(&Zoid[1], GameZoid[1].type, GameZoid[1].color);
}

void menu_sDispBattleSetZoidStatus(void)
{
    char text[64];
    s32 idx = 9;
    HSD_JObj *joint;

    if (menumode == 0)
        return;
    menu_sDispBattleSetLButtonEtc();
    joint = GetChild(menu1p->models[idx], 0, 6, 0, -1, -1);
    sprintf(text, "%s", Tea_zoiddat[IveSave[0].selected_zoid].name);
    putAscJobj(joint, 1, text);
    menu_sDispBattleSetZoidStatusKind(0, Tea_zoiddat[IveSave[0].selected_zoid].health);
    menu_sDispBattleSetZoidStatusKind(1, Tea_zoiddat[IveSave[0].selected_zoid].armor);
    menu_sDispBattleSetZoidStatusKind(2, Tea_zoiddat[IveSave[0].selected_zoid].field_0056);
}

void menu_sDispBattleSetLButtonReset(void)
{
    s32 idx = 9;
    s32 n = 4;
    HSD_JObj *button;
    s32 frame_padding[2];

    button = GetChild(menu1p->models[idx], 0, n, -1, -1, -1);
    if (menusetbtanm[n].cur != menusetbtanm[n].old) {
        menusetbtanm[n].state = 1;
        menusetbtanm[n].old = menusetbtanm[n].cur;
    }
    if (menusetbtanm[n].state == 1) {
        menusetbtanm[n].state = 2;
        sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, n, -1, -1, -1), menusetbtanm[n].cur);
    }
    if (menusetbtanm[n].state == 2) {
        if (jobjAnim1(GetChild(menu1p->models[idx], 0, n, -1, -1, -1)) != 0) {
            menusetbtanm[n].state = 3;
            menuanmend = 1;
            if (menusetbtanm[n].cur == 5)
                return;
            if (menusetbtanm[n].cur == 0) {
                if (menusetbtanm[n].cur == 0)
                    menusetbtanm[n].cur = 1;
                sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, n, -1, -1, -1), menusetbtanm[n].cur);
                jobjAnim1(GetChild(menu1p->models[idx], 0, n, -1, -1, -1));
            } else {
                menusetbtanm[n].state = 1;
            }
        }
    }
    HSD_JObjDispAll(button, 0, 7, 0);
}

void menu_sDispBattleSetLButtonExit(void)
{
    s32 idx = 9;
    s32 n = 5;
    HSD_JObj *button;
    s32 frame_padding[2];

    button = GetChild(menu1p->models[idx], 0, n, -1, -1, -1);
    if (menusetbtanm[n].cur != menusetbtanm[n].old) {
        menusetbtanm[n].state = 1;
        menusetbtanm[n].old = menusetbtanm[n].cur;
    }
    if (menusetbtanm[n].state == 1) {
        menusetbtanm[n].state = 2;
        sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, n, -1, -1, -1), menusetbtanm[n].cur);
    }
    if (menusetbtanm[n].state == 2) {
        if (jobjAnim1(GetChild(menu1p->models[idx], 0, n, -1, -1, -1)) != 0) {
            menusetbtanm[n].state = 3;
            menuanmend = 1;
            if (menusetbtanm[n].cur == 5)
                return;
            if (menusetbtanm[n].cur == 0) {
                if (menusetbtanm[n].cur == 0)
                    menusetbtanm[n].cur = 1;
                sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, n, -1, -1, -1), menusetbtanm[n].cur);
                jobjAnim1(GetChild(menu1p->models[idx], 0, n, -1, -1, -1));
            } else {
                menusetbtanm[n].state = 1;
            }
        }
    }
    HSD_JObjDispAll(button, 0, 7, 0);
}

void menu_TITLE_disp(s32 state)
{
    menuanmend = 0;
    menutitleanm[0].mode = 1;
    menutitleanm[1].mode = 1;
    menutitleanm[2].mode = 1;
    menutitleanm[3].mode = 1;
    menutitleanm[4].mode = 1;
    menutitleanm[5].mode = 1;
    menutitleanm[6].mode = 1;
    if (state == 1) {
        menutitleanm[0].state = 0;
        menutitleanm[1].state = 0;
        menutitleanm[2].state = 0;
        menutitleanm[3].state = 0;
        menutitleanm[4].state = 0;
        menutitleanm[5].state = 0;
        menutitleanm[6].state = 0;
    } else {
        menutitleanm[0].state = 2;
        menutitleanm[1].state = 2;
        menutitleanm[2].state = 2;
        menutitleanm[3].state = 2;
        menutitleanm[4].state = 2;
        menutitleanm[5].state = 2;
        menutitleanm[6].state = 2;
    }
    while (menuanmend == 0) {
        menu_sDispSetButton();
        menu_sDispBattleFarm();
    }
    menuanmend = 0;
}

void menu_TITLE_dispEntry(s32 state)
{
    menuanmend = 0;
    menutitleanm[0].mode = 1;
    menutitleanm[1].mode = 1;
    menutitleanm[2].mode = 1;
    menutitleanm[3].mode = 1;
    menutitleanm[4].mode = 1;
    menutitleanm[5].mode = 1;
    menutitleanm[6].mode = 1;
    if (state == 1) {
        menutitleanm[0].state = 0;
        menutitleanm[1].state = 0;
        menutitleanm[2].state = 0;
        menutitleanm[3].state = 0;
        menutitleanm[4].state = 0;
        menutitleanm[5].state = 0;
        menutitleanm[6].state = 0;
    } else {
        menutitleanm[0].state = 2;
        menutitleanm[1].state = 2;
        menutitleanm[2].state = 2;
        menutitleanm[3].state = 2;
        menutitleanm[4].state = 2;
        menutitleanm[5].state = 2;
        menutitleanm[6].state = 2;
    }
    while (menuanmend == 0) {
        menu_sDispSetButton();
        menu_sDispBattleEntry();
    }
    menuanmend = 0;
}

void menu_TITLE_dispMis(s32 state)
{
    menuanmend = 0;
    menutitleanm[0].mode = 1;
    menutitleanm[1].mode = 1;
    menutitleanm[2].mode = 1;
    menutitleanm[3].mode = 1;
    menutitleanm[4].mode = 1;
    menutitleanm[5].mode = 1;
    menutitleanm[6].mode = 1;
    if (state == 1) {
        menutitleanm[0].state = 0;
        menutitleanm[1].state = 0;
        menutitleanm[2].state = 0;
        menutitleanm[3].state = 0;
        menutitleanm[4].state = 0;
        menutitleanm[5].state = 0;
        menutitleanm[6].state = 0;
    } else {
        menutitleanm[0].state = 2;
        menutitleanm[1].state = 2;
        menutitleanm[2].state = 2;
        menutitleanm[3].state = 2;
        menutitleanm[4].state = 2;
        menutitleanm[5].state = 2;
        menutitleanm[6].state = 2;
    }
    while (menuanmend == 0) {
        menu_sDispSetButton();
        menu_sDispMisFarm();
    }
    menuanmend = 0;
}

void menu_TITLE_dispVs(s32 state)
{
    menuanmend = 0;
    menutitleanm[0].mode = 1;
    menutitleanm[1].mode = 1;
    menutitleanm[2].mode = 1;
    menutitleanm[3].mode = 1;
    menutitleanm[4].mode = 1;
    menutitleanm[5].mode = 1;
    menutitleanm[6].mode = 1;
    if (state == 1) {
        menutitleanm[0].state = 0;
        menutitleanm[1].state = 0;
        menutitleanm[2].state = 0;
        menutitleanm[3].state = 0;
        menutitleanm[4].state = 0;
        menutitleanm[5].state = 0;
        menutitleanm[6].state = 0;
    } else {
        menutitleanm[0].state = 2;
        menutitleanm[1].state = 2;
        menutitleanm[2].state = 2;
        menutitleanm[3].state = 2;
        menutitleanm[4].state = 2;
        menutitleanm[5].state = 2;
        menutitleanm[6].state = 2;
    }
    while (menuanmend == 0) {
        menu_sDispVsFarm();
    }
    menuanmend = 0;
}

void menu_TITLE_dispVsEntry(s32 state)
{
    menuanmend = 0;
    menutitleanm[0].mode = 1;
    menutitleanm[1].mode = 1;
    menutitleanm[2].mode = 1;
    menutitleanm[3].mode = 1;
    menutitleanm[4].mode = 1;
    menutitleanm[5].mode = 1;
    menutitleanm[6].mode = 1;
    if (state == 1) {
        menutitleanm[0].state = 0;
        menutitleanm[1].state = 0;
        menutitleanm[2].state = 0;
        menutitleanm[3].state = 0;
        menutitleanm[4].state = 0;
        menutitleanm[5].state = 0;
        menutitleanm[6].state = 0;
    } else {
        menutitleanm[0].state = 2;
        menutitleanm[1].state = 2;
        menutitleanm[2].state = 2;
        menutitleanm[3].state = 2;
        menutitleanm[4].state = 2;
        menutitleanm[5].state = 2;
        menutitleanm[6].state = 2;
    }
    while (menuanmend == 0) {
        menu_sDispVsEntry();
    }
    menuanmend = 0;
}

void menuHiddenTitle(void)
{
    s16 i;

    menutitleanm[0].state = 2;
    for (i = 1; i < 7; i++) {
        if (menutitleguide[i] != -1)
            menutitleanm[i].state = 2;
    }
}

void MissionLoadInitData(void)
{
    menuZoidBattleModeSingleTeam = 0;
    IveSave[0].single_team = 0;
    IveSave[0].partner_zoid = -1;
    IveSave[0].partner_zoid_slot = -1;
    IveSave[0].partner_person = 57;
}

void menu_BlackInWhite(void)
{
    menutitleanm[1].mode = 1;
    menutitleanm[1].state = 0;
    menutitleanm[1].next = 1;
    do {
        menu_sDispStart();
    } while (menutitleanm[1].state != 2);
}

void menu_BlackInWhiteSet(void)
{
    menutitleanm[1].mode = 1;
    menutitleanm[1].state = 0;
    menutitleanm[1].next = 1;
}

void menu_WhiteOutBlack(void)
{
    menutitleanm[1].mode = 1;
    menutitleanm[1].state = 1;
    menutitleanm[1].next = 0;
    do {
        menu_sDispStart();
    } while (menutitleanm[1].state != 3);
}

#pragma push
#pragma auto_inline off
void configGet(void)
{
    VolSe = IveSaveFlag.vol_se;
    VolBgm = IveSaveFlag.vol_bgm;
    VolVoice = IveSaveFlag.vol_voice;
    rumble = IveSaveFlag.rumble;
    VsTime = IveSaveFlag.vs_time;
    VsMode = IveSaveFlag.vs_mode;
    configSet();
}

void configPut(void)
{
    IveSaveFlag.vol_se = VolSe;
    IveSaveFlag.vol_bgm = VolBgm;
    IveSaveFlag.vol_voice = VolVoice;
    IveSaveFlag.rumble = rumble;
    IveSaveFlag.vs_time = VsTime;
    IveSaveFlag.vs_mode = VsMode;
}

void configClear(void)
{
    IveSaveFlag.vol_se = 8;
    IveSaveFlag.vol_bgm = 8;
    IveSaveFlag.vol_voice = 8;
    IveSaveFlag.rumble = 1;
    IveSaveFlag.vs_time = 3;
    IveSaveFlag.vs_mode = 1;
    configGet();
}
#pragma pop


static const char sSpPictureFormat[24] = "menu/picture/sp%02d.dat";
static const char sSp00PicturePath[22] = "menu/picture/sp00.dat";
static const char sSzPictureFormat[24] = "menu/picture/sz%02d.dat";
static const char sSz00PicturePath[22] = "menu/picture/sz00.dat";
static const char sLogGxCull[9] = "GX_CULL\n";
static const char sLogSetZmode[10] = "SetZmode\n";
static const char sLogCurCamOn[11] = "CurCam On\n";
static const char sLogCurCamOff[12] = "CurCam Off\n";
static const char sLogCurCamEnd[12] = "CurCam End\n";
static const char sLogEndRender[11] = "EndRender\n";
static const char sLogResetCam[27] = "ResetCam.................\n";
static const char sTomyLogoMoviePath[19] = "movie/TomyLogo.THP";
static const char sZoidVsMoviePath[18] = "movie/zoid_vs.thp";
static const char sRebirthMoviePath[20] = "thpdemo/rebirth.thp";
typedef struct YesNoAnim {
    s16 state;
    s16 anim;
} YesNoAnim;

extern YesNoAnim menudispyesnoanm;

/* addresses of sTomyLogoMoviePath, sZoidVsMoviePath, "", "", sRebirthMoviePath, "" */
static const u32 sMoviePaths[6] = { 0x800F0370, 0x800F0384, 0x802A0928, 0x802A0928, 0x800F0398, 0x802A0928 };

typedef struct MovieTable {
    char *path[6];
} MovieTable;

extern s64 gametimestart;
extern void memcopy(void *dst, void *src, u32 size);
extern void EndeFin(void);
extern void debug11(void);
extern s32 menuYesNo(s32 selected, const char *first, const char *second);
extern char *GetMenuMsgAdr(s16 message);
extern void ttlMenuLoadSaveLoad(void);
extern void ttlMenuPurgeSaveLoad(void);
extern void menu_sDispSaveLoad(void);
extern s32 ttlMemCardChkStartNew(void);
extern s32 ttlMenuSystemMemCardSave(void);
extern s32 ttlMenuBatSaveLoad(s32 mode);
extern s32 menudispyesnopoint;
extern BatMapEntry menu_BatMapData[37];
extern s32 sCamNN, sCamNN2;
extern s16 menufncPushStart(void);
extern s32 menufncMainMenu(void);
extern s32 menufncStoryMode01(void);
extern s32 menufncMission_Menu(void);
extern s32 menufncZoidMission_MenuEntry(void);
extern s32 menufncZoidBattle01Human(void);
extern s32 menufncZoidBattle_BattleMenu(void);
extern s32 menufncZoidBattle_BattleMenuEntry(void);
extern s32 menufncZoidBattle_HumanBattleMenuEntry(void);
extern s32 menufncZoidBattleEnd(void);
extern s32 menufncZoidVs01(void);
extern s32 menufncZoidVsMenu(void);
extern s32 menufncZoidVsMenuEntry(void);
extern void menufncZoidBattle02(void);
extern void menufncZoidBattle02Hokyu(void);
extern void ttlMenu_sDispMissionHokyu(void);
extern void ttlMenu_sDispBattleNextYokok(void);
extern void menuZoidVS_NonSaveData_InitData(s16 rec);
extern void ttlMenuOption(void);
extern void testbitsetmenu_zoid(void);
extern void ttlMenuAllPurge(void);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
void ttlMain(void)
{
    MovieTable movies = *(MovieTable *)sMoviePaths;
    s32 ret;
    s8 kind;
    s32 unused[1];

    ret = 0;
    menudispyesnoflag = 0;
    PSMTXTrans(dspMtx, 0.0f, 0.0f, 0.0f);
    if (ttlLight == 0)
        ttlLight = HSD_LObjLoadDesc(&infinite_light);
    HSD_VISetBlack(0);
    OSReport("GameStart01\n");
    if (GameMode.game_type == GAME_TYPE_MISSION) {
        OSReport("mission --");
        if (GameMode.win == 1) {
            OSReport("1 ");
            ret = 107;
            OSReport("GameStartMis 107\n");
        }
        if (GameMode.win == 2) {
            OSReport("Youre Win\n");
            memcopy(&IveSave[0], &IveSave[4], sizeof(GameSaveRecord));
            if (GameMode.map >= 100) {
                OSReport("after epilogue ---");
                GameMode.map = 0;
                kind = IveSave[0].country;
                if ((s32)(u8)kind == 1)
                    IveSaveFlag.system_flags[1] = 1;
                if (kind == 2)
                    IveSaveFlag.system_flags[2] = 1;
                if ((s32)IveSaveFlag.system_flags[1] == 1 && (s32)IveSaveFlag.system_flags[2] == 1)
                    IveSaveFlag.system_flags[3] = 1;
                if ((s32)IveSaveFlag.system_flags[3] == 1 && (s32)IveSaveFlag.system_flags[0] == 1)
                    IveSaveFlag.system_flags[8] = 1;
                ttlMenuLoadSaveLoad();
                menudispyesnoflag = 1;
                menudispyesnopoint = 1;
                do {
                    sPadAll();
                    menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_SAVE_PROMPT), "");
                    menu_sDispSaveLoad();
                } while (sPad1->pressed_a == 0);
                menudispyesnoflag = 0;
                if (menudispyesnopoint == 1) {
                    IveSave[0].field_166B = 0;
                    IveSave[0].stage = 0;
                    IveSave[0].win = 0;
                    GameMode.map = 0;
                    memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                    memcpy(&IveSave[3], &IveSaveFlag, sizeof(GameSaveRecord));
                    if (ttlMemCardChkStartNew() != 0) {
                        TEA_mcMsgNoChkSlot(0, MENU_MSG_SAVE_NOTICE);
                        memcpy(&IveSaveFlag, &IveSave[3], sizeof(GameSaveRecord));
                        ttlMenuSystemMemCardSave();
                        ttlMemCardChkStartNew();
                    } else {
                        memcpy(&IveSaveFlag, &IveSave[3], sizeof(GameSaveRecord));
                    }
                }
                EndeFin();
                OSReport("save end \n");
                ttlMenuPurgeSaveLoad();
                menudispyesnoflag = 0;
                ret = 0;
                GameMode.win = 0;
            } else {
                GameMode.map++;
                ret = 101;
                IveSave[0].field_166E++;
                IveSave[0].stage++;
                menuZoidBattleModeSingleTeam = IveSave[0].single_team;
                OSReport("GameStartMis Win Next %d\n", IveSave[0].field_166E);
            }
        }
        if (GameMode.win == 3) {
            memcopy(&IveSave[0], &IveSave[4], sizeof(GameSaveRecord));
            GameMode.map = IveSave[0].stage;
            ret = 107;
            menuZoidBattleModeSingleTeam = IveSave[0].single_team;
            OSReport("GameStartMis loss Continue stage=%d\n", IveSave[0].field_166E);
        }
    }
    if (GameMode.game_type == GAME_TYPE_BATTLE) {
        if (GameMode.win == 1)
            ret = 230;
        if (GameMode.win == 2) {
            memcopy(&IveSave[0], &IveSave[4], sizeof(GameSaveRecord));
            IveSave[0].money += GameMode.bp_earned;
            ret = 230;
            IveSave[4].money += GameMode.bp_earned;
            IveSave[0].play_time += GameMode.gametime;
            IveSave[4].play_time += GameMode.gametime;
            if (GameMode.map >= 11) {
                OSReport("Youre Win 12\x96\xca\n");
                OSReport("save load icon\n");
                OSReport("addHuman\n");
                ttlMenuLoadSaveLoad();
                menudispyesnoflag = 1;
                menudispyesnopoint = 1;
                do {
                    sPadAll();
                    menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_SAVE_PROMPT), "");
                    menu_sDispSaveLoad();
                } while (sPad1->pressed_a == 0);
                menudispyesnoflag = 0;
                if (menudispyesnopoint == 1) {
                    IveSave[0].field_166B = 0;
                    IveSave[0].stage = 0;
                    IveSave[0].field_166D = 0;
                    IveSave[0].map_no = menu_BatMapData[0].map;
                    IveSave[0].win = 0;
                    IveSave[0].field_166E = 0;
                    GameMode.map = 0;
                    IveSaveFlag.system_flags[0] = 1;
                    memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                    memcpy(&IveSave[3], &IveSaveFlag, sizeof(GameSaveRecord));
                    OSReport("END GAME save system end \n");
                    do {
                        if (ttlMemCardChkStartNew() == 0)
                            break;
                        if (ttlMenuBatSaveLoad(1) == 1) {
                            memcpy(&IveSaveFlag, &IveSave[3], sizeof(GameSaveRecord));
                            break;
                        }
                        memcpy(&IveSaveFlag, &IveSave[3], sizeof(GameSaveRecord));
                    } while (flag_saveok != 1);
                }
                EndeFin();
                OSReport("save end \n");
                ttlMenuPurgeSaveLoad();
                menudispyesnoflag = 0;
                ret = 0;
                GameMode.win = 0;
            }
            GameMode.map++;
            IveSave[0].stage = GameMode.map;
            IveSave[0].field_166E = GameMode.map;
            menuZoidBattleModeSingleTeam = IveSave[0].single_team;
            OSReport("GameStart Win Next %d time=%d bp=%d\n", IveSave[0].field_166E, IveSave[0].play_time, IveSave[0].money);
        }
        if (GameMode.win == 3) {
            memcopy(&IveSave[0], &IveSave[4], sizeof(GameSaveRecord));
            IveSave[0].play_time += GameMode.gametime;
            ret = 230;
            menuZoidBattleModeSingleTeam = IveSave[0].single_team;
            OSReport("GameStart loss Continue stage=%d\n", IveSave[0].field_166E);
        }
    }
    if (GameMode.game_type == GAME_TYPE_VS || GameMode.game_type == GAME_TYPE_3) {
        if (GameMode.win != 0) {
            memcopy(&IveSave[0], &IveSave[4], sizeof(GameSaveRecord));
            memcopy(&IveSave[1], &IveSave[5], sizeof(GameSaveRecord));
            sCamNN2 = 2;
            ret = 306;
            sCamNN = 2;
            IveSave[0].single_team = 1;
            menuZoidBattleModeSingleTeam = 1;
        }
        IveSave[0].single_team = 1;
        menuZoidBattleModeSingleTeam = 1;
    }
    OSReport("GameStart02\n");
    while (1) {
        debug11();
        OSReport("menu=%d type=%d win=%d ", ret, GameMode.game_type, GameMode.win);
        switch (ret) {
        case 0:
            menudispyesnoanm.anim = 1;
            menudispyesnoanm.state = 1;
            if (GameMode.field_2C == 0) {
                ttlMemCardChkStartNew();
                ret = 2;
            } else if (GameMode.field_2C == 1) {
                ret = 8;
            } else {
                ttlMemCardChkStartNew();
                ret = 8;
            }
            break;
        case 1:
            ret = 8;
            break;
        case 2:
            ttlMovie(movies.path[1]);
            ret = 8;
            break;
        case 5:
            ttlMovie(movies.path[4]);
            ret = 1;
            break;
        case 8:
            ret = menufncPushStart();
            break;
        case 10:
            ret = menufncMainMenu();
            break;
        case 100:
            ret = menufncStoryMode01();
            OSReport("Mission DEMO \x8fI\x97\xb9 \n");
            if (IveSave[0].stage == 100) {
                GameMode.map = 100;
                GameZoid[0].type = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                OSReport("Mission DEMO 100 %s\n", Tea_zoiddat[GameZoid[0].type].name);
                ret = 9999;
            } else {
                GameMode.map = IveSave[0].stage;
            }
            break;
        case 101:
            menufncStoryMode01();
            OSReport("Mission DEMOb \x8fI\x97\xb9 \n");
            if (IveSave[0].stage == 100) {
                GameZoid[0].type = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                OSReport("Mission DEMO 100 %s\n", Tea_zoiddat[GameZoid[0].type].name);
                GameMode.map = 100;
                ret = 9999;
                break;
            }
            GameMode.map = IveSave[0].stage;
            menufncZoidBattle02Hokyu();
            ttlMenu_sDispMissionHokyu();
            ttlMenuLoadZoid();
        case 104:
            ret = menufncMission_Menu();
            break;
        case 105:
            ret = menufncZoidMission_MenuEntry();
            break;
        case 107:
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            OSReport("Mission DATA Load Start\n");
            menufncZoidBattle02();
            OSReport("Mission DATA Load End\n");
            OSReport("Mission DATA Load End\n");
            OSReport("Mission DATA Load End\n");
            OSReport("Mission DATA Load End\n");
            OSReport("Mission DATA Load End\n");
            OSReport("Mission DATA Load End\n");
            ret = menufncMission_Menu();
            break;
        case 200:
            ret = menufncZoidBattle01Human();
            break;
        case 204:
            ret = menufncZoidBattle_BattleMenu();
            break;
        case 205:
            ret = menufncZoidBattle_BattleMenuEntry();
            break;
        case 220:
            ret = menufncZoidBattle_HumanBattleMenuEntry();
            break;
        case 221:
            ttlMenu_sDispBattleNextYokok();
            ret = 204;
            break;
        case 222:
            menufncZoidBattle02();
            ret = 204;
            break;
        case 230:
            menufncZoidBattle02();
            ret = 221;
            break;
        case 210:
        case 310:
            ret = menufncZoidBattleEnd();
            break;
        case 300:
            menuZoidVS_NonSaveData_InitData(0);
            menuZoidVS_NonSaveData_InitData(1);
            ret = menufncZoidVs01();
            break;
        case 304:
            ret = menufncZoidVsMenu();
            break;
        case 305:
            ret = menufncZoidVsMenuEntry();
            break;
        case 306:
            menufncZoidVs01();
            ret = 304;
            break;
        case 400:
            ret = 10;
            break;
        case 500:
            ttlMenuOption();
            ret = 10;
            break;
        case 9000:
            testbitsetmenu_zoid();
            ret = 10;
            break;
        case 9999:
            TeaBgm(-1);
            if (ttlLight != 0)
                HSD_LObjRemoveAll(ttlLight);
            ttlLight = 0;
            memcopy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
            ttlMenuAllPurge();
            return;
        default:
            ret = 1;
            break;
        }
    }
}
#pragma pop
#pragma readonly_strings off
static const char sZoidDataPath[15] = "etc/n_Zoid.dat";
static const char sPartsDataPath[16] = "etc/n_Parts.dat";
static const char sBulletDataPath[17] = "etc/n_Bullet.dat";
static const char sPersonDataPath[17] = "etc/n_Person.dat";
static const char sEffectDataPath[17] = "etc/n_Effect.dat";
static const char sMenuTextPath[17] = "etc/TXT_Menu.BIN";
static const char sStoryModeLabel[11] = "STORY MODE";
static const char sZoidsBattleModeLabel[18] = "ZOIDS BATTLE MODE";
static const char sMissionReplayModeLabel[20] = "MISSION REPLAY MODE";
static const char sZoidsMuseumModeLabel[18] = "ZOIDS MUSEUM MODE";
static const char sOptionModeLabel[12] = "OPTION MODE";
static const char sZoidSettingLabel[9] = "Zoid\x90\xdd\x92\xe8";
#pragma readonly_strings on
s32 menufncStoryMode01(void)
{
    s16 i;

    menudemo[0] = LoadArc2("menu/demo/demo.dat");
    menudemo[1] = LoadArc2("menu/demo/demosell00.dat");
    menudemo[2] = LoadArc2("menu/demo/demosell01.dat");
    menudemo[3] = LoadArc2("menu/demo/demosell02.dat");
    GameMode.map = IveSave[0].stage;
    menu_MissionDemo();
    for (i = 0; i < 4; i++) {
        if (menudemo[i] != 0) {
            PurgeArc2(menudemo[i]);
            menudemo[i] = 0;
        }
    }
    return 101;
}
#pragma readonly_strings off
static const char sRepublicArmyLabel[9] = "\x8b\xa4\x98" "a\x8d\x91\x8cR";
static const char sLogMenuStoryMode2[16] = "MenuStoryMode2\n";
static const char sTestStoryMode2Label[17] = "TEST STORY MODE2";
static const char sLogMenuZoidBattle[16] = "MenuZoidBattle\n";
static const s32 sPowersOfTen[6] = { 1, 10, 100, 1000, 10000, 100000 };
static const char sLogPartsSet[21] = "PARTS SET %d max=%d\n";
static const char sLogPartsList[21] = "PARTS List %d %d %s\n";
static const char sLogPartsWeaponPoint[28] = "PARTS WepP=%d pr=%d  %d:%s\n";
static const char sLogPartsSetWeapon[27] = "PARTS SET %d Wep%d max=%d\n";
static const char sLogMountPointDisp[19] = "MountPointDsip:%d\n";
static const char sLogZoidListDispNow[17] = "ZoidListDisp:Now";
static const char sLogWeaponPointMount[16] = "WepP=%d mt=%d \n";
static const char sZoids1FileNameFormat[16] = "ZOIDS1_%01d.TEA";
static const char sLogMemCardLoad[16] = "MemCardLoad:%s\n";
static const char sLogMemCardSave[16] = "MemCardSave:%s\n";
static const u8 r1386[64] = { 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x02, 0x00, 0x04, 0x00, 0x17, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 };
static const u8 r1387[30] = { 0x00, 0x00, 0x00, 0x17, 0x00, 0x11, 0x00, 0x04, 0x00, 0x02, 0x00, 0x22, 0x00, 0x01, 0x00, 0x02, 0x00, 0x0D, 0x00, 0x16, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
static const char sLogMemCardTest[16] = "MemCardTest:%s\n";
static const char sZoidDatPathFormat[12] = "zoid/%s.dat";
static const char sLogAddPerson[46] = "add man %d ---------------------------------\n";
static const char sLogAddZoid[43] = "add-zoid %d ----------------------------\n ";
extern void addZoids(s32 save, s32 zoid);
extern void ttl_HaveAddHuman(s16 save, s16 person);
extern s32 fexist(char *name);
extern void ttl_IveSaveSetZoidDefParts(s16 record, s16 slot, s16 zoid);

#pragma readonly_strings on
void menuZoidBattle_NonSaveData_InitData(void)
{
    s16 zoidsA[32] = { 0, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    s16 zoidsB[32] = { 21, 22, 42, 35, 36, 37, 38, 26, 29, 30, 39, 40, 41, 16, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    s16 persons[28] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, -1, -1 };
    char path[80];
    s16 i;
    s16 j;
    s16 n;
    s16 rec;
    s32 found;
    s32 unused[1];

    OSReport("menuZoidBattle_NonSaveData_InitData\n");
    sprintf(path, "ZOIDS1B%01d.TEA", 0);
    OSReport((char *)sLogMemCardTest, path);
    rec = 0;
    IveSave[rec].money = 30000;
    IveSave[rec].have_zoid_count = 0;
    IveSave[rec].field_1431 = 0;
    IveSave[rec].has_data = 0;
    for (i = 0; i < 100; i++) {
        IveSave[rec].have_zoid[i] = -1;
        IveSave[rec].have_zoid_flag[i] = 0;
    }
    n = 0;
    for (i = 0; i < 100; i++) {
        found = 0;
        for (j = 0; j < 30; j++) {
            found = 0;
            if (i == zoidsB[j]) {
                found = 1;
                break;
            }
        }
        if (found != 1 && Tea_zoiddat[i].price != 0) {
            IveSave[rec].have_zoid[n] = i;
            IveSave[rec].have_zoid_flag[n] = 1;
            n++;
            IveSave[rec].have_zoid_count++;
            IveSave[rec].field_1431++;
        }
    }
    for (i = 0; i < 4; i++) {
        if ((s8)IveSaveFlag.system_flags[4 + i] != 0) {
            addZoids(0, i + 35);
            OSReport("add-zoid-4 diab =====================================================================================================================================================\n");
        }
    }
    if ((s8)IveSaveFlag.system_flags[1] != 0) {
        addZoids(0, 17);
        OSReport("add-zoid-17\n");
    }
    if ((s8)IveSaveFlag.system_flags[0] != 0) {
        addZoids(0, 16);
        OSReport("add-zoids-16\n");
    }
    for (i = 0; i < 50; i++)
        IveSave[rec].system_flags[i] = 0;
    for (i = 0; i < 30; i++)
        IveSave[rec].owned_zoids[i] = -1;
    for (i = 0; i < 30; i++) {
        IveSave[rec].field_0AD2[i] = 0;
        IveSave[rec].owned_zoids[i] = zoidsA[i];
    }
    for (i = 0; i < 30; i++) {
        IveSave[rec].zoid_colors[i] = 0;
        for (j = 0; j < 28; j++)
            IveSave[rec].zoid_weapons[i][j] = -1;
    }
    IveSave[rec].owned_zoid_count = 0;
    for (i = 0; i < 30; i++) {
        if (IveSave[rec].owned_zoids[i] != -1) {
            sprintf(path, (char *)sZoidDatPathFormat, Tea_zoiddat[IveSave[0].owned_zoids[i]].model_name);
            if (fexist(path) == 1)
                IveSave[rec].owned_zoid_count++;
            else
                IveSave[rec].owned_zoids[i] = -1;
        }
    }
    j = 0;
    for (i = 0; i < IveSave[rec].owned_zoid_count; i++)
        ttl_IveSaveSetZoidDefParts(j, i, IveSave[j].owned_zoids[i]);
    IveSave[0].person_list_count = 0;
    IveSave[0].field_1303 = 0;
    IveSave[0].field_1302 = 0;
    for (i = 0; i < 58; i++) {
        j = 0;
        IveSave[0].have_person[i] = 0;
        IveSave[0].person_list[i] = -1;
        for (; j < 26; j++) {
            if (i == persons[j]) {
                IveSave[0].have_person[i] = 1;
                IveSave[0].field_1302++;
                sprintf(path, "menu/picture/p%02d.dat", i, IveSave[0].field_1303++);
                IveSave[0].person_list[(s8)IveSave[0].person_list_count] = i;
                IveSave[0].person_list_count++;
            }
        }
    }
    if ((s8)IveSaveFlag.system_flags[0] != 0) {
        ttl_HaveAddHuman(0, 27);
        ttl_HaveAddHuman(0, 28);
        ttl_HaveAddHuman(0, 29);
        ttl_HaveAddHuman(0, 30);
        OSReport("add-chara-27.28.29.30\n");
    }
    if ((s8)IveSaveFlag.system_flags[1] != 0) {
        ttl_HaveAddHuman(0, 31);
        ttl_HaveAddHuman(0, 32);
        ttl_HaveAddHuman(0, 33);
        ttl_HaveAddHuman(0, 42);
        OSReport("add-chara-27.28.29.30\n");
    }
    if ((s8)IveSaveFlag.system_flags[2] != 0) {
        ttl_HaveAddHuman(0, 34);
        ttl_HaveAddHuman(0, 35);
        ttl_HaveAddHuman(0, 36);
        ttl_HaveAddHuman(0, 41);
        OSReport("add-chara-34.35.36.42\n");
    }
    if ((s8)IveSaveFlag.system_flags[3] != 0) {
        ttl_HaveAddHuman(0, 37);
        ttl_HaveAddHuman(0, 38);
        ttl_HaveAddHuman(0, 39);
        ttl_HaveAddHuman(0, 40);
        ttl_HaveAddHuman(0, 43);
        ttl_HaveAddHuman(0, 44);
        ttl_HaveAddHuman(0, 45);
        ttl_HaveAddHuman(0, 46);
        OSReport("add-chara-37.38.39.40.43.44.45.46\n");
    }
    if ((s8)IveSaveFlag.system_flags[9] != 0) {
        ttl_HaveAddHuman(0, 15);
        OSReport("add-chara-15 \n");
    }
    IveSave[rec].selected_zoid = IveSave[rec].owned_zoids[0];
    IveSave[rec].selected_zoid_slot = 0;
    IveSave[rec].partner_zoid = IveSave[rec].owned_zoids[1];
    IveSave[rec].partner_zoid_slot = 1;
    IveSave[rec].selected_person = 0;
    IveSave[rec].partner_person = 1;
    IveSave[rec].owned_part_count = 0;
    for (i = 0; i < 450; i++)
        IveSave[rec].owned_parts[i] = -1;
    IveSave[0].parts_num = 0;
    for (i = 0; i < 450; i++) {
        IveSave[rec].shop_flags[i] = 1;
        IveSave[0].parts_num++;
    }
    OSReport("MemCard_NonSaveDataInit_06\n");
}
#pragma readonly_strings off


#pragma readonly_strings on
#pragma push
#pragma dont_inline on
extern s32 fexist(char *name);
extern void ttl_IveSaveSetZoidDefParts(s16 record, s16 slot, s16 zoid);

void menuZoidMission_NonSaveData_InitData(void)
{
    s16 zoidsA[32] = { 27, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    s16 zoidsB[32] = { 34, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    s16 persons[15] = { 31, 32, 33, 34, 35, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    char path[80];
    s32 pad1[2];
    s16 i;
    s16 j;

    sprintf(path, "ZOIDS1M%01d.TEA", 0);
    OSReport((char *)sLogMemCardTest, path);
    IveSave[0].money = 30000;
    IveSave[0].have_zoid_count = 0;
    IveSave[0].field_1431 = 0;
    IveSave[0].has_data = 0;
    for (i = 0; i < 100; i++) {
        IveSave[0].have_zoid[i] = i;
        IveSave[0].have_zoid_flag[i] = 1;
        IveSave[0].have_zoid_count++;
        IveSave[0].field_1431++;
        for (j = 0; j < 30; j++) {
        }
    }
    for (i = 0; i < 50; i++)
        IveSave[0].system_flags[i] = 0;
    for (i = 0; i < 30; i++)
        IveSave[0].owned_zoids[i] = -1;
    for (i = 0; i < 30; i++) {
        IveSave[0].field_0AD2[i] = 0;
        if (GameMode.country == 1)
            IveSave[0].owned_zoids[i] = zoidsA[i];
        else
            IveSave[0].owned_zoids[i] = zoidsB[i];
    }
    for (i = 0; i < 30; i++) {
        IveSave[0].zoid_colors[i] = 0;
        for (j = 0; j < 28; j++)
            IveSave[0].zoid_weapons[i][j] = -1;
    }
    IveSave[0].owned_zoid_count = 0;
    for (i = 0; i < 30; i++) {
        if (IveSave[0].owned_zoids[i] != -1) {
            sprintf(path, (char *)sZoidDatPathFormat, Tea_zoiddat[IveSave[0].owned_zoids[i]].model_name);
            if (fexist(path) == 1)
                IveSave[0].owned_zoid_count++;
            else
                IveSave[0].owned_zoids[i] = -1;
        }
    }
    j = 0;
    for (i = 0; i < IveSave[0].owned_zoid_count; i++)
        ttl_IveSaveSetZoidDefParts(j, i, IveSave[j].owned_zoids[i]);
    IveSave[0].person_list_count = 0;
    IveSave[0].field_1303 = 0;
    IveSave[0].field_1302 = 0;
    for (i = 0; i < 58; i++) {
        IveSave[0].have_person[i] = 0;
        IveSave[0].person_list[i] = -1;
        for (j = 0; j < 3; j++) {
            if (i == persons[(s16)((GameMode.country - 1) * 3 + j)]) {
                IveSave[0].have_person[(s8)IveSave[0].field_1302] = 1;
                IveSave[0].field_1302++;
                sprintf(path, "menu/picture/p%02d.dat", i, IveSave[0].field_1303++);
                IveSave[0].person_list[(s8)IveSave[0].person_list_count] = i;
                IveSave[0].person_list_count++;
            }
        }
    }
    IveSave[0].selected_zoid = IveSave[0].owned_zoids[0];
    IveSave[0].selected_zoid_slot = 0;
    IveSave[0].partner_zoid = IveSave[0].owned_zoids[1];
    IveSave[0].partner_zoid_slot = 1;
    IveSave[0].selected_person = IveSave[0].person_list[0];
    IveSave[0].partner_person = IveSave[0].person_list[1];
    IveSave[0].owned_part_count = 0;
    for (i = 0; i < 450; i++)
        IveSave[0].owned_parts[i] = -1;
    IveSave[0].parts_num = 0;
    for (i = 0; i < 450; i++) {
        IveSave[0].shop_flags[i] = 1;
        IveSave[0].parts_num++;
    }
    OSReport("MemCard_NonSaveDataInit_06 Mission\n");
}
#pragma pop
#pragma readonly_strings off

#pragma readonly_strings on
void menuZoidMission_EndSaveData_start(void)
{
    s16 list[15] = {31, 32, 33, 34, 35, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    s16 i;
    s16 j;
    s16 rec;
    s32 unused[2];

    OSReport("menuZoidMission_EndSaveData_start\n");
    rec = 0;
    IveSave[rec].has_data = 0;
    IveSave[rec].person_list_count = 0;
    IveSave[rec].field_1303 = 0;
    IveSave[rec].field_1302 = 0;
    for (i = 0; i < 58; i++) {
        IveSave[rec].have_person[i] = 0;
        IveSave[rec].person_list[i] = -1;
        for (j = 0; j < 3; j++) {
            if (i == list[(s16)((GameMode.country - 1) * 3 + j)]) {
                IveSave[rec].have_person[(s8)IveSave[rec].field_1302] = 1;
                IveSave[rec].field_1302++;
                IveSave[rec].field_1303++;
                IveSave[rec].person_list[IveSave[rec].person_list_count] = i;
                IveSave[rec].person_list_count++;
            }
        }
    }
    IveSave[rec].selected_person = IveSave[rec].person_list[0];
    IveSave[rec].partner_person = IveSave[rec].person_list[1];
    OSReport("MemCard_EndSaveDataInit_Start\n");
}
#pragma readonly_strings off


#pragma readonly_strings on
#pragma push
#pragma dont_inline on
extern void ttl_HaveAddHuman(s16 save, s16 person);
void menuZoidVS_NonSaveData_InitData(s16 rec)
{
    s16 zoids[32] = { 0, 1, 2, 3, 4, 5, 8, 9, 14, 15, 19, 23, 27, 28, 31, 34, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    s16 persons[28] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, -1, -1 };
    char path[80];
    s16 i;
    s16 j;
    s32 unused[2];

    sprintf(path, "ZOIDS1V%01d.TEA", 0);
    OSReport((char *)sLogMemCardTest, path);
    IveSave[rec].money = 30000;
    IveSave[rec].have_zoid_count = 0;
    IveSave[rec].field_1431 = 0;
    IveSave[rec].has_data = 0;
    for (i = 0; i < 100; i++) {
        IveSave[rec].have_zoid[i] = i;
        IveSave[rec].have_zoid_flag[i] = 1;
        IveSave[rec].have_zoid_count++;
        IveSave[rec].field_1431++;
    }
    for (i = 0; i < 30; i++)
        IveSave[rec].owned_zoids[i] = -1;
    for (i = 0; i < 30; i++) {
        IveSave[rec].field_0AD2[i] = 0;
        IveSave[rec].owned_zoids[i] = zoids[i];
    }
    for (i = 0; i < 30; i++) {
        IveSave[rec].zoid_colors[i] = 0;
        for (j = 0; j < 28; j++)
            IveSave[rec].zoid_weapons[i][j] = -1;
    }
    IveSave[rec].owned_zoid_count = 0;
    for (i = 0; i < 30; i++) {
        if (IveSave[rec].owned_zoids[i] != -1) {
            sprintf(path, (char *)sZoidDatPathFormat, Tea_zoiddat[IveSave[rec].owned_zoids[i]].model_name);
            if (fexist(path) == 1)
                IveSave[rec].owned_zoid_count++;
            else
                IveSave[rec].owned_zoids[i] = -1;
        }
    }
    for (i = 0; i < IveSave[rec].owned_zoid_count; i++)
        ttl_IveSaveSetZoidDefParts(rec, i, IveSave[rec].owned_zoids[i]);
    IveSave[rec].person_list_count = 0;
    IveSave[rec].field_1303 = 0;
    IveSave[rec].field_1302 = 0;
    for (i = 0; i < 58; i++) {
        j = 0;
        IveSave[rec].have_person[i] = 0;
        IveSave[rec].person_list[i] = -1;
        for (; j < 26; j++) {
            if (i == persons[j]) {
                IveSave[rec].have_person[i] = 1;
                IveSave[rec].field_1302++;
                sprintf(path, "menu/picture/p%02d.dat", i, IveSave[rec].field_1303++);
                IveSave[rec].person_list[(s8)IveSave[rec].person_list_count] = i;
                IveSave[rec].person_list_count++;
            }
        }
    }
    if ((s8)IveSaveFlag.system_flags[0] != 0) {
        ttl_HaveAddHuman(rec, 27);
        ttl_HaveAddHuman(rec, 28);
        ttl_HaveAddHuman(rec, 29);
        ttl_HaveAddHuman(rec, 30);
        OSReport("add-chara-27.28.29.30\n");
    }
    if ((s8)IveSaveFlag.system_flags[1] != 0) {
        ttl_HaveAddHuman(rec, 31);
        ttl_HaveAddHuman(rec, 32);
        ttl_HaveAddHuman(rec, 33);
        ttl_HaveAddHuman(rec, 42);
        OSReport("add-chara-27.28.29.30\n");
    }
    if ((s8)IveSaveFlag.system_flags[2] != 0) {
        ttl_HaveAddHuman(rec, 34);
        ttl_HaveAddHuman(rec, 35);
        ttl_HaveAddHuman(rec, 36);
        ttl_HaveAddHuman(rec, 41);
        OSReport("add-chara-34.35.36.42\n");
    }
    if ((s8)IveSaveFlag.system_flags[3] != 0) {
        ttl_HaveAddHuman(rec, 37);
        ttl_HaveAddHuman(rec, 38);
        ttl_HaveAddHuman(rec, 39);
        ttl_HaveAddHuman(rec, 40);
        ttl_HaveAddHuman(rec, 43);
        ttl_HaveAddHuman(rec, 44);
        ttl_HaveAddHuman(rec, 45);
        ttl_HaveAddHuman(rec, 46);
        OSReport("add-chara-37.38.39.40.43.44.45.46\n");
    }
    if ((s8)IveSaveFlag.system_flags[9] != 0) {
        ttl_HaveAddHuman(rec, 15);
        OSReport("add-chara-15 \n");
    }
    IveSave[rec].selected_zoid = IveSave[rec].owned_zoids[0];
    IveSave[rec].selected_zoid_slot = 0;
    IveSave[rec].partner_zoid = IveSave[rec].owned_zoids[1];
    IveSave[rec].partner_zoid_slot = 1;
    IveSave[rec].selected_person = 0;
    IveSave[rec].partner_person = 1;
    IveSave[rec].owned_part_count = 0;
    for (i = 0; i < 450; i++)
        IveSave[rec].owned_parts[i] = -1;
    IveSave[rec].parts_num = 0;
    for (i = 0; i < 450; i++) {
        IveSave[rec].shop_flags[i] = 1;
        (IveSave[rec].parts_num)++;
    }
    OSReport("MemCard_NonSaveDataInit_VS\n");
}
#pragma pop
#pragma readonly_strings off

static const char sLogAddParts[63] = "ADD PartsNo=%d p=%d max=%d-----------------------------------\n";
static const char sLogPartsEntry[23] = "Parts p=%d:No=%3d %s \n";
static const char sLogRemoveParts[29] = "\x8e\xe6\x8aO\x82\xb5Parts=%d WepPOint=%d \n";
static const char sLogMountSetIveSave[23] = "MountSetIveSave zd=%s ";
static const char sLogMountSetIveSaveEntry[22] = "WP=%02d MP=%02d %s \n ";

#pragma push
#pragma dont_inline on
void ttl_IveSaveSetZoidDefParts(s16 save, s16 slot, s16 zoid)
{
    ZoidData *data;
    s16 part;
    s16 mount;
    s16 i;

    if (save < 0)
        return;
    if (slot < 0)
        return;
    if (zoid < 0)
        return;
    IveSave[save].field_1673 = -1;
    IveSave[save].field_1674 = -1;
    for (i = 0; i < 28; i++)
        IveSave[save].zoid_weapons[slot][i] = -1;
    for (i = 0; i < 28; i++)
        menuwepdispmount[i] = -1;
    IveSave[save].contract_options[slot] = 0;
    for (i = 0; i < 3; i++)
        IveSave[save].contract_subparts[slot][i] = 0;
    menuwepdispnum = 0;
    IveSave[save].owned_zoids[slot] = zoid;
    IveSave[save].zoid_colors[slot] = (s8)Tea_zoiddat[zoid].field_078E;
    OSReport(sLogMountSetIveSave, Tea_zoiddat[zoid].name);
    data = &Tea_zoiddat[zoid];
    for (i = 0; i < 10; i++) {
        (void)data;
        part = data->default_parts[i];
        if (part > 0) {
            mount = Tea_zoiddat[zoid].mount[i];
            if (mount >= 0) {
                if (i == 8 || i == 9) {
                    if (data->weapon_permissions[i] == 1)
                        IveSave[save].contract_options[slot] = part;
                } else {
                    IveSave[save].zoid_weapons[slot][i] = part;
                }
                if (i == 8)
                    IveSave[save].field_1673 = mount;
                if (i == 9)
                    IveSave[save].field_1674 = mount;
                menuwepdispmount[menuwepdispnum] = mount;
                OSReport(sLogMountSetIveSaveEntry, i, mount, Tea_partsdat[part].name, menuwepdispnum++);
            }
        }
    }
}
#pragma pop

static const char sLogMountSetGameZoid[24] = "MountSetGameZoid zd=%s ";
static const char sLogMountSetGameZoidEntry[18] = "i=%02d %s-%02d : ";
static const char sLogNowZoid[35] = "NowZoid=%s %d wepp=%d parts=%d %d\n";
static const char sLogYesNoMenuNotLoading[23] = "YesNoMenu Not Loading\n";
static const u8 r2621[14] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const char sLogSlotPresent[12] = "SLOT \x82\xa0\x82\xe8 \n";
static const char sLogSlotSectorSizeOk[22] = "SLOT \x83Z\x83N\x83^\x83T\x83" "C\x83Y ok\n";
static const char sLogMountAllowed[11] = "MOunt\x8b\x96\x89\xc2\n";

#pragma readonly_strings on
s32 ttlMemCardChkStartNew(void)
{
    s32 retry;

    configClear();
    ttlMenuLoadYesNo();
    ttlMenuSaveDataSetFileName(-1, 0);
    menusaveloadslot = 0;
    retry = 0;
    while (1) {
        if (retry == 1) {
            if (TEA_mcMsgYesNoNotChkSlot(0, MENU_MSG_SAVE_DISABLED_PROMPT) != 0) {
                OSReport("\x82\xb1\x82\xcc\x82\xdc\x82\xdc\x83Q\x81[\x83\x80\n");
                return 0;
            }
            OSReport("SLOT \n");
            TEA_mcUnMount(0);
            retry = 0;
            continue;
        }
        OSReport("SLOT CHK\n");
        menu_SlotOn = TEA_mcChkSlot(0);
        if (menu_SlotOn == 0) {
            TEA_mcMsgNoChkSlot(0, MENU_MSG_NO_CARD_A);
            retry = 1;
            continue;
        }
        if (MemCardStatus[0] == -2) {
            retry = 1;
            continue;
        }
        OSReport(sLogSlotPresent);
        if (TEA_mcMountNoChk(0) == 0) {
            if (MemCardStatus[0] == -2) {
                retry = 1;
                continue;
            }
            if (MemCardStatus[0] == -5) {
                TEA_mcMsgNoChkSlot(0, MENU_MSG_UNUSABLE_A);
                retry = 1;
                continue;
            }
            if (MemCardStatus[0] == -13) {
                if (TEA_mcBadEncFormatEnc(0) == 1) {
                    retry = 0;
                    continue;
                }
                if (TEA_mcChkSlot(0) == 0)
                    TEA_mcMsgNoChkSlot(0, MENU_MSG_NO_CARD_A);
                retry = 1;
                continue;
            }
        }
        if (TEA_mcChkSector(0) == 0) {
            TEA_mcMsgNoChkSlot(0, MENU_MSG_UNSUPPORTED_CARD);
            retry = 1;
            continue;
        }
        OSReport("SLOT IOERR CHK\n");
        if (TEA_mcChkIoErr(0) == 0)
            OSReport("SLOT IOERR \x8eg\x82\xa6\x82\xc8\x82\xa2\x83\x81\x83" "f\x83" "B\x83" "A\n");
        OSReport("SLOT BROKEN CHK\n");
        if (TEA_mcChkBroken(0) == 0 && MemCardStatus[0] == -6) {
            if (TEA_mcBadEncFormatEnc(0) == 1) {
                retry = 0;
                continue;
            }
            if (TEA_mcChkSlot(0) == 0) {
                TEA_mcMsgNoChkSlot(0, MENU_MSG_NO_CARD_A);
                retry = 1;
                continue;
            }
            retry = 1;
            continue;
        }
        clrYesNoMsg();
        OSReport(sLogSlotSectorSizeOk);
        if (TeaMemCardChk() == 0) {
            retry = 1;
            continue;
        }
        clrYesNoMsg();
        OSReport(sLogMountAllowed);
        ZoidFileBroken = 0;
        if (ttlMenuSaveLoadexistenceDataStartNew0() != 0) {
            TEA_mcUnMount(0);
            return 1;
        }
        if (ZoidFileBroken == 1) {
            ZoidFileBroken = 0;
            if (TEA_mcChkSlot(0) == 0) {
                TEA_mcMsgNoChkSlot(0, MENU_MSG_NO_CARD_A);
                retry = 1;
                continue;
            }
            TEA_mcMsgNoChkSlot(0, 4);
            TEA_mcMsgNoChkSlot(0, 5);
            retry = 1;
            continue;
        }
        if (TEA_mcMsgYesNo(0, MENU_MSG_NO_SYSTEM_DATA_PROMPT_A) != 0) {
            TEA_mcMsgDisp(0, MENU_MSG_SAVING);
            OSReport("Zoid SystemData \x8d\xec\x90\xac\x8aJ\x8en\n");
            if (ttlMenuSaveLoadexistenceData0(1) != 0) {
                menudispyesnoflag = 0;
                return 1;
            }
            TEA_mcUnMount(0);
            if (ZoidFileBroken == 1)
                TEA_mcMsgNoChkSlot(0, MENU_MSG_CARD_BROKEN_A);
            ZoidFileBroken = 0;
            retry = 1;
            continue;
        }
        TEA_mcUnMount(0);
        retry = 1;
    }
}
#pragma readonly_strings off

static const char sLogNoSaveLoadArchive[20] = "non menu_saveloadp\n";
static const char sLogSaveLoadArchive10[23] = "menu_saveloadp 1-0 %d\n";
static const char sSaveDateFormat[15] = "%02d/%02d/%02d";
static const char sBattleNumberFormat[11] = "BATTLE%-2d";
static const char sFarmLabel[9] = "\x83t\x83@\x81[\x83\x80";
static const char sNoDataLabel[9] = " NO DATA";
static const char sSaveLoadArchivePath[27] = "menu/saveload/saveload.dat";
static const char sSaveLoadTitleBgPath[26] = "menu/saveload/bgtitle.dat";
static const char sLogSlotACheck[14] = "SLOT A CHECK\n";
static const char sSaveFileName[12] = "ZOIDSVS.TEA";
static const char sLogSaveMinus1[10] = "save -1 \n";
static const char sLogSaveMinus2[10] = "save -2 \n";
static const char sNowSaveLabel[9] = "NOW SAVE";
static const char sLogMemFormatReadSt[18] = "MemFormat ReadSt\n";
static const char sLogMemLoadEnd[72] = "MemLoad End Stage=%d Mapno=%d Single=%d NowZoid=%d NowCust=%d \x90l\x95\xa8=%d \n";
static const char sOutFileLabel[9] = "OUT FILE";
static const char sLogMemCardSaveTrueEnd[41] = "MemCard SaveTrueEnd \x90l\x95\xa8=%d:%s Zd=%d:%s\n";
static const char sLogMemCardLoadTrueEnd[41] = "MemCard LoadTrueEnd \x90l\x95\xa8=%d:%s Zd=%d:%s\n";
static const char sLogGameModeSlotData[54] = "\n\n\n\n\n\n\n\n Gamemode=%d menu_SlotData %d_%d:%d Stage=%d\n";
static const char sLogSlotData[33] = "menu_SlotData %d_%d:%d Stage=%d\n";
static const char sSaveFileComment[50] = "\x83v\x83\x8c\x83" "C\x83" "f\x81[\x83^\x81@\x81@                                 ";
static const char sLogMemSystemAreaCreateOk[37] = "MemSecurableSystemAreaCreate Ok %d \n";
static const char sLogMemDataCreateOk[31] = "MemSecurableDataCreate Ok %d \n";
static const s16 r3729[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r3730[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };
static const s16 r3731[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const char sLogMemExistDataKeep[54] = "MemExistData USE:%d KeepBlk:%d %d\x83Z\x83N\x83^ \x8b\xf3\x82\xab[%d]DIR \n";
static const s16 r3797[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r3798[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };
static const s16 r3799[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };

#pragma push
#pragma dont_inline on
s32 ttlMenuSaveLoadexistenceData0(s32 mode)
{
    SaveFileTable name = *(SaveFileTable *)r3797;
    SaveFileTable kind = *(SaveFileTable *)r3798;
    s32 result;
    s32 unused[6];
    s16 slot;

    result = 0;
    slot = 0;
    MemCardKeepBlock = 10;
    menusaveloadslot = slot;
    ZoidFileBroken = slot;
    ttlMenuSaveDataSetFileName(name.value[slot], kind.value[slot]);
    strcpy((char *)menusaveloadfilename, sSaveFileName);
    if (TEA_mcFileMountExist(menusaveloadslot, (char *)menusaveloadfilename) == 1) {
        if (TEA_mcLoadFile0(menusaveloadslot, 1, -1) != 0) {
            result = 1;
            configGet();
        }
    }
    if (result == 1)
        return 1;
    MemCardKeepBlock = 10;
    OSReport((char *)sLogMemExistDataKeep, 0, MemCardKeepBlock, MemCardFreeSize, MemCardFreeDir);
    if (MemCardFreeSize < MemCardKeepBlock * 0x2000) {
        TEA_mcMsgNoChkSlot(0, MENU_MSG_NO_SPACE_A);
        TEA_mcMsgNoChkSlot(0, MENU_MSG_ORGANIZE_CARD_HINT);
        return 0;
    }
    CARDFreeBlocks(0, 0, &MemCardFreeDir);
    if (MemCardFreeDir < 1) {
        TEA_mcMsgNoChkSlot(0, MENU_MSG_NO_SPACE_OR_FILES_A);
        TEA_mcMsgNoChkSlot(0, MENU_MSG_NEED_10_BLOCKS);
        TEA_mcMsgNoChkSlot(0, MENU_MSG_ORGANIZE_CARD_HINT);
        return 0;
    }
    ttlMenuSaveDataSetFileName(name.value[slot], kind.value[slot]);
    strcpy((char *)menusaveloadfilename, sSaveFileName);
    if (TEA_mcSaveFile0(0, 1, -1) == 0) {
        ZoidFileBroken = 1;
        return 0;
    }
    return 1;
}
#pragma pop

static const s16 r3818[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r3819[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };
static const s16 r3820[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const char sLogMemExistData[34] = "MemExistData USE:%d \x8b\xf3\x82\xab[%d]DIR \n";
static const s16 r3849[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r3850[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };
static const s16 r3851[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const s16 r3883[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r3884[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };
static const s16 r3885[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const s16 r3917[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r3918[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };

#pragma readonly_strings on
s32 ttlMenuSaveLoadexistenceDataStartNew0(void)
{
    s32 frame_padding[2];
    SaveFileTable name = *(SaveFileTable *)r3917;
    SaveFileTable kind = *(SaveFileTable *)r3918;
    s32 result;
    s16 slot;
    s32 unused[7];

    result = 0;
    slot = 0;
    MemCardKeepBlock = 10;
    menusaveloadslot = slot;
    ttlMenuSaveDataSetFileName(name.value[slot], kind.value[slot]);
    strcpy((char *)menusaveloadfilename, sSaveFileName);
    if (TEA_mcFileMountExist(0, (char *)menusaveloadfilename) == 1) {
        if (TEA_mcLoadFile0(0, 1, -1) != 0) {
            configGet();
            result = 1;
        } else {
            ZoidFileBroken = 1;
            result = 0;
        }
    } else {
        ZoidFileBroken = slot;
    }
    if (result == 0)
        return 0;
    return 1;
}
#pragma readonly_strings off

static const s16 r3919[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const s16 r3930[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r3931[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };
static const s16 r3932[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const s16 r4016[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r4017[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };

#pragma readonly_strings on
s32 ttlMenuSystemMemCardSave(void)
{
    s32 frame_padding[2];
    SaveFileTable name = *(SaveFileTable *)r4016;
    SaveFileTable kind = *(SaveFileTable *)r4017;
    s16 slot;
    s32 unused[6];

    slot = 0;
    MemCardKeepBlock = 10;
    menusaveloadslot = slot;
    flag_saveok = slot;
    ttlMenuSaveDataSetFileName(name.value[slot], kind.value[slot]);
    TEA_mcMsgDisp(0, MENU_MSG_SAVING);
    strcpy((char *)menusaveloadfilename, sSaveFileName);
    if (TEA_mcSaveFile0(0, 1, -1) != 0) {
        TEA_mcMsgNoChkSlot(0, MENU_MSG_SAVE_DONE);
        flag_saveok = 1;
        return 1;
    }
    TEA_mcMsgNoChkSlot(0, MENU_MSG_SAVE_FAILED);
    flag_saveok = slot;
    return 0;
}
#pragma readonly_strings off

static const s16 r4018[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const s16 r4028[10] = { -1, -2, 0, 0, 0, 0, 1, 1, 1, 1 };
static const s16 r4029[10] = { 0, 0, 0, 1, 2, 3, 0, 1, 2, 3 };
static const s16 r4030[10] = { -1, -2, 0, 0, 0, 0, 0, 0, 0, 0 };
static const u8 r4095[12] = { 0x00, 0x01, 0x04, 0x01, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const char sLogPersonPosBool[25] = "person=%d pos=%d BOOL%d\n";
static const char sLogZoidNum[12] = "ZoidNum=%d\n";
static const char sLogEntry[43] = "Entry:person=%d partner=%d zoid=%d z2=%d \n";
static const char sLogZoidBattleEntryStart[25] = "Zoid bat ent main start\n";
static const char sLogZd1Zd2[15] = "zd1=%d zd2=%d\n";
static const char sOutOfMemoryBackError[31] = "out of memory. menu back error";
static const char sPaddedStringFormat[73] = "%s                                                                      ";
static const char sLogDebug09[10] = "debug-09\n";
static const char sLogMenuMode01Start[18] = "menumode01=Start\n";
static const char sLogMenuMode03Start[18] = "menumode03=Start\n";
static const char sLogSubParts[29] = "Sub=%d %d %d custm=%d po=%d\n";
static const char sLogList1[23] = "List1=%d po=%d wep=%d\n";
static const char sLogList2[23] = "List2=%d po=%d wep=%d\n";
static const char sLogMenuMode5End[15] = "menumode5=End\n";
static const char sLogZoidColor[15] = "ZoidColor=%d \n";
static const char sLogMenu1p10[15] = "menu1p 1-0 %d\n";
static const char sJObjQuaternionAssert[37] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static const u8 r6164[12] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#define TTL_MAIN_CPP
#include "ttl_main_data.h"

extern f32 lookCamY;
extern f32 rPadX(void);
extern void eyeCamPos(void);
extern void HSD_CObjSetInterest(struct HSD_CObj *cobj, Vec3 *interest);
extern void zdDispCursor(void);

static inline void menuLookCamSet(Vec3 *pos, f32 y)
{
    pos->x = menubackintpos.x;
    pos->y = menubackintpos.y + y;
    pos->z = menubackintpos.z;
    lookCam.x = pos->x;
    lookCam.y = pos->y + lookCamY;
    lookCam.z = pos->z;
}

void menu_sDispBattleFarmZoid(void)
{
    s16 zoid = IveSave[0].selected_zoid;
    HSD_JObj *source;
    HSD_JObj *target;

    rPadX();
    {
        Vec3 eye;
        Vec3 interest;
        f32 roll;
        Vec3 pos = { 0.0f, 0.0f, 0.0f };
        Vec3 up;

        if (zoid != -1 && Zoid[0].joint != 0) {
            eyeCamPos();
            menuLookCamSet(&pos, 0.0f);
            eyeCamPos();
            HSD_CObjSetInterest(menu_back1p->camera, &lookCam);
            source = GetChild(menu_back1p->models[1], 0, 2, -1, -1, -1);
            target = Zoid[0].joint;
            jobjAnim(target);
            jobjCopyPos(source, target);
            target->matrix[0][0] = source->matrix[0][0];
            target->matrix[0][1] = source->matrix[0][1];
            target->matrix[0][2] = source->matrix[0][2];
            target->matrix[0][3] = source->matrix[0][3];
            target->matrix[1][0] = source->matrix[1][0];
            target->matrix[1][1] = source->matrix[1][1];
            target->matrix[1][2] = source->matrix[1][2];
            target->matrix[1][3] = source->matrix[1][3];
            target->matrix[2][0] = source->matrix[2][0];
            target->matrix[2][1] = source->matrix[2][1];
            target->matrix[2][2] = source->matrix[2][2];
            target->matrix[2][3] = source->matrix[2][3];
            HSD_JObjDispAll(target, 0, 7, 0);
            zdDispCursor();
        }
    }
}

static const char sLogMenuCamPos[29] = "Menu CamPos x=%f y=%f z=%f \n";
static const char sLogMenuZoidBattleEntryOn[25] = "MenuZoidBattle Entry On\n";
static const char sLogMenuZoidBattleEntryOk[25] = "MenuZoidBattle Entry Ok\n";
static const char sLogMenuZoidBattleEntry[22] = "MenuZoidBattle Entry\n";
static const char sLogMenuZoidBattleFarm[21] = "MenuZoidBattle Farm\n";

#pragma readonly_strings on
s16 TEA_menufnc(s16 *menup, s16 *menust, s16 maxn, s16 max)
{
    s16 p;
    s16 s;
    s16 value;

    if (*menust == -1) {
        value = *menup;
        *menust = value;
        *menup = 0;
        if (*menup + *menust > maxn - max) {
            *menup = *menust;
            *menust = maxn - max;
        } else {
            *menup = value;
            *menust = 0;
        }
        if (*menup + 1 > max) {
            if (*menup + max >= maxn) {
                *menust = maxn - max;
                *menup = value - *menust;
            } else {
                *menust = value;
                *menup = 0;
            }
        } else {
            *menust = 0;
        }
        OSReport("menupSet=%d maxh=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
    }
    if (sPad1->pressed_up != 0) {
        SeSelectB();
        if (*menup == 0) {
            if (*menust > 0)
                (*menust)--;
            OSReport("Menu UP menup=%d max=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
            return *menust;
        }
        (*menup)--;
        OSReport("Menu UP menup=%d max=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
        return *menust + *menup;
    }
    if (sPad1->pressed_down != 0) {
        SeSelectB();
        p = *menup;
        if (p == max - 1) {
            s = *menust;
            if (p + s >= maxn - 1)
                return p + s;
            *menust = s + 1;
            OSReport("Menu Down Lst menup=%d max=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
            return *menust + *menup;
        }
        *menup = p + 1;
        OSReport("Menu Down menup=%d max=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
        return *menust + *menup;
    }
    if (sPad1->right != 0)
        SeSelectB();
    if (sPad1->left != 0)
        SeSelectB();
    return *menust + *menup;
}
#pragma readonly_strings off

#pragma readonly_strings on
s32 TEA_menufnc2p(s16 *menup, s16 *menust, s16 maxn, s16 max)
{
    s16 p;
    s16 s;
    s16 value;

    if (*menust == -1) {
        value = *menup;
        *menust = value;
        *menup = 0;
        if (*menup + *menust > maxn - max) {
            *menup = *menust;
            *menust = maxn - max;
        } else {
            *menup = value;
            *menust = 0;
        }
        if (*menup + 1 > max) {
            if (*menup + max >= maxn) {
                *menust = maxn - max;
                *menup = value - *menust;
            } else {
                *menust = value;
                *menup = 0;
            }
        } else {
            *menust = 0;
        }
        OSReport("menup2Set=%d maxh=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
    }
    if (sPad2->pressed_up != 0) {
        SeSelectB();
        if (*menup == 0) {
            if (*menust > 0)
                (*menust)--;
            OSReport("Menu2 UP menup=%d max=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
            return *menust;
        }
        (*menup)--;
        OSReport("Menu2 UP menup=%d max=%d menust=%d maxn=%d\n", *menup, max, *menust, maxn);
        return *menust + *menup;
    }
    if (sPad2->pressed_down != 0) {
        SeSelectB();
        p = *menup;
        if (p == max - 1) {
            s = *menust;
            if (p + s >= maxn - 1)
                return p + s;
            *menust = s + 1;
            OSReport("Menu Down Last menup=%d max=%d\n", *menup, max);
            return *menust + *menup;
        }
        *menup = p + 1;
        OSReport("Menu Down ok menup=%d max=%d\n", *menup, max);
        return *menust + *menup;
    }
    if (sPad2->right != 0)
        SeSelectB();
    if (sPad2->left != 0)
        SeSelectB();
    return *menust + *menup;
}
#pragma readonly_strings off

#pragma readonly_strings on
s32 TEA_menufnc12p(s16 *menup, s16 *menust, s16 maxn, s16 max)
{
    if (*menust == -1) {
        *menust = *menup;
        *menup = 0;
        if (*menup + *menust > maxn - max) {
            *menust = maxn - max;
            *menup = max - 1;
        } else {
            *menup = 0;
        }
    }
    if (sPad1->pressed_up != 0 || sPad2->pressed_up != 0) {
        SeSelectB();
        if (*menup == 0) {
            if (*menust > 0) {
                (*menust)--;
                OSReport("menus=%d:menup=%d menu=%d \n", *menust, *menup, *menust);
                return *menust;
            }
            *menust = maxn - max;
            *menup = max - 1;
            OSReport("menus=%d:menup=%d menu=%d \n", *menust, *menup, (s16)(*menust + *menup));
            return *menust + *menup;
        }
        (*menup)--;
        OSReport("menus=%d:menup=%d menu=%d \n", *menust, *menup, (s16)(*menust + *menup));
        return *menust + *menup;
    }
    if (sPad1->pressed_down != 0 || sPad2->pressed_down != 0) {
        SeSelectB();
        if (*menup == max - 1) {
            if (*menup + *menust >= maxn - 1) {
                *menup = 0;
                *menust = 0;
                OSReport("menus=%d:menup=%d menu=%d \n", *menust, *menup, (s16)(*menust + *menup));
                return *menust + *menup;
            }
            (*menust)++;
            OSReport("menus=%d:menup=%d menu=%d \n", *menust, *menup, (s16)(*menust + *menup));
            return *menust + *menup;
        }
        (*menup)++;
        OSReport("menus=%d:menup=%d menu=%d \n", *menust, *menup, (s16)(*menust + *menup));
        return *menust + *menup;
    }
    if (sPad2->right != 0)
        SeSelectB();
    if (sPad2->left != 0)
        SeSelectB();
    return *menust + *menup;
}
#pragma readonly_strings off

static const char sOutOfMemoryBackShop[30] = "out of memory. menu back shop";
static const char sOutOfMemory1Shop[27] = "out of memory. menu 1 shop";
static const char sLogWhoErr[9] = "who=err\n";
static const char sLogPartsDash[11] = "parts --- ";
static const char sLogMenuSetCl[19] = "menu set cl =%2d \n";
static const char sLogMineChangeColor[21] = "mine change col=%d \n";
static const char sLogPartnerChangeColor[24] = "partnar change col=%d \n";
static const char sLogErr2Etczn[34] = "Err 2:etczn=%d cl[3]=%d znum=%d \n";
static const char sLogErr2[10] = "Err 2:%d\n";
static const char sLogPartsColorMax[31] = "po=%d parts=%d col=%d max=%d \n";
static const u8 r8311[12] = { 0x00, 0x01, 0x04, 0x01, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const char sNoEntryLabel[9] = "NO ENTRY";
static const char sVictoryConditionLabel[9] = "\x8f\x9f\x97\x98\x8f\xf0\x8c\x8f";
static const char sDefeatConditionLabel[9] = "\x94s\x96k\x8f\xf0\x8c\x8f";
static const char sMapInfoError[15] = "map info error";
static const char sLogMapInfoError[16] = "map info error\n";
static const char sFarmPathFormat[29] = "menu/battle_menu/farm/%s.dat";
static const char sPicturePathFormat[20] = "menu/picture/%s.dat";
static const char sLogZoidPathId[14] = "zoid =%s %d \n";
static const char sLogPart[12] = "part = %d \n";
static const char sLogStageStage2[98] = "=================================\n stage=%d , stage2=%d \n=======================================\n";
static const char sLogStageVariantOver[50] = "mg  stage*3 + stage2  stage2 over(0,1,2)  is %d \n";
static const char sVsBgLogoPath[28] = "menu/vs_menu/new/bglogo.dat";
static const char sLogMenu1pNone[13] = "menu1p non \n";
static const char sLogMenuMission[13] = "MenuMission\n";
static const char sLogNow[16] = "Now= %d %d %d \n";
static const char sLogMissionStartDisp00[34] = "mis-start-disp-00---------------\n";
static const char sLogMissionStartDisp01[34] = "mis-start-disp-01---------------\n";
static const char sLogMissionStartDisp02[34] = "mis-start-disp-02---------------\n";
static const char sLogMissionStartDisp03[34] = "mis-start-disp-03---------------\n";
static const char sLogMissionStartDisp04[34] = "mis-start-disp-04---------------\n";
static const char sLogManZoidStage[28] = "man=%s zoid=%s stage=%d:%d\n";
static const char sLogGameZoidZ[26] = "z0=%d z1=%d z5=%d z6=%d \n";
static const char sLogGameZoidP[26] = "p0=%d p1=%d p2=%d p3=%d \n";
static const u8 r9730[12] = { 0x00, 0x01, 0x04, 0x01, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const char sLogPersonPos[19] = "person=%d pos=%d \n";
static const char sLogFlagErr[23] = "FLAG ERR fl=%d dat=%d\n";
static const char sLogFlagSet[21] = "FLAG SET FL=%d D=%d\n";

void ttl_demoflagset(s16 flag, s16 value)
{
    if (flag < 0 || flag >= 50)
        OSReport(sLogFlagErr, flag, value);
    IveSave[0].system_flags[flag] = (s8)value;
    IveSave[4].system_flags[flag] = (s8)value;
    if (flag == 0 && value == 100) {
        IveSave[0].stage = (s8)value;
        GameMode.map = value;
    }
    OSReport(sLogFlagSet, flag, value);
}

#pragma readonly_strings on
void menu_MissionDemo(void)
{
    menudemop = 0;
    menudemoC = 0;
    menudemocha[1] = -1;
    menudemocha[4] = -1;
    menudemofase[0] = -1;
    menudemofase[1] = -1;
    menudemomsg = -1;
    menudemobg = -1;
    menudemobgm = -1;
    menudemovno = -1;
    menudemokeywait = 0;
    menudemojmp = -1;
    menudemoselmsg[0] = -1;
    menudemoselmsg[1] = -1;
    menudemoseljmp[0] = -1;
    menudemoseljmp[1] = -1;
    menudemocur = 0;
    menudemoanmend[0] = 0;
    menudemoanmend[1] = 0;
    menudemocharain = 0;
    menudemoselect = -1;
    menudemoend = 0;
    TeaBgm(30);
    TEA_AudioSeqVol(0, 0);
    menu_MissionDemoLoadScrFile(GameMode.map);
    OSReport("DemoLoadEnd\n");
    OSReport("DemoLoadEnd\n");
    OSReport("DemoLoadEnd\n");
    OSReport("DemoLoadEnd\n");
    OSReport("DemoLoadEnd\n");
    OSReport("DemoLoadEnd\n");
    OSReport("DemoLoadEnd\n");
    menudemop = 0;
    menudemoend = 1;
    menudemoC = 0;
    MenuDemoSkipFlag = 0;
    menu_MissionDemoScrPlay1();
    while (1) {
        sPadAll();
        menu_sDispMissionDemo();
        if (sPad1->pressed_start != 0) {
            if (MenuDemoSkipFlag == 1)
                MenuDemoSkipFlag = 0;
            else
                MenuDemoSkipFlag = 1;
        }
        if (MenuDemoSkipFlag == 1)
            menudemokeywait = 0;
        if (sPad1->pressed_a != 0) {
            SeRetDemo();
            if (menudemokeywait == 1 && menudemoanmend[0] == 1 && menudemoanmend[1] == 1) {
                menudemop++;
                if (menu_MissionDemoScrPlay1() == 0)
                    break;
            }
        }
        if (menudemokeywait == 0 && menudemoanmend[0] == 1 && menudemoanmend[1] == 1) {
            menudemop++;
            if (menu_MissionDemoScrPlay1() == 0)
                break;
        }
    }
    TeaBgm(-1);
    menudemoend = 0;
    menu_sDispMissionDemo();
    HSD_VIWaitEFBFlush();
    OSReport("demo End\n");
}
#pragma readonly_strings off

static const char sLogDemoNoMode[21] = "demo no=%d mode=%d \n";
static const char sLogFlagJmp[28] = "FLAG JMP FL=%d JMP=%d D=%d\n";
static const char sLogFlagJmpOk[15] = "FLAG JMP --OK\n";
static const char sLogPersonChange[27] = "\x90l\x95\xa8\x83`\x83" "F\x83\x93\x83W \x8d\xb6:%d \x89" "E:%d \n";

extern s16 menudemoselflg[2];
extern s16 menudemoseldat[2];
extern s16 TEA_BGMVOL;
extern s16 menuDemoSelectMenu(s32 selected);
extern void SeBuzzerC(void);
extern void SeRet(void);
extern void TEA_SeOn(u16 se, s32 a, s32 b);

#pragma push
#pragma dont_inline on
s32 menu_MissionDemoScrPlay1(void)
{
    s16 p;
    s16 cmd;
    s16 v;

    p = menudemop;
    cmd = Tea_demomsg[p].cmd;
    menudemokeywait = 0;
    menudemocur = 0;
    menudemoanmend[0] = 0;
    menudemoanmend[1] = 0;
    menudemoselect = -1;
    OSReport(sLogDemoNoMode, p, cmd);
    switch (cmd) {
    case -1:
        MenuDemoSkipFlag = 0;
        return 0;
    case -2:
        menudemoend = 1;
        MenuDemoSkipFlag = 0;
        memcpy(Tea_demomenu, &Tea_demomsg[menudemop], sizeof(DemoMsg));
        menudemoselmsg[0] = Tea_demomenu[1];
        menudemoseljmp[0] = Tea_demomenu[2];
        menudemoselflg[0] = Tea_demomenu[3];
        menudemoseldat[0] = Tea_demomenu[4];
        menudemoselmsg[1] = Tea_demomenu[6];
        menudemoseljmp[1] = Tea_demomenu[7];
        menudemoselflg[1] = Tea_demomenu[8];
        menudemoseldat[1] = Tea_demomenu[9];
        menudemoselect = -2;
        while (1) {
            menudemoselect = menuDemoSelectMenu(menudemoselect);
            menu_sDispMissionDemo();
            if (sPad1->pressed_a != 0) {
                if (menudemoselect != -2)
                    break;
                SeBuzzerC();
            }
        }
        SeRet();
        if (menudemoselflg[menudemoselect] != -1)
            ttl_demoflagset(menudemoselflg[menudemoselect], menudemoseldat[menudemoselect]);
        if (menudemoseljmp[menudemoselect] != -1) {
            menu_MissionDemoLoadScrFile(menudemoseljmp[menudemoselect]);
            menudemoselect = -1;
            menudemokeywait = 0;
            menudemop = -1;
            menudemocur = 0;
            menudemoanmend[0] = 0;
            menudemoanmend[1] = 0;
            return 1;
        }
        menudemop = p;
        menudemoselect = -1;
        menudemokeywait = 0;
        return 1;
    case -3:
        MenuDemoSkipFlag = 0;
        memcpy(Tea_demomenu, &Tea_demomsg[menudemop], sizeof(DemoMsg));
        OSReport(sLogFlagJmp, Tea_demomenu[3], Tea_demomenu[2], Tea_demomenu[4]);
        menudemoseljmp[0] = Tea_demomenu[2];
        menudemoselflg[0] = Tea_demomenu[3];
        menudemoseldat[0] = Tea_demomenu[4];
        if (menudemoselflg[0] != -1 && (s8)IveSave[0].system_flags[menudemoselflg[0]] == menudemoseldat[0]) {
            OSReport(sLogFlagJmpOk);
            if (menudemoseljmp[0] != -1) {
                menu_MissionDemoLoadScrFile(menudemoseljmp[0]);
                menudemop = -1;
                menudemokeywait = 0;
                menudemocur = 0;
                menudemoanmend[0] = 0;
                menudemoanmend[1] = 0;
                return 1;
            }
        }
        menudemop = p;
        menudemokeywait = 0;
        menudemoanmend[0] = 1;
        menudemoanmend[1] = 1;
        return 1;
    case -4:
        memcpy(Tea_demomenu, &Tea_demomsg[menudemop], sizeof(DemoMsg));
        OSReport(sLogFlagSet, Tea_demomenu[3], Tea_demomenu[4]);
        menudemoselflg[0] = Tea_demomenu[3];
        menudemoseldat[0] = Tea_demomenu[4];
        if (menudemoselflg[0] != -1)
            ttl_demoflagset(menudemoselflg[0], menudemoseldat[0]);
        menudemop = p;
        menudemokeywait = 0;
        menudemoanmend[0] = 1;
        menudemoanmend[1] = 1;
        return 1;
    default:
        menudemoend = 1;
        menudemoC = menudemop;
        OSReport(sLogPersonChange, Tea_demomsg[menudemop].cha0, Tea_demomsg[menudemop].cha1);
        if (Tea_demomsg[menudemop].cha0 == -1)
            Tea_demomsg[menudemop].cha0 = 2;
        if (menudemofase[0] != Tea_demomsg[menudemop].cha0) {
            menudemocha[1] = Tea_demomsg[menudemop].cha0;
            if (menudemocha[1] == -1)
                menudemocha[1] = 2;
            menudemocha[0] = 1;
            menudemocharain = 0;
        }
        if (Tea_demomsg[menudemop].cha1 == -1)
            Tea_demomsg[menudemop].cha1 = 2;
        if (menudemofase[1] != Tea_demomsg[menudemop].cha1) {
            menudemocha[4] = Tea_demomsg[menudemop].cha1;
            if (menudemocha[4] == -1)
                menudemocha[4] = 2;
            menudemocha[3] = 1;
            menudemocharain = 0;
        }
        menudemobg = Tea_demomsg[menudemop].bg;
        v = Tea_demomsg[menudemop].msg;
        if (v == -2 || menudemomsg == v) {
            menudemokeywait = 0;
            menudemocharain = 1;
            menudemocur = 0;
        } else {
            menudemomsg = v;
            if (v != -1) {
                menudemokeywait = 1;
                menudemocur = 1;
            } else {
                menudemokeywait = 0;
                menudemocur = 0;
            }
        }
        v = Tea_demomsg[menudemop].bgm;
        if (v == -2) {
            if (v < 1000) {
                menudemobgm = v;
            } else if (v - 1000 != -1) {
                TEA_SeOn(v - 1000, 0, 0);
            }
        } else {
            if (v < 1000) {
                menudemobgm = v;
                TeaBgm(menudemobgm);
                TEA_AudioSeqVol((u8)TEA_BGMVOL, 1);
            } else if (v - 1000 != -1) {
                TEA_SeOn(v - 1000, 0, 0);
            }
        }
        menudemovno = Tea_demomsg[menudemop].vno;
        return 1;
    }
}
#pragma pop




static const char sDemoScriptPathFormat[23] = "etc/demo/demo_%03d.bin";
static const char sLogDemoFileName[61] = "=========================================================\n%s";

void menu_MissionDemoLoadScrFile(s16 stage)
{
    char filename[80];
    void *data;

    sprintf(filename, sDemoScriptPathFormat, stage);
    data = sReadFileU(filename, 0);
    memcpy(Tea_demomsg, data, sizeof(Tea_demomsg));
    free(data);
    OSReport(sLogDemoFileName, filename);
    menudemop = 0;
    menudemocha[1] = -1;
    menudemocha[4] = -1;
    GameMode.map = stage;
    IveSave[0].stage = (s8)stage;
    if (stage != 100)
        rdMapInfo(1, stage);
}

static const char sSupplyListLabel[12] = "SUPPLY LIST";
static const char sNewPartsLabel[10] = "NEW PARTS";
static const char sNewZoidsLabel[10] = "NEW ZOIDS";

extern s32 anmN;
extern void menu_sDispBattleFarmBack(void);
extern void HSD_SetZSortMode(s32, s32);
extern void sMakeMatrix(HSD_JObj *joint);

s32 menu_sDispMissionHokyu(MapInfo *info, ModelArchive *archive, s32 done)
{
    s32 i;
    s32 k;
    s32 sub;
    s32 part;
    HSD_JObj *zj;
    s32 unused[2];
    s32 zoid;
    HSD_JObj *jobj;
    s32 anim;
    HSD_JObj *root;

    if (info == 0)
        return 1;
    if (menu1p == 0)
        return 1;
    root = archive->models[5];
    HSD_SetZSortMode(1, 1);
    HSD_SetZSortMode(1, 1);
    if (HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_back1p->lights);
        HSD_LObjSetupInit(menu_back1p->camera);
        GXSetCullMode(2);
        menu_sDispBattleFarmBack();
        menu_sDispBattleFarmZoid();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_SetZSortMode(0, 0);
    if (HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        if (archive != 0) {
            if (jobjAnim(archive->models[5]) != 0) {
                if (done != 0) {
                    if (anmN == 3) {
                        SetAnimArc2(archive, 5, 0);
                        anmN = 0;
                    } else {
                        SetAnimArc2(archive, 5, 3);
                        anmN = 3;
                    }
                } else {
                    SetAnimArc2(archive, 5, 2);
                    anmN = 2;
                }
            }
            if (anmN != 0) {
                jobjDispAll(archive->models[5]);
                sMakeMatrix(root);
                jobj = GetChild(root, 0, 0, -1, -1, -1);
                putAscJobj(jobj, 4, (char *)sSupplyListLabel);
                jobj = GetChild(root, 0, 1, -1, -1, -1);
                putAscJobj(jobj, 4, (char *)sNewPartsLabel);
                jobj = GetChild(root, 0, 2, -1, -1, -1);
                putAscJobj(jobj, 4, (char *)sNewZoidsLabel);
            }
            for (i = 0, k = 0; i < 2; i++) {
                zoid = info->new_zoids[i];
                if (zoid != -1) {
                    zj = GetChild(menu_zoidp[zoid]->models[0], 0, 1, -1, -1, -1);
                    jobjCopyPos(GetChild(root, 0, 2, k, -1, -1), zj);
                    jobjDispAll(zj);
                    zj->matrix[0][3] += 1.0f;
                    putAscJobj(zj, 0, Tea_zoiddat[zoid].name);
                    k++;
                }
            }
            for (i = 0, k = 0; i < 8; i++) {
                if (k >= 6)
                    break;
                part = info->new_parts[i];
                if (part > 0) {
                    jobj = menu1p->models[11];
                    jobjCopyPos(GetChild(root, 0, 1, k, -1, -1), jobj);
                    sMakeMatrix(jobj);
                    sub = 1;
                    anim = Tea_partsdat[part].icon;
                    if (Tea_partsdat[part].category == 2)
                        sub = 3;
                    if (Tea_partsdat[part].category == 3)
                        sub = 4;
                    if (sub == 1 && anim > 16)
                        anim = 16;
                    if (sub == 3 && anim > 4)
                        anim = 4;
                    if (sub == 4 && anim > 8)
                        anim = 8;
                    jobjDispAll(GetChild(jobj, 0, sub, anim, -1, -1));
                    putAscJobj(GetChild(jobj, 0, 2, -1, -1, -1), 2, Tea_partsdat[part].english_name);
                    k++;
                }
            }
        }
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
    if (anmN == 0 && done != 0)
        return 1;
    return 0;
}


static const char sDetailArchivePath[28] = "menu/battle_menu/detail.dat";
static const char sLogHokyuStart[24] = "hokyu start   --------\n";
static const char sLogMapNo[12] = "map no= %d\n";
static const char sLogGameStart101[15] = "GameStart 101\n";
static const char sLogGameStartMission[69] = "GameStart Mission stage=%d type=%d win=%d single=%d zoid=%d man=%d \n";
static const char sLogGameStartLoadErr[19] = "GameStart LoadErr\n";

extern s64 gametimestart;
extern u32 __OSBusClock : 0x800000F8;
extern s32 sCamNN, sCamNN2;
extern s8 menumodeShop;
extern s32 menuCursor;
extern s32 menuParticles;
extern void TEA_SoundMasterVol(s32 vol, s32 mode);
extern void TEA_SetTimerInit(void);
extern void TEA_VoiceOn(u8 character, s32 voice);
extern u32 VIGetRetraceCount(void);
extern s32 HSD_Rand(void);
extern s64 OSGetTime(void);
extern s16 menufncPushStartMain(void);
extern s16 menufncZoidBattleNewGameLoadGame(void);
extern s16 menufncZoidMissionEmpireCountry(void);
extern s16 menufncZoidBattleSingleTeamGame(void);
extern void menuZoidMission_NonSaveData_InitData(void);
extern void menuZoidBattle_NonSaveData_InitData(void);
extern void menuZoidMission_EndSaveData_start(void);
extern s32 ttlMenuBatSaveLoad(s32 mode);
extern s32 ttlMenuSystemMemCardSave(void);
extern void menufncZoid_ConfigMenu(void);
extern void configGet(void);
extern void SeRet(void);

#pragma push
#pragma dont_inline on
s16 menufncPushStart(void)
{
    s32 unused[1];
    GXColor black;
    s32 ret;
    s16 r;
    s32 i;

    if (ttlLight != 0)
        HSD_LObjRemoveAll(ttlLight);
    ttlLight = 0;
    menuCursor = 0;
    menuParticles = 0;
    TEA_SoundMasterVol(127, 0);
    configGet();
    TeaBgm(0);
    ttlMenuLoadParts(6);
    TEA_SetTimerInit();
    menumodeShop = 0;
    menumode = 0;
    menudispyesnoanm.state = 1;
    menudispyesnoanm.anim = 1;
    menutitleanm[0].mode = 0;
    menutitleanm[0].state = 2;
    menutitleanm[0].next = 2;
    menutitleanm[9].mode = 0;
    menutitleanm[9].state = 0;
    menutitleanm[9].next = 0;
    menutitleanm[1].mode = 0;
    menutitleanm[1].state = 2;
    menutitleanm[1].next = 2;
    menutitleanm[1].mode = 1;
    menutitleanm[1].state = 3;
    menuanmend = 0;
    menumode = 0;
    menutitleanm[0].state = 0;
    menutitleanm[9].mode = 1;
    menu_BlackInWhiteSet();
    while (menutitleanm[1].state != 2)
        menu_sDispStart();
    menumode = 1;
    menu_WhiteOutBlack();
    u8 voice[8] = { 0, 1, 2, 4, 13, 17, 22, 23 };
    s32 pad;
    TEA_VoiceOn(voice[(u8)VIGetRetraceCount() % 8], 17);
    while (1) {
        sPadAll();
        HSD_Rand();
        if (sPad1->pressed_start != 0 || sPad2->pressed_start != 0)
            break;
        menu_sDispStart();
    }
    SeRet();
    menuanmend = 0;
    menutitleanm[0].mode = 1;
    menutitleanm[0].state = 2;
    while (1) {
        if (menutitleanm[0].mode == 0)
            break;
        menu_sDispStart();
    }
    menutitleanm[0].mode = 0;
    menuanmend = 0;
    menutitleanm[9].mode = 1;
    menutitleanm[9].state = 0;
    while (1) {
        menu_sDispStart();
        if (menutitleanm[9].state == 2)
            break;
        if (menutitleanm[9].state == 0)
            menutitleanm[9].state = 1;
    }
    menuanmend = 0;
    menumode = 2;
    while (1) {
        if (menumode == 2) {
            r = menufncPushStartMain();
            if (r == 0) {
                r = menufncZoidBattleNewGameLoadGame();
                GameMode.game_type = GAME_TYPE_MISSION;
                if (r == -1) {
                    menumode = 2;
                } else if (r == 0) {
                    GameMode.game_type = GAME_TYPE_MISSION;
                    gametimestart = OSGetTime() / (__OSBusClock / 4);
                    IveSave[0].play_time = 0;
                    menumode = 6;
                    GameMode.map = 0;
                    IveSave[0].stage = 0;
                    IveSave[0].game_type = GAME_TYPE_MISSION;
                    if (menufncZoidMissionEmpireCountry() == -1) {
                        menumode = 2;
                        continue;
                    }
                    menuZoidMission_NonSaveData_InitData();
                    GameMode.game_type = GAME_TYPE_MISSION;
                    GameMode.win = 0;
                    GameMode.map_no = 0;
                    GameMode.win = 0;
                    ret = 101;
                    OSReport(sLogGameStart101);
                    break;
                } else if (r == 1) {
                    GameMode.game_type = GAME_TYPE_MISSION;
                    GameMode.win = 0;
                    GameMode.map = 0;
                    GameMode.map_no = 12;
                    memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                    if (ttlMemCardChkStartNew() == 0) {
                        GameMode.game_type = GAME_TYPE_MISSION;
                        menumode = 2;
                        continue;
                    }
                    if (ttlMenuBatSaveLoad(0) == 1) {
                        for (i = 0; i < 60; i++) {
                            HSD_StartRender(0);
                            HSD_EndRender();
                            debugmenudraw();
                            vsyncN++;
                        }
                        menudispyesnoflag = 0;
                        memcpy(&IveSave[0], &IveSave[2], sizeof(GameSaveRecord));
                        GameMode.map = IveSave[0].stage;
                        rdMapInfo(1, GameMode.map);
                        GameMode.map_no = IveSave[0].map_no;
                        IveSave[0].game_type = GAME_TYPE_MISSION;
                        GameMode.game_type = GAME_TYPE_MISSION;
                        IveSave[0].win = 1;
                        GameMode.win = 1;
                        GameMode.country = IveSave[0].country;
                        IveSave[0].single_team = 0;
                        menuZoidBattleModeSingleTeam = 0;
                        IveSave[0].partner_zoid = -1;
                        IveSave[0].partner_person = 57;
                        if ((s8)IveSave[0].field_166B == 0) {
                            while (menufncZoidMissionEmpireCountry() == -1)
                                ;
                            if (IveSave[0].country == 1) {
                                IveSave[0].stage = 0;
                                GameMode.map = 0;
                            } else {
                                IveSave[0].stage = 19;
                                GameMode.map = 19;
                            }
                            rdMapInfo(1, GameMode.map);
                            menuZoidMission_EndSaveData_start();
                            GameMode.game_type = GAME_TYPE_MISSION;
                            GameMode.win = 0;
                        }
                        OSReport(sLogGameStartMission, IveSave[0].stage, IveSave[0].game_type, (s8)IveSave[0].win, (s8)IveSave[0].single_team, IveSave[0].selected_zoid, IveSave[0].selected_person);
                        if (menu1p != 0)
                            PurgeArc2(menu1p);
                        menu1p = 0;
                        GameMode.game_type = GAME_TYPE_MISSION;
                        return 107;
                    }
                    GameMode.game_type = GAME_TYPE_MISSION;
                    menudispyesnoflag = 0;
                    OSReport(sLogGameStartLoadErr);
                    menumode = 2;
                    GameMode.game_type = GAME_TYPE_MISSION;
                    menumode = 2;
                    continue;
                }
                GameMode.game_type = GAME_TYPE_MISSION;
                menumode = 2;
                continue;
            }
            if (r == 1) {
                menumode = 3;
            } else if (r == 2) {
                menuZoidBattleModeSingleTeam = 1;
                menumode = 5;
            } else if (r == 3) {
                menufncZoid_ConfigMenu();
                memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                memcpy(&IveSave[3], &IveSaveFlag, sizeof(GameSaveRecord));
                memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                if (ttlMemCardChkStartNew() == 1) {
                    if (ttlMenuSaveLoadexistenceDataStartNew0() == 1) {
                        memcpy(&IveSaveFlag, &IveSave[3], sizeof(GameSaveRecord));
                        ttlMenuSystemMemCardSave();
                        ttlMemCardChkStartNew();
                    } else {
                        memcpy(&IveSaveFlag, &IveSaveFlagBak, sizeof(GameSaveRecord));
                        configGet();
                    }
                } else {
                    memcpy(&IveSaveFlag, &IveSaveFlagBak, sizeof(GameSaveRecord));
                    configGet();
                }
                TeaBgm(0);
            }
        }
        if (menumode == 3) {
            r = menufncZoidBattleNewGameLoadGame();
            if (r == -1)
                menumode = 2;
            menuZoidBattleModeSingleTeam = 1;
            menuZoidBattleStage = -1;
            ret = 200;
            if (r == 0) {
                gametimestart = OSGetTime() / (__OSBusClock / 4);
                menuZoidBattle_NonSaveData_InitData();
                GameMode.game_type = GAME_TYPE_BATTLE;
                GameMode.win = 0;
                IveSave[0].field_166E = 0;
                GameMode.map = 0;
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[0];
                IveSave[0].selected_zoid_slot = 0;
                IveSave[0].partner_zoid = IveSave[0].owned_zoids[1];
                IveSave[0].partner_zoid_slot = 1;
                IveSave[0].selected_person = 0;
                IveSave[0].partner_person = 1;
                IveSave[0].country = 0;
                GameMode.country = 0;
                GameMode.game_type = GAME_TYPE_BATTLE;
                GameMode.win = 0;
                GameMode.map_no = 12;
                GameMode.map = 0;
                IveSave[0].stage = GameMode.map;
                IveSave[0].map_no = GameMode.map_no;
                IveSave[0].game_type = GameMode.game_type;
                IveSave[0].win = (s8)GameMode.win;
                IveSave[0].single_team = menuZoidBattleModeSingleTeam;
                IveSave[0].play_time = 0;
                break;
            }
            if (r == 1) {
                memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                if (ttlMemCardChkStartNew() == 0)
                    continue;
                GameMode.game_type = GAME_TYPE_BATTLE;
                GameMode.win = 0;
                GameMode.map = 0;
                GameMode.map_no = 12;
                if (ttlMenuBatSaveLoad(0) != 1)
                    continue;
                memcpy(&IveSave[0], &IveSave[2], sizeof(GameSaveRecord));
                GameMode.map = IveSave[0].stage;
                menuZoidBattleStage = IveSave[0].stage;
                GameMode.map_no = IveSave[0].map_no;
                IveSave[0].game_type = GAME_TYPE_BATTLE;
                GameMode.game_type = GAME_TYPE_BATTLE;
                IveSave[0].win = 1;
                GameMode.win = 1;
                menuZoidBattleModeSingleTeam = IveSave[0].single_team;
                GameMode.win = 1;
                if ((s8)IveSave[0].field_166B == 1)
                    ret = 222;
                break;
            }
        }
        if (menumode == 4) {
            r = menufncZoidBattleSingleTeamGame();
            if (r == -1)
                menumode = 3;
            ret = 200;
            if (r == 0)
                break;
            if (r == 1)
                break;
        }
        if (menumode == 5) {
            menuZoidBattleModeSingleTeam = 1;
            GameMode.game_type = GAME_TYPE_VS;
            ret = 300;
            sCamNN2 = 2;
            sCamNN = 2;
            menuZoidBattleModeSingleTeam = 1;
            break;
        }
    }
    menu_BlackInWhite();
    menumode = 0;
    menu_WhiteOutBlack();
    menuanmend = 0;
    black = (GXColor){ 0, 0, 0, 0 };
    HSD_VIData.current.vi.clear_clr = black;
    TeaBgm(-1);
    if (menu1p != 0)
        PurgeArc2(menu1p);
    menu1p = 0;
    return ret;
}
#pragma pop





static const char sLogMenuMainEnd[14] = "menumain end\n";
static const char sLogMenuVs[9] = "menu VS\n";
static const char sLogVsEntry[10] = "VS ENTRY\n";
static const char sLogVsEntrySt[13] = "VS ENTRY ST\n";
static const char sLogNoSaveLoad[14] = "SaveLoad\x96\xb3\x82\xb5\n";
static const char sLogSaveLoadEnd[13] = "SaveLoadEnd\n";
static const char sMapPictureFormat[23] = "menu/picture/m%02d.dat";

#define TTL_MAIN_DATA_TAIL
#include "ttl_main_data.h"

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
extern s16 flag_VsFarmPlayer1Icon;
extern s16 flag_VsFarmPlayer2Icon;
extern s16 flag_VsFarmEntryButton[2];
extern s16 flag_VsFarmStageButton[2];
extern s16 flag_VsFarmBattleButton[2];
extern s16 flag_VsFarmExitButton[2];
extern s32 flag_VsFarmEntryStageBattleExit;
extern ModelArchive *menu1p_map;
extern s32 menuretno;
extern s8 menufarmmode;
extern s32 menuCursor;
extern s32 menuParticles;
extern s32 menudispyesnopoint;
extern void menuSetTitle(s16 type);
extern void menuSetTitleButton(s16 type);
extern void TEA_setvsync(void);
extern void menu_VsFarmMapLoad(s32 map);
extern void ttlMenuAllPurge(void);
extern void menu_TITLE_dispVs(s32 state);
extern s32 menufncZoidVsMenuEntry(void);
extern s32 menuYesNo(s32 selected, const char *first, const char *second);
extern char *GetMenuMsgAdr(s16 message);
extern s16 TEA_menufnc(s16 *menup, s16 *menust, s16 maxn, s16 max);
extern void menuZoidBattleGoPartsOptSet_GameZoid(s16 game, s16 save, s16 slot, s32 flag);
extern void SeRet(void);

s32 menufncZoidVsMenu(void)
{
    s32 pad0[6];
    s8 maplist[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    s32 i;
    s16 j;

    menuCursor = 0;
    menuParticles = 0;
    menumode = 0;
    for (i = 0; i < 20; i++)
        menumodeanm[i] = 0;
    for (i = 0; i < 20; i++) {
        menufarmanm[i] = 2;
        menufarmanmold[i] = 2;
    }
    OSReport("MenuZoidVs\n");
    vsyncN = 0;
    flag_VsFarmPlayer1Icon = 0;
    flag_VsFarmPlayer2Icon = 2;
    TeaBgm(7);
    menuSetTitle(0);
    OSReport("title aaaaa");
    menuSetTitleButton(11);
    TEA_setvsync();
    menufarmmode = 0;
    menumodeanm[0] = 0;
    menufarmanm[0] = 0;
    menufarmcl[0] = 0;
    menufarmsl[0] = 0;
    menufarmst[0] = 0;
    menufarmmh[0] = 3;
    menufarmmn[0] = 3;
    menufarmcl[1] = 0;
    menufarmsl[1] = 0;
    menufarmst[1] = 0;
    menufarmmh[1] = 3;
    menufarmmn[1] = 3;
    menufarmcl[2] = 0;
    menufarmsl[2] = 0;
    menufarmst[2] = 0;
    menufarmmh[2] = 2;
    menufarmmn[2] = 2;
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 2;
    menufarmmn[3] = 2;
    menufarmcl[4] = 0;
    menufarmsl[4] = 0;
    menufarmst[4] = 0;
    menufarmmh[4] = 2;
    menufarmmn[4] = 2;
    menubackanm[0].state = 1;
    menubackanm[0].cur = 1;
    menubackanm[0].old = 0;
    GameMode.map = 1;
    menu_VsFarmMapLoad(maplist[GameMode.map]);
    flag_VsFarmEntryButton[1] = 0;
    flag_VsFarmEntryButton[0] = 1;
    flag_VsFarmStageButton[1] = 0;
    flag_VsFarmStageButton[0] = 1;
    flag_VsFarmBattleButton[1] = 0;
    flag_VsFarmBattleButton[0] = 1;
    flag_VsFarmExitButton[1] = 0;
    flag_VsFarmExitButton[0] = 1;
    flag_VsFarmEntryStageBattleExit = 1;
    for (i = 1; i <= 9; i++)
        menufarmanm[i] = 0;
    memcpy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
    for (i = 0; i < 8; i++) {
        menumodeanm[i] = 1;
        menufarmanm[i] = 0;
    }
    menucuranm = 1;
    OSReport("VsFarm 01 \n");
    while (1) {
        sPadAll();
        for (j = 0; j < 2; j++) {
            if (j == 0)
                menufarmcl[j] = TEA_menufnc(&menufarmsl[j], &menufarmst[j], menufarmmn[j], menufarmmh[j]);
            if (j == 1)
                menufarmcl[j] = (u16)TEA_menufnc2p(&menufarmsl[j], &menufarmst[j], menufarmmn[j], menufarmmh[j]);
        }
        menu_sDispVsFarm();
        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0) {
            menudispyesnoflag = 1;
            menudispyesnopoint = 1;
            do {
                sPadAll();
                menudispyesnopoint = menuYesNo(menudispyesnopoint, "", GetMenuMsgAdr(MENU_MSG_QUIT_VS_PROMPT));
                menu_sDispVsFarm();
            } while (sPad1->pressed_a == 0 && sPad2->pressed_a == 0);
            menudispyesnoflag = 0;
            SeRet();
            if (menudispyesnopoint != 0) {
                if (menu1p_map != 0) {
                    PurgeArc2(menu1p_map);
                    menu1p_map = 0;
                }
                TeaBgm(-1);
                ttlMenuAllPurge();
                menuretno = 8;
                return 8;
            }
        } else if ((menufarmcl[0] == 2 && sPad1->pressed_a != 0) || (menufarmcl[1] == 2 && sPad2->pressed_a != 0)) {
            SeRet();
            for (i = 0; i < 10; i++)
                GameZoid[i].type = -1;
            menuZoidBattleGoPartsOptSet_GameZoid(0, 0, IveSave[0].selected_zoid_slot, 0);
            menuZoidBattleGoPartsOptSet_GameZoid(5, 1, IveSave[1].selected_zoid_slot, 0);
            menu_TITLE_dispVs(0);
            HSD_VISetBlack(1);
            menu_sDispVsFarm();
            if (menu1p_map != 0) {
                PurgeArc2(menu1p_map);
                menu1p_map = 0;
            }
            GameMode.map_no = maplist[GameMode.map];
            memcpy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
            memcpy(&IveSave[5], &IveSave[1], sizeof(GameSaveRecord));
            GameMode.win = 1;
            ttlMenuAllPurge();
            menuretno = 9999;
            return 210;
        } else if ((menufarmcl[0] == 0 && sPad1->pressed_a != 0) || (menufarmcl[1] == 0 && sPad2->pressed_a != 0)) {
            SeRet();
            menuanmend = 0;
            OSReport((char *)sLogMenuZoidBattleEntryOn);
            menu_TITLE_dispVs(0);
            menufncZoidVsMenuEntry();
            menuSetTitle(0);
            menuSetTitleButton(11);
            menu_sDispVsFarm();
            menufarmcl[0] = 0;
            menufarmsl[0] = 0;
            menufarmst[0] = 0;
            menufarmmh[0] = 3;
            menufarmmn[0] = 3;
            menufarmcl[1] = 0;
            menufarmsl[1] = 0;
            menufarmst[1] = 0;
            menufarmmh[1] = 3;
            menufarmmn[1] = 3;
        } else if ((menufarmcl[0] == 1 && sPad1->pressed_a != 0) || (menufarmcl[1] == 1 && sPad2->pressed_a != 0)) {
            SeRet();
            GameMode.map++;
            if (GameMode.map >= 17)
                GameMode.map = 1;
            GameMode.map_no = maplist[GameMode.map];
            menu_VsFarmMapLoad(maplist[GameMode.map]);
        }
    }
}
#pragma pop
#pragma readonly_strings off

static const char sLogConfigVolume[32] = "config voice  volume %d  bgm%d\n";
static const s32 r12264[7] = { 0, 2, 4, 5, 6, 7, -1 };
static const char sLogAddSysFlag[19] = "add sys-flag[%d] \n";
static const s32 r12451[7] = { 0, 1, 4, 7, 10, 13, 0 };
static const s32 r12452[7] = { 0, 2, 5, 8, 11, 14, 0 };
static const s32 r12453[7] = { 0, 3, 6, 9, 12, 15, 0 };

#pragma readonly_strings on
typedef struct ConfigAnimTable {
    s32 value[7];
} ConfigAnimTable;

extern s32 sbT, sbTO, sbTA;
extern s32 crO, crN, csA, csAO, csN;
extern void HSD_SetZSortMode(s32, s32);
extern void dispBGM(ModelArchive *archive);
extern void dispVoice(ModelArchive *archive);
extern void dispSe(ModelArchive *archive);
extern void dispRumble(ModelArchive *archive);
extern void dispVsTime(ModelArchive *archive);
extern void dispVsMode(ModelArchive *archive);
extern s32 getEndF(HSD_JObj *joint);
extern s32 jobjAnim1(HSD_JObj *joint);
extern void sMakeMatrix(HSD_JObj *joint);

s32 menu_sDispConfig(ModelArchive *archive, s32 mode)
{
    s32 done;
    HSD_JObj *cursor;
    HSD_JObj *list;
    HSD_JObj *item;
    s32 end;
    s32 i;

    done = 0;
    HSD_StartRender(0);
    HSD_SetZSortMode(1, 1);
    if (HSD_CObjSetCurrent(archive->camera) != 0) {
        HSD_LObjSetCurrentAll(archive->lights);
        HSD_LObjSetupInit(archive->camera);
        GXSetCullMode(2);
        jobjDispAll(archive->models[2]);
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_SetZSortMode(0, 0);
    if (HSD_CObjSetCurrent(archive->camera) != 0) {
        ConfigAnimTable select = *(ConfigAnimTable *)r12451;
        ConfigAnimTable next = *(ConfigAnimTable *)r12452;
        ConfigAnimTable wait = *(ConfigAnimTable *)r12453;

        HSD_LObjSetCurrentAll(archive->lights);
        HSD_LObjSetupInit(archive->camera);
        GXSetCullMode(0);
        mode &= 3;
        item = archive->models[0];
        if (mode == 1)
            SetAnimArc2(archive, 0, 2);
        if (jobjAnim(item) != 0) {
            if (mode == 3)
                done = 1;
            else
                SetAnimArc2(archive, 0, 1);
        }
        jobjDispAll(item);
        if (sbTO != sbT) {
            if (sbTO == -1) {
                SetAnimArc2(archive, 4, 0);
                jobjAnim(archive->models[4]);
                sbTA = 0;
                sbTO = sbT;
            }
            jobjAnim(archive->models[4]);
            if (sbTA != 2) {
                SetAnimArc2(archive, 4, 2);
                sbTA = 2;
                jobjAnim(archive->models[4]);
            } else {
                sbTO = sbT;
                if (sbT != -1) {
                    SetAnimArc2(archive, 4, 0);
                    sbTA = 0;
                    jobjAnim(archive->models[4]);
                }
            }
        } else if (sbT != -1) {
            if (jobjAnim(archive->models[4]) != 0) {
                SetAnimArc2(archive, 4, 1);
                sbTA = 1;
            }
            jobjAnim(archive->models[4]);
        }
        if (sbTO != -1) {
            jobjCopyPos(GetChild(archive->models[18], 0, sbTO, -1, -1, -1), archive->models[4]);
            jobjDispAll(archive->models[4]);
        }
        dispBGM(archive);
        dispVoice(archive);
        dispSe(archive);
        dispRumble(archive);
        dispVsTime(archive);
        dispVsMode(archive);
        cursor = archive->models[17];
        list = archive->models[5];
        jobjAnim(cursor);
        end = getEndF(cursor);
        if (crO != crN) {
            csA = wait.value[crO + 1];
            if (csAO == csA && end != 0) {
                crO = crN;
                csA = next.value[crN + 1];
                csAO = -1;
            }
        } else if (csA == select.value[crN + 1]) {
            if (end != 0)
                csA = next.value[crN + 1];
        } else {
            csA = next.value[crN + 1];
        }
        if (csAO != csA) {
            csAO = csA;
            SetAnimArc2(archive, 17, csA);
            jobjAnim(cursor);
        }
        sMakeMatrix(cursor);
        for (i = 0; i < 7; i++) {
            item = GetChild(list, 0, i, -1, -1, -1);
            jobjCopyPos(GetChild(cursor, 0, i, -1, -1, -1), item);
            if (jobjAnim1(item) != 0)
                sSetAnim1(archive, 5, item, i == csN ? 2 : 1);
            jobjDispAll(item);
        }
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    return done;
}
#pragma readonly_strings off

static const char sConfigArchivePath[16] = "menu/config.dat";
static const char sLogConfig[12] = "config    \n";

typedef struct PartnerAnimTable {
    u8 anim[12];
} PartnerAnimTable;

void menu_sDispBattleEntryPersonPartner(void)
{
    s32 frame_padding[2];
    PartnerAnimTable table = *(PartnerAnimTable *)r4095;
    s32 idx = 5;
    s32 result;
    s32 done;
    s16 i;
    s32 j;

    for (i = 0; i < 7; i++) {
        j = i;
        if (menufarmanm[j] == 7) {
            menumodeanm[j] = 0;
            menufarmanmold[j] = menufarmanm[j];
        }
        if (menufarmanm[j] != menufarmanmold[j]) {
            menumodeanm[j] = 1;
            menufarmanmold[j] = menufarmanm[j];
        }
        if (menumodeanm[j] == 3 && menufarmanm[j] == 0)
            menufarmanm[j] = 1;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 1)
            menumodeanm[j] = 1;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 3)
            menumodeanm[j] = 3;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 4)
            menumodeanm[j] = 4;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 5)
            menumodeanm[j] = 5;
        if (menumodeanm[j] == 1) {
            menumodeanm[j] = 2;
            sSetAnim1(menu1p, 5, GetChild(menu1p->models[idx], 0, i, -1, -1, -1), table.anim[menufarmanm[j]]);
        }
    }
    result = 0;
    done = 0;
    for (i = 0; i < 7; i++) {
        j = i;
        if (menumodeanm[j] == 2) {
            if (done == 0) {
                result = jobjAnim(menu1p->models[idx]);
                done = 1;
            }
            if (result != 0) {
                menumodeanm[j] = 3;
                menuanmend = 1;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        j = i;
        if (menufarmanm[j] != 7)
            jobjDispAll(GetChild(menu1p->models[idx], 0, j, -1, -1, -1));
    }
}

void voiceSn2a(s32 voice)
{
    s32 index;
    s32 previous;

    for (index = 19; index > 0; index--) {
        previous = index - 1;
        if (previous < 0)
            return;
        voiceSn2[index] = voiceSn2[previous];
    }
    voiceSn2[0] = voice;
}

#pragma push
#pragma opt_common_subs off
void menu_BattleSet_HumanEntryPersonPartnerExit(void)
{
    s16 mode = menumode;

    if (mode == 2) {
        menufarmanm[2] = menufarmanm[1] = menufarmanm[0] = 1;
        if (menufarmcl[2] == 2)
            menufarmanm[2] = 2;
    } else if (mode == 3) {
        menufarmanm[0] = 5;
        menufarmanm[1] = 3;
        menufarmanm[2] = 7;
    } else if (mode == 4) {
        menufarmanm[1] = 5;
        menufarmanm[0] = 3;
        menufarmanm[2] = 7;
    } else if (mode == 0) {
        menufarmanm[2] = menufarmanm[0] = menufarmanm[1] = 7;
    } else {
        menufarmanm[2] = 7;
    }
}

#pragma pop

void menu_MissionSet_EntryPersonPartnerExit(void)
{
    s16 mode = menumode;
    s16 index;

    if (mode == 2) {
        for (index = 0; index < 3; index++) {
            if (index == menufarmcl[2])
                menufarmanm[index] = 4;
            else
                menufarmanm[index] = 1;
        }
        if (menuZoidBattleModeSingleTeam == 0)
            menufarmanm[1] = 7;
    } else if (mode == 3) {
        menufarmanm[0] = 5;
        menufarmanm[1] = 3;
        menufarmanm[2] = 3;
        if (menuZoidBattleModeSingleTeam == 0)
            menufarmanm[1] = 7;
    } else if (mode == 4) {
        menufarmanm[1] = 5;
        menufarmanm[0] = 3;
        menufarmanm[2] = 7;
    } else if (mode == 0) {
        menufarmanm[1] = 7;
        menufarmanm[0] = 7;
        menufarmanm[2] = 7;
    } else {
        menufarmanm[2] = 7;
    }
}

void menuZoidBattleGoPartsOptSet_GameZoid(s16 game, s16 save, s16 slot, s32 flag)
{
    s16 zoid;
    s16 weapon;
    s16 mount;
    s16 i;

    zoid = GameZoid[game].type = IveSave[save].owned_zoids[slot];
    if (flag != 0)
        GameZoid[game].person = IveSave[save].partner_person;
    else
        GameZoid[game].person = IveSave[save].selected_person;
    GameZoid[game].color = IveSave[save].zoid_colors[slot];
    for (i = 0; i < 28; i++)
        GameZoid[game].weapons[i] = -1;
    for (i = 0; i < 10; i++) {
        if (IveSave[save].zoid_weapons[slot][i] == 0)
            IveSave[save].zoid_weapons[slot][i] = -1;
    }
    for (i = 0; i < 10; i++) {
        weapon = IveSave[save].zoid_weapons[slot][i];
        if (weapon != -1) {
            mount = ttl_GetMountNo(zoid, i);
            if (mount != -1) {
                GameZoid[game].weapons[mount] = weapon;
                OSReport(sLogWeaponPointMount, i, mount);
            }
        }
    }
    GameZoid[game].option = IveSave[save].contract_options[slot];
    for (i = 0; i < 3; i++)
        GameZoid[game].additional_parts[i] = IveSave[save].contract_subparts[slot][i];
}

void ttl_HaveAddHuman(s16 save, s16 person)
{
    if (IveSave[save].have_person[person] != 0)
        return;
    IveSave[save].have_person[person] = 1;
    IveSave[save].field_1302++;
    IveSave[save].field_1303++;
    IveSave[save].person_list[IveSave[save].person_list_count] = person;
    IveSave[save].person_list_count++;
    OSReport(sLogAddPerson, person);
}

void addZoids(s32 save, s32 zoid)
{
    s32 i;

    for (i = 0; i < IveSave[save].have_zoid_count; i++) {
        if (IveSave[save].have_zoid_flag[i] != 0 && IveSave[save].have_zoid[i] == zoid)
            return;
    }
    if (i == 100)
        return;
    IveSave[save].have_zoid[i] = zoid;
    IveSave[save].have_zoid_flag[i] = 1;
    IveSave[save].have_zoid_count++;
    IveSave[save].field_1431++;
    (void)IveSaveFlag;
    (void)IveSaveFlagBak;
    OSReport(sLogAddZoid, zoid);
}

s16 ttl_ZoidRemoveContractWep(s16 save, s16 slot, s16 mount)
{
    s16 zoid;
    s16 weapon;

    if (slot >= IveSave[save].owned_zoid_count)
        return -1;
    if (slot < 0)
        return -1;
    zoid = IveSave[save].owned_zoids[slot];
    if (zoid < 0)
        return -1;
    if (mount < 0)
        return -1;
    if (mount >= 8)
        return -1;
    if (Tea_zoiddat[zoid].weapon_permissions[mount] == 0)
        return -1;
    weapon = IveSave[save].zoid_weapons[slot][mount];
    if (weapon <= 0)
        return -1;
    IveSave[save].zoid_weapons[slot][mount] = -1;
    OSReport(sLogRemoveParts, weapon, mount);
    return weapon;
}

void ttl_WeaponAllMount(s16 slot)
{
    s16 zoid;
    s16 mount;
    s16 i;

    zoid = IveSave[0].owned_zoids[slot];
    for (i = 0; i < 10; i++) {
        if (IveSave[0].zoid_weapons[slot][i] != -1) {
            mount = ttl_GetMountNo(zoid, i);
            sWeaponMount(IveSave[0].zoid_weapons[slot][i], &Zoid[0], mount, i);
            OSReport(sLogNowZoid, Tea_zoiddat[zoid].name, i, ttl_GetMountNo(zoid, i),
                     Tea_zoiddat[zoid].default_parts[i], IveSave[0].zoid_weapons[slot][i]);
        }
    }
}

void ttl_HaveAddParts(s16 save, s16 part)
{
    s16 i;

    if (part == -1)
        return;
    OSReport(sLogAddParts, part,
             IveSave[save].owned_part_count, IveSave[save].owned_part_count);
    IveSave[save].owned_parts[IveSave[save].owned_part_count] = part;
    IveSave[save].owned_part_count++;
    for (i = 0; i < IveSave[save].owned_part_count; i++) {
        OSReport(sLogPartsEntry, i, IveSave[save].owned_parts[i],
                 Tea_partsdat[IveSave[save].owned_parts[i]].name);
    }
}

void menufnczoidmountpointdispset(s8 mount)
{
    s16 i;

    for (i = 0; i < 28; i++)
        menuZoidMountPointDsip[i] = 0;
    if (mount >= 0) {
        menuZoidMountPointDsip[mount] = 1;
        OSReport(sLogMountPointDisp, mount);
    }
}

void ttl_GameZoidSetZoidDefParts(s16 game, s16 zoid)
{
    GameZoidEntry *entry;
    s16 part;
    s16 mount;
    s16 i;
    ZoidData *data;

    if (game < 0)
        return;
    if (zoid < 0)
        return;
    GameZoid[game].field_64 = -1;
    for (i = 0; i < 28; i++)
        GameZoid[game].weapons[i] = -1;
    GameZoid[game].option = 0;
    for (i = 0; i < 3; i++)
        GameZoid[game].additional_parts[i] = 0;
    entry = &GameZoid[game];
    entry->type = zoid;
    OSReport(sLogMountSetGameZoid, Tea_zoiddat[zoid].name);
    data = &Tea_zoiddat[zoid];
    for (i = 0; i < 10; i++) {
        part = data->default_parts[i];
        if (part > 0) {
            mount = Tea_zoiddat[zoid].mount[i];
            if (mount >= 0) {
                if (i == 8 || i == 9) {
                    if (data->weapon_permissions[i] == 1)
                        entry->option = part;
                } else {
                    entry->weapons[mount] = part;
                }
                if (i == 8)
                    entry->field_64 = mount;
                if (i == 9)
                    entry->field_65 = mount;
                OSReport(sLogMountSetGameZoidEntry, i, Tea_partsdat[part].name, mount);
            }
        }
    }
    GameZoid[game].color = Tea_zoiddat[zoid].field_078E;
    OSReport("\n");
}


extern void menu_TITLE_dispEntry(s32 state);

#pragma push
#pragma dont_inline on
void menu_sDispBattleFarmTitleSubButton(void)
{
    s16 i;
    s32 idx;
    HSD_JObj *pos;
    HSD_JObj *jobj;
    s16 guide;
    s32 unused[2];

    idx = 0;
    for (i = 1; i < 7; i++) {
        if (menutitleguide[i] == -1)
            idx++;
    }
    for (i = 1; i < 7; i++) {
        if (menutitleguide[i] == -1)
            continue;
        if (menutitleanm[i].state != menutitleanm[i].next) {
            menutitleanm[i].mode = 1;
            menutitleanm[i].next = menutitleanm[i].state;
        }
        if (menutitleanm[i].mode == 3 && menutitleanm[i].state == 0)
            menutitleanm[i].state = 1;
        if (menutitleanm[i].mode == 3 && menutitleanm[i].state == 1)
            menutitleanm[i].mode = 1;
        if (menutitleanm[i].mode == 1) {
            menutitleanm[i].mode = 2;
            if (i == 4) {
                SetAnimArc2(menu1p, 1, 0);
                OSReport((char *)sLogMenu1p10, i);
            }
        }
    }
    for (i = 1; i < 7; i++) {
        idx = 1;
        guide = menutitleguide[i];
        if (guide != -1 && menutitleanm[i].mode == 2) {
            jobjAnim1(GetChild(menu1p->models[idx], 0, 4, guide, -1, -1));
            break;
        }
    }
    for (i = 1; i < 7; i++) {
        if (menutitleguide[i] == -1)
            continue;
    }
    if (menutitleguide[1] != -1) {
        idx = 1;
        pos = GetChild(menu1p->models[idx], 0, 3, -1, -1, -1);
        if (menutitleguide[3] == -1)
            jobj = GetChild(menu1p->models[idx], 0, 0, 0, -1, -1);
        else
            jobj = GetChild(menu1p->models[idx], 0, 0, 1, -1, -1);
        jobjCopyPos(pos, jobj);
        jobjDispAll(jobj);
    }
    if (menutitleguide[4] != -1) {
        idx = 1;
        pos = GetChild(menu1p->models[idx], 0, 2, -1, -1, -1);
        if (menutitleguide[6] == -1)
            jobj = GetChild(menu1p->models[idx], 0, 1, 0, -1, -1);
        else
            jobj = GetChild(menu1p->models[idx], 0, 1, 1, -1, -1);
        jobjCopyPos(pos, jobj);
        jobjDispAll(jobj);
    }
    for (i = 1; i < 7; i++) {
        guide = menutitleguide[i];
        if (guide == -1)
            continue;
        idx = 1;
        if (i <= 3)
            pos = GetChild(menu1p->models[idx], 0, 0, i + 1, -1, -1);
        else
            pos = GetChild(menu1p->models[idx], 0, 1, i - 2, -1, -1);
        (void)(guide == 0);
        jobj = GetChild(menu1p->models[idx], 0, 4, guide, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
    }
}
#pragma pop

extern u8 menumodeanm[20];
extern u8 menufarmjfl[20];
extern s32 getEndF1(HSD_JObj *joint);

void menu_sDispBattleFarmModeButton(void)
{
    u8 a;
    s16 i;
    s32 jno;
    s32 pad0;
    s16 n;
    u8 anm[6] = { 0, 1, 4, 1, 2, 3 };
    s32 unused[1];
    s32 k;

    n = 9;
    if (menuZoidBattleModeSingleTeam == 0)
        n = 9;
    for (i = 0; i < 20; i++)
        menufarmjfl[i] = 0;
    for (k = 1; k <= n; k++) {
        jno = menufarmjno[k];
        if (jno != -1) {
            menufarmjfl[jno] = 1;
            if (menufarmanm[k] != menufarmanmold[k]) {
                menumodeanm[k] = 1;
                menufarmanmold[k] = menufarmanm[k];
            }
            if (menumodeanm[k] == 3 && menufarmanm[k] == 0)
                menufarmanm[k] = 1;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 1)
                menumodeanm[k] = 1;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 3)
                menumodeanm[k] = 3;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 4)
                menumodeanm[k] = 4;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 5)
                menumodeanm[k] = 5;
            if (menumodeanm[k] == 1) {
                menumodeanm[k] = 2;
                a = menufarmanm[k];
                (void)(a == menufarmanm[k]);
                sSetAnim1(menu1p, jno, GetChild(menu1p->models[jno], 0, menufarmano[k], -1, -1, -1), anm[a]);
            }
        }
    }
    for (i = 0; i < 20; i++) {
        if (menufarmjfl[i] == 1)
            jobjAnim(menu1p->models[i]);
    }
    for (k = 1; k <= 9; k++) {
        jno = menufarmjno[k];
        if (jno != -1 && menumodeanm[k] == 2) {
            (void)(menufarmanm[k]);
            if (getEndF1(GetChild(menu1p->models[jno], 0, menufarmano[k], -1, -1, -1)) != 0) {
                menumodeanm[k] = 3;
                menuanmend = 1;
            }
        }
    }
    for (i = 0; i < 20; i++) {
        if (menufarmjfl[i] == 1)
            jobjDispAll(menu1p->models[i]);
    }
}




#pragma push
#pragma dont_inline on
extern s8 menuzoidhavepartslist;
#pragma readonly_strings on
void menu_sDispBattleSetHavePartsList(void)
{
    s32 unused[4];
    ModelArchive *ma;
    s32 idx = 10;
    HSD_JObj *item;
    s16 i;
    HSD_JObj *jobj2;
    s32 kind = 1;
    s16 part;
    s16 slot;
    HSD_JObj *jobj;
    HSD_JObj *pos = 0;
    s32 item_idx;
    s32 show = 0;

    if (menumode == 7) {
        show = 1;
        kind = 1;
    }
    if (menumode == 5) {
        show = 1;
        kind = 3;
    }
    if (menumode == 8) {
        show = 1;
        kind = 4;
    }
    if (show == 0)
        return;
    if (menuzoidhavepartslist == 0)
        return;
    if (menumode == 5)
        pos = GetChild(menu1p->models[14], 0, 8, -1, -1, -1);
    if (menumode == 7)
        pos = GetChild(menu1p->models[14], 0, 8, -1, -1, -1);
    if (menumode == 8)
        pos = GetChild(menu1p->models[14], 0, 8, -1, -1, -1);
    jobj = GetChild(menu1p->models[idx], 0, -1, -1, -1, -1);
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
    item_idx = 11;
    for (i = 0; i < menusetmh[menumode]; i++) {
        ma = menu1p;
        item = GetChild(ma->models[10], 0, 3, i, -1, -1);
        jobj2 = GetChild(menu1p->models[item_idx], 0, -1, -1, -1, -1);
        jobjCopyPos(item, jobj2);
        HSD_JObjDisp(jobj2, 0, 7, 0);
        part = IveSave[0].list_parts[i + menusetst[menumode]];
        if (part <= 0) {
            slot = 16;
            kind = 1;
            part = -1;
        } else {
            if (Tea_partsdat[part].category == 1)
                kind = 1;
            if (Tea_partsdat[part].category == 2)
                kind = 3;
            if (Tea_partsdat[part].category == 3)
                kind = 4;
            slot = Tea_partsdat[part].icon;
            if (kind == 1 && slot > 16)
                slot = 16;
            if (kind == 3 && slot > 4)
                slot = 4;
            if (kind == 4 && slot > 8)
                slot = 8;
        }
        HSD_JObjDispAll(GetChild(menu1p->models[item_idx], 0, kind, slot, -1, -1), 0, 7, 0);
        jobj2 = GetChild(menu1p->models[item_idx], 0, 2, -1, -1, -1);
        if (part == -1)
            putAscJobj(jobj2, 2, "NONE");
        else
            putAscJobj(jobj2, 2, Tea_partsdat[part].english_name);
        if (i == menusetsl[menumode]) {
            jobj2 = GetChild(menu1p->models[7], 0, 2, -1, -1, -1);
            jobjCopyPos(item, jobj2);
            HSD_JObjDispAll(jobj2, 0, 7, 0);
            sprintf((char *)menudispwinstr, (char *)sPaddedStringFormat, Tea_partsdat[part].name);
            ((char *)menudispwinstr)[56] = 0;
        }
    }
}
#pragma readonly_strings off

#pragma pop

#pragma push
#pragma dont_inline on
void menuZoidBattleGo(void)
{
    s32 unused[2];
    s16 i;
    s16 slot;
    s16 pick;
    s16 n;
    s16 j;

    for (i = 0; i < 10; i++)
        GameZoid[i].type = -1;
    GameZoid[0].type = IveSave[0].selected_zoid;
    GameZoid[0].person = IveSave[0].selected_person;
    slot = IveSave[0].selected_zoid_slot;
    menuZoidBattleGoPartsOptSet_GameZoid(0, 0, slot, 0);
    if (menuZoidBattleModeSingleTeam == 1) {
        menuZoidBattleGoPartsOptSet_GameZoid(1, 0, IveSave[0].partner_zoid_slot, 1);
    } else {
        GameZoid[1].type = -1;
        GameZoid[1].person = -1;
        GameZoid[1].color = IveSave[0].zoid_colors[slot];
        for (i = 0; i < 10; i++) {
            GameZoid[1].weapons[i] = -1;
            GameZoid[1].reserved_3B[i] = 0;
        }
        GameZoid[1].option = -1;
        GameZoid[1].additional_parts[0] = -1;
        GameZoid[1].additional_parts[1] = -1;
        GameZoid[1].additional_parts[2] = -1;
    }
    while (1) {
        pick = IveSave[0].person_list[(s16)((OSGetTime() / (__OSBusClock / 4 / 1000)) % IveSave[0].person_list_count)];
        if (IveSave[0].selected_person != pick && IveSave[0].partner_person != pick)
            break;
    }
    if (IveSave[0].field_166E >= 12)
        IveSave[0].field_166E = 0;
    n = IveSave[0].field_166E * 3;
    for (j = 0; j < 3; j++) {
        if (IveSave[0].selected_person == menu_BatMapData[n + j].first || IveSave[0].selected_person == menu_BatMapData[n + j].second)
            continue;
        if (menuZoidBattleModeSingleTeam == 0)
            break;
        if (IveSave[0].partner_person != menu_BatMapData[n + j].first && IveSave[0].partner_person != menu_BatMapData[n + j].second)
            break;
    }
    IveSave[0].field_166D = n;
    GameZoid[5].person = menu_BatMapData[n].first;
    GameZoid[6].person = menu_BatMapData[n].second;
    ttl_GameZoidSetZoidDefParts(5, menu_BatMapData[n].first_zoid);
    ttl_GameZoidSetZoidDefParts(6, menu_BatMapData[n].second_zoid);
    GameMode.map_no = menu_BatMapData[n].map;
    IveSave[0].map_no = menu_BatMapData[n].map;
    GameMode.map = IveSave[0].field_166E;
    GameMode.map_variant = 0;
}
#pragma pop


void menufncZoidBattle_BattleMenuReturn(void)
{
    s16 i;
    GXColor color;

    menu_TITLE_dispEntry(0);
    for (i = 0; i < 1; i++) {
        color = (GXColor){ 0, 0, 0, 0 };
        HSD_VIData.current.vi.clear_clr = color;
        VIWaitForRetrace();
        HSD_VICopyXFB(HSD_RP_SCREEN);
        HSD_VISetXFBDrawDone();
    }
    GameZoid[0].type = IveSave[0].selected_zoid;
    GameZoid[1].type = IveSave[0].partner_zoid;
}

void menuZoidBattleSettingmenubuttonset(void)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        menusetbtanm[i].cur = 1;
    }
    if (menumode == 1) {
        menusetbtanm[menusetcl[menumode] + 4].cur = 2;
    } else if (menumode == 2) {
        menusetbtanm[menusetcl[menumode] + 0].cur = 2;
    } else if (menumode == 3) {
        menusetbtanm[menusetcl[menumode] * 0].cur = 3;
    } else if (menumode == 4) {
        menusetbtanm[1].cur = 3;
    }
}


extern void menu_sDispBattleSet(void);
extern void SeLiftStart(void);
extern void SeLiftStop(void);
extern s16 dlgpersonno;
extern s16 dlgzoidno;
extern s32 menuzoidequippartslist;
extern s8 menuzoidhavepartslist;
extern s32 menu_StageUpDownFlag;
extern s16 flag_AllHavePartsList;
extern s32 menu_sDispBattleStageDown(s32 mode);
extern void SetMenuMsgAdr(s32 message, char *text);
extern s32 ttl_ZoidWepPointPermission(s16 zoid, s16 point);
extern s16 ttl_ZoidRemoveContractSub(s16 record, s16 slot, s16 subpart);
extern s16 ttl_ZoidRemoveContractOpt(s16 zoid, s16 slot);
extern void menuPartsWepSetListZoid(s16 category, s16 zoid, s16 point);
extern void menuPartsSetListZoid(s16 category, s16 zoid);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);
extern void SeCancel(void);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 menufncZoidBattle_BattleMenuSet(void)
{
    s32 unused[9];
    s32 i;
    s32 part;
    s32 color;
    s32 full;
    s32 removed;

    menuCursor = 0;
    menuParticles = 0;
    menumode = 0;
    dlgpersonno = 0;
    dlgzoidno = 0;
    ((char *)menudispwinstr)[0] = 0;
    menudispyesnoflag = 0;
    TEA_SetTimerInit();
    IveSave[0].owned_zoid_count = 0;
    for (i = 0; i < 30; i++) {
        if (IveSave[0].owned_zoids[i] < 0)
            break;
    }
    IveSave[0].owned_zoid_count = i;
    memcpy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
    menubackcampos.x = menubackcambak.x - 2.0;
    for (i = 0; i < 12; i++) {
        menubackintpos.x = menubackintbak.x - i * 0.5;
        menu_sDispBattleSet();
    }
    menubackintpos.x = menubackintbak.x - 6.0;
    menu_sDispBattleSet();
    for (i = 0; i < 7; i++) {
        menusetbtanm[i].cur = 0;
        menusetbtanm[i].old = 0;
        menusetbtanm[i].state = 1;
    }
    menusetbtanm[7].cur = 1;
    menusetbtanm[7].old = 1;
    menusetbtanm[7].state = 0;
    menusetbtanm[8].cur = 1;
    menusetbtanm[8].old = 1;
    menusetbtanm[8].state = 0;
    menusetbtanm[9].cur = 0;
    menusetbtanm[9].old = 0;
    menusetbtanm[9].state = 0;
    menusetbtanm[10].cur = 0;
    menusetbtanm[10].old = 0;
    menusetbtanm[10].state = 0;
    for (i = 0; i < 20; i++) {
        menusetcl[i] = 0;
        menusetsl[i] = 0;
        menusetst[i] = 0;
        menusetmh[i] = 0;
        menusetmn[i] = 0;
    }
    menusetcl[1] = 1;
    menusetsl[1] = 1;
    menusetmh[1] = 2;
    menusetmn[1] = 2;
    menusetcl[2] = 0;
    menusetsl[2] = 0;
    menusetmh[2] = 4;
    menusetmn[2] = 4;
    menusetcl[3] = 0;
    menusetsl[3] = 0;
    menusetmh[3] = 4;
    menusetmn[3] = IveSave[0].owned_zoid_count;
    if (menusetmn[3] < 4)
        menusetmh[3] = menusetmn[3];
    menusetcl[4] = 0;
    menusetsl[4] = 0;
    menusetmh[4] = 8;
    menusetmn[4] = 8;
    menusetcl[6] = 0;
    menusetsl[6] = 0;
    menusetmh[6] = 3;
    menusetmn[6] = 3;
    menusetcl[5] = 0;
    menusetsl[5] = 0;
    menusetmh[5] = 5;
    menusetcl[7] = 0;
    menusetsl[7] = 0;
    menusetmh[7] = 5;
    menusetmn[7] = 8;
    menusetcl[8] = 0;
    menusetsl[8] = 0;
    menusetmh[8] = 5;
    menusetmn[8] = 10;
    flag_AllHavePartsList = 0;
    menumode = 1;
    menuZoidBattleSettingmenubuttonset();
    dlgzoidno = IveSave[0].selected_zoid;
    menucuranm = 1;
    SetMenuMsgAdr(30, (char *)menudispwinstr);
    while (1) {
        sPadAll();
        menusetcl[menumode] = TEA_menufnc(&menusetsl[menumode], &menusetst[menumode], menusetmn[menumode], menusetmh[menumode]);
        if (menumode == 1) {
            if (menusetcl[menumode] == 0)
                SetMenuMsgAdr(29, (char *)menudispwinstr);
            if (menusetcl[menumode] == 1)
                SetMenuMsgAdr(30, (char *)menudispwinstr);
        } else if (menumode == 2) {
            SetMenuMsgAdr(menusetcl[menumode] + 25, (char *)menudispwinstr);
        } else if (menumode == 4) {
            SetMenuMsgAdr(32, (char *)menudispwinstr);
        } else if (menumode == 6) {
            SetMenuMsgAdr(10, (char *)menudispwinstr);
        }
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0) {
            if (menumode == 4 || menumode == 7)
                menufnczoidmountpointdispset(menusetcl[4]);
            menuZoidBattleSettingmenubuttonset();
        }
        if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0) {
            if (menumode == 4 || menumode == 7)
                menufnczoidmountpointdispset(menusetcl[4]);
            menuZoidBattleSettingmenubuttonset();
        }
        if (sPad1->pressed_dpad_left != 0 || sPad1->pressed_stick_left != 0) {
            if (menumode == 1)
                menumode = 2;
            menuZoidBattleSettingmenubuttonset();
        }
        if (sPad1->pressed_dpad_right != 0 || sPad1->pressed_stick_right != 0) {
            if (menumode == 2)
                menumode = 1;
            menuZoidBattleSettingmenubuttonset();
        }
        if (sPad1->pressed_a != 0) {
            if (menumode == 1) {
                SeRet();
                if (menusetcl[menumode] == 0) {
                    if (IveSave[0].owned_part_count >= 450) {
                        menudispyesnopoint = 1;
                        menudispyesnoflag = 1;
                        do {
                            sPadAll();
                            menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_CANNOT_REMOVE_PARTS), "NOT");
                            menu_sDispBattleSet();
                        } while (sPad1->pressed_a == 0);
                        SeRet();
                        menudispyesnoflag = 0;
                        continue;
                    }
                    menudispyesnopoint = 1;
                    menudispyesnoflag = 1;
                    do {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_CLEAR_SETTINGS_PROMPT), "");
                        menu_sDispBattleSet();
                    } while (sPad1->pressed_a == 0);
                    SeRet();
                    menudispyesnoflag = 0;
                    menu_sDispBattleSet();
                    if (menudispyesnopoint != 0) {
                        ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                        full = 0;
                        removed = 0;
                        for (i = 0; i < 8; i++) {
                            if (IveSave[0].owned_part_count < 450) {
                                if ((part = ttl_ZoidRemoveContractWep(0, IveSave[0].selected_zoid_slot, i)) != -1) {
                                    ttl_HaveAddParts(0, part);
                                    removed = 1;
                                }
                            } else {
                                full = 1;
                            }
                        }
                        if (IveSave[0].owned_part_count < 450) {
                            if ((part = ttl_ZoidRemoveContractOpt(0, IveSave[0].selected_zoid_slot)) != -1) {
                                ttl_HaveAddParts(0, part);
                                removed = 1;
                            }
                        } else {
                            full = 1;
                        }
                        for (i = 0; i < 3; i++) {
                            if (IveSave[0].owned_part_count < 450) {
                                if ((part = ttl_ZoidRemoveContractSub(0, IveSave[0].selected_zoid_slot, i)) != -1) {
                                    ttl_HaveAddParts(0, part);
                                    removed = 1;
                                }
                            } else {
                                full = 1;
                            }
                        }
                        if (full == 1 && removed == 1) {
                            menudispyesnopoint = 1;
                            menudispyesnoflag = 1;
                            do {
                                sPadAll();
                                menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_CANNOT_REMOVE_PARTS), "NOT");
                                menu_sDispBattleSet();
                            } while (sPad1->pressed_a == 0);
                            SeRet();
                            menudispyesnoflag = 0;
                            menu_sDispBattleSet();
                        }
                        menudispyesnoflag = 0;
                        ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                    }
                    continue;
                }
                if (menusetcl[menumode] == 1) {
                    ((char *)menudispwinstr)[0] = 0;
                    menusetbtanm[5].cur = 4;
                    menusetbtanm[5].state = 1;
                    if (IveSave[4].selected_zoid_slot != IveSave[0].selected_zoid_slot) {
                        SeLiftStart();
                        menu_StageUpDownFlag = 0;
                        while (menu_sDispBattleStageDown(1) == 0)
                            menu_sDispBattleSet();
                        SeLiftStop();
                        ZoidWeaponPurge(&Zoid[0]);
                        ttl_WeaponAllUnMount(menusetcl[3]);
                        ZoidPurge(&Zoid[0]);
                        IveSave[0].selected_zoid_slot = IveSave[4].selected_zoid_slot;
                        IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                        ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                        ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                        SeLiftStart();
                        menu_StageUpDownFlag = 0;
                        while (menu_sDispBattleStageDown(0) == 0)
                            menu_sDispBattleSet();
                        SeLiftStop();
                    } else {
                        ZoidWeaponPurge(&Zoid[0]);
                        ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                        ZoidPurge(&Zoid[0]);
                        ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                        ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                    }
                    break;
                }
            }
            if (menumode == 2) {
                if (menusetcl[menumode] == 0) {
                    SeRet();
                    menumode = 3;
                    menuZoidBattleSettingmenubuttonset();
                    menu_sDispBattleSet();
                    menusetbtanm[7].cur = 0;
                    menusetbtanm[7].state = 1;
                    while (menusetbtanm[7].cur != 1)
                        menu_sDispBattleSet();
                    menuanmend = 0;
                    while (menuanmend == 0)
                        menu_sDispBattleSet();
                    continue;
                } else if (menusetcl[menumode] == 1) {
                    SeRet();
                    menuzoidequippartslist = 0;
                    menusetbtanm[8].cur = 26;
                    menusetbtanm[8].old = 26;
                    menusetbtanm[8].state = 0;
                    menumode = 4;
                    menuZoidBattleSettingmenubuttonset();
                    menu_sDispBattleSet();
                    menusetbtanm[7].cur = 3;
                    menuanmend = 0;
                    menusetbtanm[7].state = 1;
                    while (menusetbtanm[7].cur != 4)
                        menu_sDispBattleSet();
                    menu_sDispBattleSet();
                    menuzoidequippartslist = 1;
                    menusetbtanm[8].cur = 0;
                    menusetbtanm[8].state = 1;
                    while (menusetbtanm[8].state != 3)
                        menu_sDispBattleSet();
                    menusetbtanm[8].cur = 1;
                    menu_sDispBattleSet();
                    menufnczoidmountpointdispset(menusetcl[4]);
                    continue;
                } else if (menusetcl[menumode] == 2) {
                    OSReport(sLogDebug09);
                    menuPartsSetListZoid(2, IveSave[0].selected_zoid);
                    if (IveSave[0].list_count == 0) {
                        SeCancel();
                        continue;
                    }
                    SeRet();
                    menusetmn[5] = IveSave[0].list_count;
                    menusetmh[5] = 5;
                    if (menusetmn[5] < 5)
                        menusetmh[5] = menusetmn[5];
                    if (menusetmn[5] < menusetsl[5] - 1) {
                        menusetcl[5] = 0;
                        menusetsl[5] = 0;
                        menusetst[5] = 0;
                    }
                    if (menusetmh[5] < menusetsl[5] - 1) {
                        menusetcl[5] = 0;
                        menusetsl[5] = 0;
                        menusetst[5] = 0;
                    }
                    menusetst[5] = 0;
                    menumode = 5;
                    menuZoidBattleSettingmenubuttonset();
                    menu_sDispBattleSet();
                    menusetbtanm[7].cur = 6;
                    menuanmend = 0;
                    menusetbtanm[7].state = 1;
                    while (menusetbtanm[7].cur != 7)
                        menu_sDispBattleSet();
                    OSReport(sLogMenuMode01Start);
                    menusetbtanm[7].cur = 7;
                    menu_sDispBattleSet();
                    menuzoidhavepartslist = 1;
                    menusetbtanm[8].cur = 2;
                    menusetbtanm[8].state = 1;
                    menuzoidequippartslist = 1;
                    menu_sDispBattleSet();
                    menuzoidhavepartslist = 1;
                    while (menusetbtanm[8].state != 3)
                        menu_sDispBattleSet();
                    menusetbtanm[8].cur = 3;
                    menusetbtanm[8].state = 1;
                    menuzoidhavepartslist = 1;
                    menu_sDispBattleSet();
                    OSReport(sLogMenuMode03Start);
                    menusetcl[5] = 0;
                    menusetsl[5] = 0;
                    menusetst[5] = 0;
                    menusetst[menumode] = 0;
                    menusetsl[menumode] = 0;
                    menusetcl[menumode] = 0;
                    continue;
                } else if (menusetcl[menumode] == 3) {
                    SeRet();
                    menuzoidequippartslist = 0;
                    menusetbtanm[8].cur = 26;
                    menusetbtanm[8].old = 26;
                    menusetbtanm[8].state = 0;
                    menumode = 6;
                    menuZoidBattleSettingmenubuttonset();
                    menu_sDispBattleSet();
                    menuzoidequippartslist = 1;
                    menusetbtanm[8].cur = 0;
                    menusetbtanm[8].state = 1;
                    while (menusetbtanm[8].state != 3)
                        menu_sDispBattleSet();
                    menusetbtanm[8].cur = 1;
                    menu_sDispBattleSet();
                    menufnczoidmountpointdispset(menusetcl[4]);
                    continue;
                }
            }
            if (menumode == 3) {
                if (IveSave[0].selected_zoid_slot == menusetcl[3])
                    continue;
                SeRet();
                menuZoidBattleSettingmenubuttonset();
                menuanmend = 0;
                menusetbtanm[7].cur = 2;
                menusetbtanm[7].state = 1;
                while (menusetbtanm[7].cur != 9)
                    menu_sDispBattleSet();
                menu_sDispBattleSet();
                menumode = 2;
                SeLiftStart();
                menu_StageUpDownFlag = 0;
                while (menu_sDispBattleStageDown(1) == 0)
                    menu_sDispBattleSet();
                SeLiftStop();
                ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                ZoidPurge(&Zoid[0]);
                IveSave[0].selected_zoid_slot = menusetcl[3];
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                SeLiftStart();
                menu_StageUpDownFlag = 0;
                while (menu_sDispBattleStageDown(0) == 0)
                    menu_sDispBattleSet();
                SeLiftStop();
                dlgzoidno = IveSave[0].selected_zoid;
                menuZoidBattleSettingmenubuttonset();
                menusetst[4] = 0;
                menusetsl[4] = 0;
                menusetcl[4] = 0;
                menusetst[5] = 0;
                menusetsl[5] = 0;
                menusetcl[5] = 0;
                menusetst[6] = 0;
                menusetsl[6] = 0;
                menusetcl[6] = 0;
                menusetst[7] = 0;
                menusetsl[7] = 0;
                menusetcl[7] = 0;
                menusetst[8] = 0;
                menusetsl[8] = 0;
                menusetcl[8] = 0;
            }
            if (menumode == 4) {
                menuPartsWepSetListZoid(1, IveSave[0].selected_zoid, menusetsl[4]);
                if (IveSave[0].list_count == 0) {
                    SeCancel();
                    continue;
                }
                if (ttl_ZoidWepPointPermission(IveSave[0].selected_zoid, menusetsl[4]) == 0) {
                    SeBuzzerC();
                    continue;
                }
                SeRet();
                menuzoidhavepartslist = 1;
                menusetbtanm[8].cur = menusetsl[4] * 3 + 2;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].state != 3)
                    menu_sDispBattleSet();
                menusetbtanm[8].cur = menusetsl[4] * 3 + 3;
                menusetbtanm[8].state = 1;
                menu_sDispBattleSet();
                menumode = 7;
                menuZoidBattleSettingmenubuttonset();
                menu_sDispBattleSet();
                menusetmn[7] = IveSave[0].list_count;
                menusetmh[7] = 5;
                if (menusetmn[7] < 5)
                    menusetmh[7] = menusetmn[7];
                if (menusetmn[7] < menusetsl[7] - 1) {
                    menusetcl[7] = 0;
                    menusetsl[7] = 0;
                    menusetst[7] = 0;
                }
                if (menusetmh[7] < menusetsl[7] - 1) {
                    menusetcl[7] = 0;
                    menusetsl[7] = 0;
                    menusetst[7] = 0;
                }
                menusetsl[7] = 0;
                menusetst[7] = 0;
                menusetcl[7] = 0;
                menusetst[7] = 0;
                menusetst[menumode] = 0;
                menusetsl[menumode] = 0;
                menusetcl[menumode] = 0;
                continue;
            }
            if (menumode == 7) {
                s16 zoid;
                s16 old;
                s16 *flag;
                s16 cl;

                SeRet();
                zoid = IveSave[0].selected_zoid_slot;
                old = IveSave[0].zoid_weapons[zoid][menusetcl[4]];
                OSReport("wep %d ", old);
                IveSave[0].zoid_weapons[zoid][menusetcl[4]] = IveSave[0].list_parts[menusetcl[7]];
                menuzoidequippartslist = 1;
                menusetbtanm[8].cur = 4;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].cur != 27)
                    menu_sDispBattleSet();
                menuzoidhavepartslist = 0;
                menusetbtanm[8].cur = 1;
                menusetbtanm[8].state = 1;
                menu_sDispBattleSet();
                menumode = 4;
                menuZoidBattleSettingmenubuttonset();
                menu_sDispBattleSet();
                ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                menuzoidhavepartslist = 0;
                flag = &IveSave[0].list_flag[menusetcl[7]];
                cl = *flag;
                if (old != -1) {
                    IveSave[0].owned_parts[cl] = old;
                } else {
                    IveSave[0].owned_part_count--;
                    IveSave[0].owned_parts[*flag] = IveSave[0].owned_parts[IveSave[0].owned_part_count];
                    IveSave[0].owned_parts[IveSave[0].owned_part_count] = -1;
                }
                continue;
            }
            if (menumode == 6) {
                menuPartsSetListZoid(3, IveSave[0].selected_zoid);
                if (IveSave[0].list_count == 0) {
                    SeCancel();
                    continue;
                }
                SeRet();
                menuzoidhavepartslist = 1;
                menusetbtanm[8].cur = (menusetsl[6] - 1) * 3 + 5;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].state != 3)
                    menu_sDispBattleSet();
                menusetbtanm[8].cur = (menusetsl[6] - 1) * 3 + 6;
                menusetbtanm[8].state = 1;
                menu_sDispBattleSet();
                menumode = 8;
                menuZoidBattleSettingmenubuttonset();
                menu_sDispBattleSet();
                menuPartsSetListZoid(3, IveSave[0].selected_zoid);
                menusetmn[8] = IveSave[0].list_count;
                menusetmh[8] = 5;
                if (menusetmn[8] < 5)
                    menusetmh[8] = menusetmn[8];
                if (menusetmn[8] < menusetsl[8] - 1) {
                    menusetcl[8] = 0;
                    menusetsl[8] = 0;
                    menusetst[8] = 0;
                }
                if (menusetmh[8] < menusetsl[8] - 1) {
                    menusetcl[8] = 0;
                    menusetsl[8] = 0;
                    menusetst[8] = 0;
                }
                menusetst[8] = 0;
                menusetst[menumode] = 0;
                menusetsl[menumode] = 0;
                menusetcl[menumode] = 0;
                continue;
            }
            if (menumode == 8) {
                s32 zoid;
                s32 slot;
                s16 parts;
                s32 old;

                SeRet();
                menuzoidequippartslist = 1;
                menusetbtanm[8].cur = menusetsl[6] * 3 + 7;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].cur != 27)
                    menu_sDispBattleSet();
                menuzoidhavepartslist = 0;
                menusetbtanm[8].cur = 1;
                menusetbtanm[8].state = 1;
                menu_sDispBattleSet();
                zoid = IveSave[0].selected_zoid_slot;
                slot = menusetcl[6];
                parts = IveSave[0].list_parts[menusetcl[8]];
                old = IveSave[0].contract_subparts[zoid][slot];
                OSReport(sLogSubParts, slot, old, parts, zoid, menusetcl[8]);
                IveSave[0].contract_subparts[zoid][slot] = parts;
                menumode = 6;
                menuZoidBattleSettingmenubuttonset();
                menu_sDispBattleSet();
                menuzoidhavepartslist = 0;
                if (old > 0) {
                    IveSave[0].owned_parts[IveSave[0].list_flag[menusetcl[8]]] = old;
                    OSReport(sLogList1, menusetcl[8], IveSave[0].list_flag[menusetcl[8]], IveSave[0].owned_parts[IveSave[0].list_flag[menusetcl[8]]]);
                } else {
                    IveSave[0].owned_part_count--;
                    parts = IveSave[0].owned_parts[IveSave[0].owned_part_count];
                    IveSave[0].owned_parts[IveSave[0].list_flag[menusetcl[8]]] = parts;
                    IveSave[0].owned_parts[IveSave[0].owned_part_count] = -1;
                    OSReport(sLogList2, menusetcl[8], IveSave[0].list_flag[menusetcl[8]], parts);
                }
            }
            if (menumode == 5) {
                s16 zoid;
                s32 old;
                s16 n;

                SeRet();
                menusetbtanm[7].cur = 8;
                menusetbtanm[7].state = 1;
                while (menusetbtanm[7].cur != 9)
                    menu_sDispBattleSet();
                OSReport(sLogMenuMode5End);
                menuzoidhavepartslist = 0;
                menu_sDispBattleSet();
                zoid = IveSave[0].selected_zoid_slot;
                old = IveSave[0].contract_options[zoid];
                IveSave[0].contract_options[zoid] = IveSave[0].list_parts[menusetcl[5]];
                n = IveSave[0].list_flag[menusetcl[5]];
                if (old > 0) {
                    IveSave[0].owned_parts[n] = old;
                } else {
                    IveSave[0].owned_part_count--;
                    IveSave[0].owned_parts[n] = IveSave[0].owned_parts[IveSave[0].owned_part_count];
                    IveSave[0].owned_parts[IveSave[0].owned_part_count] = -1;
                }
                menuPartsSetListZoid(2, IveSave[0].selected_zoid);
                menumode = 2;
                menuZoidBattleSettingmenubuttonset();
                continue;
            }
        }
        if (sPad1->pressed_b != 0) {
            SeCancel();
            if (menumode == 3) {
                menusetbtanm[7].cur = 2;
                menusetbtanm[7].state = 1;
                menuanmend = 0;
                while (menusetbtanm[7].cur != 9)
                    menu_sDispBattleSet();
                menu_sDispBattleSet();
                menumode = 2;
                menuZoidBattleSettingmenubuttonset();
                menuanmend = 0;
                while (menuanmend == 0)
                    menu_sDispBattleSet();
            } else if (menumode == 4) {
                menufnczoidmountpointdispset(-1);
                menusetbtanm[8].cur = 26;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].state != 3)
                    menu_sDispBattleSet();
                menuzoidequippartslist = 0;
                menusetbtanm[7].cur = 5;
                menusetbtanm[7].state = 1;
                while (menusetbtanm[7].cur != 9)
                    menu_sDispBattleSet();
                menu_sDispBattleSet();
                menuanmend = 0;
                menumode = 2;
                menuZoidBattleSettingmenubuttonset();
                menuanmend = 0;
                while (menuanmend == 0)
                    menu_sDispBattleSet();
            } else if (menumode == 7) {
                menuzoidequippartslist = 1;
                menusetbtanm[8].cur = menusetsl[4] * 3 + 4;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].cur != 27)
                    menu_sDispBattleSet();
                menuzoidhavepartslist = 0;
                menusetbtanm[8].cur = 1;
                menusetbtanm[8].state = 1;
                menu_sDispBattleSet();
                menuzoidhavepartslist = 0;
                menumode = 4;
                menuZoidBattleSettingmenubuttonset();
                menuanmend = 0;
                while (menuanmend == 0)
                    menu_sDispBattleSet();
            } else if (menumode == 5) {
                menusetbtanm[7].cur = 8;
                menusetbtanm[7].state = 1;
                while (menusetbtanm[7].cur != 9)
                    menu_sDispBattleSet();
                OSReport(sLogMenuMode5End);
                menuzoidhavepartslist = 0;
                menu_sDispBattleSet();
                menumode = 2;
                menuZoidBattleSettingmenubuttonset();
            } else if (menumode == 6) {
                menusetbtanm[8].cur = 26;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].state != 3)
                    menu_sDispBattleSet();
                menuzoidequippartslist = 0;
                menuanmend = 0;
                menumode = 2;
                menuZoidBattleSettingmenubuttonset();
                while (menuanmend == 0)
                    menu_sDispBattleSet();
            } else if (menumode == 8) {
                menuzoidequippartslist = 1;
                menusetbtanm[8].cur = menusetsl[6] * 3 + 4;
                menusetbtanm[8].state = 1;
                while (menusetbtanm[8].cur != 27)
                    menu_sDispBattleSet();
                menuzoidhavepartslist = 0;
                menusetbtanm[8].cur = 1;
                menusetbtanm[8].state = 1;
                menu_sDispBattleSet();
                menuzoidhavepartslist = 0;
                menumode = 6;
                menuZoidBattleSettingmenubuttonset();
                menuanmend = 0;
                while (menuanmend == 0)
                    menu_sDispBattleSet();
            } else {
                menumode = 1;
                menusetcl[menumode] = 1;
                menusetst[menumode] = 0;
                menusetsl[menumode] = 1;
                menuZoidBattleSettingmenubuttonset();
            }
            continue;
        }
        if (sPad1->pressed_x != 0 && menumode <= 6) {
            color = (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot] + 1;
            if (ZoidColor(&Zoid[0], color, 0) == 0) {
                color = 0;
                ZoidColor(&Zoid[0], 0, 0);
            }
            OSReport(sLogZoidColor, color);
            IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot] = (s8)color;
            GameZoid[0].color = color;
        }
        menu_sDispBattleSet();
    }
    IveSave[0].owned_zoid_count = 0;
    for (i = 0; i < 30; i++) {
        if (IveSave[0].owned_zoids[i] < 0)
            break;
    }
    IveSave[0].owned_zoid_count = i;
    for (i = 0; i < 11; i++) {
        menusetbtanm[i].cur = 5;
        menusetbtanm[i].state = 1;
    }
    menuanmend = 0;
    do {
        menu_sDispBattleSet();
    } while (menusetbtanm[5].state != 3);
    menumode = 0;
    menu_sDispBattleSet();
    menubackcampos.x = menubackcambak.x;
    for (i = 0; i < 12; i++) {
        menubackintpos.x = -6.0 - (menubackintbak.x - i * 0.5);
        menu_sDispBattleSet();
    }
    menubackcampos.x = menubackcambak.x;
    menubackintpos.x = menubackintbak.x;
    menu_sDispBattleSet();
    return 205;
}
#pragma pop
#pragma readonly_strings off
extern s8 menumodeShop;

void menuZoidBattleShopmenubuttonset(void)
{
    s32 i;

    for (i = 0; i < 7; i++) {
        menusetbtanm[i].cur = 1;
    }
    if (menumode == 1) {
        menusetbtanm[menusetcl[menumode] + 4].cur = 2;
    } else if (menumode == 10) {
        menusetbtanm[menusetcl[menumode] + 5].cur = 2;
    } else if (menumode == 2) {
        if (menumodeShop == 1) {
            menusetbtanm[5].cur = 3;
            menusetbtanm[5].state = 1;
        }
        if (menumodeShop == 2) {
            menusetbtanm[6].cur = 3;
            menusetbtanm[6].state = 1;
        }
        menusetbtanm[menusetcl[menumode] + 0].cur = 2;
    } else if (menumode == 3) {
        if (menumodeShop == 1) {
            menusetbtanm[5].cur = 3;
            menusetbtanm[5].state = 1;
        }
        if (menumodeShop == 2) {
            menusetbtanm[6].cur = 3;
            menusetbtanm[6].state = 1;
        }
        menusetbtanm[menumode * 0].cur = 3;
        menusetbtanm[0].state = 1;
    } else if (menumode == 4) {
        return;
    }
}

extern void menu_sDispBattleShop(void);
extern void menufncShopyesno(s32 buy);
extern void shopDispParts(s32 record);
extern void shopSortParts(s32 record);
extern s16 dlgpersonno;
extern s16 dlgzoidno;
extern s16 dlgpartsno;
extern s16 menudispshophavezoidlist;
extern s8 menuzoidhavepartslist;
extern s32 menu_StageUpDownFlag;
extern s32 menu_sDispBattleStageDown(s32 mode);
extern void SetMenuMsgAdr(s32 message, char *text);
extern s16 ttl_ZoidRemoveContractSub(s16 record, s16 slot, s16 subpart);
extern s16 ttl_ZoidRemoveContractOpt(s16 zoid, s16 slot);
extern s32 ZoidColor(ZoidState *zoid, s32 color, s32 flags);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void SeCancel(void);

#pragma push
#pragma dont_inline on
s32 menufncZoidBattle_BattleMenuShop(void)
{
    s32 stB;
    s32 st;
    s32 mnB;
    s32 slB;
    s32 mh;
    s32 mhB;
    s32 sl;
    s32 mn;
    s32 change;
    s32 j;
    s32 i;
    s32 part;
    s16 zn[3];
    s32 sel;
    s32 count;
    s32 last;
    s32 unused[12];

    change = 0;
    menumode = 0;
    dlgpersonno = 0;
    dlgzoidno = 0;
    menumodeShop = 0;
    TEA_SetTimerInit();
    memcpy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
    menudispyesnoflag = 0;
    menubackcampos.x = menubackcambak.x - 2.0;
    for (i = 0; i < 12; i++) {
        menubackintpos.x = menubackintbak.x - i * 0.5;
        menu_sDispBattleShop();
    }
    menubackintpos.x = menubackintbak.x - 6.0;
    menu_sDispBattleShop();
    for (i = 0; i < 7; i++) {
        menusetbtanm[i].cur = 0;
        menusetbtanm[i].old = 0;
        menusetbtanm[i].state = 1;
    }
    menusetbtanm[7].cur = 1;
    menusetbtanm[7].old = 1;
    menusetbtanm[7].state = 0;
    menusetbtanm[8].cur = 0;
    menusetbtanm[8].old = 0;
    menusetbtanm[8].state = 0;
    menusetbtanm[9].cur = 0;
    menusetbtanm[9].old = 0;
    menusetbtanm[9].state = 0;
    menusetbtanm[10].cur = 0;
    menusetbtanm[10].old = 0;
    menusetbtanm[10].state = 0;
    for (i = 0; i < 20; i++) {
        menusetcl[i] = 0;
        menusetsl[i] = 0;
        menusetst[i] = 0;
        menusetmh[i] = 0;
        menusetmn[i] = 0;
    }
    menusetcl[1] = 0;
    menusetsl[1] = 0;
    menusetmh[1] = 1;
    menusetmn[1] = 1;
    menusetcl[2] = 0;
    menusetsl[2] = 0;
    menusetmh[2] = 4;
    menusetmn[2] = 4;
    menusetcl[3] = 0;
    menusetsl[3] = 0;
    menusetmh[3] = 4;
    menusetmn[3] = IveSave[0].owned_zoid_count;
    if (menusetmn[3] < 4)
        menusetmh[3] = menusetmn[3];
    menusetcl[4] = 0;
    menusetsl[4] = 0;
    menusetmh[4] = 8;
    menusetmn[4] = 10;
    menusetcl[6] = 0;
    menusetsl[6] = 0;
    menusetmh[6] = 3;
    menusetmn[6] = 3;
    menusetcl[5] = 0;
    menusetsl[5] = 0;
    menusetmh[5] = 5;
    menusetcl[7] = 0;
    menusetsl[7] = 0;
    menusetmh[7] = 5;
    menusetmn[7] = 10;
    menusetcl[8] = 0;
    menusetsl[8] = 0;
    menusetmh[8] = 5;
    menusetmn[8] = 10;
    menusetcl[10] = 0;
    menusetsl[10] = 0;
    menusetmh[10] = 2;
    menusetmn[10] = 2;
    menusetbtanm[7].cur = 0;
    menumode = 1;
    menuZoidBattleShopmenubuttonset();
    dlgzoidno = IveSave[0].owned_zoids[menusetst[3]];
    menudispshophavezoidlist = 0;
    menuzoidhavepartslist = 0;
    menusetbtanm[10].cur = 0;
    menusetbtanm[10].state = 1;
    menu_sDispBattleShop();
    menucuranm = 1;
    SetMenuMsgAdr(79, (char *)menudispwinstr);
    zn[2] = IveSave[0].selected_zoid_slot;
    if (menuZoidBattleModeSingleTeam == 1)
        zn[1] = IveSave[0].partner_zoid_slot;
    else
        zn[1] = -1;
    while (1) {
        sPadAll();
        menusetcl[menumode] = TEA_menufnc(&menusetsl[menumode], &menusetst[menumode], menusetmn[menumode], menusetmh[menumode]);
        if (menumode == 1)
            SetMenuMsgAdr(88, (char *)menudispwinstr);
        if (menumode == 10)
            SetMenuMsgAdr(menusetcl[menumode] + 57, (char *)menudispwinstr);
        if (menumode == 2)
            SetMenuMsgAdr(menusetcl[menumode] + 59 + (menumodeShop - 1) * 4, (char *)menudispwinstr);
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0) {
            if (menumode == 4 || menumode == 7)
                menufnczoidmountpointdispset(menusetcl[4]);
            menuZoidBattleShopmenubuttonset();
        }
        if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0) {
            if (menumode == 4 || menumode == 7)
                menufnczoidmountpointdispset(menusetcl[4]);
            menuZoidBattleShopmenubuttonset();
        }
        if (sPad1->pressed_dpad_left != 0 || sPad1->pressed_stick_left != 0) {
            if (menumode == 1) {
                menumode = 10;
                menuZoidBattleShopmenubuttonset();
            }
        }
        if (sPad1->pressed_dpad_right != 0 || sPad1->pressed_stick_right != 0) {
            if (menumode == 10)
                menumode = 1;
            menuZoidBattleShopmenubuttonset();
        }
        if (sPad1->pressed_a != 0) {
            if (menumode == 1) {
                SeRet();
                ((char *)menudispwinstr)[0] = 0;
                if (IveSave[0].selected_zoid_slot == zn[2]) {
                    menudispshophavezoidlist = 0;
                    menu_StageUpDownFlag = 0;
                    while (menu_sDispBattleStageDown(1) == 0)
                        menu_sDispBattleShop();
                    ZoidWeaponPurge(&Zoid[0]);
                    ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                    IveSave[0].selected_zoid_slot = zn[2];
                    IveSave[4].selected_zoid_slot = zn[2];
                    ZoidPurge(&Zoid[0]);
                    IveSave[0].selected_zoid = IveSave[4].selected_zoid;
                    IveSave[0].selected_zoid_slot = IveSave[4].selected_zoid_slot;
                    IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                    ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                    ZoidSetAnim(&Zoid[0], 103);
                    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                    menu_StageUpDownFlag = 0;
                    while (menu_sDispBattleStageDown(0) == 0)
                        menu_sDispBattleShop();
                    menuZoidBattleShopmenubuttonset();
                }
                break;
            } else if (menumode == 10) {
                SeRet();
                if (menusetcl[menumode] == 0) {
                    menumodeShop = 1;
                    menusetbtanm[10].cur = 1;
                    menusetbtanm[10].state = 1;
                    while (menusetbtanm[10].cur != 2)
                        menu_sDispBattleShop();
                    menusetbtanm[7].cur = 0;
                    menusetbtanm[7].state = 1;
                    while (menusetbtanm[7].cur != 1)
                        menu_sDispBattleShop();
                    menusetcl[3] = 0;
                    menusetsl[3] = 0;
                    menusetst[3] = 0;
                    menusetmh[3] = 4;
                    menusetmn[3] = IveSave[0].have_zoid_count;
                    if (menusetmn[3] < 4)
                        menusetmh[3] = menusetmn[3];
                    menusetbtanm[5].cur = 3;
                }
                if (menusetcl[menumode] == 1) {
                    menumodeShop = 2;
                    menusetbtanm[10].cur = 4;
                    menusetbtanm[10].state = 1;
                    while (menusetbtanm[10].cur != 5)
                        menu_sDispBattleShop();
                    menusetbtanm[7].cur = 0;
                    menusetbtanm[7].state = 1;
                    while (menusetbtanm[7].cur != 1)
                        menu_sDispBattleShop();
                    menusetcl[3] = 0;
                    menusetsl[3] = 0;
                    menusetst[3] = 0;
                    menusetmh[3] = 4;
                    menusetmn[3] = IveSave[0].owned_zoid_count;
                    if (menusetmn[3] < 4)
                        menusetmh[3] = menusetmn[3];
                    menusetbtanm[6].cur = 3;
                }
                menumode = 2;
                menuZoidBattleShopmenubuttonset();
                continue;
            } else if (menumode == 2) {
                if (menusetcl[menumode] == 0) {
                    if (IveSave[0].owned_zoid_count == 0 && menumodeShop == 2) {
                        change = 0;
                        SeCancel();
                        continue;
                    }
                    SeRet();
                    menusetcl[3] = 0;
                    menusetsl[3] = 0;
                    menusetst[3] = 0;
                    menusetmh[3] = 4;
                    if (menumodeShop == 1)
                        menusetmn[3] = IveSave[0].have_zoid_count;
                    if (menumodeShop == 2)
                        menusetmn[3] = IveSave[0].owned_zoid_count;
                    if (menusetmn[3] < 4)
                        menusetmh[3] = menusetmn[3];
                    menumode = 3;
                    menuZoidBattleShopmenubuttonset();
                    menu_sDispBattleShop();
                    menusetbtanm[7].cur = 2;
                    menusetbtanm[7].state = 1;
                    while (menusetbtanm[7].cur != 3)
                        menu_sDispBattleShop();
                    menudispshophavezoidlist = menumodeShop;
                    menusetbtanm[8].cur = 1;
                    menu_sDispBattleShop();
                    IveSave[0].previous_zoid_slot = IveSave[0].selected_zoid_slot;
                    if (menumodeShop == 1) {
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                menudispshophavezoidlist = 0;
                                if (IveSave[0].owned_zoid_count >= 30) {
                                    SeCancel();
                                    menudispyesnoflag = 1;
                                    menudispyesnopoint = 1;
                                    do {
                                        sPadAll();
                                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_ZOIDS_FULL), "BUY");
                                        menu_sDispBattleShop();
                                    } while (sPad1->pressed_a == 0 && sPad2->pressed_a == 0);
                                    menudispyesnoflag = 0;
                                    menu_sDispBattleShop();
                                    menudispshophavezoidlist = menumodeShop;
                                } else {
                                    dlgzoidno = IveSave[0].have_zoid[menusetcl[3]];
                                    if (IveSave[0].money >= Tea_zoiddat[dlgzoidno].price) {
                                        SeRet();
                                        menu_StageUpDownFlag = 0;
                                        while (menu_sDispBattleStageDown(1) == 0)
                                            menu_sDispBattleShop();
                                        ttl_WeaponAllUnMount(IveSave[0].previous_zoid_slot);
                                        ZoidPurge(&Zoid[0]);
                                        ttl_GameZoidSetZoidDefParts(0, dlgzoidno);
                                        if (dlgzoidno != -1)
                                            ZoidInit(&Zoid[0], dlgzoidno);
                                        if (ZoidColor(&Zoid[0], Zoid[0].color, 0) == 0)
                                            ZoidColor(&Zoid[0], 0, 0);
                                        menu_StageUpDownFlag = 0;
                                        while (menu_sDispBattleStageDown(0) == 0)
                                            menu_sDispBattleShop();
                                        menudispyesnopoint = 1;
                                        menufncShopyesno(1);
                                        if (menudispyesnopoint != 0) {
                                            IveSave[0].money -= Tea_zoiddat[dlgzoidno].price;
                                            ttl_IveSaveSetZoidDefParts(0, IveSave[0].owned_zoid_count, dlgzoidno);
                                            ttl_WeaponAllMount(IveSave[0].owned_zoid_count);
                                            IveSave[0].selected_zoid_slot = IveSave[0].owned_zoid_count;
                                            IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                                            IveSave[0].owned_zoid_count++;
                                            menudispshophavezoidlist = menumodeShop;
                                            menuZoidBattleShopmenubuttonset();
                                        } else {
                                            menu_StageUpDownFlag = 0;
                                            while (menu_sDispBattleStageDown(1) == 0)
                                                menu_sDispBattleShop();
                                            ZoidWeaponPurge(&Zoid[0]);
                                            ZoidPurge(&Zoid[0]);
                                            IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                                            if (IveSave[0].selected_zoid != -1) {
                                                ZoidInit(&Zoid[0], IveSave[0].selected_zoid);
                                                ZoidSetAnim(&Zoid[0], 103);
                                            }
                                            ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                                            if (ZoidColor(&Zoid[0], (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot], 0) == 0)
                                                ZoidColor(&Zoid[0], 0, 0);
                                            menu_StageUpDownFlag = 0;
                                            while (menu_sDispBattleStageDown(0) == 0)
                                                menu_sDispBattleShop();
                                            menudispshophavezoidlist = menumodeShop;
                                        }
                                    } else {
                                        SeCancel();
                                        menudispshophavezoidlist = menumodeShop;
                                    }
                                }
                            }
                        }
                    } else if (menumodeShop == 2) {
                        menusetmn[3] = IveSave[0].owned_zoid_count;
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                OSReport(sLogMenuSetCl, menusetcl[3]);
                                if (zn[2] == menusetcl[3]) {
                                    SeBuzzerC();
                                } else if (zn[1] == menusetcl[3] && menuZoidBattleModeSingleTeam == 1) {
                                    SeBuzzerC();
                                } else if (IveSave[0].owned_zoid_count <= 2) {
                                    SeBuzzerC();
                                } else {
                                    SeRet();
                                    menudispyesnopoint = 1;
                                    menufncShopyesno(0);
                                    if (menudispyesnopoint == 0) {
                                        menudispshophavezoidlist = menumodeShop;
                                    } else {
                                        ttl_WeaponAllUnMount(menusetcl[3]);
                                        for (j = 0; j < 8; j++) {
                                            if ((part = ttl_ZoidRemoveContractWep(0, menusetcl[3], j)) != -1) {
                                                if (IveSave[0].owned_part_count < 450)
                                                    ttl_HaveAddParts(0, part);
                                                else
                                                    IveSave[0].money += Tea_partsdat[part].sell_price;
                                            }
                                        }
                                        if ((part = ttl_ZoidRemoveContractOpt(0, menusetcl[3])) != -1) {
                                            if (IveSave[0].owned_part_count < 450)
                                                ttl_HaveAddParts(0, part);
                                            else
                                                IveSave[0].money += Tea_partsdat[part].sell_price;
                                        }
                                        for (j = 0; j < 3; j++) {
                                            if ((part = ttl_ZoidRemoveContractSub(0, menusetcl[3], j)) != -1) {
                                                if (IveSave[0].owned_part_count < 450)
                                                    ttl_HaveAddParts(0, part);
                                                else
                                                    IveSave[0].money += Tea_partsdat[part].sell_price;
                                            }
                                        }
                                        menudispshophavezoidlist = 0;
                                        change = 0;
                                        (void)(menusetcl[3] + 1);
                                        j = menusetcl[3];
                                        zn[0] = j;
                                        dlgzoidno = IveSave[0].owned_zoids[menusetcl[3]];
                                        IveSave[0].money += Tea_zoiddat[dlgzoidno].sell_price;
                                        menuZoidPartsCopy(0, IveSave[0].owned_zoid_count - 1, 0, zn[0]);
                                        menusetmn[3]--;
                                        if (menusetmn[3] < menusetmh[3])
                                            menusetmh[3] = menusetmn[3];
                                        if (menusetmn[3] - 1 < menusetcl[3]) {
                                            if (menusetst[3] > 0)
                                                menusetst[3]--;
                                        }
                                        if (menusetmh[3] - 1 < menusetsl[3])
                                            menusetsl[3] = menusetmh[3] - 1;
                                        IveSave[0].owned_zoid_count--;
                                        IveSave[4].owned_zoid_count--;
                                        if (IveSave[0].owned_zoid_count == zn[2]) {
                                            zn[2] = j;
                                            IveSave[0].selected_zoid = zn[2];
                                            OSReport(sLogMineChangeColor, j);
                                        }
                                        if (menuZoidBattleModeSingleTeam == 1 && IveSave[0].owned_zoid_count == zn[1]) {
                                            zn[1] = j;
                                            IveSave[0].partner_zoid = zn[1];
                                            OSReport(sLogPartnerChangeColor, j);
                                        }
                                        menusetcl[3] = 0;
                                        menusetst[3] = 0;
                                        IveSave[0].owned_zoids[j] = IveSave[0].owned_zoids[IveSave[0].owned_zoid_count];
                                        IveSave[0].owned_zoids[IveSave[0].owned_zoid_count] = -1;
                                        IveSave[0].selected_zoid_slot = zn[2];
                                        IveSave[0].partner_zoid_slot = zn[1];
                                        IveSave[0].selected_zoid = IveSave[0].owned_zoids[zn[2]];
                                        IveSave[0].partner_zoid = IveSave[0].owned_zoids[zn[1]];
                                        OSReport(sLogErr2Etczn, zn[0], menusetcl[3], IveSave[0].owned_zoid_count);
                                        OSReport(sLogErr2, menusetcl[3]);
                                        menu_StageUpDownFlag = 0;
                                        while (menu_sDispBattleStageDown(1) == 0)
                                            menu_sDispBattleShop();
                                        ZoidWeaponPurge(&Zoid[0]);
                                        ZoidPurge(&Zoid[0]);
                                        ZoidInit(&Zoid[0], IveSave[0].selected_zoid);
                                        ZoidSetAnim(&Zoid[0], 103);
                                        ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                                        if (ZoidColor(&Zoid[0], (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot], 0) == 0)
                                            ZoidColor(&Zoid[0], 0, 0);
                                        menu_StageUpDownFlag = 0;
                                        while (menu_sDispBattleStageDown(0) == 0)
                                            menu_sDispBattleShop();
                                        count = IveSave[0].owned_zoid_count;
                                        IveSave[0].zoid_colors[count] = 0;
                                        IveSave[4].zoid_colors[count] = 0;
                                        IveSave[0].owned_zoids[count] = -1;
                                        IveSave[4].owned_zoids[count] = -1;
                                        for (i = 0; i < 28; i++)
                                            IveSave[0].zoid_weapons[count][i] = -1;
                                        for (i = 0; i < 28; i++)
                                            IveSave[4].zoid_weapons[count][i] = -1;
                                        IveSave[0].contract_subparts[count][0] = -1;
                                        IveSave[0].contract_subparts[count][1] = -1;
                                        IveSave[0].contract_subparts[count][2] = -1;
                                        IveSave[4].contract_subparts[count][0] = -1;
                                        IveSave[4].contract_subparts[count][1] = -1;
                                        IveSave[4].contract_subparts[count][2] = -1;
                                        IveSave[0].contract_options[count] = -1;
                                        menudispshophavezoidlist = menumodeShop;
                                    }
                                }
                            }
                        }
                    }
                    menusetbtanm[8].cur = 3;
                    while (menusetbtanm[8].cur != 0)
                        menu_sDispBattleShop();
                    menusetbtanm[8].cur = 0;
                    menu_sDispBattleShop();
                    menudispshophavezoidlist = 0;
                    menuanmend = 0;
                    menusetbtanm[7].cur = 4;
                    menusetbtanm[7].state = 1;
                    menu_sDispBattleShop();
                    menumode = 2;
                    continue;
                } else if (menusetcl[menumode] == 1) {
                    if (menumodeShop == 1) {
                        if (IveSave[0].owned_zoid_count == 0) {
                            SeCancel();
                            continue;
                        }
                        SeRet();
                        SetMenuMsgAdr(68, (char *)menudispwinstr);
                        menusetbtanm[7].cur = 5;
                        menusetbtanm[7].state = 1;
                        while (menusetbtanm[7].cur != 6)
                            menu_sDispBattleShop();
                        menusetbtanm[5].cur = 3;
                        menusetbtanm[1].cur = 3;
                        menusetcl[3] = 0;
                        menusetsl[3] = 0;
                        menusetst[3] = 0;
                        menusetmh[3] = 4;
                        menusetmn[3] = IveSave[0].owned_zoid_count;
                        if (menusetmn[3] < 4)
                            menusetmh[3] = menusetmn[3];
                        menudispshophavezoidlist = 2;
                        menusetbtanm[8].cur = 1;
                        menu_sDispBattleShop();
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                dlgzoidno = IveSave[0].owned_zoids[menusetcl[3]];
                                sl = menusetsl[3];
                                st = menusetst[3];
                                mn = menusetmn[3];
                                mh = menusetmh[3];
                                menuPartsShopListZoid(1, IveSave[0].owned_zoids[menusetcl[3]]);
                                if (IveSave[0].list_count == 0) {
                                    SeCancel();
                                    break;
                                }
                                SeRet();
                                menusetbtanm[8].cur = 3;
                                while (menusetbtanm[8].cur != 0)
                                    menu_sDispBattleShop();
                                menudispshophavezoidlist = 0;
                                menusetsl[3] = 0;
                                menusetcl[3] = 0;
                                menusetst[3] = 0;
                                menusetmh[3] = 5;
                                menusetmn[3] = IveSave[0].list_count;
                                if (menusetmn[3] < 5)
                                    menusetmh[3] = menusetmn[3];
                                menuzoidhavepartslist = 1;
                                menusetbtanm[8].cur = 4;
                                while (menusetbtanm[8].cur != 5)
                                    menu_sDispBattleShop();
                                while (1) {
                                    sPadAll();
                                    menu_sDispBattleShop();
                                    menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                                    if (sPad1->pressed_b != 0) {
                                        SeCancel();
                                        SetMenuMsgAdr(68, (char *)menudispwinstr);
                                        break;
                                    }
                                    if (sPad1->pressed_a != 0) {
                                        if (IveSave[0].owned_part_count >= 450) {
                                            SeCancel();
                                            menudispyesnoflag = 1;
                                            menudispyesnopoint = 1;
                                            do {
                                                sPadAll();
                                                menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_PARTS_FULL), "BUY");
                                                menu_sDispBattleShop();
                                            } while (sPad1->pressed_a == 0 && sPad2->pressed_a == 0);
                                            menudispyesnoflag = 0;
                                            menu_sDispBattleShop();
                                        } else {
                                            dlgpartsno = IveSave[0].list_parts[menusetcl[3]];
                                            if (IveSave[0].money >= Tea_partsdat[dlgpartsno].field_50) {
                                                SeRet();
                                                menudispyesnopoint = 1;
                                                menufncShopyesno(1);
                                                if (menudispyesnopoint == 1) {
                                                    IveSave[0].owned_parts[IveSave[0].owned_part_count] = dlgpartsno;
                                                    IveSave[0].owned_part_count++;
                                                    IveSave[0].money -= Tea_partsdat[dlgpartsno].field_50;
                                                }
                                            } else {
                                                SeCancel();
                                            }
                                        }
                                    }
                                }
                                menusetsl[3] = sl;
                                menusetst[3] = st;
                                menusetmh[3] = mh;
                                menusetmn[3] = mn;
                                menusetbtanm[8].cur = 6;
                                while (menusetbtanm[8].cur != 0)
                                    menu_sDispBattleShop();
                                menuzoidhavepartslist = 0;
                                menudispshophavezoidlist = 2;
                                menusetbtanm[8].cur = 1;
                                SetMenuMsgAdr(68, (char *)menudispwinstr);
                            }
                        }
                        menusetbtanm[8].cur = 3;
                        while (menusetbtanm[8].cur != 0)
                            menu_sDispBattleShop();
                        menudispshophavezoidlist = 0;
                        menusetbtanm[7].cur = 7;
                        menusetbtanm[7].state = 1;
                        menu_sDispBattleShop();
                        menumode = 2;
                        menuZoidBattleShopmenubuttonset();
                    } else if (menumodeShop == 2) {
                        menuPartsHaveListZoid(1, -1);
                        if (IveSave[0].list_count == 0) {
                            SeCancel();
                            continue;
                        }
                        SeRet();
                        menusetbtanm[7].cur = 5;
                        menusetbtanm[7].state = 1;
                        while (menusetbtanm[7].cur != 6)
                            menu_sDispBattleShop();
                        menusetbtanm[6].cur = 3;
                        menusetbtanm[1].cur = 3;
                        menusetsl[3] = 0;
                        menusetcl[3] = 0;
                        menusetst[3] = 0;
                        menusetmh[3] = 5;
                        menusetmn[3] = IveSave[0].list_count;
                        if (menusetmn[3] < 5)
                            menusetmh[3] = menusetmn[3];
                        menuzoidhavepartslist = 1;
                        menusetbtanm[8].cur = 7;
                        while (menusetbtanm[8].cur != 8)
                            menu_sDispBattleShop();
                        shopDispParts(0);
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                    s32 sel;
                                    s32 count;

                                sel = menusetcl[3];
                                count = IveSave[0].list_count;
                                if (IveSave[0].list_parts[sel] <= 0 || count <= 0) {
                                    SeCancel();
                                } else {
                                    SeRet();
                                    menudispyesnopoint = 1;
                                    menufncShopyesno(0);
                                    if (menudispyesnopoint != 0) {
                                        s16 slot;

                                        slot = IveSave[0].list_flag[sel];
                                        dlgpartsno = IveSave[0].list_parts[sel];
                                        OSReport(sLogPartsColorMax, slot, dlgpartsno, menusetcl[3], count);
                                        IveSave[0].money += Tea_partsdat[dlgpartsno].sell_price;
                                        IveSave[0].list_count--;
                                        last = count - 1;
                                        IveSave[0].list_parts[sel] = IveSave[0].list_parts[last];
                                        IveSave[0].list_flag[sel] = IveSave[0].list_flag[last];
                                        IveSave[0].list_parts[last] = -1;
                                        IveSave[0].list_flag[last] = -1;
                                        IveSave[0].owned_parts[slot] = -1;
                                        menusetmn[3] = IveSave[0].list_count;
                                        if (menusetmn[3] < menusetmh[3])
                                            menusetmh[3] = menusetmn[3];
                                        if (menusetmn[3] - 1 < menusetcl[3])
                                            menusetsl[3] = menusetmn[3] - 1;
                                        if (menusetmn[3] - 1 < menusetcl[3]) {
                                            if (menusetst[3] > 0)
                                                menusetst[3]--;
                                        }
                                        if (menusetmh[3] - 1 < menusetsl[3])
                                            menusetsl[3] = menusetmh[3] - 1;
                                    }
                                }
                            }
                        }
                        menusetbtanm[8].cur = 9;
                        while (menusetbtanm[8].cur != 0)
                            menu_sDispBattleShop();
                        menuzoidhavepartslist = 0;
                        menusetbtanm[7].cur = 7;
                        menusetbtanm[7].state = 1;
                        menu_sDispBattleShop();
                        shopDispParts(0);
                        shopSortParts(0);
                        shopDispParts(0);
                        menumode = 2;
                        menuZoidBattleShopmenubuttonset();
                        shopDispParts(0);
                    }
                    continue;
                } else if (menusetcl[menumode] == 2) {
                    if (menumodeShop == 1) {
                        if (IveSave[0].owned_zoid_count == 0) {
                            SeCancel();
                            continue;
                        }
                        SeRet();
                        SetMenuMsgAdr(69, (char *)menudispwinstr);
                        menusetbtanm[7].cur = 8;
                        menusetbtanm[7].state = 1;
                        while (menusetbtanm[7].cur != 9)
                            menu_sDispBattleShop();
                        menusetbtanm[5].cur = 3;
                        menusetbtanm[2].cur = 3;
                        menusetcl[3] = 0;
                        menusetsl[3] = 0;
                        menusetst[3] = 0;
                        menusetmh[3] = 4;
                        menusetmn[3] = IveSave[0].owned_zoid_count;
                        if (menusetmn[3] < 4)
                            menusetmh[3] = menusetmn[3];
                        menudispshophavezoidlist = 2;
                        menusetbtanm[8].cur = 1;
                        menu_sDispBattleShop();
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                SeRet();
                                dlgzoidno = IveSave[0].owned_zoids[menusetcl[3]];
                                slB = menusetsl[3];
                                stB = menusetst[3];
                                mhB = menusetmn[3];
                                mnB = menusetmh[3];
                                menuPartsShopListZoid(2, IveSave[0].owned_zoids[menusetcl[3]]);
                                menusetbtanm[8].cur = 3;
                                while (menusetbtanm[8].cur != 0)
                                    menu_sDispBattleShop();
                                menudispshophavezoidlist = 0;
                                menusetsl[3] = 0;
                                menusetcl[3] = 0;
                                menusetst[3] = 0;
                                menusetmh[3] = 5;
                                menusetmn[3] = IveSave[0].list_count;
                                if (menusetmn[3] < 5)
                                    menusetmh[3] = menusetmn[3];
                                menuzoidhavepartslist = 2;
                                menusetbtanm[8].cur = 4;
                                while (menusetbtanm[8].cur != 5)
                                    menu_sDispBattleShop();
                                while (1) {
                                    sPadAll();
                                    menu_sDispBattleShop();
                                    menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                                    if (sPad1->pressed_b != 0) {
                                        SeCancel();
                                        break;
                                    }
                                    if (sPad1->pressed_a != 0) {
                                        if (IveSave[0].owned_part_count >= 450) {
                                            SeCancel();
                                            menudispyesnoflag = 1;
                                            menudispyesnopoint = 1;
                                            do {
                                                sPadAll();
                                                menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_PARTS_FULL), "BUY");
                                                menu_sDispBattleShop();
                                            } while (sPad1->pressed_a == 0 && sPad2->pressed_a == 0);
                                            menudispyesnoflag = 0;
                                            menu_sDispBattleShop();
                                        } else {
                                            dlgpartsno = IveSave[0].list_parts[menusetcl[3]];
                                            if (IveSave[0].money >= Tea_partsdat[dlgpartsno].field_50) {
                                                SeRet();
                                                menudispyesnopoint = 1;
                                                menufncShopyesno(1);
                                                if (menudispyesnopoint != 0) {
                                                    IveSave[0].owned_parts[IveSave[0].owned_part_count] = dlgpartsno;
                                                    IveSave[0].owned_part_count++;
                                                    IveSave[0].money -= Tea_partsdat[dlgpartsno].field_50;
                                                }
                                            } else {
                                                SeCancel();
                                            }
                                        }
                                    }
                                }
                                menusetsl[3] = slB;
                                menusetst[3] = stB;
                                menusetmh[3] = mnB;
                                menusetmn[3] = mhB;
                                menusetbtanm[8].cur = 6;
                                while (menusetbtanm[8].cur != 0)
                                    menu_sDispBattleShop();
                                menuzoidhavepartslist = 0;
                                menudispshophavezoidlist = 2;
                                menusetbtanm[8].cur = 1;
                                SetMenuMsgAdr(69, (char *)menudispwinstr);
                            }
                        }
                        menusetbtanm[8].cur = 3;
                        while (menusetbtanm[8].cur != 0)
                            menu_sDispBattleShop();
                        menudispshophavezoidlist = 0;
                        menusetbtanm[7].cur = 10;
                        menusetbtanm[7].state = 1;
                        menu_sDispBattleShop();
                        menumode = 2;
                        menuZoidBattleShopmenubuttonset();
                    } else if (menumodeShop == 2) {
                        menuPartsHaveListZoid(2, -1);
                        if (IveSave[0].list_count == 0) {
                            SeCancel();
                            continue;
                        }
                        SeRet();
                        menusetbtanm[7].cur = 8;
                        menusetbtanm[7].state = 1;
                        while (menusetbtanm[7].cur != 9)
                            menu_sDispBattleShop();
                        menusetbtanm[6].cur = 3;
                        menusetbtanm[2].cur = 3;
                        menusetsl[3] = 0;
                        menusetcl[3] = 0;
                        menusetst[3] = 0;
                        menusetmh[3] = 5;
                        menusetmn[3] = IveSave[0].list_count;
                        if (menusetmn[3] < 5)
                            menusetmh[3] = menusetmn[3];
                        menuzoidhavepartslist = 2;
                        menusetbtanm[8].cur = 7;
                        while (menusetbtanm[8].cur != 8)
                            menu_sDispBattleShop();
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                    s16 sel;
                                    s32 count;
                                    s16 slot2;

                                if (IveSave[0].list_parts[menusetcl[3]] <= 0 || IveSave[0].list_count <= 0) {
                                    SeCancel();
                                } else {
                                    SeRet();
                                    menudispyesnopoint = 1;
                                    menufncShopyesno(0);
                                    if (menudispyesnopoint != 0) {
                                        sel = menusetcl[3];
                                        count = IveSave[0].list_count - 1;
                                        slot2 = IveSave[0].list_flag[sel];
                                        dlgpartsno = IveSave[0].list_parts[sel];
                                        IveSave[0].money += Tea_partsdat[dlgpartsno].sell_price;
                                        IveSave[0].list_count--;
                                        IveSave[0].list_parts[menusetcl[3]] = IveSave[0].list_parts[count];
                                        IveSave[0].list_flag[menusetcl[3]] = IveSave[0].list_flag[count];
                                        IveSave[0].list_parts[count] = -1;
                                        IveSave[0].list_flag[count] = -1;
                                        IveSave[0].owned_parts[slot2] = -1;
                                        IveSave[0].owned_part_count--;
                                        menusetmn[3] = IveSave[0].list_count;
                                        if (menusetmn[3] < menusetmh[3])
                                            menusetmh[3] = menusetmn[3];
                                        if (menusetmn[3] - 1 < sel) {
                                            if (menusetst[3] > 0)
                                                menusetst[3]--;
                                        }
                                        if (menusetmh[3] - 1 < menusetsl[3])
                                            menusetsl[3] = menusetmh[3] - 1;
                                    }
                                }
                            }
                        }
                        menusetbtanm[8].cur = 9;
                        while (menusetbtanm[8].cur != 0)
                            menu_sDispBattleShop();
                        menuzoidhavepartslist = 0;
                        shopSortParts(0);
                        menusetbtanm[7].cur = 10;
                        menusetbtanm[7].state = 1;
                        menu_sDispBattleShop();
                        menumode = 2;
                        menuZoidBattleShopmenubuttonset();
                    }
                    continue;
                } else if (menusetcl[menumode] == 3) {
                    if (menumodeShop == 1) {
                        if (IveSave[0].owned_zoid_count == 0) {
                            SeCancel();
                            continue;
                        }
                        SeRet();
                        SetMenuMsgAdr(70, (char *)menudispwinstr);
                        menusetbtanm[7].cur = 11;
                        menusetbtanm[7].state = 1;
                        while (menusetbtanm[7].cur != 12)
                            menu_sDispBattleShop();
                        menusetbtanm[5].cur = 3;
                        menusetbtanm[3].cur = 3;
                        menusetcl[3] = 0;
                        menusetsl[3] = 0;
                        menusetst[3] = 0;
                        menusetmh[3] = 4;
                        menusetmn[3] = IveSave[0].owned_zoid_count;
                        if (menusetmn[3] < 4)
                            menusetmh[3] = menusetmn[3];
                        menudispshophavezoidlist = 2;
                        menusetbtanm[8].cur = 1;
                        menu_sDispBattleShop();
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                SeRet();
                                dlgzoidno = IveSave[0].owned_zoids[menusetcl[3]];
                                mh = menusetmh[3];
                                sl = menusetsl[3];
                                mn = menusetmn[3];
                                st = menusetst[3];
                                menuPartsShopListZoid(3, IveSave[0].owned_zoids[menusetcl[3]]);
                                menusetbtanm[8].cur = 3;
                                while (menusetbtanm[8].cur != 0)
                                    menu_sDispBattleShop();
                                menudispshophavezoidlist = 0;
                                menusetsl[3] = 0;
                                menusetcl[3] = 0;
                                menusetst[3] = 0;
                                menusetmh[3] = 5;
                                menusetmn[3] = IveSave[0].list_count;
                                if (menusetmn[3] < 5)
                                    menusetmh[3] = menusetmn[3];
                                menuzoidhavepartslist = 3;
                                menusetbtanm[8].cur = 4;
                                while (menusetbtanm[8].cur != 5)
                                    menu_sDispBattleShop();
                                while (1) {
                                    sPadAll();
                                    menu_sDispBattleShop();
                                    menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                                    if (sPad1->pressed_b != 0) {
                                        SeCancel();
                                        break;
                                    }
                                    if (sPad1->pressed_a != 0) {
                                        if (IveSave[0].owned_part_count >= 450) {
                                            SeCancel();
                                            menudispyesnoflag = 1;
                                            menudispyesnopoint = 1;
                                            do {
                                                sPadAll();
                                                menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_PARTS_FULL), "BUY");
                                                menu_sDispBattleShop();
                                            } while (sPad1->pressed_a == 0 && sPad2->pressed_a == 0);
                                            menudispyesnoflag = 0;
                                            menu_sDispBattleShop();
                                        } else {
                                            dlgpartsno = IveSave[0].list_parts[menusetcl[3]];
                                            if (IveSave[0].money >= Tea_partsdat[dlgpartsno].field_50) {
                                                SeRet();
                                                menudispyesnopoint = 1;
                                                menufncShopyesno(1);
                                                if (menudispyesnopoint != 0) {
                                                    IveSave[0].owned_parts[IveSave[0].owned_part_count] = dlgpartsno;
                                                    IveSave[0].owned_part_count++;
                                                    IveSave[0].money -= Tea_partsdat[dlgpartsno].field_50;
                                                }
                                            } else {
                                                SeCancel();
                                            }
                                        }
                                    }
                                }
                                menusetsl[3] = sl;
                                menusetst[3] = st;
                                menusetmh[3] = mh;
                                menusetmn[3] = mn;
                                SetMenuMsgAdr(70, (char *)menudispwinstr);
                                menusetbtanm[8].cur = 6;
                                while (menusetbtanm[8].cur != 0)
                                    menu_sDispBattleShop();
                                menuzoidhavepartslist = 0;
                                menudispshophavezoidlist = 2;
                                menusetbtanm[8].cur = 1;
                                SetMenuMsgAdr(70, (char *)menudispwinstr);
                            }
                        }
                        menusetbtanm[8].cur = 3;
                        while (menusetbtanm[8].cur != 0)
                            menu_sDispBattleShop();
                        menudispshophavezoidlist = 0;
                        menusetbtanm[7].cur = 10;
                        menusetbtanm[7].state = 1;
                        menu_sDispBattleShop();
                        menumode = 2;
                        menuZoidBattleShopmenubuttonset();
                    } else if (menumodeShop == 2) {
                        menuPartsHaveListZoid(3, -1);
                        if (IveSave[0].list_count == 0) {
                            SeCancel();
                            continue;
                        }
                        SeRet();
                        menusetbtanm[7].cur = 11;
                        menusetbtanm[7].state = 1;
                        while (menusetbtanm[7].cur != 12)
                            menu_sDispBattleShop();
                        menusetbtanm[6].cur = 3;
                        menusetbtanm[3].cur = 3;
                        menusetsl[3] = 0;
                        menusetcl[3] = 0;
                        menusetst[3] = 0;
                        menusetmh[3] = 5;
                        menusetmn[3] = IveSave[0].list_count;
                        if (menusetmn[3] < 5)
                            menusetmh[3] = menusetmn[3];
                        menuzoidhavepartslist = 3;
                        menusetbtanm[8].cur = 7;
                        while (menusetbtanm[8].cur != 8)
                            menu_sDispBattleShop();
                        while (1) {
                            sPadAll();
                            menu_sDispBattleShop();
                            menusetcl[3] = TEA_menufnc(&menusetsl[3], &menusetst[3], menusetmn[3], menusetmh[3]);
                            if (sPad1->pressed_b != 0) {
                                SeCancel();
                                break;
                            }
                            if (sPad1->pressed_a != 0) {
                                    s16 sel;
                                    s32 count;
                                    s16 slot2;

                                if (IveSave[0].list_parts[menusetcl[3]] <= 0 || IveSave[0].list_count <= 0) {
                                    SeCancel();
                                } else {
                                    SeRet();
                                    menudispyesnopoint = 1;
                                    menufncShopyesno(0);
                                    if (menudispyesnopoint != 0) {
                                        sel = menusetcl[3];
                                        count = IveSave[0].list_count - 1;
                                        slot2 = IveSave[0].list_flag[sel];
                                        dlgpartsno = IveSave[0].list_parts[sel];
                                        IveSave[0].money += Tea_partsdat[dlgpartsno].sell_price;
                                        IveSave[0].list_count--;
                                        IveSave[0].list_parts[menusetcl[3]] = IveSave[0].list_parts[count];
                                        IveSave[0].list_flag[menusetcl[3]] = IveSave[0].list_flag[count];
                                        IveSave[0].list_parts[count] = -1;
                                        IveSave[0].list_flag[count] = -1;
                                        IveSave[0].owned_parts[slot2] = -1;
                                        IveSave[0].owned_part_count--;
                                        menusetmn[3] = IveSave[0].list_count;
                                        if (menusetmn[3] < menusetmh[3])
                                            menusetmh[3] = menusetmn[3];
                                        if (menusetmn[3] - 1 < sel) {
                                            if (menusetst[3] > 0)
                                                menusetst[3]--;
                                        }
                                        if (menusetmh[3] - 1 < menusetsl[3])
                                            menusetsl[3] = menusetmh[3] - 1;
                                    }
                                }
                            }
                        }
                        menusetbtanm[8].cur = 9;
                        while (menusetbtanm[8].cur != 0)
                            menu_sDispBattleShop();
                        menuzoidhavepartslist = 0;
                        shopSortParts(0);
                        menusetbtanm[7].cur = 10;
                        menusetbtanm[7].state = 1;
                        menu_sDispBattleShop();
                        menumode = 2;
                        menuZoidBattleShopmenubuttonset();
                    }
                    continue;
                }
            }
            if (menumode == 3) {
                menusetbtanm[8].cur = 3;
                while (menusetbtanm[8].cur != 0)
                    menu_sDispBattleShop();
                menusetbtanm[8].cur = 0;
                menu_sDispBattleShop();
                menudispshophavezoidlist = 0;
                if (menumodeShop == 1) {
                    dlgzoidno = IveSave[0].have_zoid[menusetcl[3]];
                    if (IveSave[0].money >= Tea_zoiddat[dlgzoidno].price) {
                        SeRet();
                        ttl_IveSaveSetZoidDefParts(0, IveSave[0].owned_zoid_count, dlgzoidno);
                        IveSave[0].owned_zoid_count++;
                        change = 1;
                        IveSave[0].money -= Tea_zoiddat[dlgzoidno].price;
                        menuanmend = 0;
                        menusetbtanm[7].cur = 4;
                        menusetbtanm[7].state = 1;
                        menu_sDispBattleShop();
                        menu_StageUpDownFlag = 0;
                        menumode = 2;
                        while (menu_sDispBattleStageDown(1) == 0)
                            menu_sDispBattleShop();
                        ttl_WeaponAllUnMount(IveSave[0].previous_zoid_slot);
                        ZoidPurge(&Zoid[0]);
                        IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot] = 0;
                    } else {
                        SeCancel();
                    }
                }
                if (menumodeShop == 2) {
                    menuanmend = 0;
                    menusetbtanm[7].cur = 4;
                    menusetbtanm[7].state = 1;
                    menu_sDispBattleShop();
                    menumode = 2;
                    if (IveSave[0].owned_zoid_count <= 1) {
                        change = 0;
                        SeCancel();
                    } else {
                        SeRet();
                        sel = menusetcl[3];
                        dlgzoidno = IveSave[0].owned_zoids[sel];
                        if (dlgzoidno == IveSave[0].selected_zoid)
                            change = 1;
                        else
                            change = 0;
                        IveSave[0].money += Tea_zoiddat[dlgzoidno].sell_price;
                        if (IveSave[0].owned_zoid_count != 0) {
                            if (change == 1) {
                                menu_StageUpDownFlag = 0;
                                while (menu_sDispBattleStageDown(1) == 0)
                                    menu_sDispBattleShop();
                                ZoidWeaponPurge(&Zoid[0]);
                                ttl_WeaponAllUnMount(menusetcl[3]);
                                ZoidPurge(&Zoid[0]);
                            }
                            IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot] = 0;
                            IveSave[0].owned_zoid_count--;
                            IveSave[0].owned_zoids[sel] = IveSave[0].owned_zoids[IveSave[0].owned_zoid_count];
                            for (i = 0; i < 28; i++)
                                IveSave[0].zoid_weapons[sel][i] = IveSave[0].zoid_weapons[IveSave[0].owned_zoid_count][i];
                            IveSave[0].owned_zoids[IveSave[0].owned_zoid_count] = -1;
                            for (i = 0; i < 10; i++)
                                IveSave[0].zoid_weapons[IveSave[0].owned_zoid_count][i] = -1;
                            IveSave[0].selected_zoid = IveSave[0].owned_zoids[0];
                        } else {
                            IveSave[0].owned_zoid_count = 0;
                            IveSave[0].owned_zoids[0] = -1;
                            IveSave[0].selected_zoid = -1;
                        }
                        IveSave[0].selected_zoid_slot = 0;
                    }
                }
                if (change == 1) {
                    if (IveSave[0].selected_zoid != -1) {
                        ZoidSetAnim(&Zoid[0], 103);
                        ZoidInit(&Zoid[0], IveSave[0].selected_zoid);
                    }
                    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                    menu_StageUpDownFlag = 0;
                    while (menu_sDispBattleStageDown(0) == 0)
                        menu_sDispBattleShop();
                    menuZoidBattleShopmenubuttonset();
                }
            }
            if (menumode == 4) {
                menumode = 2;
                continue;
            }
            if (menumode == 7) {
                menumode = 2;
                continue;
            }
            if (menumode == 6) {
                menumode = 2;
                continue;
            }
            if (menumode == 8) {
                menumode = 2;
                continue;
            }
            if (menumode == 5) {
                menumode = 2;
                continue;
            }
        }
        if (sPad1->pressed_b != 0) {
            SeCancel();
            if (menumode == 3) {
                menuanmend = 0;
                menusetbtanm[7].cur = 4;
                menusetbtanm[7].state = 1;
                menu_sDispBattleShop();
                menudispshophavezoidlist = 0;
                menumode = 2;
                menuZoidBattleShopmenubuttonset();
                menudispshophavezoidlist = 0;
            } else if (menumode == 2) {
                menusetbtanm[10].cur = 0;
                menusetbtanm[10].state = 1;
                menu_sDispBattleShop();
                menuanmend = 0;
                menusetbtanm[7].cur = 14;
                menusetbtanm[7].state = 1;
                menu_sDispBattleShop();
                menumode = 10;
                menuZoidBattleShopmenubuttonset();
            } else if (menumode == 10) {
                menusetbtanm[10].cur = 0;
                menusetbtanm[10].state = 1;
                menu_sDispBattleShop();
                menumode = 1;
                menuZoidBattleShopmenubuttonset();
            } else {
                menumode = 1;
            }
            continue;
        }
        menu_sDispBattleShop();
    }
    menusetbtanm[4].cur = 4;
    menusetbtanm[4].state = 1;
    menuHiddenTitle();
    menubackcampos.x = menubackcambak.x;
    for (i = 0; i < 12; i++) {
        menubackintpos.x = -6.0 - (menubackintbak.x - i * 0.5);
        menu_sDispBattleShop();
    }
    menumode = 0;
    menu_sDispBattleShop();
    menubackcampos.x = menubackcambak.x;
    menubackintpos.x = menubackintbak.x;
    menu_sDispBattleShop();
    return 205;
}
#pragma pop


void menu_sDispMissionDemoMsgCursor(void)
{
    HSD_JObj *cursor;
    s32 unused[2];

    if (menudemocur == 0)
        return;
    if (menudemokeywait == 0)
        return;
    if (menudemocharain == 0)
        return;
    cursor = GetChild(menudemo[0]->models[1], 0, -1, -1, -1, -1);
    if (menudemocur == 1) {
        SetAnimArc2(menudemo[0], 1, 0);
        menudemocur = 2;
    }
    if (menudemocur == 2)
        jobjAnim(menudemo[0]->models[1]);
    jobjDispAll(cursor);
}


void menu_sDispMisEntryPersonPartnerZoidPic(void)
{
    HSD_JObj *pos;
    HSD_JObj *pic;
    s16 partner;
    s32 unused[6];

    partner = IveSave[0].selected_person;
    if (partner != -1) {
        pos = GetChild(menu1p->models[6], 0, 0, 1, -1, -1);
        pic = GetChild(menu_personp[partner]->models[0], 0, 0, -1, -1, -1);
        jobjCopyPos(pos, pic);
        HSD_JObjDispAll(pic, 0, 7, 0);
    }
    pos = GetChild(menu1p->models[6], 0, 0, 2, -1, -1);
    pic = GetChild(menu_zoidp[IveSave[0].selected_zoid]->models[0], 0, 0, -1, -1, -1);
    if (pic != 0) {
        jobjCopyPos(pos, pic);
        HSD_JObjDispAll(pic, 0, 7, 0);
    }
}


void menu_sDispBattleHumanEntryPersonPartnerZoidPic(void)
{
    HSD_JObj *pos;
    HSD_JObj *pic;
    s16 partner;
    s32 unused[6];

    partner = IveSave[0].selected_person;
    if (partner != -1) {
        pos = GetChild(menu1p->models[4], 0, 0, 1, -1, -1);
        pic = GetChild(menu_personp[partner]->models[0], 0, 0, -1, -1, -1);
        jobjCopyPos(pos, pic);
        HSD_JObjDispAll(pic, 0, 7, 0);
    }
    if (menuZoidBattleModeSingleTeam == 1) {
        partner = IveSave[0].partner_person;
        if (partner != -1) {
            pos = GetChild(menu1p->models[4], 0, 1, 1, -1, -1);
            pic = GetChild(menu_personp[partner]->models[0], 0, 0, -1, -1, -1);
            jobjCopyPos(pos, pic);
            HSD_JObjDispAll(pic, 0, 7, 0);
        }
    }
}


void menu_sDispBattleHumanEntryPersonZoidStatus(void)
{
    s32 idx = 4;
    s32 unused[4];

    jobjDispAll(GetChild(menu1p->models[idx], 0, 0, 0, -1, -1));
    jobjDispAll(GetChild(menu1p->models[idx], 0, 1, 0, -1, -1));
    putAscJobj(GetChild(menu1p->models[idx], 0, 0, 0, 0, -1), 1, Tea_persondat[IveSave[0].selected_person].name);
    if (menuZoidBattleModeSingleTeam == 1)
        putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), 1, Tea_persondat[IveSave[0].partner_person].name);
    else
        putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), 1, (char *)sNoEntryLabel);
}


void menu_sDispStartWhiteInWhiteOut(void)
{
    s32 unused[4];

    if (menu1p == 0)
        return;
    if (menutitleanm[1].state != menutitleanm[1].next) {
        menutitleanm[1].mode = 1;
        menutitleanm[1].next = menutitleanm[1].state;
    }
    if (menutitleanm[1].mode == 3)
        return;
    if (menutitleanm[1].mode == 1) {
        menutitleanm[1].mode = 2;
        SetAnimArc2(menu1p, 8, menutitleanm[1].state);
    }
    if (menutitleanm[1].mode == 2 && jobjAnim(menu1p->models[8]) != 0) {
        if (menutitleanm[1].state == 0) {
            menutitleanm[1].state = 2;
            menutitleanm[1].mode = 2;
        } else if (menutitleanm[1].state == 1) {
            menutitleanm[1].state = 3;
            menutitleanm[1].mode = 2;
        }
        SetAnimArc2(menu1p, 8, menutitleanm[1].state);
        jobjAnim(menu1p->models[8]);
        menuanmend = 1;
        return;
    }
    HSD_JObjDispAll(GetChild(menu1p->models[8], 0, -1, -1, -1, -1), 0, 7, 0);
}


void menu_sDispStartMainMenu(void)
{
    s32 n;
    s32 unused[2];

    if (menu1p == 0)
        return;
    if (menumode != 2)
        return;
    n = 2;
    if (menutitleanm[2].state != menutitleanm[2].next) {
        menutitleanm[2].mode = 1;
        menutitleanm[2].next = menutitleanm[2].state;
    }
    if (menutitleanm[2].mode == 1) {
        menutitleanm[2].mode = 2;
        SetAnimArc2(menu1p, 2, menutitleanm[n].state);
    }
    if (menutitleanm[2].mode == 2) {
        u8 idx = 2;

        if (jobjAnim(menu1p->models[idx]) != 0) {
            menutitleanm[2].mode = 3;
            menuanmend = 1;
            if (menutitleanm[2].state == 2)
                return;
            if (menutitleanm[2].state == 0) {
                menutitleanm[2].state = 1;
                menutitleanm[2].mode = idx;
            }
            SetAnimArc2(menu1p, 2, menutitleanm[n].state);
            jobjAnim(menu1p->models[idx]);
        }
    }
    {
        s32 idx = 2;

        HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
    }
}


void menu_sDispZoidBattleNewGameLoadGame(void)
{
    s32 n;
    s32 unused[2];

    if (menu1p == 0)
        return;
    if (menumode != 3)
        return;
    n = 3;
    if (menutitleanm[3].state != menutitleanm[3].next) {
        menutitleanm[3].mode = 1;
        menutitleanm[3].next = menutitleanm[3].state;
    }
    if (menutitleanm[3].mode == 1) {
        menutitleanm[3].mode = 2;
        SetAnimArc2(menu1p, 3, menutitleanm[n].state);
    }
    if (menutitleanm[3].mode == 2) {
        u8 idx = 3;

        if (jobjAnim(menu1p->models[idx]) != 0) {
            menutitleanm[3].mode = 3;
            menuanmend = 1;
            if (menutitleanm[3].state == 2)
                return;
            if (menutitleanm[3].state == 0) {
                menutitleanm[3].state = 1;
                menutitleanm[3].mode = 2;
            }
            SetAnimArc2(menu1p, 3, menutitleanm[n].state);
            jobjAnim(menu1p->models[idx]);
        }
    }
    {
        s32 idx = 3;

        HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
    }
}


void menu_sDispZoidBattleSingleTeamGame(void)
{
    s32 n;
    s32 unused[2];

    if (menu1p == 0)
        return;
    if (menumode != 4)
        return;
    n = 4;
    if (menutitleanm[4].state != menutitleanm[4].next) {
        menutitleanm[4].mode = 1;
        menutitleanm[4].next = menutitleanm[4].state;
    }
    if (menutitleanm[4].mode == 1) {
        menutitleanm[4].mode = 2;
        SetAnimArc2(menu1p, 4, menutitleanm[n].state);
    }
    if (menutitleanm[4].mode == 2) {
        u8 idx = 4;

        if (jobjAnim(menu1p->models[idx]) != 0) {
            menutitleanm[4].mode = 3;
            menuanmend = 1;
            if (menutitleanm[4].state == 2)
                return;
            if (menutitleanm[4].state == 0) {
                menutitleanm[4].state = 1;
                menutitleanm[4].mode = 2;
            }
            SetAnimArc2(menu1p, 4, menutitleanm[n].state);
            jobjAnim(menu1p->models[idx]);
        }
    }
    {
        s32 idx = 4;

        HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
    }
}


void menu_sDispZoidVSGame(void)
{
    s32 n;
    s32 unused[2];

    if (menu1p == 0)
        return;
    if (menumode != 5)
        return;
    n = 5;
    if (menutitleanm[5].state != menutitleanm[5].next) {
        menutitleanm[5].mode = 1;
        menutitleanm[5].next = menutitleanm[5].state;
    }
    if (menutitleanm[5].mode == 1) {
        menutitleanm[5].mode = 2;
        SetAnimArc2(menu1p, 5, menutitleanm[n].state);
    }
    if (menutitleanm[5].mode == 2) {
        u8 idx = 5;

        if (jobjAnim(menu1p->models[idx]) != 0) {
            menutitleanm[5].mode = 3;
            menuanmend = 1;
            if (menutitleanm[5].state == 2)
                return;
            if (menutitleanm[5].state == 0) {
                menutitleanm[5].state = 1;
                menutitleanm[5].mode = 2;
            }
            SetAnimArc2(menu1p, 5, menutitleanm[n].state);
            jobjAnim(menu1p->models[idx]);
        }
    }
    {
        s32 idx = 5;

        HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
    }
}


void menu_sDispZoidEmpireCountry(void)
{
    s32 n;
    s32 unused[2];

    if (menu1p == 0)
        return;
    if (menumode != 6)
        return;
    n = 6;
    if (menutitleanm[6].state != menutitleanm[6].next) {
        menutitleanm[6].mode = 1;
        menutitleanm[6].next = menutitleanm[6].state;
    }
    if (menutitleanm[6].mode == 1) {
        menutitleanm[6].mode = 2;
        SetAnimArc2(menu1p, 6, menutitleanm[n].state);
    }
    if (menutitleanm[6].mode == 2) {
        u8 idx = 6;

        if (jobjAnim(menu1p->models[idx]) != 0) {
            menutitleanm[6].mode = 3;
            menuanmend = 1;
            if (menutitleanm[6].state == 2)
                return;
            if (menutitleanm[6].state == 0) {
                menutitleanm[6].state = 1;
                menutitleanm[6].mode = 2;
            }
            SetAnimArc2(menu1p, 6, menutitleanm[n].state);
            jobjAnim(menu1p->models[idx]);
        }
    }
    {
        s32 idx = 6;

        HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
    }
}


void menu_sDispStartPushStart(void)
{
    s32 idx = 1;
    s32 unused[4];

    if (menu1p == 0)
        return;
    if (menumode == 0)
        return;
    if (menumode > 1)
        return;
    if (menutitleanm[0].state != menutitleanm[0].next) {
        menutitleanm[0].mode = 1;
        menutitleanm[0].next = menutitleanm[0].state;
    }
    if (menutitleanm[0].mode == 1) {
        menutitleanm[0].mode = 2;
        SetAnimArc2(menu1p, 1, menutitleanm[0].state);
    }
    if (menutitleanm[0].mode == 2 && jobjAnim(menu1p->models[1]) != 0) {
        menutitleanm[0].mode = 3;
        menuanmend = 1;
        if (menutitleanm[0].state == 2) {
            menutitleanm[0].next = 2;
            menutitleanm[0].mode = 0;
            return;
        } else if (menutitleanm[0].state == 0) {
            menutitleanm[0].state = 1;
            menutitleanm[0].mode = 2;
        } else if (menutitleanm[0].state == 1) {
            menutitleanm[0].state = 3;
            menutitleanm[0].mode = 2;
        } else if (menutitleanm[0].state == 3) {
            menutitleanm[0].state = 3;
            menutitleanm[0].mode = 1;
        }
        SetAnimArc2(menu1p, 1, menutitleanm[0].state);
        jobjAnim(menu1p->models[1]);
    }
    if (menutitleanm[0].mode == 0)
        return;
    HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
}


void menu_sDispStartPushLogo(void)
{
    s32 idx = 9;
    s32 n = 9;
    s32 unused[4];

    if (menu1p == 0)
        return;
    if (menutitleanm[9].state != menutitleanm[9].next) {
        menutitleanm[9].mode = 1;
        menutitleanm[9].next = menutitleanm[9].state;
    }
    if (menutitleanm[9].mode == 1) {
        menutitleanm[9].mode = 2;
        SetAnimArc2(menu1p, 9, menutitleanm[n].state);
    }
    if (menutitleanm[9].mode == 2 && jobjAnim(menu1p->models[idx]) != 0) {
        menutitleanm[9].mode = 3;
        menuanmend = 1;
        if (menutitleanm[9].state == 1 || menutitleanm[9].state == 3) {
            if (menutitleanm[9].state == 1)
                menutitleanm[9].state = 2;
            if (menutitleanm[9].state == 3)
                menutitleanm[9].state = 0;
            SetAnimArc2(menu1p, 9, menutitleanm[n].state);
            jobjAnim(menu1p->models[idx]);
        } else if (menutitleanm[9].state == 0 || menutitleanm[9].state == 2) {
            if (menutitleanm[9].state == 0)
                menutitleanm[9].mode = 2;
            if (menutitleanm[9].state == 3)
                menutitleanm[9].mode = 2;
            SetAnimArc2(menu1p, 9, menutitleanm[n].state);
            jobjAnim(menu1p->models[idx]);
        }
    }
    if (menutitleanm[9].mode == 0)
        return;
    HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
}


extern char *GetMenuMsgAdr(s16 message);
extern void jobjDisp(HSD_JObj *joint);
extern void sPutFontRect(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);

void menu_sDispMissionDemoMsgArea(void)
{
    HSD_JObj *end;
    HSD_JObj *start;

    jobjDispAll(GetChild(menudemo[0]->models[0], 0, 1, IveSave[0].country - 1, -1, -1));
    jobjDisp(GetChild(menudemo[0]->models[0], 0, -1, -1, -1, -1));
    jobjDispAll(GetChild(menudemo[0]->models[0], 0, 0, -1, -1, -1));
    if (menudemocharain == 1 && menudemomsg != -1) {
        start = GetChild(menudemo[0]->models[0], 0, 0, 0, -1, -1);
        end = GetChild(menudemo[0]->models[0], 0, 0, 2, 0, -1);
        sPutFontRect(GetMenuMsgAdr(menudemomsg), start, end, (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);
    }
}


void menu_sDispMissionDemoPerson(s16 side)
{
    s32 who;
    s32 i;
    s16 anm;
    s32 unused[2];
    HSD_JObj *jobj;

    if (side == 0)
        who = Tea_demomsg[menudemoC].who0;
    else
        who = Tea_demomsg[menudemoC].who1;
    if (who == -1) {
        menudemoanmend[side] = 1;
        return;
    }
    i = side;
    jobj = GetChild(menudemo[side + 1]->models[0], 0, who, -1, -1, -1);
    anm = menudemocha[i * 3 + 1];
    if (menudemocha[i * 3] == 1) {
        SetAnimArc2(menudemo[side + 1], 0, anm);
        menudemocha[i * 3] = 2;
    }
    if (menudemocha[i * 3] == 2 && jobjAnim(menudemo[side + 1]->models[0]) != 0) {
        menudemoanmend[i] = 1;
        menudemocha[i * 3] = 3;
        switch (menudemocha[i * 3 + 1]) {
        case 0:
            return;
        case 1:
            menudemocha[i * 3 + 1] = 2;
            menudemocha[i * 3] = 2;
            break;
        case 3:
            menudemocha[i * 3 + 1] = 0;
            menudemocha[i * 3] = 2;
            break;
        case 4:
            menudemocha[i * 3 + 1] = 0;
            menudemocha[i * 3] = 2;
            break;
        case 5:
            menudemocha[i * 3 + 1] = 2;
            menudemocha[i * 3] = 2;
            break;
        default:
            menudemocha[i * 3] = 2;
            break;
        }
        SetAnimArc2(menudemo[side + 1], 0, menudemocha[i * 3 + 1]);
        jobjAnim(menudemo[side + 1]->models[0]);
    }
    jobjDispAll(jobj);
}




extern void ttlMenuDispParts(HSD_JObj *joint, s32 a, s32 b, s32 c, s32 d);

void menu_sDispBattleFarmTitle(void)
{
    s32 idx = 0;
    s32 unused[6];

    if (menutitleanm[0].state != menutitleanm[0].next) {
        menutitleanm[0].mode = 1;
        menutitleanm[0].next = menutitleanm[0].state;
    }
    if (menutitleanm[0].mode == 1) {
        menutitleanm[0].mode = 2;
        SetAnimArc2(menu1p, 0, menutitleanm[0].state);
    }
    if (menutitleanm[0].mode == 2 && menutitleanm[idx].mode == 2 && jobjAnim(menu1p->models[idx]) != 0) {
        menutitleanm[0].mode = 3;
        menuanmend = 1;
        if (menutitleanm[0].state == 2) {
            menutitleanm[0].mode = 0;
            return;
        } else if (menutitleanm[0].state <= 2) {
            if (menutitleanm[0].state == 0)
                menutitleanm[0].state = 1;
            if (menutitleanm[0].state == 1)
                menutitleanm[0].mode = 1;
            SetAnimArc2(menu1p, 0, menutitleanm[0].state);
            jobjAnim(menu1p->models[idx]);
        }
    }
    if (menutitleanm[0].mode == 0)
        return;
    ttlMenuDispParts(menu1p->models[idx], 0, -1, -1, -1);
    ttlMenuDispParts(menu1p->models[idx], 0, menutitleguide[0], -1, -1);
}

extern void sReadPre(void);
extern s32 TXT_Menu_size;

s32 TEA_defstatusload(void)
{
    void *data;
    s32 unused[2];

    sReadPre();
    data = sReadFileU((char *)sZoidDataPath, 0);
    memcpy(Tea_zoiddat, data, sizeof(Tea_zoiddat));
    free(data);
    sReadPre();
    data = sReadFileU((char *)sPartsDataPath, 0);
    memcpy(Tea_partsdat, data, sizeof(Tea_partsdat));
    free(data);
    sReadPre();
    data = sReadFileU((char *)sBulletDataPath, 0);
    memcpy(Tea_bulletdat, data, sizeof(Tea_bulletdat));
    free(data);
    sReadPre();
    data = sReadFileU((char *)sPersonDataPath, 0);
    memcpy(Tea_persondat, data, sizeof(Tea_persondat));
    free(data);
    sReadPre();
    data = sReadFileU((char *)sEffectDataPath, 0);
    memcpy(Tea_effectdat, data, sizeof(Tea_effectdat));
    free(data);
    sReadPre();
    data = sReadFileU((char *)sMenuTextPath, 0);
    memcpy(TXT_Menu_dat, data, TXT_Menu_size);
    free(data);
    return 1;
}


void menu_sDispBattleShopunfold(void)
{
    s32 idx = 16;
    s32 n = 10;

    if (menusetbtanm[10].cur != menusetbtanm[10].old) {
        menusetbtanm[10].state = 1;
        menusetbtanm[10].old = menusetbtanm[10].cur;
    }
    if (menusetbtanm[10].state == 1) {
        menusetbtanm[10].state = 2;
        SetAnimArc2(menu1p, 16, menusetbtanm[n].cur);
    }
    if (menusetbtanm[10].state == 2 && jobjAnim(menu1p->models[idx]) != 0) {
        sMakeMatrix(menu1p->models[idx]);
        menusetbtanm[10].state = 3;
        menuanmend = 1;
        switch (menusetbtanm[10].cur) {
        case 1:
            menusetbtanm[10].cur = 2;
            menusetbtanm[10].state = 2;
            break;
        case 3:
            menusetbtanm[10].cur = 0;
            menusetbtanm[10].state = 2;
            break;
        case 4:
            menusetbtanm[10].cur = 5;
            menusetbtanm[10].state = 2;
            break;
        case 6:
            menusetbtanm[10].cur = 0;
            menusetbtanm[10].state = 2;
            break;
        default:
            menusetbtanm[10].state = 2;
            break;
        }
        SetAnimArc2(menu1p, 16, menusetbtanm[n].cur);
        jobjAnim(menu1p->models[idx]);
    }
    HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
}


void menu_sDispBattleSetunfold(void)
{
    s32 idx = 13;
    s32 n = 7;
    s32 result;

    if (menumode < 3)
        return;
    if (menumode > 6)
        return;
    if (menusetbtanm[7].cur != menusetbtanm[7].old) {
        menusetbtanm[7].state = 1;
        menusetbtanm[7].old = menusetbtanm[7].cur;
    }
    if (menusetbtanm[7].state == 1) {
        menusetbtanm[7].state = 2;
        SetAnimArc2(menu1p, 13, menusetbtanm[n].cur);
    }
    if (menusetbtanm[7].state == 2) {
        result = jobjAnim(menu1p->models[idx]);
        sMakeMatrix(menu1p->models[idx]);
        if (result != 0) {
            menusetbtanm[7].state = 3;
            menuanmend = 1;
            if (menusetbtanm[7].cur == 0)
                menusetbtanm[7].cur = 1;
            if (menusetbtanm[7].cur == 2)
                menusetbtanm[7].cur = 9;
            if (menusetbtanm[7].cur == 3)
                menusetbtanm[7].cur = 4;
            if (menusetbtanm[7].cur == 5)
                menusetbtanm[7].cur = 9;
            if (menusetbtanm[7].cur == 6)
                menusetbtanm[7].cur = 7;
            if (menusetbtanm[7].cur == 8)
                menusetbtanm[7].cur = 9;
            menusetbtanm[7].state = 2;
            SetAnimArc2(menu1p, 13, menusetbtanm[n].cur);
            jobjAnim(menu1p->models[idx]);
            sMakeMatrix(menu1p->models[idx]);
        }
    }
    HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), 0, 7, 0);
}


void menu_sDispBattleSetLButtonAnm(s32 button)
{
    s32 idx = 9;
    HSD_JObj *pos;
    HSD_JObj *jobj;

    pos = GetChild(menu1p->models[13], 0, button - 1, -1, -1, -1);
    jobj = GetChild(menu1p->models[idx], 0, button, -1, -1, -1);
    if (menusetbtanm[button].cur != menusetbtanm[button].old) {
        menusetbtanm[button].state = 1;
        menusetbtanm[button].old = menusetbtanm[button].cur;
    }
    if (menusetbtanm[button].state == 1) {
        menusetbtanm[button].state = 2;
        sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, button, -1, -1, -1), menusetbtanm[button].cur);
    }
    if (menusetbtanm[button].state == 2 && jobjAnim1(GetChild(menu1p->models[idx], 0, button, -1, -1, -1)) != 0) {
        menusetbtanm[button].state = 3;
        menuanmend = 1;
        if (menusetbtanm[button].cur == 5)
            return;
        if (menusetbtanm[button].cur == 0) {
            if (menusetbtanm[button].cur == 0)
                menusetbtanm[button].cur = 1;
            sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, button, -1, -1, -1), menusetbtanm[button].cur);
            jobjAnim1(GetChild(menu1p->models[idx], 0, button, -1, -1, -1));
        } else {
            menusetbtanm[button].state = 1;
        }
    }
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
}


void menu_sDispBattleShopLButtonAnm(s32 button)
{
    s32 idx = 15;
    HSD_JObj *pos;
    HSD_JObj *jobj;
    s32 k;

    pos = GetChild(menu1p->models[16], 0, button, -1, -1, -1);
    jobj = GetChild(menu1p->models[idx], 0, button, -1, -1, -1);
    k = button + 5;
    if (k == 7)
        k = 4;
    if (menusetbtanm[k].cur != menusetbtanm[k].old) {
        menusetbtanm[k].state = 1;
        menusetbtanm[k].old = menusetbtanm[k].cur;
    }
    if (menusetbtanm[k].state == 1) {
        menusetbtanm[k].state = 2;
        sSetAnim1(menu1p, 15, GetChild(menu1p->models[idx], 0, button, -1, -1, -1), menusetbtanm[k].cur);
    }
    if (menusetbtanm[k].state == 2 && jobjAnim1(GetChild(menu1p->models[idx], 0, button, -1, -1, -1)) != 0) {
        menusetbtanm[k].state = 3;
        menuanmend = 1;
        if (menusetbtanm[k].cur == 5)
            return;
        if (menusetbtanm[k].cur == 0) {
            if (menusetbtanm[k].cur == 0)
                menusetbtanm[k].cur = 1;
            sSetAnim1(menu1p, 15, GetChild(menu1p->models[idx], 0, button, -1, -1, -1), menusetbtanm[k].cur);
            jobjAnim1(GetChild(menu1p->models[idx], 0, button, -1, -1, -1));
        } else {
            menusetbtanm[k].state = 1;
        }
    }
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
}


void menu_sDispBattleSetLButtonZoid(void)
{
    s32 idx = 9;
    HSD_JObj *pos;
    HSD_JObj *jobj;

    pos = GetChild(menu1p->models[13], 0, 4, -1, -1, -1);
    jobj = GetChild(menu1p->models[idx], 0, 0, -1, -1, -1);
    jobjCopyPos(pos, jobj);
    if (menusetbtanm[0].cur != menusetbtanm[0].old) {
        menusetbtanm[0].state = 1;
        menusetbtanm[0].old = menusetbtanm[0].cur;
    }
    if (menusetbtanm[0].state == 1) {
        menusetbtanm[0].state = 2;
        sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, 0, -1, -1, -1), menusetbtanm[0].cur);
    }
    if (menusetbtanm[0].state == 2 && jobjAnim1(GetChild(menu1p->models[idx], 0, 0, -1, -1, -1)) != 0) {
        menusetbtanm[0].state = 3;
        menuanmend = 1;
        if (menusetbtanm[0].cur == 5)
            return;
        if (menusetbtanm[0].cur == 0) {
            if (menusetbtanm[0].cur == 0)
                menusetbtanm[0].cur = 1;
            sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, 0, -1, -1, -1), menusetbtanm[0].cur);
            jobjAnim1(GetChild(menu1p->models[idx], 0, 0, -1, -1, -1));
        } else {
            menusetbtanm[0].state = 1;
        }
    }
    HSD_JObjDispAll(jobj, 0, 7, 0);
}


void menu_sDispBattleShopLButtonZoid(void)
{
    s32 idx = 9;
    HSD_JObj *pos;
    HSD_JObj *jobj;

    pos = GetChild(menu1p->models[17], 0, 0, -1, -1, -1);
    jobj = GetChild(menu1p->models[idx], 0, 0, -1, -1, -1);
    jobjCopyPos(pos, jobj);
    if (menusetbtanm[0].cur != menusetbtanm[0].old) {
        menusetbtanm[0].state = 1;
        menusetbtanm[0].old = menusetbtanm[0].cur;
    }
    if (menusetbtanm[0].state == 1) {
        menusetbtanm[0].state = 2;
        sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, 0, -1, -1, -1), menusetbtanm[0].cur);
    }
    if (menusetbtanm[0].state == 2 && jobjAnim1(GetChild(menu1p->models[idx], 0, 0, -1, -1, -1)) != 0) {
        menusetbtanm[0].state = 3;
        menuanmend = 1;
        if (menusetbtanm[0].cur == 5)
            return;
        if (menusetbtanm[0].cur == 0) {
            if (menusetbtanm[0].cur == 0)
                menusetbtanm[0].cur = 1;
            sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, 0, -1, -1, -1), menusetbtanm[0].cur);
            jobjAnim1(GetChild(menu1p->models[idx], 0, 0, -1, -1, -1));
        } else {
            menusetbtanm[0].state = 1;
        }
    }
    HSD_JObjDispAll(jobj, 0, 7, 0);
}


void menu_sDispBattleShopLButtonMainAnm(s32 button)
{
    s32 idx = 9;
    HSD_JObj *pos;
    HSD_JObj *jobj;

    pos = GetChild(menu1p->models[17], 0, button, -1, -1, -1);
    jobj = GetChild(menu1p->models[idx], 0, button, -1, -1, -1);
    if (menusetbtanm[button].cur != menusetbtanm[button].old) {
        menusetbtanm[button].state = 1;
        menusetbtanm[button].old = menusetbtanm[button].cur;
    }
    if (menusetbtanm[button].state == 1) {
        menusetbtanm[button].state = 2;
        sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, button, -1, -1, -1), menusetbtanm[button].cur);
    }
    if (menusetbtanm[button].state == 2 && jobjAnim1(GetChild(menu1p->models[idx], 0, button, -1, -1, -1)) != 0) {
        menusetbtanm[button].state = 3;
        menuanmend = 1;
        switch (menusetbtanm[button].cur) {
        case 0:
            menusetbtanm[button].cur = 1;
            menusetbtanm[button].state = 2;
            break;
        case 1:
            menusetbtanm[button].cur = 1;
            menusetbtanm[button].state = 2;
            break;
        case 2:
            menusetbtanm[button].cur = 2;
            menusetbtanm[button].state = 2;
            break;
        case 3:
            menusetbtanm[button].cur = 3;
            menusetbtanm[button].state = 2;
            break;
        case 4:
            menusetbtanm[button].cur = 4;
            menusetbtanm[button].state = 2;
            break;
        case 5:
            menusetbtanm[button].state = 0;
            return;
        default:
            menusetbtanm[button].state = 1;
            break;
        }
        sSetAnim1(menu1p, 9, GetChild(menu1p->models[idx], 0, button, -1, -1, -1), menusetbtanm[button].cur);
        jobjAnim1(GetChild(menu1p->models[idx], 0, button, -1, -1, -1));
    }
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
}


void menu_sDispVsEntryPersonPartnerZoidPic(void)
{
    HSD_JObj *pos;
    HSD_JObj *pic;
    s32 unused[6];

    pos = GetChild(menu1p->models[6], 0, 0, 1, -1, -1);
    pic = GetChild(menu_personp[IveSave[0].selected_person]->models[0], 0, 0, -1, -1, -1);
    jobjCopyPos(pos, pic);
    HSD_JObjDispAll(pic, 0, 7, 0);
    pos = GetChild(menu1p->models[6], 0, 0, 2, -1, -1);
    pic = GetChild(menu_zoidp[IveSave[0].selected_zoid]->models[0], 0, 0, -1, -1, -1);
    if (pic != 0) {
        jobjCopyPos(pos, pic);
        HSD_JObjDispAll(pic, 0, 7, 0);
    }
    pos = GetChild(menu1p->models[6], 0, 1, 1, -1, -1);
    pic = GetChild(menu_personp[IveSave[1].selected_person]->models[0], 0, 0, -1, -1, -1);
    jobjCopyPos(pos, pic);
    HSD_JObjDispAll(pic, 0, 7, 0);
    pos = GetChild(menu1p->models[6], 0, 1, 2, -1, -1);
    pic = GetChild(menu_zoidp[IveSave[1].selected_zoid]->models[0], 0, 0, -1, -1, -1);
    if (pic != 0) {
        jobjCopyPos(pos, pic);
        HSD_JObjDispAll(pic, 0, 7, 0);
    }
}


extern void menu_sDispVsEntryZoidStatusKind(s32 group, s32 kind, s32 value);

void menu_sDispVsEntryPersonZoidStatus(void)
{
    s32 idx = 6;
    s32 unused[4];

    jobjDispAll(GetChild(menu1p->models[idx], 0, 0, -1, -1, -1));
    jobjDispAll(GetChild(menu1p->models[idx], 0, 0, 0, -1, -1));
    putAscJobj(GetChild(menu1p->models[idx], 0, 0, 0, 0, -1), 1, Tea_persondat[IveSave[0].selected_person].name);
    putAscJobj(GetChild(menu1p->models[idx], 0, 0, 0, 1, -1), 1, Tea_zoiddat[IveSave[0].selected_zoid].name);
    menu_sDispVsEntryZoidStatusKind(0, 0, Tea_zoiddat[IveSave[0].selected_zoid].health);
    menu_sDispVsEntryZoidStatusKind(0, 1, Tea_zoiddat[IveSave[0].selected_zoid].armor);
    menu_sDispVsEntryZoidStatusKind(0, 2, Tea_zoiddat[IveSave[0].selected_zoid].field_0056);
    jobjDispAll(GetChild(menu1p->models[idx], 0, 1, -1, -1, -1));
    putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 0, -1), 1, Tea_persondat[IveSave[1].selected_person].name);
    putAscJobj(GetChild(menu1p->models[idx], 0, 1, 0, 1, -1), 1, Tea_zoiddat[IveSave[1].selected_zoid].name);
    menu_sDispVsEntryZoidStatusKind(1, 0, Tea_zoiddat[IveSave[1].selected_zoid].health);
    menu_sDispVsEntryZoidStatusKind(1, 1, Tea_zoiddat[IveSave[1].selected_zoid].armor);
    menu_sDispVsEntryZoidStatusKind(1, 2, Tea_zoiddat[IveSave[1].selected_zoid].field_0056);
}


void menu_sDispBattleHumanEntryPersonPartner(void)
{
    s32 idx = 3;
    s32 unused[6];
    s32 result;
    s32 done;
    s16 i;
    s32 j;

    for (i = 0; i < 7; i++) {
        j = i;
        if (menufarmanm[j] == 7) {
            menumodeanm[j] = 0;
            menufarmanmold[j] = menufarmanm[j];
        }
        if (menufarmanm[j] != menufarmanmold[j]) {
            menumodeanm[j] = 1;
            menufarmanmold[j] = menufarmanm[j];
        }
        if (menumodeanm[j] == 3 && menufarmanm[j] == 0)
            menufarmanm[j] = 1;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 1)
            menumodeanm[j] = 1;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 3)
            menumodeanm[j] = 3;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 4)
            menumodeanm[j] = 4;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 5)
            menumodeanm[j] = 5;
        if (menumodeanm[j] == 1) {
            menumodeanm[j] = 2;
            sSetAnim1(menu1p, 3, GetChild(menu1p->models[idx], 0, i, -1, -1, -1), menufarmanm[j]);
        }
    }
    result = 0;
    done = 0;
    for (i = 0; i < 7; i++) {
        j = i;
        if (menumodeanm[j] == 2) {
            if (done == 0) {
                result = jobjAnim(menu1p->models[idx]);
                done = 1;
            }
            if (result != 0) {
                menumodeanm[j] = 3;
                menuanmend = 1;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        j = i;
        if (menufarmanm[j] != 7)
            jobjDispAll(GetChild(menu1p->models[idx], 0, j, -1, -1, -1));
    }
}


void menu_sDispMisEntryPersonPartner(void)
{
    s32 unused[2];
    PartnerAnimTable table = *(PartnerAnimTable *)r9730;
    s32 idx = 5;
    s32 result;
    s32 done;
    s16 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        j = i;
        if (menufarmanm[j] == 7) {
            menumodeanm[j] = 0;
            menufarmanmold[j] = menufarmanm[j];
        }
        if (menufarmanm[j] != menufarmanmold[j]) {
            menumodeanm[j] = 1;
            menufarmanmold[j] = menufarmanm[j];
        }
        if (menumodeanm[j] == 3 && menufarmanm[j] == 0)
            menufarmanm[j] = 1;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 1)
            menumodeanm[j] = 1;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 3)
            menumodeanm[j] = 3;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 4)
            menumodeanm[j] = 4;
        if (menumodeanm[j] == 3 && menufarmanm[j] == 5)
            menumodeanm[j] = 5;
        if (menumodeanm[j] == 1) {
            menumodeanm[j] = 2;
            sSetAnim1(menu1p, 5, GetChild(menu1p->models[idx], 0, i, -1, -1, -1), table.anim[menufarmanm[j]]);
        }
    }
    result = 0;
    done = 0;
    for (i = 0; i < 3; i++) {
        j = i;
        if (menumodeanm[j] == 2) {
            if (done == 0) {
                result = jobjAnim(menu1p->models[idx]);
                done = 1;
            }
            if (result != 0) {
                menumodeanm[j] = 3;
                menuanmend = 1;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        j = i;
        if (menufarmanm[j] != 7)
            jobjDispAll(GetChild(menu1p->models[idx], 0, j, -1, -1, -1));
    }
}


extern void menu_sDispBattleHumanEntryPersonListDisp(s16 person, s16 slot);

void menu_sDispBattleHumanEntryPilotZoidList(void)
{
    s32 idx = 4;
    HSD_JObj *target;
    HSD_JObj *source;
    s16 i;
    s32 unused[2];

    if (menumode < 5)
        return;
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, -1, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 0, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 1, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 2, -1, -1), 0, 7, 0);
    if (menumode == 5 || menumode == 6) {
        for (i = 0; i < menufarmmh[menumode]; i++)
            menu_sDispBattleHumanEntryPersonListDisp(IveSave[0].person_list[i + menufarmst[menumode]], i);
    }
    if (menucuranm == 1) {
        SetAnimArc2(menu1p, 5, 0);
        menucuranm = 2;
    }
    if (menucuranm == 2) {
        if (jobjAnim(menu1p->models[5]) != 0)
            menucuranm = 3;
    } else if (menucuranm == 3) {
        SetAnimArc2(menu1p, 5, 0);
        jobjAnim(menu1p->models[5]);
        menucuranm = 2;
    }
    source = GetChild(menu1p->models[4], 0, 2, 4, menufarmsl[menumode], -1);
    target = GetChild(menu1p->models[5], 0, 1, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDisp(target, 0, 7, 0);
}


void menu_sDispMissionEntryPilotZoidList(void)
{
    s32 idx = 6;
    HSD_JObj *target;
    HSD_JObj *source;
    s16 i;
    s32 unused[2];

    if (menumode < 5)
        return;
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, -1, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 0, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 1, -1, -1), 0, 7, 0);
    HSD_JObjDisp(GetChild(menu1p->models[idx], 0, 2, 2, -1, -1), 0, 7, 0);
    if (menumode == 5 || menumode == 6) {
        for (i = 0; i < menufarmmh[menumode]; i++)
            menu_sDispBattleEntryPersonListDisp(IveSave[0].person_list[i + menufarmst[menumode]], i);
    }
    if (menumode == 7 || menumode == 8) {
        for (i = 0; i < menufarmmh[menumode]; i++)
            menu_sDispBattleEntryZoidListDisp(IveSave[0].owned_zoids[i + menufarmst[menumode]], i);
    }
    if (menucuranm == 1) {
        SetAnimArc2(menu1p, 7, 0);
        menucuranm = 2;
    }
    if (menucuranm == 2) {
        if (jobjAnim(menu1p->models[7]) != 0)
            menucuranm = 3;
    } else if (menucuranm == 3) {
        SetAnimArc2(menu1p, 7, 0);
        jobjAnim(menu1p->models[7]);
        menucuranm = 2;
    }
    source = GetChild(menu1p->models[6], 0, 2, 4, menufarmsl[menumode], -1);
    target = GetChild(menu1p->models[7], 0, 1, -1, -1, -1);
    jobjCopyPos(source, target);
    HSD_JObjDisp(target, 0, 7, 0);
}


#pragma readonly_strings on
void menu_sDispBattleSetZoidHaveZoidList(void)
{
    char text[64];
    HSD_JObj *pos;
    s16 i;
    HSD_JObj *base;
    HSD_JObj *list;
    HSD_JObj *jobj;

    if (menumode != 3)
        return;
    base = GetChild(menu1p->models[13], 0, 3, -1, -1, -1);
    list = GetChild(menu1p->models[12], 0, -1, -1, -1, -1);
    jobjCopyPos(base, list);
    HSD_JObjDispAll(list, 0, 7, 0);
    for (i = 0; i < menusetmh[3]; i++) {
        pos = GetChild(menu1p->models[12], 0, 3, i, -1, -1);
        jobj = GetChild(menu_zoidp[IveSave[0].owned_zoids[menusetst[3] + i]]->models[0], 0, 1, -1, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        sprintf(text, " %s", Tea_zoiddat[IveSave[0].owned_zoids[menusetst[3] + i]].name);
        putAscJobj(pos, 0, text);
        if (i == menusetsl[3]) {
            pos = GetChild(menu1p->models[12], 0, 3, i, -1, -1);
            jobj = GetChild(menu1p->models[7], 0, 1, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
        }
    }
}
#pragma readonly_strings off


#pragma readonly_strings on
#pragma push
#pragma dont_inline on
void clearFlagThink(s32 save)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((s8)IveSaveFlag.system_flags[4 + i] != 0) {
            addZoids(save, i + 35);
            OSReport("add-zoid-4 diab =====================================================================================================================================================\n");
        }
    }
    if ((s8)IveSaveFlag.system_flags[1] != 0) {
        addZoids(save, 17);
        OSReport("add-zoid-17\n");
    }
    if ((s8)IveSaveFlag.system_flags[0] != 0) {
        addZoids(save, 16);
        OSReport("add-zoids-16\n");
    }
    if ((s8)IveSaveFlag.system_flags[0] != 0) {
        ttl_HaveAddHuman(save, 27);
        ttl_HaveAddHuman(save, 28);
        ttl_HaveAddHuman(save, 29);
        ttl_HaveAddHuman(save, 30);
        OSReport("add-chara-27.28.29.30\n");
    }
    if ((s8)IveSaveFlag.system_flags[1] != 0) {
        ttl_HaveAddHuman(save, 31);
        ttl_HaveAddHuman(save, 32);
        ttl_HaveAddHuman(save, 33);
        ttl_HaveAddHuman(save, 42);
        OSReport("add-chara-27.28.29.30\n");
    }
    if ((s8)IveSaveFlag.system_flags[2] != 0) {
        ttl_HaveAddHuman(save, 34);
        ttl_HaveAddHuman(save, 35);
        ttl_HaveAddHuman(save, 36);
        ttl_HaveAddHuman(save, 41);
        OSReport("add-chara-34.35.36.42\n");
    }
    if ((s8)IveSaveFlag.system_flags[3] != 0) {
        ttl_HaveAddHuman(save, 37);
        ttl_HaveAddHuman(save, 38);
        ttl_HaveAddHuman(save, 39);
        ttl_HaveAddHuman(save, 40);
        ttl_HaveAddHuman(save, 43);
        ttl_HaveAddHuman(save, 44);
        ttl_HaveAddHuman(save, 45);
        ttl_HaveAddHuman(save, 46);
        OSReport("add-chara-37.38.39.40.43.44.45.46\n");
    }
    if ((s8)IveSaveFlag.system_flags[9] != 0) {
        ttl_HaveAddHuman(save, 15);
        OSReport("add-chara-15 \n");
    }
}
#pragma pop
#pragma readonly_strings off


extern struct HSD_TObj *searchTObjN(HSD_JObj *joint, s32 *index);
extern void texScroll(struct HSD_TObj *tobj, f32 x, f32 y, f32 z);
extern void SeCancel(void);
extern void SeRet(void);
extern char *GetMenuMsgAdr(s16 message);
extern s16 TEA_menufnc(s16 *menup, s16 *menust, s16 maxn, s16 max);

#pragma push
#pragma dont_inline on
s16 menufncZoidBattleNewGameLoadGame(void)
{
    u8 idx = 3;
    struct HSD_TObj *tobj;
    s32 pad0[2];
    s32 index = 0;
    s32 pad1[4];
    f32 step;
    f32 zero;

    index = 0;
    tobj = searchTObjN(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), &index);
    texScroll(tobj, 0.0f, 0.0f, 0.0f);
    menumode = idx;
    menutitleanm[3].mode = 1;
    menutitleanm[3].state = 0;
    menutitleanm[3].next = 2;
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 2;
    menufarmmn[3] = 2;
    menuanmend = 0;
    step = 0.0625f;
    zero = 0.0f;
    while (1) {
        sPadAll();
        menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        strcpy((char *)menudispwinstr, GetMenuMsgAdr(menufarmcl[menumode] + 6));
        if (menuanmend == 1) {
            if (menutitleanm[menumode].state == 0)
                menutitleanm[menumode].state = 1;
            menuanmend = 0;
        }
        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0) {
            SeCancel();
            texScroll(tobj, 0.0f, 0.0f, 0.0f);
            return -1;
        }
        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0)
            break;
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0 || sPad2->pressed_dpad_up != 0 || sPad2->pressed_stick_up != 0) {
            SeSelectB();
            if (menufarmcl[menumode] == 0)
                texScroll(tobj, zero, zero, zero);
        }
        if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0 || sPad2->pressed_dpad_down != 0 || sPad2->pressed_stick_down != 0) {
            SeSelectB();
            if (menufarmcl[menumode] == 1)
                texScroll(tobj, 0.0f, step, 0.0f);
        }
        menu_sDispStart();
    }
    SeRet();
    return menufarmcl[menumode];
}
#pragma pop


extern struct HSD_TObj *searchTObjN(HSD_JObj *joint, s32 *index);
extern void texScroll(struct HSD_TObj *tobj, f32 x, f32 y, f32 z);
extern void SeCancel(void);
extern void SeRet(void);
extern char *GetMenuMsgAdr(s16 message);
extern s16 TEA_menufnc(s16 *menup, s16 *menust, s16 maxn, s16 max);

#pragma push
#pragma dont_inline on
s16 menufncZoidMissionEmpireCountry(void)
{
    u8 idx = 6;
    struct HSD_TObj *tobj;
    s32 pad0[1];
    s32 index = 0;
    s32 pad1[3];
    f32 step;
    f32 zero;

    index = 0;
    tobj = searchTObjN(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), &index);
    texScroll(tobj, 0.0f, 0.0f, 0.0f);
    menumode = idx;
    menutitleanm[6].mode = 1;
    menutitleanm[6].state = 0;
    menutitleanm[6].next = 2;
    menufarmcl[6] = 0;
    menufarmsl[6] = 0;
    menufarmst[6] = 0;
    menufarmmh[6] = 2;
    menufarmmn[6] = 2;
    menuanmend = 0;
    step = 0.0625f;
    zero = 0.0f;
    while (1) {
        sPadAll();
        menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        strcpy((char *)menudispwinstr, GetMenuMsgAdr(menufarmcl[menumode] + 8));
        if (menuanmend == 1) {
            if (menutitleanm[menumode].state == 0)
                menutitleanm[menumode].state = 1;
            menuanmend = 0;
        }
        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0) {
            SeCancel();
            texScroll(tobj, 0.0f, 0.0f, 0.0f);
            return -1;
        }
        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0)
            break;
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0 || sPad2->pressed_dpad_up != 0 || sPad2->pressed_stick_up != 0) {
            SeSelectB();
            if (menufarmcl[menumode] == 0)
                texScroll(tobj, zero, zero, zero);
        }
        if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0 || sPad2->pressed_dpad_down != 0 || sPad2->pressed_stick_down != 0) {
            SeSelectB();
            if (menufarmcl[menumode] == 1)
                texScroll(tobj, 0.0f, step, 0.0f);
        }
        menu_sDispStart();
    }
    SeRet();
    {
        s32 cl = menufarmcl[menumode];

        if (cl == 0) {
            IveSave[0].country = 1;
            GameMode.country = 1;
            IveSave[0].stage = 0;
            GameMode.map = 0;
        }
        if (cl == 1) {
            IveSave[0].country = 2;
            GameMode.country = 2;
            IveSave[0].stage = 19;
            GameMode.map = 19;
        }
        return menufarmcl[menumode];
    }
}
#pragma pop

#pragma push
#pragma dont_inline on
s16 menufncZoidBattleSingleTeamGame(void)
{
    u8 idx = 4;
    struct HSD_TObj *tobj;
    s32 unused[2];
    s32 index = 0;
    s32 unused2[3];
    f32 step;
    f32 zero;

    index = 0;
    tobj = searchTObjN(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), &index);
    menumode = idx;
    texScroll(tobj, 0.0f, 0.0f, 0.0f);
    menutitleanm[menumode].mode = 1;
    menutitleanm[menumode].state = 0;
    menutitleanm[menumode].next = 2;
    menufarmcl[menumode] = 0;
    menufarmsl[menumode] = 0;
    menufarmst[menumode] = 0;
    menufarmmh[menumode] = 2;
    menufarmmn[menumode] = 2;
    menuanmend = 0;
    step = 0.0625f;
    zero = 0.0f;
    while (1) {
        sPadAll();
        menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        if (menuanmend == 1) {
            if (menutitleanm[menumode].state == 0)
                menutitleanm[menumode].state = 1;
            menuanmend = 0;
        }
        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0) {
            SeCancel();
            texScroll(tobj, 0.0f, 0.0f, 0.0f);
            return -1;
        }
        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0) {
            (void)menufarmcl[menumode];
            break;
        }
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0 || sPad2->pressed_dpad_up != 0 || sPad2->pressed_stick_up != 0) {
            SeSelectB();
            if (menufarmcl[menumode] == 0)
                texScroll(tobj, zero, zero, zero);
        }
        if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0 || sPad2->pressed_dpad_down != 0 || sPad2->pressed_stick_down != 0) {
            SeSelectB();
            if (menufarmcl[menumode] == 1)
                texScroll(tobj, 0.0f, step, 0.0f);
        }
        menu_sDispStart();
    }
    SeRet();
    menuZoidBattleModeSingleTeam = menufarmcl[menumode];
    return menufarmcl[menumode];
}
#pragma pop



extern s32 menudispyesnopoint;
extern ModelArchive *menu_yesnop;
extern void jobjDisp(HSD_JObj *joint);
extern void sPutFontRect(char *text, HSD_JObj *top_left, HSD_JObj *bottom_right, GXColor color, GXColor shadow, s32 alpha, s32 flags);

#pragma readonly_strings on
void menu_sDispYesNoMenu(void)
{
    s32 unused[4];
    GXColor color = {255, 255, 255, 255};
    GXColor shadow = {0, 0, 0, 0};
    char text[180];
    s32 idx;

    if (menudispyesnoflag == 0)
        return;
    if (menu_yesnop != 0) {
        idx = 2;
        if (menudispyesnostr1[0] != 0 && menudispyesnostr2[0] == 0)
            idx = 1;
        if (menudispyesnoanm.state == 1) {
            SetAnimArc2(menu_yesnop, idx, menudispyesnoanm.anim);
            menudispyesnoanm.state = 2;
        }
        if (menudispyesnoanm.state == 2 && jobjAnim(menu_yesnop->models[idx]) != 0) {
            menudispyesnoanm.state = 2;
            menudispyesnoanm.anim = 1;
            SetAnimArc2(menu_yesnop, idx, menudispyesnoanm.anim);
            jobjAnim(menu_yesnop->models[idx]);
            sMakeMatrix(menu_yesnop->models[idx]);
        }
        jobjDisp(GetChild(menu_yesnop->models[idx], 0, -1, -1, -1, -1));
        if (menudispyesnostr1[0] == 0 || menudispyesnostr2[0] == 0) {
            if (menudispyesnopoint == 1)
                jobjDispAll(GetChild(menu_yesnop->models[idx], 0, 0, -1, -1, -1));
            else
                jobjDisp(GetChild(menu_yesnop->models[idx], 0, 0, -1, -1, -1));
            if (menudispyesnopoint == 0)
                jobjDispAll(GetChild(menu_yesnop->models[idx], 0, 1, -1, -1, -1));
            else
                jobjDisp(GetChild(menu_yesnop->models[idx], 0, 1, -1, -1, -1));
        }
        if (menudispyesnostr1[0] != 0 && menudispyesnostr2[0] == 0)
            sprintf(text, "%s ", menudispyesnostr1);
        if (menudispyesnostr1[0] == 0 && menudispyesnostr2[0] != 0)
            sprintf(text, "%s ", menudispyesnostr2);
        if (menudispyesnostr1[0] != 0 && menudispyesnostr2[0] != 0)
            sprintf(text, "%s ", menudispyesnostr1);
        sPutFontRect(text, GetChild(menu_yesnop->models[idx], 0, 2, -1, -1, -1), GetChild(menu_yesnop->models[idx], 0, 2, 0, -1, -1), color, shadow, 0, 2);
    } else {
        OSReport((char *)sLogYesNoMenuNotLoading);
    }
}
#pragma readonly_strings off


extern s32 menuzoidequippartslist;

void menu_sDispBattleSetequipPartsList(void)
{
    s32 idx = 14;
    s32 n = 8;
    s32 unused[2];
    s32 show;
    s32 slot;
    s32 result;
    HSD_JObj *pos;
    HSD_JObj *jobj;

    show = 0;
    if (menumode == 5)
        show = 1;
    if (menumode == 4)
        show = 1;
    if (menumode == 7)
        show = 1;
    if (menumode == 6)
        show = 1;
    if (menumode == 8)
        show = 1;
    if (show == 0)
        return;
    if (menuzoidequippartslist == 0)
        return;
    if (menumode < 7)
        slot = menumode;
    else
        slot = menumode - 3;
    if (menumode == 8)
        slot = 6;
    pos = GetChild(menu1p->models[13], 0, slot - 4, -1, -1, -1);
    if (menusetbtanm[8].cur != menusetbtanm[8].old) {
        menusetbtanm[8].state = 1;
        menusetbtanm[8].old = menusetbtanm[8].cur;
    }
    if (menusetbtanm[8].state == 0)
        return;
    if (menusetbtanm[8].state == 1) {
        menusetbtanm[8].state = 2;
        SetAnimArc2(menu1p, 14, menusetbtanm[n].cur);
    }
    if (menusetbtanm[8].state == 2) {
        result = jobjAnim(menu1p->models[idx]);
        sMakeMatrix(menu1p->models[idx]);
        if (result != 0) {
            menusetbtanm[8].state = 3;
            menuanmend = 1;
            if (menusetbtanm[8].cur == 0)
                return;
            if (menusetbtanm[8].cur == 2)
                return;
                if (menusetbtanm[8].cur == 4)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 5)
                    return;
                if (menusetbtanm[8].cur == 7)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 8)
                    return;
                if (menusetbtanm[8].cur == 10)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 11)
                    return;
                if (menusetbtanm[8].cur == 13)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 14)
                    return;
                if (menusetbtanm[8].cur == 16)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 17)
                    return;
                if (menusetbtanm[8].cur == 19)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 20)
                    return;
                if (menusetbtanm[8].cur == 22)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 23)
                    return;
                if (menusetbtanm[8].cur == 25)
                    menusetbtanm[8].cur = 27;
                if (menusetbtanm[8].cur == 26)
                    return;
            menusetbtanm[8].state = 2;
            SetAnimArc2(menu1p, 14, menusetbtanm[n].cur);
            jobjAnim(menu1p->models[idx]);
            sMakeMatrix(menu1p->models[idx]);
        }
    }
    jobj = GetChild(menu1p->models[idx], 0, -1, -1, -1, -1);
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
}


#pragma readonly_strings on
void menu_sDispBattleSetequipParts(void)
{
    s32 idx = 11;
    s32 kind;
    s32 group;
    s16 type;
    s16 slot;
    s32 show;
    HSD_JObj *pos;
    s32 count;
    s16 *sl;
    HSD_JObj *jobj;
    s32 unused[4];
    s16 i;
    s32 flag;
    s32 cursor;
    s16 part;

    kind = 4;
    count = 0;
    group = 0;
    show = 0;
    cursor = 0;
    part = 0;
    if (menumode == 4) {
        show = 1;
        kind = 4;
        group = 1;
        count = 8;
        cursor = 1;
    }
    if (menumode == 7) {
        show = 1;
        kind = 4;
        group = 1;
        count = 5;
    }
    if (menumode == 5) {
        show = 1;
        kind = 5;
        group = 3;
        count = 1;
    }
    if (menumode == 6) {
        show = 1;
        kind = 6;
        group = 4;
        count = 3;
        cursor = 1;
    }
    if (menumode == 8) {
        show = 1;
        kind = 6;
        group = 4;
        count = 3;
    }
    if (show == 0)
        return;
    if (menuzoidequippartslist == 0)
        return;
    (void)menusetst[kind];
    sl = &menusetsl[kind];
    for (i = 0; i < count; i++) {
        pos = GetChild(menu1p->models[14], 0, i, -1, -1, -1);
        jobj = GetChild(menu1p->models[idx], 0, -1, -1, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDisp(jobj, 0, 7, 0);
        if (kind == 4) {
            flag = 0;
            if (ttl_ZoidWepPointPermission(IveSave[0].selected_zoid, i) == 0)
                flag = -1;
            jobj = GetChild(menu1p->models[idx], 0, 0, i + menusetst[kind], flag, -1);
            HSD_JObjDisp(jobj, 0, 7, 0);
        }
        if (kind == 4)
            part = IveSave[0].zoid_weapons[IveSave[0].selected_zoid_slot][i + menusetst[kind]];
        if (kind == 5)
            part = IveSave[0].contract_options[IveSave[0].selected_zoid_slot];
        if (kind == 6)
            part = IveSave[0].contract_subparts[IveSave[0].selected_zoid_slot][i];
        if (part <= 0) {
            slot = 15;
            group = 1;
            part = -1;
        } else {
            type = Tea_partsdat[part].category;
            if (type == 1)
                group = 1;
            if (type == 2)
                group = 3;
            if (type == 3)
                group = 4;
            slot = Tea_partsdat[part].icon;
            if (kind == 4 && slot > 15)
                slot = 16;
            if (kind == 5 && slot > 4)
                slot = 4;
            if (kind == 6 && slot > 8)
                slot = 8;
        }
        jobj = GetChild(menu1p->models[idx], 0, group, slot, -1, -1);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        jobj = GetChild(menu1p->models[idx], 0, 2, -1, -1, -1);
        if (part == -1)
            putAscJobj(jobj, 2, "NONE");
        else
            putAscJobj(jobj, 2, Tea_partsdat[part].english_name);
        if (i == *sl && cursor == 1) {
            jobj = GetChild(menu1p->models[7], 0, 2, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
        }
    }
}
#pragma readonly_strings off


extern s16 menudispshophavezoidlist;

#pragma readonly_strings on
void menu_sDispBattleShopZoidHaveZoidList(void)
{
    char text[56];
    s16 i;
    s16 zoid;
    HSD_JObj *pos;
    HSD_JObj *jobj;
    HSD_JObj *pic;

    zoid = 0;
    if (menumode == 0)
        return;
    if (menudispshophavezoidlist == 0)
        return;
    pos = GetChild(menu1p->models[21], 0, 0, -1, -1, -1);
    jobj = GetChild(menu1p->models[12], 0, -1, -1, -1, -1);
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
    for (i = 0; i < menusetmh[3]; i++) {
        jobj = GetChild(menu1p->models[12], 0, 3, i, -1, -1);
        if (menudispshophavezoidlist == 1)
            zoid = IveSave[0].have_zoid[menusetst[3] + i];
        if (menudispshophavezoidlist == 2)
            zoid = IveSave[0].owned_zoids[menusetst[3] + i];
        if (zoid == -1 || menu_zoidp[zoid] == 0 || menu_zoidp[zoid]->models[0] == 0) {
            OSReport((char *)sLogWhoErr, menusetst[3] + i);
            continue;
        }
        pic = GetChild(menu_zoidp[zoid]->models[0], 0, 1, -1, -1, -1);
        jobjCopyPos(jobj, pic);
        HSD_JObjDispAll(pic, 0, 7, 0);
        sprintf(text, " %s", Tea_zoiddat[zoid].name);
        putAscJobj(jobj, 0, text);
        if (i != menusetsl[3])
            continue;
        if (menumodeShop == 1 && menudispshophavezoidlist == 1) {
            pos = GetChild(menu1p->models[12], 0, 4, -1, -1, -1);
            jobj = GetChild(menu1p->models[18], 0, 1, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
            pos = GetChild(menu1p->models[18], 0, 1, 1, -1, -1);
            sprintf(text, "%6d", Tea_zoiddat[IveSave[0].have_zoid[menusetst[3] + i]].price);
            putAscJobj(pos, 4, text);
        }
        if (menumodeShop == 2 && menudispshophavezoidlist == 2) {
            pos = GetChild(menu1p->models[12], 0, 4, -1, -1, -1);
            jobj = GetChild(menu1p->models[18], 0, 1, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
            pos = GetChild(menu1p->models[18], 0, 1, 1, -1, -1);
            sprintf(text, "%6d", Tea_zoiddat[IveSave[0].owned_zoids[menusetst[3] + i]].sell_price);
            putAscJobj(pos, 4, text);
        }
        menuyesnoshopmsg[32] = 0;
        if (menucuranm == 1) {
            SetAnimArc2(menu1p, 7, 0);
            menucuranm = 2;
        }
        if (menucuranm == 2) {
            if (jobjAnim(menu1p->models[7]) != 0)
                menucuranm = 3;
        } else if (menucuranm == 3) {
            SetAnimArc2(menu1p, 7, 0);
            jobjAnim(menu1p->models[7]);
            menucuranm = 2;
        }
        pos = GetChild(menu1p->models[12], 0, 3, i, -1, -1);
        jobj = GetChild(menu1p->models[7], 0, 1, -1, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
    }
}
#pragma readonly_strings off


extern s32 menu_StageUpDownFlag;
extern void __assert(const char *file, u32 line, const char *condition);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *joint);

static inline s32 HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    s32 result;
    if (!jobj)
        __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40))
        result = 1;
    return result;
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, f32 y)
{
    if (!jobj)
        __assert("jobj.h", 696, "jobj");
    if (jobj->flags & 0x20000)
        __assert("jobj.h", 697, (char *)sJObjQuaternionAssert);
    jobj->rotation[1] = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

void menu_sDispBattleFarmBack(void)
{
    f32 ry;
    s32 unused[2];

    ry = rPadX();
    if (menubackanm[0].cur != menubackanm[0].old) {
        menubackanm[0].state = 1;
        menubackanm[0].old = menubackanm[0].cur;
    }
    if (menubackanm[0].state == 1) {
        menubackanm[0].state = 2;
        SetAnimArc2(menu_back1p, 1, menubackanm[0].cur);
        menu_StageUpDownFlag = 0;
    }
    if (menubackanm[0].state == 2 && jobjAnim(menu_back1p->models[1]) != 0) {
        menubackanm[0].state = 3;
        menuanmend = 1;
        menu_StageUpDownFlag = 1;
        if (menubackanm[0].cur == 2 || menubackanm[0].cur == 3) {
            if (menubackanm[0].cur == 2)
                menubackanm[0].cur = 0;
            if (menubackanm[0].cur == 3)
                menubackanm[0].cur = 1;
            SetAnimArc2(menu_back1p, 1, menubackanm[0].cur);
            jobjAnim(menu_back1p->models[1]);
        }
    }
    HSD_JObjSetRotationY(GetChild(menu_back1p->models[1], 0, 2, -1, -1, -1), ry);
    HSD_JObjSetRotationY(GetChild(menu_back1p->models[0], 0, -1, -1, -1, -1), ry);
    HSD_JObjSetRotationY(GetChild(menu_back1p->models[1], 0, -1, -1, -1, -1), ry);
    jobjDispAll(menu_back1p->models[0]);
    jobjDispAll(menu_back1p->models[1]);
}


extern s8 vsman;
extern s32 flag_menuvsenthuman[2];
extern s32 flag_menuvsentzoid[2];
extern s8 menuvsmode[4];
extern void menu_sDispVsEntryPersonListDisp(s16 index, s16 slot);
extern void menu_sDispVsEntryZoidListDisp(s16 index, s16 slot);
extern void jobjDisp(HSD_JObj *joint);

void menu_sDispVsEntryPilotZoidList(void)
{
    s16 i;
    HSD_JObj *cursor;
    HSD_JObj *pos;
    HSD_JObj *pos2;
    HSD_JObj *cursor2;
    s32 unused[2];

    if (flag_menuvsentzoid[vsman] == 1 || flag_menuvsenthuman[vsman] == 1)
        jobjDispAll(GetChild(menu1p->models[9], 0, vsman, -1, -1, -1));
    if (menuvsmode[vsman] == vsman + 4 && flag_menuvsenthuman[vsman] != 0) {
        for (i = 0; i < IveSave[vsman].person_list_count; i++) {
            if (menufarmst[vsman + 4] <= i && i - menufarmst[vsman + 4] <= menufarmmh[vsman + 4] - 1)
                menu_sDispVsEntryPersonListDisp(IveSave[vsman].person_list[i], i - menufarmst[vsman + 4]);
        }
        pos = GetChild(menu1p->models[9], 0, vsman, 3, menufarmsl[vsman + 4], -1);
        cursor = GetChild(menu1p->models[7], 0, 1, -1, -1, -1);
        jobjCopyPos(pos, cursor);
        jobjDisp(cursor);
    }
    if (menuvsmode[vsman] == vsman + 6 && flag_menuvsentzoid[vsman] != 0) {
        for (i = 0; i < IveSave[vsman].owned_zoid_count; i++) {
            if (menufarmst[vsman + 6] <= i && i - menufarmst[vsman + 6] <= menufarmmh[vsman + 6] - 1)
                menu_sDispVsEntryZoidListDisp(IveSave[vsman].owned_zoids[i], i - menufarmst[vsman + 6]);
        }
        pos2 = GetChild(menu1p->models[9], 0, vsman, 3, menufarmsl[vsman + 6], -1);
        cursor2 = GetChild(menu1p->models[7], 0, 1, -1, -1, -1);
        jobjCopyPos(pos2, cursor2);
        jobjDisp(cursor2);
    }
}


#pragma readonly_strings on
void menuSetTitleButton(s16 type)
{
    s16 i;

    for (i = 1; i < 7; i++) {
        menutitleanm[i].mode = 3;
        menutitleanm[i].state = 2;
        menutitleanm[i].next = 2;
        menutitleanm[i].reserved = 1;
    }
    if (type == 0) {
        menutitleguide[1] = 0;
        menutitleguide[2] = 1;
        menutitleguide[3] = -1;
        menutitleguide[4] = -1;
        menutitleguide[5] = -1;
        menutitleguide[6] = -1;
    }
    if (type == 1) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 0;
        menutitleguide[5] = 1;
        menutitleguide[6] = -1;
    }
    if (type == 2) {
        menutitleguide[1] = 0;
        menutitleguide[2] = 1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 3;
        menutitleguide[5] = 4;
        menutitleguide[6] = 5;
    }
    if (type == 3) {
        menutitleguide[1] = 0;
        menutitleguide[2] = 1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 4;
        menutitleguide[5] = 5;
        menutitleguide[6] = -1;
    }
    if (type == 10) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 1;
        menutitleguide[5] = -1;
        menutitleguide[6] = -1;
    }
    if (type == 11) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 0;
        menutitleguide[5] = 1;
        menutitleguide[6] = -1;
    }
    if (type == 101) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 0;
        menutitleguide[5] = 1;
        menutitleguide[6] = -1;
    }
    for (i = 1; i < 7; i++) {
        if (menutitleguide[i] == -1) {
            menutitleanm[i].mode = 0;
            menutitleanm[i].state = 2;
            menutitleanm[i].next = 2;
        } else {
            menutitleanm[i].mode = 1;
            menutitleanm[i].state = 0;
            menutitleanm[i].next = 2;
        }
        OSReport("%d:%d ", menutitleanm[i].mode, menutitleanm[i].state);
    }
    OSReport("\n");
}
#pragma readonly_strings off


#pragma readonly_strings on
void menuSetTitle(s16 type)
{
    s16 i;

    menutitleanm[0].mode = 1;
    menutitleanm[0].state = 0;
    menutitleanm[0].next = 2;
    menutitleanm[0].reserved = 0;
    for (i = 1; i < 7; i++) {
        menutitleanm[i].mode = 3;
        menutitleanm[i].state = 2;
        menutitleanm[i].next = 2;
        menutitleanm[i].reserved = 1;
    }
    menutitleguide[0] = type;
    if (type == 0) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 0;
        menutitleguide[5] = 1;
        menutitleguide[6] = -1;
    }
    if (type == 1) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 0;
        menutitleguide[5] = 1;
        menutitleguide[6] = -1;
    }
    if (type == 2) {
        menutitleguide[1] = 0;
        menutitleguide[2] = 1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 3;
        menutitleguide[5] = -1;
        menutitleguide[6] = -1;
    }
    if (type == 3) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 0;
        menutitleguide[5] = 1;
        menutitleguide[6] = -1;
    }
    if (type == 101) {
        menutitleguide[1] = -1;
        menutitleguide[2] = -1;
        menutitleguide[3] = -1;
        menutitleguide[4] = 0;
        menutitleguide[5] = 1;
        menutitleguide[6] = -1;
    }
    if (type == 101)
        menutitleguide[0] = 0;
    for (i = 1; i < 7; i++) {
        if (menutitleguide[i] == -1) {
            menutitleanm[i].mode = 0;
            menutitleanm[i].state = 2;
            menutitleanm[i].next = 2;
        } else {
            menutitleanm[i].mode = 1;
            menutitleanm[i].state = 0;
            menutitleanm[i].next = 2;
        }
        OSReport("%d:%d ", menutitleanm[i].mode, menutitleanm[i].state);
    }
    OSReport("\n");
}
#pragma readonly_strings off


extern s16 dlgzoidno;
extern s8 menuzoidhavepartslist;

#pragma readonly_strings on
void menu_sDispBattleShopHavePartsList(void)
{
    char text[80];
    HSD_JObj *b;
    s16 i;
    HSD_JObj *item;
    HSD_JObj *c;
    s32 idx;
    s32 kind = 1;
    HSD_JObj *e;
    HSD_JObj *jobj;
    HSD_JObj *a;
    HSD_JObj *f;
    HSD_JObj *d;
    s16 slot;
    s16 zoid;
    s16 part = 0;

    if (menuzoidhavepartslist == 0)
        return;
    a = GetChild(menu1p->models[21], 0, 2, -1, -1, -1);
    b = GetChild(menu1p->models[10], 0, -1, -1, -1, -1);
    jobjCopyPos(a, b);
    HSD_JObjDispAll(b, 0, 7, 0);
    if (menumodeShop != 0) {
        c = GetChild(menu1p->models[10], 0, 4, -1, -1, -1);
        d = GetChild(menu1p->models[18], 0, 1, -1, -1, -1);
        jobjCopyPos(c, d);
        HSD_JObjDispAll(d, 0, 7, 0);
        if (menumodeShop == 1) {
            zoid = dlgzoidno;
            e = GetChild(menu1p->models[21], 0, 1, -1, -1, -1);
            f = GetChild(menu_zoidp[zoid]->models[0], 0, 1, -1, -1, -1);
            jobjCopyPos(e, f);
            HSD_JObjDispAll(f, 0, 7, 0);
            sprintf(text, " %s", Tea_zoiddat[zoid].name);
            putAscJobj(e, 0, text);
        }
    }
    idx = 11;
    if (menuzoidhavepartslist == 1)
        kind = 1;
    if (menuzoidhavepartslist == 2)
        kind = 3;
    if (menuzoidhavepartslist == 3)
        kind = 4;
    for (i = 0; i < menusetmh[3]; i++) {
        item = GetChild(menu1p->models[10], 0, 3, i, -1, -1);
        jobj = GetChild(menu1p->models[idx], 0, -1, -1, -1, -1);
        jobjCopyPos(item, jobj);
        HSD_JObjDisp(jobj, 0, 7, 0);
        if (menumodeShop == 1)
            part = IveSave[0].list_parts[menusetst[3] + i];
        if (menumodeShop == 2)
            part = IveSave[0].list_parts[menusetst[3] + i];
        if (part == -1) {
            slot = 16;
            kind = 1;
        } else {
            slot = Tea_partsdat[part].icon;
        }
        if (kind == 1 && slot > 16)
            slot = 16;
        if (kind == 3 && slot > 4)
            slot = 4;
        if (kind == 4 && slot > 8)
            slot = 8;
        HSD_JObjDispAll(GetChild(menu1p->models[idx], 0, kind, slot, -1, -1), 0, 7, 0);
        jobj = GetChild(menu1p->models[idx], 0, 2, -1, -1, -1);
        if (part == -1) {
            putAscJobj(jobj, 2, "NONE");
            part = 0;
        } else {
            putAscJobj(jobj, 2, Tea_partsdat[part].english_name);
        }
        if (i != menusetsl[3])
            continue;
        if (menumodeShop != 0) {
            jobj = GetChild(menu1p->models[18], 0, 1, 1, -1, -1);
            if (menumodeShop == 1)
                sprintf(text, "%6d", Tea_partsdat[part].field_50);
            if (menumodeShop == 2)
                sprintf(text, "%6d", Tea_partsdat[part].sell_price);
            putAscJobj(jobj, 4, text);
        }
        if (menucuranm == 1) {
            SetAnimArc2(menu1p, 7, 0);
            menucuranm = 2;
        }
        if (menucuranm == 2) {
            if (jobjAnim(menu1p->models[7]) != 0)
                menucuranm = 3;
        } else if (menucuranm == 3) {
            SetAnimArc2(menu1p, 7, 0);
            jobjAnim(menu1p->models[7]);
            menucuranm = 2;
        }
        jobj = GetChild(menu1p->models[7], 0, 2, -1, -1, -1);
        jobjCopyPos(item, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        sprintf((char *)menudispwinstr, (char *)sPaddedStringFormat, Tea_partsdat[part].name, GetMenuMsgAdr(37));
        ((char *)menudispwinstr)[36] = 0;
    }
}
#pragma readonly_strings off





void menu_sDispSetButton(void)
{
    s16 i;
    s16 on;
    s16 off;
    s32 unused[2];

    if (menumode != 0) {
        menufarmanm[2] = 3;
        menufarmanm[3] = 3;
        menufarmanm[4] = 3;
        menufarmanm[5] = 3;
        menufarmanm[6] = 3;
    }
    switch (menumode) {
    case -1:
        for (i = 0; i <= 9; i++) {
            menufarmanm[i] = 2;
            menumodeanm[i] = 1;
        }
        break;
    case 0:
        menufarmanm[1] = 3;
        menufarmanm[7] = 3;
        menufarmanm[8] = 3;
        menufarmanm[9] = 3;
        menufarmanm[2] = 3;
        menufarmanm[3] = 3;
        menufarmanm[4] = 3;
        menufarmanm[5] = 3;
        menufarmanm[6] = 3;
        menufarmanm[(s16)(menufarmcl[0] + 2)] = 4;
        break;
    case 1:
        if (menufarmcl[1] == 0) {
            on = 1;
            off = 7;
        } else {
            on = 7;
            off = 1;
        }
        menufarmanm[on] = 4;
        menufarmanm[off] = 3;
        break;
    case 2:
        menufarmanm[1] = 5;
        if (menufarmcl[2] == 0) {
            on = 8;
            off = 9;
        } else {
            on = 9;
            off = 8;
        }
        menufarmanm[on] = 4;
        menufarmanm[off] = 3;
        break;
    }
}


extern struct HSD_TObj *searchTObjN(HSD_JObj *joint, s32 *index);
extern void texScroll(struct HSD_TObj *tobj, f32 x, f32 y, f32 z);
extern void SeCancel(void);
extern void SeRet(void);
extern char *GetMenuMsgAdr(s16 message);
extern s32 TEA_menufnc12p(s16 *menup, s16 *menust, s16 maxn, s16 max);

#pragma push
#pragma dont_inline on
s16 menufncPushStartMain(void)
{
    s32 pad0[3];
    u8 idx = 2;
    s32 index = 0;
    s32 pad1[1];
    struct HSD_TObj *tobj;
    s16 i;
    s32 result;
    f32 y;
    f32 delta;
    f32 step;

    index = 1;
    delta = 0.003f;
    tobj = searchTObjN(GetChild(menu1p->models[idx], 0, -1, -1, -1, -1), &index);
    menumode = idx;
    menutitleanm[2].mode = 0;
    menutitleanm[2].state = 0;
    menutitleanm[2].next = 2;
    menufarmcl[2] = 1;
    menufarmsl[2] = 1;
    menufarmst[2] = 0;
    menufarmmh[2] = 4;
    menufarmmn[2] = 4;
    y = 0.0625f * menufarmcl[2];
    texScroll(tobj, 0.0f, y, 0.0f);
    menu_sDispStart();
    texScroll(tobj, 0.0f, y, 0.0f);
    menu_sDispStart();
    texScroll(tobj, 0.0f, y, 0.0f);
    texScroll(tobj, 0.0f, y, 0.0f);
    menu_sDispStart();
    menu_sDispStart();
    menu_sDispStart();
    step = 0.0625f;
    while (1) {
        sPadAll();
        menufarmcl[menumode] = (u16)TEA_menufnc12p(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        strcpy((char *)menudispwinstr, GetMenuMsgAdr(menufarmcl[menumode]));
        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0)
            SeCancel();
        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0 || sPad1->pressed_start != 0 || sPad2->pressed_start != 0) {
            if (menufarmcl[menumode] == 0)
                break;
            if (menufarmcl[menumode] == 1)
                break;
            if (menufarmcl[menumode] == 2)
                break;
            if (menufarmcl[menumode] == 3)
                break;
        }
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0 || sPad2->pressed_dpad_up != 0 || sPad2->pressed_stick_up != 0) {
            SeSelectB();
            i = 0;
            do {
                texScroll(tobj, 0.0f, y - i * delta, 0.0f);
                menu_sDispStart();
                i++;
            } while (i < 19);
            y = step * menufarmcl[menumode];
            texScroll(tobj, 0.0f, y, 0.0f);
            menu_sDispStart();
        }
        if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0 || sPad2->pressed_dpad_down != 0 || sPad2->pressed_stick_down != 0) {
            SeSelectB();
            i = 0;
            do {
                texScroll(tobj, 0.0f, y + i * delta, 0.0f);
                menu_sDispStart();
                i++;
            } while (i < 19);
            y = step * menufarmcl[menumode];
            texScroll(tobj, 0.0f, y, 0.0f);
            menu_sDispStart();
        }
        menu_sDispStart();
    }
    SeRet();
    if (menufarmcl[menumode] == 1 || menufarmcl[menumode] == 2)
        menutitleanm[menumode].state = 2;
    else
        menutitleanm[menumode].state = 3;
    menutitleanm[menumode].state = 2;
    menutitleanm[menumode].mode = 1;
    menuanmend = 0;
    while (menutitleanm[menumode].mode != 3)
        menu_sDispStart();
    result = menufarmcl[menumode];
    OSReport((char *)sLogMenuMainEnd);
    return result;
}
#pragma pop


#pragma readonly_strings on
void menu_sDispBattleFarmPersonZoidPartner(void)
{
    char text[80];
    HSD_JObj *pos;
    HSD_JObj *jobj;

    pos = GetChild(menu1p->models[8], 0, 0, 0, -1, -1);
    jobj = GetChild(menu1p->models[6], 0, 2, 3, -1, -1);
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
    pos = GetChild(menu1p->models[8], 0, 0, 0, -1, -1);
    jobj = GetChild(menu_personp[IveSave[0].selected_person]->models[0], 0, 1, -1, -1, -1);
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
    sprintf(text, " %s", Tea_persondat[IveSave[0].selected_person].name);
    putAscJobj(pos, 0, text);
    pos = GetChild(menu1p->models[8], 0, 0, 1, -1, -1);
    jobj = GetChild(menu1p->models[6], 0, 2, 3, -1, -1);
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
    pos = GetChild(menu1p->models[8], 0, 0, 1, -1, -1);
    jobj = GetChild(menu_zoidp[IveSave[0].selected_zoid]->models[0], 0, 1, -1, -1, -1);
    jobjCopyPos(pos, jobj);
    HSD_JObjDispAll(jobj, 0, 7, 0);
    sprintf(text, " %s", Tea_zoiddat[IveSave[0].selected_zoid].name);
    putAscJobj(pos, 0, text);
    if (menuZoidBattleModeSingleTeam == 1) {
        pos = GetChild(menu1p->models[8], 0, 1, 0, -1, -1);
        jobj = GetChild(menu1p->models[6], 0, 2, 3, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        pos = GetChild(menu1p->models[8], 0, 1, 0, -1, -1);
        jobj = GetChild(menu_personp[IveSave[0].partner_person]->models[0], 0, 1, -1, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        sprintf(text, " %s", Tea_persondat[IveSave[0].partner_person].name);
        putAscJobj(pos, 0, text);
        pos = GetChild(menu1p->models[8], 0, 1, 1, -1, -1);
        jobj = GetChild(menu1p->models[6], 0, 2, 3, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        pos = GetChild(menu1p->models[8], 0, 1, 1, -1, -1);
        jobj = GetChild(menu_zoidp[IveSave[0].partner_zoid]->models[0], 0, 1, -1, -1, -1);
        jobjCopyPos(pos, jobj);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        sprintf(text, " %s", Tea_zoiddat[IveSave[0].partner_zoid].name);
        putAscJobj(pos, 0, text);
    }
}
#pragma readonly_strings off


extern void jobjCopyPosS(HSD_JObj *source, HSD_JObj *target);
extern void sGlobal2Local(HSD_JObj *joint);
extern void HiddenParts(HSD_JObj *joint, s32 hidden);
extern void menu_sDispBattleFarmTitleSubButton(void);
extern s32 radarLen[];

static inline void HSD_JObjAddTranslationX(HSD_JObj *jobj, f32 x)
{
    if (!jobj)
        __assert("jobj.h", 1109, "jobj");
    jobj->translation.x += x;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjAddTranslationY(HSD_JObj *jobj, f32 y)
{
    if (!jobj)
        __assert("jobj.h", 1120, "jobj");
    jobj->translation.y += y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj))
            HSD_JObjSetMtxDirtySub(jobj);
    }
}

#pragma readonly_strings on
#pragma push
#pragma bool off
#pragma auto_inline off
void menu_sDispBattleMapInfo(char *info, u8 *flags, s32 cursor, s32 previous, ModelArchive *back, ModelArchive **pictures)
{
    char *unit;
    GXColor white = { 255, 255, 255, 255 };
    GXColor black = { 0, 0, 0, 0 };
    GXColor green = { 0, 255, 0, 255 };
    GXColor blue = { 0, 0, 0, 255 };
    s32 j;
    HSD_JObj *title;
    HSD_JObj *list;
    HSD_JObj *start;
    HSD_JObj *end;
    HSD_JObj *base;
    s32 i;
    HSD_JObj *jobj;
    s32 kind;
    s32 len;
    s32 idx;
    f32 x;
    f32 y;

    title = menu1p->models[19];
    list = menu1p->models[20];
    HSD_StartRender(0);
    if (HSD_CObjSetCurrent(menu_back1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu_back1p->lights);
        HSD_LObjSetupInit(menu_back1p->camera);
        GXSetCullMode(0);
        menu_sDispBattleFarmBack();
        menu_sDispBattleFarmZoid();
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    if (HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        menu_sDispBattleFarmTitle();
        menu_sDispBattleFarmTitleSubButton();
        if (previous == -1)
            SetAnimArc2(menu1p, 19, 0);
        if (jobjAnim(title) != 0) {
            SetAnimArc2(menu1p, 19, 1);
            jobjAnim(title);
        }
        sMakeMatrix(title);
        jobjDispAll(GetChild(title, 0, 1, -1, -1, -1));
        putAscJobj(GetChild(title, 0, 1, 0, -1, -1), 4, ((MapInfo *)info)->label);
        start = GetChild(title, 0, 1, 1, -1, -1);
        end = GetChild(title, 0, 1, 1, 0, -1);
        sPutFontRect(((MapInfo *)info)->title, start, end, white, black, 0, 2);
        jobjDispAll(GetChild(title, 0, 3, -1, -1, -1));
        start = GetChild(title, 0, 3, 0, -1, -1);
        end = GetChild(title, 0, 3, 0, 0, -1);
        sPutFontRect((char *)sVictoryConditionLabel, start, end, green, blue, 0, 2);
        start = GetChild(title, 0, 3, 2, -1, -1);
        end = GetChild(title, 0, 3, 2, 0, -1);
        sPutFontRect(((MapInfo *)info)->victory_text, start, end, white, black, 0, 2);
        start = GetChild(title, 0, 3, 1, -1, -1);
        end = GetChild(title, 0, 3, 1, 0, -1);
        sPutFontRect((char *)sDefeatConditionLabel, start, end, green, blue, 0, 2);
        start = GetChild(title, 0, 3, 3, -1, -1);
        end = GetChild(title, 0, 3, 3, 0, -1);
        sPutFontRect(((MapInfo *)info)->defeat_text, start, end, white, black, 0, 2);
        base = 0;
        if (back != 0) {
            base = GetChild(title, 0, 2, -1, -1, -1);
            jobjCopyPosS(base, back->models[0]);
            jobjDispAll(back->models[0]);
        }
        if (jobjAnim(menu1p->models[5]) != 0) {
            SetAnimArc2(menu1p, 5, cursor == 0 ? 2 : 1);
            jobjAnim(menu1p->models[5]);
        }
        sMakeMatrix(menu1p->models[5]);
        jobjDispAll(GetChild(menu1p->models[5], 0, 2, -1, -1, -1));
        jobjAnim(list);
        sMakeMatrix(list);
        for (i = 1; i < 17; i++) {
            jobj = GetChild(list, 0, i - 1, -1, -1, -1);
            HiddenParts(jobj, ((MapInfo *)info)->units[i].name[0] == 0);
            switch ((s8)flags[i]) {
            case 0:
                sSetAnim1(menu1p, 20, jobj, 1);
                flags[i] = 1;
                break;
            case 1:
                if (cursor == i) {
                    sSetAnim1(menu1p, 20, jobj, 2);
                    flags[i] = 2;
                }
                break;
            case 2:
                if (cursor != i) {
                    sSetAnim1(menu1p, 20, jobj, 1);
                    flags[i] = 1;
                }
                break;
            }
        }
        jobjDispAll(list);
        if (back != 0) {
            jobjAnim(back->models[1]);
            jobjCopyPosS(base, back->models[1]);
            sMakeMatrix(back->models[1]);
            for (j = 1; j < 17; j++) {
                char text[2] = "A";
                unit = &info[j * 588];
                if (unit[300] == 0)
                    continue;
                kind = *(s32 *)(unit + 332);
                if (kind <= 0)
                    continue;
                x = *(s32 *)(unit + 476);
                y = *(s32 *)(unit + 484);
                jobj = GetChild(back->models[1], 0, kind - 1, -1, -1, -1);
                if (jobj == 0)
                    continue;
                jobjCopyPosS(base, jobj);
                len = radarLen[((MapInfo *)info)->map_no];
                if (len != 0) {
                    HSD_JObjAddTranslationX(jobj, 2.0 * (12.8 * (x / len)));
                    HSD_JObjAddTranslationY(jobj, 2.0 * (12.8 * (-y / len)));
                }
                HiddenParts(GetChild(jobj, 0, 0, -1, -1, -1), cursor != j);
                jobjDispAll(jobj);
                sMakeMatrix(jobj);
                text[0] = j + 64;
                jobj = GetChild(jobj, 0, 0, 0, -1, -1);
                sMakeMatrix(jobj);
                putAscJobj(jobj, 4, text);
            }
        }
        jobjDisp(GetChild(title, 0, 4, -1, -1, -1));
        jobjDisp(GetChild(title, 0, 4, 0, -1, -1));
        start = GetChild(title, 0, 4, 2, -1, -1);
        end = GetChild(title, 0, 4, 2, 0, -1);
        sPutFontRect(((MapInfo *)info)->units[cursor].name, start, end, white, black, 0, 2);
        if (cursor != 0) {
            Vec3 pos;

            jobj = GetChild(list, 0, cursor - 1, -1, -1, -1);
            (void)&pos;
            pos.x = jobj->matrix[0][3];
            pos.y = jobj->matrix[1][3];
            pos.z = jobj->matrix[2][3];
            jobjCopyPos(GetChild(title, 0, 4, 1, -1, -1), jobj);
            sGlobal2Local(jobj);
            sMakeMatrix(jobj);
            jobjDispAll(jobj);
            jobj->matrix[0][3] = pos.x;
            jobj->matrix[1][3] = pos.y;
            jobj->matrix[2][3] = pos.z;
            sGlobal2Local(jobj);
            sMakeMatrix(jobj);
        }
        switch (((s32 *)(info + 332))[cursor * 147]) {
        case MAP_UNIT_MAP:
            idx = 3;
            break;
        case MAP_UNIT_ZOID:
        case MAP_UNIT_PLAYER:
        case MAP_UNIT_PARTNER:
            idx = 5;
            break;
        case 2:
            idx = 3;
            break;
        default:
            idx = -1;
            break;
        }
        jobj = 0;
        if (idx != -1)
            jobj = GetChild(title, 0, 4, idx, -1, -1);
        if (pictures[cursor] != 0 && jobj != 0) {
            jobjCopyPosS(jobj, pictures[cursor]->models[0]);
            if (idx == 5)
                jobjDisp(GetChild(pictures[cursor]->models[0], 0, 0, -1, -1, -1));
            else
                jobjDispAll(pictures[cursor]->models[0]);
        }
        if (idx == 3) {
            start = GetChild(title, 0, 4, 4, -1, -1);
            end = GetChild(title, 0, 4, 4, 0, -1);
            sPutFontRect(((MapInfo *)info)->units[cursor].text, start, end, white, black, 0, 2);
        }
        if (0)
            sPutFontRect(info, start, end, white, black, 0, 2);
        HSD_CObjEndCurrent();
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
#pragma pop
#pragma readonly_strings off

#pragma push
#pragma dont_inline on
extern void putErr(char *message);
extern void menu_sDispBattleMapInfo(char *info, u8 *flags, s32 cursor, s32 previous, ModelArchive *back, ModelArchive **pictures);
extern void SeRet(void);

void menufnc_MapInfo(s32 mode, s32 map)
{
    char path[256];
    u8 flags[30];
    ModelArchive *pictures[30];
    char *info;
    s32 dir;
    s32 i;
    s32 cursor;
    s32 previous;
    char *unit;
    ModelArchive *back;
    s32 id;

    cursor = 0;
    previous = -1;
    for (i = 0; i < 30; i++) {
        flags[i] = 0;
        pictures[i] = 0;
    }
    info = rdMapInfo(mode, map);
    if (info == 0) {
        putErr((char *)sMapInfoError);
        OSReport((char *)sLogMapInfoError);
        info = rdMapInfo(mode, 99);
    }
    sprintf(path, (char *)sFarmPathFormat, info);
    back = LoadArc2(path);
    for (i = 0; i < 17; i++) {
        unit = &info[i * 588];
        if (unit[336] != 0) {
            sprintf(path, (char *)sPicturePathFormat, unit + 336);
            pictures[i] = LoadArc2(path);
        } else {
            id = -1;
            if (*(s32 *)(unit + 332) == MAP_UNIT_PARTNER) {
                if (IveSave[0].partner_person < 0)
                    unit[300] = 0;
                else
                    id = IveSave[0].partner_zoid;
                if (IveSave[0].partner_person == 57)
                    unit[300] = 0;
            }
            if (*(s32 *)(unit + 332) == MAP_UNIT_PLAYER)
                id = IveSave[0].selected_zoid;
            if (id != -1) {
                sprintf(path, (char *)sSzPictureFormat, id);
                OSReport((char *)sLogZoidPathId, path, id);
                pictures[i] = LoadArc2(path);
            }
        }
    }
    OSReport((char *)sLogPart, IveSave[0].partner_person);
    while (1) {
        dir = 0;
        if (info[cursor * 588 + 300] == 0)
            dir = 1;
        if (sPad1->pressed_down != 0)
            dir = 1;
        if (sPad1->pressed_up != 0)
            dir = -1;
        if (sPad1->right != 0) {
            dir = 0;
            cursor = 0;
        }
        if (sPad1->left != 0) {
            dir = 1;
            cursor = 0;
        }
        while (1) {
            cursor += dir;
            if (cursor < 0)
                cursor = 16;
            if (cursor > 16)
                cursor = 0;
            if (info[cursor * 588 + 300] != 0)
                break;
            if (dir == 0)
                dir = 1;
        }
        menu_sDispBattleMapInfo(info, flags, cursor, previous, back, pictures);
        if (previous != cursor && previous != -1)
            SeSelectB();
        previous = cursor;
        sPadAll();
        if (sPad1->pressed_b != 0)
            cursor = 0;
        if (sPad1->pressed_a != 0 && cursor == 0)
            break;
    }
    SeRet();
    for (i = 0; i < 30; i++) {
        if (pictures[i] != 0)
            PurgeArc2(pictures[i]);
        pictures[i] = 0;
    }
    if (back != 0)
        PurgeArc2(back);
}
#pragma pop


extern s32 csO;
extern s32 sbN;
extern s32 rumbleTm;

extern void TEA_VoiceOff(void);
extern void debug11(void);
extern void getSubMenuT(void);
extern void subMenu(void);
extern void configGet(void);
extern void configSet(void);
extern void configPut(void);
extern s32 menu_sDispConfig(ModelArchive *archive, s32 mode);
extern void SeCancel(void);
extern void SeRet(void);

#pragma push
#pragma dont_inline on
void menufncZoid_ConfigMenu(void)
{
    ModelArchive *archive;
    s32 done;
    s32 flags;
    s32 previous;

    TeaBgm(1);
    archive = LoadArc2((char *)sConfigArchivePath);
    OSReport((char *)sLogConfig);
    if (archive == 0)
        return;
    configGet();
    configSet();
    flags = 0;
    csO = 1;
    csN = 6;
    csA = 0;
    csAO = 0;
    crO = -1;
    crN = -1;
    sbN = -1;
    sbT = -1;
    sbTA = -1;
    TEA_VoiceOff();
    debug11();
    do {
        getSubMenuT();
        subMenu();
        done = menu_sDispConfig(archive, flags);
        sPadAll();
        if (sPad1->pressed_a != 0 || sPad1->pressed_b != 0) {
            sPad1->pressed_down = 0;
            sPad1->pressed_up = 0;
            sPad1->left = 0;
            sPad1->right = 0;
        }
        if (sPad1->pressed_a != 0)
            sPad1->pressed_b = 0;
        if (sPad1->pressed_down != 0)
            sPad1->pressed_up = 0;
        if (sPad1->right != 0) {
            sPad1->left = 0;
            sPad1->pressed_down = 0;
        }
        flags = (flags & 1) + flags * 2;
        if (sPad1->pressed_b != 0) {
            if (crN == -1) {
                if (csN != 6)
                    SeCancel();
                csN = 6;
            } else {
                SeCancel();
                crN = -1;
                sbN = -1;
                TeaBgm(1);
            }
        } else if (sPad1->pressed_a != 0 && csN == 6) {
            flags |= 1;
            SeRet();
        } else {
            if (rumbleTm != 0) {
                rumbleTm--;
                sPad1->rumble = 1;
            } else {
                sPad1->rumble = 0;
            }
            if (flags & 1)
                sPad1->rumble = 0;
            if (crN == -1) {
                previous = csN;
                if (csN == 6 && sPad1->left != 0)
                    csN = 0;
                if (csN != 6 && sPad1->right != 0)
                    csN = 6;
                if (sPad1->pressed_up != 0)
                    csN--;
                if (sPad1->pressed_down != 0)
                    csN++;
                if (csN != previous) {
                    SeSelectB();
                    continue;
                }
            } else if (csN != 6) {
                previous = sbN;
                if (sPad1->pressed_up != 0)
                    sbN--;
                if (sPad1->pressed_down != 0)
                    sbN++;
                if (sbN < 0)
                    sbN = menuMax[csN] - 1;
                if (sbN >= (s32)menuMax[csN])
                    sbN = 0;
                if (previous != sbN)
                    SeSelectB();
                getSubMenuT();
            }
            if (csN < 0)
                csN = 6;
            if (csN > 6)
                csN = 0;
            if (sPad1->pressed_a != 0 && crN == -1) {
                crN = csN;
                sbN = 0;
                SeRet();
                switch (csN) {
                case 0:
                case 1:
                case 2:
                    TeaBgm(-1);
                    break;
                }
            }
        }
    } while (done == 0);
    sPad1->rumble = 0;
    PurgeArc2(archive);
    configPut();
}
#pragma pop


void menuPartsSetListZoid(s16 category, s16 zoid)
{
    s16 found;
    s16 i;
    s16 j;
    s16 part;

    found = 0;
    for (i = 0; i < 450; i++) {
        IveSave[0].list_flag[i] = -1;
        IveSave[0].list_parts[i] = -1;
    }
    IveSave[0].list_count = 0;
    for (i = 0; i < 450; i++) {
        part = IveSave[0].owned_parts[i];
        if (part != -1 && Tea_partsdat[part].category == category) {
            if (Tea_partsdat[part].zoids[0] == -1) {
                found = 1;
            } else {
                for (j = 0; j < 12; j++) {
                    if (zoid == Tea_partsdat[part].zoids[j]) {
                        found = 1;
                        break;
                    }
                }
            }
            if (found != 0) {
                found = 0;
                IveSave[0].list_parts[IveSave[0].list_count] = part;
                IveSave[0].list_flag[IveSave[0].list_count] = i;
                IveSave[0].list_count++;
            }
        }
    }
    OSReport((char *)sLogPartsSet, category, IveSave[0].list_count);
    if (IveSave[0].list_count == 0) {
        for (j = 0; j < 450; j++) {
            if (IveSave[0].list_parts[j] == -1)
                continue;
        }
    }
}


void menuPartsWepSetListZoid(s16 category, s16 zoid, s16 point)
{
    s16 found;
    s16 i;
    s16 j;
    s16 part;
    s16 mount;
    s16 wp;

    for (i = 0; i < 450; i++) {
        IveSave[0].list_flag[i] = -1;
        IveSave[0].list_parts[i] = -1;
    }
    IveSave[0].list_count = 0;
    for (i = 0; i < IveSave[0].owned_part_count; i++) {
        part = IveSave[0].owned_parts[i];
        if (part > 0) {
            OSReport((char *)sLogPartsList, i, part, Tea_partsdat[part].name);
            found = 0;
            for (j = 0; j < 10; j++) {
                mount = Tea_zoiddat[zoid].mount_parts[j];
                if (mount == -1)
                    continue;
                if (IveSave[0].owned_parts[i] != mount)
                    continue;
                wp = Tea_zoiddat[zoid].weapon_points[j];
                if (point != wp)
                    continue;
                OSReport((char *)sLogPartsWeaponPoint, wp, Tea_partsdat[IveSave[0].owned_parts[i]].category, mount, Tea_partsdat[mount].name);
                found = 1;
            }
            if (found != 0) {
                IveSave[0].list_parts[IveSave[0].list_count] = IveSave[0].owned_parts[i];
                IveSave[0].list_flag[IveSave[0].list_count] = i;
                IveSave[0].list_count++;
            }
        }
    }
    OSReport((char *)sLogPartsSetWeapon, category, point, IveSave[0].list_count);
    if (IveSave[0].list_count == 0) {
        for (i = 0; i < 450; i++) {
            if (IveSave[0].list_parts[i] == -1)
                continue;
        }
    }
}


void ttlMenuSaveDataChk(void)
{
    s16 type;
    s16 i;
    s32 unused[1];

    i = 0;
    if (GameMode.game_type == GAME_TYPE_MISSION)
        type = 0;
    else
        type = 1;
    
    OSReport(sLogGameModeSlotData, type, 0, menu_SlotDataOn[i], IveSave[i + 5].has_data, IveSave[i + 5].stage);
    strcpy((char *)menusaveloadfilename, sSaveFileName);
    for (i = 0; i < 4; i++) {
        menu_SlotDataOn[i] = TEA_mcLoadFile0(0, type * 4 + i + 2, i + 5);
        if (menu_SlotDataOn[i] == 1)
            menu_SlotDataOn[i] = IveSave[i + 5].has_data;
        OSReport(sLogSlotData, i, menu_SlotDataOn[i], IveSave[i + 5].has_data, IveSave[i + 5].stage);
    }
}


void menu_sDispMissionDemoSelectMenu(void)
{
    s8 c;
    HSD_JObj *a;
    s32 i;
    HSD_JObj *b;
    s32 unused[2];

    if (menudemoselect == -1)
        return;
    jobjDisp(GetChild(menudemo[0]->models[2], 0, 0, -1, -1, -1));
    jobjDisp(GetChild(menudemo[0]->models[2], 0, 1, -1, -1, -1));
    if (menudemoselect == 1)
        jobjDisp(GetChild(menudemo[0]->models[2], 0, 0, 1, -1, -1));
    if (menudemoselect == 0)
        jobjDisp(GetChild(menudemo[0]->models[2], 0, 1, 1, -1, -1));
    if (menudemoselect == 0)
        c = 255;
    else
        c = 129;
    a = GetChild(menudemo[0]->models[2], 0, i = 0, 0, -1, -1);
    b = GetChild(menudemo[0]->models[2], 0, 0, 0, 0, -1);
    sPutFontRect(GetMenuMsgAdr(menudemoselmsg[i]), a, b, (GXColor){c, c, c, c}, (GXColor){0, 0, 0, 0}, 0, 2);
    if (menudemoselect == 1)
        c = 255;
    else
        c = 129;
    a = GetChild(menudemo[0]->models[2], 0, i = 1, 0, -1, -1);
    b = GetChild(menudemo[0]->models[2], 0, 1, 0, 0, -1);
    sPutFontRect(GetMenuMsgAdr(menudemoselmsg[i]), a, b, (GXColor){c, c, c, c}, (GXColor){0, 0, 0, 0}, 0, 2);
}

extern PadState *sPad3;
extern s32 menuCursor;
extern s32 menuParticles;
extern s32 testnumedit(s32 x, s32 y, s32 value);
extern void sPutString2(char *text, s32 x, s32 y, s32 z, GXColor color, GXColor shadow, s32 alpha, s32 flags);

#pragma readonly_strings on
void testbitsetmenu_zoid(void)
{
    char text[80];
    s32 unused[3];
    s32 k;
    s32 sel;
    s32 i;
    s32 row;
    s32 value;
    s32 y;

    sel = 0;
    row = 0;
    value = 0;
    menuCursor = 0;
    menuParticles = 0;
    OSReport(sLogMenuZoidBattle);
    while (1) {
        sPadAll();
        if (sPad3->pressed_r && sel < 5)
            sel++;
        if (sPad3->pressed_l && sel > 0)
            sel--;
        if (sPad3->pressed_dpad_up)
            row--;
        if (sPad3->pressed_dpad_down)
            row++;
        if (row < 0)
            row = 9;
        if (row > 9)
            row = 0;
        if (sPad3->pressed_b)
            break;
        if (sPad3->pressed_a)
            value = testnumedit(-240, -150, value);
        for (i = 0, k = 0; i < 10; i++, k += 24) {
            y = 150 - k;
            sPutString2(text, -240, y, -450, (GXColor){255, 255, 255, 255}, (GXColor){255, 255, 255, 0}, 0, 2);
        }
        sPutString2("\201\250", -280, 150 - row * 24, -450, (GXColor){255, 255, 255, 255}, (GXColor){0, 255, 255, 55}, 0, 2);
        if (sel != 5)
            sPutString2("R:\216\237\202\326", 160, -150, -450, (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);
        if (sel != 0)
            sPutString2("L:\221O\202\326", -300, -150, -450, (GXColor){255, 255, 255, 255}, (GXColor){0, 0, 0, 0}, 0, 2);
        debugmenudraw();
    }
}
#pragma readonly_strings off


extern f32 menuzoidry;
extern void menu_BattleSet_HumanEntryPersonPartnerExit(void);
extern void menu_sDispBattleHumanEntry(void);
extern void menu_sDispSetButton(void);
extern void SeCancel(void);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 menufncZoidBattle_HumanBattleMenuEntry(void)
{
    s32 unused[10];
    s32 i;
    s16 j;
    s16 zoid1;
    s16 zoid2;

    menucuranm = 1;
    menuCursor = 0;
    menuParticles = 0;
    menumode = 2;
    menuzoidry = -0.7f;
    menuZoidBattleModeSingleTeam = 1;
    IveSave[0].single_team = 1;
    for (i = 0; i < 20; i++)
        menumodeanm[i] = 0;
    for (i = 0; i < 20; i++)
        menufarmanm[i] = 0;
    vsyncN = 0;
    TeaBgm(7);
    menuSetTitle(101);
    TEA_setvsync();
    menufarmmode = 1;
    menufarmcl[2] = 0;
    menufarmsl[2] = 0;
    menufarmst[2] = 0;
    if (menuZoidBattleModeSingleTeam == 1) {
        menufarmmh[2] = 2;
        menufarmmn[2] = 2;
    } else if (menuZoidBattleStage != -1) {
        menufarmmh[2] = 1;
        menufarmmn[2] = 1;
    } else {
        menufarmmh[2] = 2;
        menufarmmn[2] = 2;
    }
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 2;
    menufarmmn[3] = 2;
    menufarmcl[4] = 0;
    menufarmsl[4] = 0;
    menufarmst[4] = 0;
    menufarmmh[4] = 2;
    menufarmmn[4] = 2;
    menufarmcl[5] = 0;
    menufarmsl[5] = 0;
    menufarmst[5] = 0;
    menufarmmh[5] = 8;
    menufarmmn[5] = 2;
    menufarmcl[6] = 0;
    menufarmsl[6] = 0;
    menufarmst[6] = 0;
    menufarmmh[6] = 8;
    menufarmmn[6] = 2;
    menufarmcl[7] = 0;
    menufarmsl[7] = 0;
    menufarmst[7] = 0;
    menufarmmh[7] = 8;
    menufarmmn[7] = 2;
    menufarmcl[8] = 0;
    menufarmsl[8] = 0;
    menufarmst[8] = 0;
    menufarmmh[8] = 8;
    menufarmmn[8] = 2;
    menudispyesnoflag = 0;
    menufarmsl[5] = 0;
    menufarmmn[5] = IveSave[0].person_list_count;
    if (menufarmmn[5] < menufarmmh[5])
        menufarmmh[5] = menufarmmn[5];
    menufarmst[5] = -1;
    menufarmsl[6] = 0;
    menufarmmn[6] = IveSave[0].person_list_count;
    if (menufarmmn[6] < menufarmmh[6])
        menufarmmh[6] = menufarmmn[6];
    menufarmst[6] = -1;
    menufarmmh[5] = 8;
    menufarmmh[6] = 8;
    menufarmmn[5] = IveSave[0].person_list_count;
    menufarmmn[6] = IveSave[0].person_list_count;
    IveSave[4].selected_zoid = IveSave[0].selected_zoid;
    IveSave[4].partner_zoid = IveSave[0].partner_zoid;
    zoid1 = IveSave[0].selected_person;
    zoid2 = IveSave[0].partner_person;
    for (i = 0; i < IveSave[0].person_list_count; i++) {
        if (IveSave[0].selected_person == IveSave[0].person_list[i]) {
            j = i;
            menufarmcl[5] = j;
            menufarmsl[5] = j;
            menufarmst[5] = -1;
            IveSave[0].selected_person_index = j;
            break;
        }
    }
    for (i = 0; i < IveSave[0].person_list_count; i++) {
        if (IveSave[0].partner_person == IveSave[0].person_list[i]) {
            j = i;
            menufarmcl[6] = j;
            menufarmsl[6] = j;
            menufarmst[6] = -1;
            IveSave[0].partner_person_index = j;
            break;
        }
    }
    IveSave[0].selected_zoid = IveSave[0].owned_zoids[0];
    IveSave[0].selected_zoid_slot = 0;
    IveSave[0].selected_person = 0;
    IveSave[0].partner_person = 1;
    IveSave[0].partner_zoid_slot = 1;
    IveSave[0].partner_zoid = IveSave[0].owned_zoids[1];
    if (IveSave[0].selected_zoid_slot == 1) {
        IveSave[0].partner_zoid_slot = 0;
        IveSave[0].partner_zoid = IveSave[0].owned_zoids[0];
    }
    menu_sDispSetButton();
    menu_BattleSet_HumanEntryPersonPartnerExit();
    while (1) {
        sPadAll();
        menu_sDispSetButton();
        if (menumode <= 2)
            menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        if (menumode >= 5)
            menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        if (menumode == 2 && menufarmcl[2] >= 2) {
            menufarmsl[2] = 2;
            menufarmcl[2] = 2;
        }
        menu_BattleSet_HumanEntryPersonPartnerExit();
        menu_sDispBattleHumanEntry();
        if (sPad1->pressed_b != 0) {
            SeCancel();
            if (menumode == 2) {
                if (menufarmcl[2] == 1) {
                    SeRet();
                    zoid2 = IveSave[0].partner_person;
                    menuZoidBattleModeSingleTeam = 0;
                    IveSave[0].partner_person = 57;
                }
                menufarmcl[menumode] = 2;
                continue;
            } else if (menumode <= 4) {
                menumode = 2;
            } else if (menumode == 5) {
                IveSave[0].selected_person = zoid1;
                menumode = 2;
            } else if (menumode == 6) {
                IveSave[0].partner_person = zoid2;
                menumode = 2;
            }
        }
        if (sPad1->pressed_a != 0) {
            switch (menumode) {
            case 2:
                if (menufarmcl[menumode] == 2) {
                    SeRet();
                    menudispyesnoflag = 1;
                    menudispyesnopoint = 1;
                    do {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_END_ENTRY_PROMPT), "");
                        menu_sDispBattleHumanEntry();
                    } while (sPad1->pressed_a == 0);
                    SeRet();
                    menudispyesnoflag = 0;
                    if (menudispyesnopoint == 0)
                        continue;
                    menumode = -1;
                    menufncZoidBattle_BattleMenuReturn();
                    IveSave[0].single_team = menuZoidBattleModeSingleTeam;
                    menuZoidBattleStage = 0;
                    GameMode.win = 1;
                    ttlMenuLoadParts(4);
                    ttlMenuLoadZoid();
                    return 221;
                }
                if (menufarmcl[2] == 1) {
                    SeRet();
                    menumode = 4;
                    menufarmcl[4] = 0;
                    menumode = 6;
                } else if (menufarmcl[2] == 0) {
                    SeRet();
                    menumode = 3;
                    menufarmcl[3] = 0;
                    menumode = 5;
                }
                break;
            case 5:
                SeRet();
                if (IveSave[0].person_list[menufarmcl[5]] != IveSave[0].partner_person) {
                    IveSave[0].selected_person = IveSave[0].person_list[menufarmcl[5]];
                    zoid1 = IveSave[0].selected_person;
                    TEA_VoiceOn(IveSave[0].selected_person, 1);
                }
                menumode = 2;
                break;
            case 6:
                SeRet();
                if (IveSave[0].person_list[menufarmcl[6]] != IveSave[0].selected_person) {
                    IveSave[0].partner_person = IveSave[0].person_list[menufarmcl[6]];
                    zoid2 = IveSave[0].partner_person;
                    TEA_VoiceOn(IveSave[0].partner_person, 1);
                } else {
                    menumode = 2;
                    continue;
                }
                menuZoidBattleModeSingleTeam = 1;
                menumode = 2;
                break;
            }
        }
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0) {
            if (menuZoidBattleModeSingleTeam == 1) {
                if (menumode == 4) {
                    menumode = 3;
                    menufarmsl[2] = 0;
                    menufarmcl[2] = 0;
                }
            } else if (menumode == 2 && menufarmcl[2] == 1) {
                menufarmsl[2] = 0;
                menufarmcl[2] = 0;
            }
            if (menumode == 3 || menumode == 4)
                SeSelectB();
            if (menumode == 7)
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
            if (menumode == 8)
                IveSave[0].partner_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
        } else if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0) {
            if (menumode == 2 && menufarmcl[2] >= 2) {
                menufarmsl[2] = 2;
                menufarmcl[2] = 2;
            }
            if (menuZoidBattleModeSingleTeam == 1 && menumode == 3) {
                menumode = 4;
                menufarmsl[2] = 1;
                menufarmcl[2] = 1;
            }
            if (menumode == 3 || menumode == 4)
                SeSelectB();
            if (menumode == 7)
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
            if (menumode == 8)
                IveSave[0].partner_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
        } else {
            if (sPad1->pressed_dpad_left != 0 || sPad1->pressed_stick_left != 0) {
                if (menumode == 2 && menufarmcl[2] == 2) {
                    menufarmsl[2] = 0;
                    menufarmcl[2] = 0;
                }
                if (menumode == 3 || menumode == 4) {
                    SeSelectB();
                    if (menufarmcl[menumode] != 0) {
                        menufarmsl[menumode] = 0;
                        menufarmcl[menumode] = 0;
                    }
                }
            }
            if (sPad1->pressed_dpad_right != 0 || sPad1->pressed_stick_right != 0) {
                if (menumode == 2 && menufarmcl[2] != 2) {
                    menufarmsl[2] = 2;
                    menufarmcl[2] = 2;
                }
                if (menumode == 3 || menumode == 4) {
                    SeSelectB();
                    if (menufarmcl[menumode] == 0) {
                        menufarmsl[menumode] = 1;
                        menufarmcl[menumode] = 1;
                    }
                }
            }
        }
    }
}
#pragma pop
#pragma readonly_strings off


extern ModelArchive *menu_saveloadp;
extern char *strcat(char *dst, const char *src);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
void menu_sDispSaveLoadDataNo(s16 slot, s16 cursor)
{
    s32 k;
    HSD_JObj *b;
    s16 m;
    s16 idx;
    s32 yr;
    s16 h;
    s16 s;
    HSD_JObj *a;
    char text[88];
    s32 money;

    idx = GameMode.game_type + 6;
    if (GameMode.game_type == GAME_TYPE_MISSION)
        idx = 6;
    else if (GameMode.game_type == GAME_TYPE_BATTLE)
        idx = 7;
    k = 5;
    a = GetChild(menu_saveloadp->models[k], 0, 1, cursor, -1, -1);
    jobjCopyPos(a, GetChild(menu_saveloadp->models[idx], 0, -1, -1, -1, -1));
    jobjDisp(GetChild(menu_saveloadp->models[idx], 0, -1, -1, -1, -1));
    jobjDisp(GetChild(menu_saveloadp->models[idx], 0, 0, -1, -1, -1));
    jobjDisp(GetChild(menu_saveloadp->models[idx], 0, 0, slot, -1, -1));
    if (menu_SlotDataOn[slot] == 1) {
        jobjDispAll(GetChild(menu_saveloadp->models[idx], 0, 1, -1, -1, -1));
        jobjDispAll(GetChild(menu_saveloadp->models[idx], 0, 2, -1, -1, -1));
        jobjDispAll(GetChild(menu_saveloadp->models[idx], 0, 3, -1, -1, -1));
        if (GameMode.game_type == GAME_TYPE_MISSION) {
            yr = IveSave[slot + 5].save_year % 100;
            sprintf(text, sSaveDateFormat, yr, IveSave[slot + 5].save_month + 1, IveSave[slot + 5].save_day);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 2, 0, -1, -1), 4, text, 0);
            h = IveSave[slot + 5].play_time / 3600;
            if (h > 99)
                h = 99;
            m = (IveSave[slot + 5].play_time / 60) % 60;
            if (m > 60)
                m = 60;
            s = (u32)IveSave[slot + 5].play_time % 60;
            if (s > 60)
                s = 60;
            sprintf(text, "%02d", h);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 3, 0, -1, -1), 1, text, 0);
            sprintf(text, "%02d", m);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 3, 1, -1, -1), 1, text, 0);
            sprintf(text, "%02d", s);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 3, 2, -1, -1), 1, text, 0);
            a = GetChild(menu_saveloadp->models[6], 0, 4, -1, -1, -1);
            b = GetChild(menu_saveloadp->models[8], 0, IveSave[slot + 5].country - 1, -1, -1, -1);
            jobjCopyPos(a, b);
            jobjDispAll(b);
            a = GetChild(menu_saveloadp->models[6], 0, 5, -1, -1, -1);
            b = GetChild(menu_saveloadp->models[9], 0, -1, -1, -1, -1);
            jobjCopyPos(a, b);
            sMakeMatrix(b);
            sprintf(text, "%s", (char *)stagename_mis[IveSave[slot + 5].stage]);
            putAscJobjLR(GetChild(menu_saveloadp->models[9], 0, 0, 0, -1, -1), 1, text, 0);
            jobjDisp(GetChild(menu_saveloadp->models[9], 0, 0, 1, 0, -1));
            jobjDisp(GetChild(menu_saveloadp->models[9], 0, 0, -1, -1, -1));
        } else {
            yr = IveSave[slot + 5].save_year % 100;
            sprintf(text, sSaveDateFormat, yr, IveSave[slot + 5].save_month + 1, IveSave[slot + 5].save_day);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 2, 0, -1, -1), 4, text, 0);
            sprintf(text, sBattleNumberFormat, IveSave[slot + 5].stage + 1);
            if ((s32)IveSave[slot + 5].field_166B == 1)
                strcat(text, sFarmLabel);
            else
                strcat(text, "\x83N\x83\x8a\x83" "A");
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 4, -1, -1, -1), 1, text, 0);
            h = IveSave[slot + 5].play_time / 3600;
            if (h > 99)
                h = 99;
            m = (IveSave[slot + 5].play_time / 60) % 60;
            if (m > 60)
                m = 60;
            s = (u32)IveSave[slot + 5].play_time % 60;
            if (s > 60)
                s = 60;
            sprintf(text, "%02d", h);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 3, 0, -1, -1), 1, text, 0);
            sprintf(text, "%02d", m);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 3, 1, -1, -1), 1, text, 0);
            sprintf(text, "%02d", s);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 3, 2, -1, -1), 1, text, 0);
            if ((money = IveSave[slot + 5].money) > 999999)
                money = 999999;
            sprintf(text, "%-6d ", money);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 6, -1, -1, -1), 1, text, 0);
            sprintf(text, "%3d", IveSave[slot + 5].owned_zoid_count);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 5, -1, -1, -1), 1, text, 0);
            sprintf(text, "%s", Tea_persondat[IveSave[slot + 5].selected_person].name);
            putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 8, 0, -1, -1), 1, text, 0);
            if ((s32)(u8)IveSave[slot + 5].single_team == 1) {
                sprintf(text, "%s", Tea_persondat[IveSave[slot + 5].partner_person].name);
                putAscJobjLR(GetChild(menu_saveloadp->models[idx], 0, 8, 1, -1, -1), 1, text, 0);
            }
        }
    } else if (GameMode.game_type == GAME_TYPE_MISSION) {
        putAscJobj(GetChild(menu_saveloadp->models[idx], 0, 6, -1, -1, -1), 1, (char *)sNoDataLabel);
    } else {
        putAscJobj(GetChild(menu_saveloadp->models[idx], 0, 7, -1, -1, -1), 1, (char *)sNoDataLabel);
    }
    if (menuSLPos[0] != cursor) {
        a = GetChild(menu_saveloadp->models[idx], 0, -1, -1, -1, -1);
        b = GetChild(menu_saveloadp->models[12], 0, -1, -1, -1, -1);
        jobjCopyPos(a, b);
        jobjDispAll(b);
    }
}
#pragma pop
#pragma readonly_strings off


extern void SetMenuMsgAdr(s32 message, char *text);
extern s16 flag_AllHavePartsList;
extern s16 flag_AllHavePartsListanm[3];
extern void SeWinon(void);
extern void menuerasewait(s16 animation);
extern void TEA_HotReset(u32 code);
extern void menu_sDispBattleFarmStageDown(s32 mode);
extern void menufncZoidBattle_MapInfo(void);
extern s32 menufncZoidBattle_BattleMenuSet(void);
extern s32 menufncZoidBattle_BattleMenuShop(void);
extern void menuZoidBattleGo(void);
extern void ZoidSetAnim(ZoidState *zoid, s32 anim);
extern void eyeCamPos(void);
extern void VIWaitForRetrace(void);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 menufncZoidBattle_BattleMenu(void)
{
    s32 unused[19];
    s32 i;

    menuCursor = 0;
    menuParticles = 0;
    menumode = 0;
    for (i = 0; i < 20; i++)
        menumodeanm[i] = 0;
    for (i = 0; i < 20; i++) {
        menufarmanm[i] = 2;
        menufarmanmold[i] = 2;
    }
    OSReport(sLogMenuZoidBattle);
    vsyncN = 0;
    TeaBgm(7);
    menuSetTitle(0);
    TEA_setvsync();
    menufarmmode = 0;
    menumodeanm[0] = 0;
    menufarmanm[0] = 0;
    menufarmcl[0] = 0;
    menufarmsl[0] = 0;
    menufarmst[0] = 0;
    menufarmmh[0] = 5;
    menufarmmn[0] = 5;
    menufarmcl[1] = 0;
    menufarmsl[1] = 0;
    menufarmst[1] = 0;
    menufarmmh[1] = 2;
    menufarmmn[1] = 2;
    menufarmcl[2] = 0;
    menufarmsl[2] = 0;
    menufarmst[2] = 0;
    menufarmmh[2] = 2;
    menufarmmn[2] = 2;
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 2;
    menufarmmn[3] = 2;
    menufarmcl[4] = 0;
    menufarmsl[4] = 0;
    menufarmst[4] = 0;
    menufarmmh[4] = 2;
    menufarmmn[4] = 2;
    menufarmcl[5] = 0;
    menufarmsl[5] = 0;
    menufarmst[5] = 0;
    menufarmmh[5] = 2;
    menufarmmn[5] = 2;
    menubackanm[0].state = 1;
    menubackanm[0].cur = 1;
    menubackanm[0].old = 0;
    menu_sDispSaveLoadMenuSet(-1);
    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
    eyeCamPos();
    SetMenuMsgAdr(50, (char *)menudispwinstr);
    OSReport(sLogMenuCamPos, menubackcampos.x, menubackcampos.y, menubackcampos.z);
    for (i = 1; i <= 9; i++)
        menufarmanm[i] = 0;
    memcpy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
    for (i = 0; i < 8; i++) {
        menumodeanm[i] = 1;
        menufarmanm[i] = 0;
    }
    flag_AllHavePartsListanm[1] = 0;
    menu_sDispSetButton();
    menuSetTitle(0);
    menu_TITLE_disp(1);
    while (1) {
        sPadAll();
        menu_sDispSetButton();
        menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        if (menumode == 1) {
            if (menufarmcl[1] == 0)
                SetMenuMsgAdr(49, (char *)menudispwinstr);
            else
                SetMenuMsgAdr(54, (char *)menudispwinstr);
        }
        if (menumode == 0) {
            if (menufarmcl[0] == 4)
                SetMenuMsgAdr(55, (char *)menudispwinstr);
            else
                SetMenuMsgAdr(menufarmcl[0] + 50, (char *)menudispwinstr);
        }
        menu_sDispBattleFarm();
        if (sPad1->pressed_l != 0) {
            SeWinon();
            flag_AllHavePartsList++;
        }
        if (sPad1->pressed_z != 0 || sPad3->pressed_z != 0)
            menufarmanm[0] = 2;
        if (sPad1->pressed_b != 0 || sPad3->pressed_b != 0) {
            if (menumode > 0) {
                menumode--;
            } else {
                SeCancel();
                continue;
            }
            SeCancel();
        }
        if (sPad1->pressed_a != 0 || sPad1->pressed_a != 0) {
            switch (menumode) {
            case 0:
                if (menufarmcl[0] == 4) {
                    SeRet();
                    menudispyesnopoint = 1;
                    menudispyesnoflag = 1;
                    do {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_START_BATTLE_PROMPT), "");
                        menu_sDispBattleFarm();
                    } while (sPad1->pressed_a == 0);
                    SeRet();
                    menudispyesnoflag = 0;
                    if (menudispyesnopoint == 0)
                        continue;
                    sCamNN2 = 2;
                    if (menuZoidBattleModeSingleTeam == 1)
                        sCamNN2 = 2;
                    if (menuZoidBattleModeSingleTeam == 0) {
                        IveSave[0].partner_zoid = -1;
                        IveSave[0].partner_person = -1;
                    }
                    menuZoidBattleGo();
                    menu_TITLE_disp(0);
                    TeaBgm(-1);
                    HSD_VISetBlack(1);
                    sPadAll();
                    VIWaitForRetrace();
                    HSD_VICopyXFB(HSD_RP_SCREEN);
                    HSD_VISetXFBDrawDone();
                    ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                    ttlMenuAllPurge();
                    menuretno = 9999;
                    return 210;
                } else if (menufarmcl[0] == 0) {
                    SeRet();
                    menu_TITLE_disp(0);
                    menuSetTitle(menufarmcl[0] + 2);
                    menufncZoidBattle_BattleMenuSet();
                    menuSetTitle(0);
                    menu_TITLE_disp(1);
                } else if (menufarmcl[0] == 1) {
                    SeRet();
                    menu_TITLE_disp(0);
                    menuSetTitle(menufarmcl[0] + 2);
                    menufncZoidBattle_BattleMenuShop();
                    menuSetTitle(0);
                    menu_TITLE_disp(1);
                } else if (menufarmcl[0] == 2) {
                    SeRet();
                    menu_TITLE_disp(0);
                    menuSetTitle(menufarmcl[0] + 2);
                    menufncZoidBattle_MapInfo();
                    menuSetTitle(0);
                    menu_TITLE_disp(1);
                } else {
                    SeRet();
                    menu_TITLE_disp(0);
                    menuSetTitle(menufarmcl[0] + 2);
                    menu_TITLE_disp(1);
                    menufarmanm[5] = 5;
                    menumodeanm[5] = 1;
                    menu_sDispSaveLoadMenuSet(-3);
                    while (menudispslwindow[0].anim != 2)
                        menu_sDispBattleFarm();
                    menumode = 5;
                    menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                    menu_sDispBattleFarm();
                    while (1) {
                        sPadAll();
                        menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
                        menu_sDispBattleFarm();
                        if (sPad1->pressed_b != 0) {
                            SeCancel();
                            break;
                        }
                        if (sPad1->pressed_a != 0) {
                            SeRet();
                            memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                            if (ttlMemCardChkStartNew() == 0)
                                continue;
                            menu_sDispSaveLoadMenuSet(-2);
                            menu_sDispBattleFarm();
                            IveSave[0].field_166B = 1;
                            if (menufarmcl[menumode] == 0) {
                                ttlMenuBatSaveLoad(1);
                                menuSetTitle(menufarmcl[0] + 2);
                                menu_sDispSetButton();
                                menu_sDispSaveLoadMenuSet(-1);
                                menu_sDispBattleFarm();
                                menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                menu_sDispBattleFarm();
                            }
                            if (menufarmcl[menumode] == 1) {
                                if (ttlMenuBatSaveLoad(0) == 1) {
                                    ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                                    if (menuZoidBattleModeSingleTeam == 1)
                                        ttl_WeaponAllUnMount(IveSave[0].partner_zoid_slot);
                                    memcpy(&IveSave[0], &IveSave[2], sizeof(GameSaveRecord));
                                    ZoidPurge(&Zoid[0]);
                                    ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                                    ZoidSetAnim(&Zoid[0], 103);
                                    jobjAnim(Zoid[0].joint);
                                    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                                    menuZoidBattleModeSingleTeam = IveSave[0].single_team;
                                    if (menuZoidBattleModeSingleTeam == 0) {
                                        IveSave[0].partner_zoid_slot = -1;
                                        IveSave[0].partner_zoid = -1;
                                    } else {
                                        IveSave[0].partner_zoid = IveSave[0].owned_zoids[IveSave[0].partner_zoid_slot];
                                    }
                                }
                                menuSetTitle(menufarmcl[0] + 2);
                                menu_sDispSetButton();
                                menu_sDispSaveLoadMenuSet(-1);
                                menu_sDispBattleFarm();
                                menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                menu_sDispBattleFarm();
                            } else {
                                menuSetTitle(menufarmcl[0] + 2);
                                menu_sDispSetButton();
                                menu_sDispSaveLoadMenuSet(-1);
                                menu_sDispBattleFarm();
                                menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                menu_sDispBattleFarm();
                            }
                            IveSave[0].field_166B = 0;
                            if (menufarmcl[menumode] == 2) {
                                menu_sDispSetButton();
                                menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                menu_sDispBattleFarm();
                                menufncZoid_ConfigMenu();
                            }
                        }
                        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0)
                            menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                        if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0)
                            menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                    }
                    menumode = 0;
                    menu_sDispSaveLoadMenuSet(-2);
                    menu_TITLE_disp(0);
                    menuSetTitle(0);
                    menu_TITLE_disp(1);
                }
                break;
            case 1:
                if (menufarmcl[1] == 0) {
                    SeRet();
                    menuanmend = 0;
                    OSReport(sLogMenuZoidBattleEntryOn);
                    menumode = -1;
                    menuHiddenTitle();
                    menu_TITLE_disp(0);
                    OSReport(sLogMenuZoidBattleEntryOk);
                    menufarmmode = 1;
                    ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                    return 205;
                }
                if (menuZoidBattleModeSingleTeam == 1) {
                    SeCancel();
                    menu_sDispBattleFarmStageDown(1);
                    ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                    ZoidWeaponPurge(&Zoid[0]);
                    ZoidWeaponPurge(&Zoid[0]);
                    ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                    ZoidPurge(&Zoid[0]);
                    memcpy(&IveSave[2], &IveSave[0], sizeof(GameSaveRecord));
                    IveSave[0].selected_person = IveSave[0].partner_person;
                    IveSave[0].partner_person = IveSave[2].selected_person;
                    IveSave[0].selected_zoid = IveSave[0].partner_zoid;
                    IveSave[0].partner_zoid = IveSave[2].selected_zoid;
                    IveSave[0].selected_zoid_slot = IveSave[0].partner_zoid_slot;
                    IveSave[0].partner_zoid_slot = IveSave[2].selected_zoid_slot;
                    ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                    ZoidSetAnim(&Zoid[0], 103);
                    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                    menu_sDispBattleFarmStageDown(0);
                } else {
                    SeRet();
                }
                break;
            case 2:
                if (menufarmcl[1] == 0)
                    menumode = 3;
                else
                    menumode = 4;
                TEA_HotReset(0);
                break;
            }
        }
        if ((sPad1->pressed_dpad_left != 0 || sPad1->pressed_stick_left != 0) && menumode == 0) {
            OSReport(sLogMenuZoidBattleEntry);
            menumode = 1;
            menufarmcl[menumode] = 0;
            menufarmsl[menumode] = 0;
            menufarmst[menumode] = 0;
        }
        if ((sPad1->pressed_dpad_right != 0 || sPad1->pressed_stick_right != 0) && menumode != 0) {
            OSReport(sLogMenuZoidBattleFarm);
            if (menumode > 1) {
                menuerasewait(0);
                menuSetTitle(0);
            }
            menumode = 0;
            menufarmmode = 0;
        }
    }
}
#pragma pop
#pragma readonly_strings off


extern s32 menu_StageUpDownFlag;
extern s16 dlgzoidno;
extern s32 menu_sDispBattleStageDown(s32 mode);
extern void menu_sDispMissionEntry(void);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 menufncZoidMission_MenuEntry(void)
{
    s32 unused[10];
    s32 i;
    s16 j;
    s16 zoid1;
    s16 zoid2;

    menuCursor = 0;
    menuParticles = 0;
    menumode = 3;
    for (i = 0; i < 20; i++)
        menumodeanm[i] = 0;
    for (i = 0; i < 20; i++)
        menufarmanm[i] = 0;
    vsyncN = 0;
    menuSetTitle(1);
    TEA_setvsync();
    menufarmmode = 1;
    menufarmcl[2] = 0;
    menufarmsl[2] = 0;
    menufarmst[2] = 0;
    if (menuZoidBattleModeSingleTeam == 1) {
        menufarmmh[2] = 2;
        menufarmmn[2] = 2;
    } else {
        menufarmmh[2] = 1;
        menufarmmn[2] = 1;
    }
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 2;
    menufarmmn[3] = 2;
    menufarmcl[4] = 0;
    menufarmsl[4] = 0;
    menufarmst[4] = 0;
    menufarmmh[4] = 2;
    menufarmmn[4] = 2;
    menufarmcl[5] = 0;
    menufarmsl[5] = 0;
    menufarmst[5] = 0;
    menufarmmh[5] = 6;
    menufarmmn[5] = 2;
    menufarmcl[6] = 0;
    menufarmsl[6] = 0;
    menufarmst[6] = 0;
    menufarmmh[6] = 6;
    menufarmmn[6] = 2;
    menufarmcl[7] = 0;
    menufarmsl[7] = 0;
    menufarmst[7] = 0;
    menufarmmh[7] = 6;
    menufarmmn[7] = 2;
    menufarmcl[8] = 0;
    menufarmsl[8] = 0;
    menufarmst[8] = 0;
    menufarmmh[8] = 6;
    menufarmmn[8] = 2;
    if (GameMode.country == 1 && GameMode.map == 0) {
        for (i = 0; i < 58; i++) {
        }
    }
    IveSave[0].owned_zoid_count = 0;
    for (i = 0; i < 30; i++) {
        if (IveSave[0].owned_zoids[i] < 0)
            break;
    }
    IveSave[0].owned_zoid_count = i;
    menufarmsl[5] = 0;
    menufarmmn[5] = IveSave[0].person_list_count;
    if (menufarmmn[5] < menufarmmh[5])
        menufarmmh[5] = menufarmmn[5];
    menufarmmn[5] = 3;
    menufarmmh[5] = 3;
    menufarmst[5] = -1;
    menufarmsl[6] = 0;
    menufarmmn[6] = IveSave[0].person_list_count;
    if (menufarmmn[6] < menufarmmh[6])
        menufarmmh[6] = menufarmmn[6];
    menufarmmn[6] = 3;
    menufarmmh[6] = 3;
    menufarmst[6] = -1;
    menufarmsl[7] = IveSave[0].selected_zoid_slot;
    menufarmmn[7] = IveSave[0].owned_zoid_count;
    menufarmmh[7] = 8;
    if (menufarmmn[7] < menufarmmh[7])
        menufarmmh[7] = menufarmmn[7];
    menufarmst[7] = -1;
    menufarmsl[8] = IveSave[0].partner_zoid_slot;
    menufarmmn[8] = IveSave[0].owned_zoid_count;
    menufarmmh[8] = 8;
    if (menufarmmn[8] < menufarmmh[8])
        menufarmmh[8] = menufarmmn[8];
    menufarmst[8] = -1;
    OSReport(sLogZoidNum, IveSave[0].owned_zoid_count);
    menufarmmh[5] = 3;
    menufarmmh[6] = 3;
    menufarmmn[5] = IveSave[0].person_list_count;
    menufarmmn[6] = IveSave[0].person_list_count;
    IveSave[4].selected_zoid = IveSave[0].selected_zoid;
    IveSave[4].partner_zoid = IveSave[0].partner_zoid;
    zoid1 = IveSave[0].selected_person;
    zoid2 = IveSave[0].selected_zoid;
    menuZoidBattleModeSingleTeam = 0;
    menuZoidBattleStage = -2;
    for (i = 0; i < IveSave[0].person_list_count; i++) {
        if (IveSave[0].selected_person == IveSave[0].person_list[i]) {
            j = i;
            menufarmcl[5] = j;
            menufarmsl[5] = j;
            menufarmst[5] = -1;
            IveSave[0].selected_person_index = j;
            break;
        }
    }
    for (i = 0; i < IveSave[0].person_list_count; i++) {
        if (IveSave[0].partner_person == IveSave[0].person_list[i]) {
            j = i;
            menufarmcl[6] = j;
            menufarmsl[6] = j;
            menufarmst[6] = -1;
            IveSave[0].partner_person_index = j;
            break;
        }
    }
    menu_MissionSet_EntryPersonPartnerExit();
    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
    while (1) {
        sPadAll();
        menu_sDispSetButton();
        if (menumode <= 2)
            menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        if (menumode >= 5)
            menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        menu_MissionSet_EntryPersonPartnerExit();
        menu_sDispMissionEntry();
        if (sPad1->pressed_b != 0) {
            SeCancel();
            if (menumode == 2) {
                if (menufarmcl[2] == 1)
                    continue;
            } else if (menumode == 3) {
                menumode = 2;
                menufarmsl[2] = 2;
                menufarmcl[2] = 2;
            } else if (menumode == 5) {
                IveSave[0].selected_person = zoid1;
                menumode = 3;
            } else if (menumode == 7) {
                IveSave[0].selected_zoid = zoid2;
                menumode = 3;
            }
            continue;
        }
        if (sPad1->pressed_a != 0) {
            switch (menumode) {
            case 2:
                if (menufarmcl[menumode] == 2) {
                    SeRet();
                    menumode = -1;
                    menufncZoidBattle_BattleMenuReturn();
                    if (menuZoidBattleStage == -1) {
                        menuZoidBattleStage = 0;
                        GameMode.win = 1;
                    }
                    return 104;
                }
                if (menufarmcl[2] == 0) {
                    SeRet();
                    menumode = 3;
                    if (menuZoidBattleStage == -1) {
                        menufarmcl[3] = 0;
                        menumode = 5;
                    } else {
                        menufarmcl[3] = 1;
                        IveSave[0].previous_zoid_slot = IveSave[0].selected_zoid_slot;
                        menumode = 7;
                    }
                }
                break;
            case 3:
                SeRet();
                if (menufarmcl[3] == 0)
                    menumode = 5;
                if (menufarmcl[3] == 1)
                    menumode = 7;
                break;
            case 5:
                SeRet();
                zoid1 = IveSave[0].selected_person;
                menumode = 3;
                TEA_VoiceOn(IveSave[0].selected_person, 1);
                menumode = 3;
                break;
            case 7:
                SeRet();
                menumode = 2;
                if (zoid2 == IveSave[0].selected_zoid)
                    continue;
                menumode = 3;
                menu_StageUpDownFlag = 0;
                while (menu_sDispBattleStageDown(1) == 0)
                    menu_sDispMissionEntry();
                ttl_WeaponAllUnMount(IveSave[0].previous_zoid_slot);
                ZoidWeaponPurge(&Zoid[0]);
                ZoidPurge(&Zoid[0]);
                IveSave[0].selected_zoid_slot = menufarmcl[7];
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
                ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                ZoidSetAnim(&Zoid[0], 103);
                ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                menu_StageUpDownFlag = 0;
                while (menu_sDispBattleStageDown(0) == 0)
                    menu_sDispMissionEntry();
                zoid2 = dlgzoidno = IveSave[0].selected_zoid;
                menumode = 3;
                break;
            }
        }
        if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0) {
            if (menuZoidBattleModeSingleTeam == 1) {
                if (menumode == 4) {
                    menumode = 3;
                    menufarmsl[2] = 0;
                    menufarmcl[2] = 0;
                }
            } else if (menumode == 2 && menufarmcl[2] == 1) {
                menufarmsl[2] = 0;
                menufarmcl[2] = 0;
            }
            if (menumode == 3 || menumode == 4)
                SeSelectB();
            if (menumode == 5)
                IveSave[0].selected_person = IveSave[0].person_list[menufarmcl[menumode]];
            if (menumode == 7)
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
        } else if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0) {
            if (menumode == 2 && menufarmcl[2] >= 2) {
                menufarmsl[2] = 2;
                menufarmcl[2] = 2;
            }
            if (menuZoidBattleModeSingleTeam == 1 && menumode == 3) {
                menumode = 4;
                menufarmsl[2] = 1;
                menufarmcl[2] = 1;
            }
            if (menumode == 3 || menumode == 4)
                SeSelectB();
            if (menumode == 5) {
                IveSave[0].selected_person = IveSave[0].person_list[menufarmcl[menumode]];
                OSReport(sLogPersonPos, IveSave[0].selected_person, menufarmcl[menumode]);
            }
            if (menumode == 7)
                IveSave[0].selected_zoid = IveSave[0].owned_zoids[menufarmcl[menumode]];
        } else {
            if (sPad1->pressed_dpad_left != 0 || sPad1->pressed_stick_left != 0) {
                if (menumode == 2 && menufarmcl[2] == 2)
                    menumode = 3;
                if (menumode == 3 || menumode == 4) {
                    SeSelectB();
                    if (menufarmcl[menumode] != 0) {
                        menufarmsl[menumode] = 0;
                        menufarmcl[menumode] = 0;
                    }
                }
            }
            if (sPad1->pressed_dpad_right != 0 || sPad1->pressed_stick_right != 0) {
                if (menumode == 2 && menufarmcl[2] != 2) {
                    menufarmsl[2] = 2;
                    menufarmcl[2] = 2;
                }
                if (menumode == 3 || menumode == 4) {
                    SeSelectB();
                    if (menufarmcl[menumode] == 0) {
                        menufarmsl[menumode] = 1;
                        menufarmcl[menumode] = 1;
                    } else if (menufarmcl[menumode] == 1) {
                        menumode = 2;
                        menufarmsl[2] = 2;
                        menufarmcl[2] = 2;
                    }
                }
            }
        }
    }
}
#pragma pop
#pragma readonly_strings off

extern s64 gametimenow;
extern void ttlMenuLoadSaveLoad(void);
extern void ttlMenuPurgeSaveLoad(void);
extern void menu_sDispSaveLoad(void);
extern void menu_sDispStartYesNo(void);
extern void menuYesNoSetStr(const char *first, const char *second);
extern s32 TEA_mcMsgYesNoEx(s32 slot, s16 message);
extern void SetMenuMsgAdr(s32 message, char *text);
extern s16 menusaveloadmode;
extern s32 menusaveloadDataSelect;
extern SaveLoadWindow menusaveloadDatamainanm;
extern SaveLoadWindow menusaveloadDataNoanm;
extern void SeCancel(void);

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 ttlMenuBatSaveLoad(s32 mode)
{
    s32 ret;
    s16 kind;
    s32 msg;
    s32 i;
    s16 m;

    ret = 0;
    OSReport("save load icon\n");
    MemCardKeepBlock = 10;
    ttlMenuLoadSaveLoad();
    menu_SlotOn = TEA_mcChkSlot(0);
    if (GameMode.game_type == GAME_TYPE_MISSION) {
        if (mode != 0)
            m = 0;
        else
            m = 1;
    } else if (mode != 0) {
        m = 2;
    } else {
        m = 3;
    }
    menusaveloadmode = m;
    menuSetTitle(m);
    menuSetTitleButton(10);
    if (mode == 1)
        msg = 0;
    else
        msg = 1;
    menusaveloadslot = 0;
    menu_SlotOn = TEA_mcChkSlot(0);
    OSReport(sLogSlotACheck);
    menusaveloadslot = 0;
    menuSLPos[0] = 0;
    menuSLPos[1] = 0;
    menuSLPos[2] = 0;
    menuSLPos[3] = 4;
    menuSLPos[4] = 4;
    menusaveloadDataSelect = 1;
    menusaveloadDatamainanm.anim = 0;
    menusaveloadDatamainanm.active = 1;
    menusaveloadDataNoanm.anim = 1;
    menusaveloadDataNoanm.active = 1;
    ttlMenuSaveDataChk();
    SetMenuMsgAdr(msg + 95, (char *)menudispwinstr);
    strcpy((char *)menusaveloadfilename, sSaveFileName);
    flag_saveok = 0;
    while (1) {
        sPadAll();
        menu_SlotOn = TEA_mcChkSlot(0);
        if (menu_SlotOn == 0) {
            ttlMenuPurgeSaveLoad();
            return 0;
        }
        menuSLPos[0] = (u16)TEA_menufnc12p(&menuSLPos[1], &menuSLPos[2], menuSLPos[3], menuSLPos[4]);
        menu_sDispSaveLoad();
        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0) {
            SeRet();
            if (GameMode.game_type == GAME_TYPE_MISSION)
                kind = 0;
            else
                kind = 1;
            strcpy((char *)menusaveloadfilename, sSaveFileName);
            if (mode == 1) {
                OSReport(sLogSaveMinus1);
                clrYesNoMsg();
                menudispyesnoflag = 1;
                menudispyesnopoint = 1;
                while (1) {
                    sPadAll();
                    menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_SAVE_PROMPT), "");
                    menu_sDispSaveLoad();
                    if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0)
                        break;
                    if (TEA_mcChkSlot(0) == 0) {
                        menuYesNoSetStr("", "");
                        menudispyesnoflag = 0;
                        ttlMenuPurgeSaveLoad();
                        TEA_mcUnMount(menusaveloadslot);
                        return 0;
                    }
                }
                OSReport(sLogSaveMinus2);
                clrYesNoMsg();
                menudispyesnoflag = 0;
                if (menudispyesnopoint == 0)
                    continue;
                if (menu_SlotDataOn[menuSLPos[0]] == 1) {
                    clrYesNoMsg();
                    menudispyesnoflag = 1;
                    menudispyesnopoint = 1;
                    while (1) {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_OVERWRITE_PROMPT), "");
                        menu_sDispSaveLoad();
                        if (TEA_mcChkSlot(0) == 0) {
                            menuYesNoSetStr("", "");
                            menudispyesnoflag = 0;
                            ttlMenuPurgeSaveLoad();
                            return 0;
                        }
                        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0)
                            break;
                    }
                    menudispyesnoflag = 0;
                    menu_sDispStartYesNo();
                    clrYesNoMsg();
                    if (menudispyesnopoint == 0)
                        continue;
                }
                memcpy(&IveSaveFlag, &IveSaveFlagBak, sizeof(GameSaveRecord));
                TEA_mcSaveFile0(0, 1, -1);
                IveSave[0].has_data = 1;
                clrYesNoMsg();
                menudispyesnoflag = 1;
                menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_SAVING), sNowSaveLabel);
                menu_sDispStartYesNo();
                IveSave[0].has_data = 1;
                gametimenow = OSGetTime() / (__OSBusClock / 4) - gametimestart;
                IveSave[0].play_time = gametimenow;
                if (TEA_mcSaveFile0(menusaveloadslot, menuSLPos[0] + kind * 4 + 2, 0) != 0) {
                    memcpy(&IveSave[menuSLPos[0] + 5], &IveSave[0], sizeof(GameSaveRecord));
                    ttlMenuSaveDataSetFileName(-1, 0);
                    TEA_mcSaveFile0(menusaveloadslot, 1, -1);
                    ttlMenuSaveDataChk();
                    menudispyesnopoint = 1;
                    clrYesNoMsg();
                    menudispyesnoflag = 1;
                    while (1) {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_SAVE_DONE), sNowSaveLabel);
                        menu_sDispStartYesNo();
                        if (TEA_mcChkSlot(0) == 0) {
                            menuYesNoSetStr("", "");
                            flag_saveok = 1;
                            ret = 1;
                            break;
                        }
                        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0) {
                            SeRet();
                            break;
                        }
                    }
                    menudispyesnoflag = 0;
                    menuYesNoSetStr("", "");
                } else {
                    menudispyesnopoint = 1;
                    clrYesNoMsg();
                    menudispyesnoflag = 1;
                    while (1) {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_SAVE_FAILED), sNowSaveLabel);
                        menu_sDispStartYesNo();
                        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0)
                            break;
                    }
                    SeRet();
                    menudispyesnoflag = 0;
                    clrYesNoMsg();
                }
                menudispyesnoflag = 0;
                menu_sDispStartYesNo();
                clrYesNoMsg();
            } else {
                if (menu_SlotDataOn[menuSLPos[0]] == 0)
                    continue;
                clrYesNoMsg();
                menudispyesnoflag = 1;
                menudispyesnopoint = 1;
                while (1) {
                    sPadAll();
                    menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_LOAD_PROMPT), "");
                    menu_sDispSaveLoad();
                    if (TEA_mcChkSlot(0) == 0) {
                        ret = 0;
                        break;
                    }
                    if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0)
                        break;
                }
                menudispyesnoflag = 0;
                clrYesNoMsg();
                if (menudispyesnopoint == 0)
                    continue;
                OSReport(sLogMemFormatReadSt);
                if (TEA_mcLoadFile0(menusaveloadslot, menuSLPos[0] + kind * 4 + 2, 2) != 0) {
                    gametimestart = OSGetTime() / (__OSBusClock / 4);
                    OSReport(sLogMemLoadEnd, IveSave[2].stage, IveSave[2].map_no, (s8)IveSave[2].single_team, IveSave[2].selected_zoid, IveSave[2].selected_zoid_slot);
                    GameMode.map = IveSave[2].stage;
                    menuZoidBattleStage = IveSave[2].stage;
                    GameMode.map_no = IveSave[2].map_no;
                    menuZoidBattleModeSingleTeam = IveSave[2].single_team;
                    if (menuZoidBattleModeSingleTeam == 0) {
                        IveSave[2].partner_zoid_slot = 0;
                        if (IveSave[2].selected_zoid_slot == 0)
                            IveSave[2].partner_zoid_slot = 1;
                        IveSave[2].partner_zoid = IveSave[2].owned_zoids[IveSave[2].partner_zoid_slot];
                    }
                    GameMode.win = 1;
                    gametimestart = OSGetTime() / (__OSBusClock / 4) - (u32)IveSave[2].play_time;
                    gametimenow = OSGetTime() / (__OSBusClock / 4) - gametimestart;
                    IveSave[2].play_time = gametimenow;
                    menudispyesnopoint = 1;
                    clrYesNoMsg();
                    menudispyesnoflag = 1;
                    while (1) {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_LOAD_DONE), sOutFileLabel);
                        menu_sDispStartYesNo();
                        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0)
                            break;
                    }
                    SeRet();
                    menudispyesnoflag = 0;
                    clrYesNoMsg();
                    for (i = 0; i < 60; i++) {
                        sPadAll();
                        HSD_StartRender(0);
                        HSD_EndRender();
                        debugmenudraw();
                        vsyncN++;
                    }
                    if (GameMode.game_type != GAME_TYPE_MISSION)
                        clearFlagThink(2);
                    ret = 1;
                } else {
                    ret = 0;
                }
                break;
            }
        }
        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0) {
            *(u8 *)menudispwinstr = 0;
            SeCancel();
            if (mode == 1) {
                if (TEA_mcMsgYesNoEx(0, MENU_MSG_QUIT_SAVE_MENU) != 0) {
                    flag_saveok = 1;
                    break;
                }
                if (TEA_mcChkSlot(0) == 0)
                    break;
            } else {
                if (TEA_mcMsgYesNoEx(0, MENU_MSG_QUIT_LOAD_MENU) != 0 || TEA_mcChkSlot(0) == 0)
                    break;
            }
        }
    }
    menuYesNoSetStr("", "");
    menusaveloadDataNoanm.anim = 2;
    menusaveloadDataNoanm.active = 1;
    menusaveloadDatamainanm.anim = 2;
    menusaveloadDatamainanm.active = 1;
    menusaveloadDataSelect = 0;
    TEA_mcUnMount(menusaveloadslot);
    menudispyesnoflag = 0;
    if (mode != 0)
        OSReport(sLogMemCardSaveTrueEnd, IveSave[0].selected_person, Tea_persondat[IveSave[0].selected_person].name, IveSave[0].selected_zoid, Tea_zoiddat[IveSave[0].selected_zoid].name);
    else
        OSReport(sLogMemCardLoadTrueEnd, IveSave[2].selected_person, Tea_persondat[IveSave[2].selected_person].name, IveSave[2].selected_zoid, Tea_zoiddat[IveSave[2].selected_zoid].name);
    menudispyesnoflag = 0;
    ttlMenuPurgeSaveLoad();
    MemCardKeepBlock = 10;
    return ret;
}
#pragma pop
#pragma readonly_strings off

extern u8 menumodeanm[20];
extern u8 menufarmjfl[20];
extern s32 getEndF1(HSD_JObj *joint);

void menu_sDispMisFarmModeButton(void)
{
    s32 j;
    s16 i;
    s32 k;
    u8 a;
    s16 n;
    HSD_JObj *q;
    u8 tbl[6] = { 0, 1, 4, 1, 2, 3 };
    s32 unused2[1];
    HSD_JObj *p;

    n = 9;
    if (menuZoidBattleModeSingleTeam == 0)
        n = 9;
    for (i = 0; i < 20; i++)
        menufarmjfl[i] = 0;
    for (k = 1; k <= n; k++) {
        j = menufarmjno[k];
        (void)menumodeanm[1];
        if (j != -1) {
            menufarmjfl[j] = 1;
            if (menufarmanm[k] != menufarmanmold[k]) {
                menumodeanm[k] = 1;
                menufarmanmold[k] = menufarmanm[k];
            }
            if (menumodeanm[k] == 3 && menufarmanm[k] == 0)
                menufarmanm[k] = 1;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 1)
                menumodeanm[k] = 1;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 3)
                menumodeanm[k] = 3;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 4)
                menumodeanm[k] = 4;
            if (menumodeanm[k] == 3 && menufarmanm[k] == 5)
                menumodeanm[k] = 5;
            if (menumodeanm[k] == 1) {
                menumodeanm[k] = 2;
                if (menufarmano[k] == 2)
                    sSetAnim1(menu1p, j, GetChild(menu1p->models[j], 0, 1, -1, -1, -1), tbl[menufarmanm[k]]);
                if (menufarmano[k] != 1)
                    sSetAnim1(menu1p, j, GetChild(menu1p->models[j], 0, menufarmano[k], -1, -1, -1), tbl[menufarmanm[k]]);
            }
        }
    }
    for (i = 0; i < 20; i++) {
        if (menufarmjfl[i] == 1)
            jobjAnim(menu1p->models[i]);
    }
    for (k = 1; k <= 9; k++) {
        if (menufarmano[k] == 1)
            continue;
        (void)menufarmanm[k];
        j = menufarmjno[k];
        if (j == -1)
            continue;
        if (menumodeanm[k] == 2) {
            if (getEndF1(GetChild(menu1p->models[j], 0, menufarmano[k], -1, -1, -1)) != 0) {
                menumodeanm[k] = 3;
                menuanmend = 1;
            }
        }
        a = menufarmano[k];
        if (a == 2) {
            p = GetChild(menu1p->models[j], 0, 2, -1, -1, -1);
            q = GetChild(menu1p->models[j], 0, 1, -1, -1, -1);
            jobjCopyPos(p, q);
            jobjDispAll(q);
        } else if (a != 6) {
            jobjDispAll(GetChild(menu1p->models[j], 0, a, -1, -1, -1));
        }
    }
}


extern void ttlMenuLoadZoidBanner(void);
extern void ttlMenuLoadPersonBanner(void);
extern void menufncZoidMission_MapInfo(void);
extern s32 menu_sDispBattleStageDown(s32 mode);
extern s32 menu_StageUpDownFlag;

#pragma readonly_strings on
#pragma push
#pragma dont_inline on
s32 menufncMission_Menu(void)
{
    s16 bgm;
    s32 unused[12];
    s32 i;
    s32 msg;
    s32 r;

    bgm = GameMode.country + 22;
    OSGetTime();
    menuCursor = 0;
    menuParticles = 0;
    menumode = 0;
    for (i = 0; i < 20; i++)
        menumodeanm[i] = 0;
    for (i = 0; i < 20; i++) {
        menufarmanm[i] = 2;
        menufarmanmold[i] = 2;
    }
    OSReport(sLogMenuMission);
    ZoidPurge(&Zoid[0]);
    TeaBgm(bgm);
    debug11();
    vsyncN = 0;
    GameMode.map_no = menu_MisMapData[(GameMode.map)].map;
    GameMode.map = IveSave[0].stage;
    IveSave[0].field_166E = IveSave[0].stage;
    GameMode.map_no = menu_MisMapData[IveSave[0].stage].map;
    menuZoidBattleModeSingleTeam = 0;
    IveSave[0].owned_zoid_count = 0;
    for (i = 0; i < 30; i++) {
        if (IveSave[0].owned_zoids[i] < 0)
            break;
    }
    IveSave[0].owned_zoid_count = i;
    menuSetTitle(0);
    TEA_setvsync();
    menufarmmode = 0;
    menumodeanm[0] = 0;
    menufarmanm[0] = 0;
    menufarmcl[0] = 1;
    menufarmsl[0] = 1;
    menufarmst[0] = 0;
    menufarmmh[0] = 5;
    menufarmmn[0] = 5;
    menufarmcl[1] = 0;
    menufarmsl[1] = 0;
    menufarmst[1] = 0;
    menufarmmh[1] = 1;
    menufarmmn[1] = 1;
    menufarmcl[2] = 0;
    menufarmsl[2] = 0;
    menufarmst[2] = 0;
    menufarmmh[2] = 2;
    menufarmmn[2] = 2;
    menufarmcl[3] = 0;
    menufarmsl[3] = 0;
    menufarmst[3] = 0;
    menufarmmh[3] = 2;
    menufarmmn[3] = 2;
    menufarmcl[4] = 0;
    menufarmsl[4] = 0;
    menufarmst[4] = 0;
    menufarmmh[4] = 2;
    menufarmmn[4] = 2;
    menubackanm[0].state = 1;
    menubackanm[0].cur = 1;
    menubackanm[0].old = 0;
    ZoidPurge(&Zoid[0]);
    IveSave[0].selected_zoid = IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot];
    ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
    ZoidSetAnim(&Zoid[0], 103);
    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
    OSReport(sLogNow, IveSave[0].selected_zoid, IveSave[0].owned_zoids[IveSave[0].selected_zoid_slot], IveSave[0].selected_zoid_slot);
    OSReport(sLogMenuCamPos, menubackcampos.x, menubackcampos.y, menubackcampos.z);
    for (i = 1; i <= 9; i++)
        menufarmanm[i] = 0;
    memcopy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
    for (i = 0; i < 8; i++) {
        menumodeanm[i] = 1;
        menufarmanm[i] = 0;
    }
    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
    OSReport(sLogMissionStartDisp00);
    menu_sDispSetButton();
    OSReport(sLogMissionStartDisp01);
    menuSetTitle(0);
    OSReport(sLogMissionStartDisp02);
    menu_TITLE_dispMis(1);
    OSReport(sLogMissionStartDisp03);
    menu_sDispMisFarm();
    OSReport(sLogMissionStartDisp04);
    while (1) {
        sPadAll();
        menu_sDispSetButton();
        menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
        if ((sPad1->pressed_up != 0 || sPad2->pressed_up != 0) && menumode == 0 && menufarmcl[0] == 0) {
            menufarmsl[0] = 1;
            menufarmcl[0] = 1;
        }
        if (menumode == 0) {
            msg = 0;
            if (menufarmcl[0] == 1)
                msg = 50;
            if (menufarmcl[0] == 2)
                msg = 52;
            if (menufarmcl[0] == 3)
                msg = 53;
            if (menufarmcl[0] == 4)
                msg = 55;
            strcpy((char *)menudispwinstr, GetMenuMsgAdr(msg));
        }
        if (menumode == 1) {
            msg = 0;
            if (menufarmcl[1] == 0)
                msg = 49;
            strcpy((char *)menudispwinstr, GetMenuMsgAdr(msg));
        }
        menu_sDispMisFarm();
        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0) {
            if (menumode > 0) {
                menumode--;
            } else {
                SeCancel();
                continue;
            }
            SeCancel();
        }
        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0) {
            switch (menumode) {
            case 0:
                if (menufarmcl[0] == 4) {
                    SeRet();
                    menudispyesnopoint = 1;
                    menudispyesnoflag = 1;
                    do {
                        sPadAll();
                        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_START_BATTLE_PROMPT), "");
                        menu_sDispMisFarm();
                    } while (sPad1->pressed_a == 0);
                    SeRet();
                    menudispyesnoflag = 0;
                    if (menudispyesnopoint == 0)
                        continue;
                    if (menuZoidBattleModeSingleTeam == 1)
                        sCamNN2 = 2;
                    else
                        sCamNN2 = 1;
                    GameMode.map = IveSave[0].stage;
                    IveSave[0].field_166E = IveSave[0].stage;
                    GameMode.map_no = menu_MisMapData[IveSave[0].stage].map;
                    menuZoidBattleGo();
                    GameMode.map_no = menu_MisMapData[(GameMode.map)].map;
                    TeaBgm(-1);
                    menu_TITLE_dispMis(0);
                    HSD_VISetBlack(1);
                    sPadAll();
                    VIWaitForRetrace();
                    HSD_VICopyXFB(HSD_RP_SCREEN);
                    HSD_VISetXFBDrawDone();
                    memcopy(&IveSave[4], &IveSave[0], sizeof(GameSaveRecord));
                    ttlMenuAllPurge();
                    HSD_VIWaitEFBFlush();
                    menuretno = 9999;
                    IveSave[4].stage = IveSave[0].stage;
                    IveSave[4].field_166E = IveSave[0].stage;
                    IveSave[0].map_no = menu_MisMapData[IveSave[0].stage].map;
                    IveSave[4].map_no = menu_MisMapData[IveSave[0].stage].map;
                    GameMode.map = IveSave[0].stage;
                    OSGetTime();
                    rdMapInfo(1, GameMode.map);
                    HSD_VIWaitEFBFlush();
                    HSD_VIWaitEFBFlush();
                    return 9999;
                } else if (menufarmcl[0] == 1) {
                    SeRet();
                    menu_TITLE_dispMis(0);
                    menuSetTitle(menufarmcl[0] + 1);
                    menufncZoidBattle_BattleMenuSet();
                    menuSetTitle(0);
                    menu_TITLE_dispMis(1);
                } else if (menufarmcl[0] == 2) {
                    SeRet();
                    menu_TITLE_dispMis(0);
                    menuSetTitle(menufarmcl[0] + 2);
                    menufncZoidMission_MapInfo();
                    menuSetTitle(0);
                    menu_TITLE_dispMis(1);
                } else {
                    SeRet();
                    menu_TITLE_dispMis(0);
                    menuSetTitle(menufarmcl[0] + 2);
                    menu_TITLE_dispMis(1);
                    menufarmanm[5] = 5;
                    menumodeanm[5] = 1;
                    menu_sDispSaveLoadMenuSet(-3);
                    while (menudispslwindow[0].anim != 2)
                        menu_sDispMisFarm();
                    menumode = 5;
                    menufarmst[menumode] = 0;
                    menufarmsl[menumode] = 0;
                    menufarmcl[menumode] = 0;
                    menufarmmh[menumode] = 2;
                    menufarmmn[menumode] = 2;
                    menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                    menu_sDispMisFarm();
                    while (1) {
                        sPadAll();
                        menufarmcl[menumode] = TEA_menufnc(&menufarmsl[menumode], &menufarmst[menumode], menufarmmn[menumode], menufarmmh[menumode]);
                        menu_sDispMisFarm();
                        if (sPad1->pressed_b != 0 || sPad2->pressed_b != 0) {
                            SeCancel();
                            break;
                        }
                        if (sPad1->pressed_a != 0 || sPad2->pressed_a != 0) {
                            SeRet();
                            memcpy(&IveSaveFlagBak, &IveSaveFlag, sizeof(GameSaveRecord));
                            if (ttlMemCardChkStartNew() == 0)
                                continue;
                            menu_sDispSaveLoadMenuSet(-2);
                            menu_sDispMisFarm();
                            IveSave[0].field_166B = 1;
                            if (menufarmcl[menumode] == 0) {
                                r = ttlMenuBatSaveLoad(1);
                                MissionLoadInitData();
                                if (r != 0)
                                    OSReport(sLogManZoidStage, Tea_persondat[IveSave[0].selected_person].name, Tea_zoiddat[IveSave[0].selected_zoid].name, GameMode.map, IveSave[0].stage);
                                menuSetTitle(menufarmcl[0] + 2);
                                menu_sDispSetButton();
                                menu_sDispSaveLoadMenuSet(-1);
                                menu_sDispMisFarm();
                                menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                menu_sDispMisFarm();
                            }
                            if (menufarmcl[menumode] == 1) {
                                r = ttlMenuBatSaveLoad(0);
                                MissionLoadInitData();
                                if (r == 1) {
                                    ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                                    ZoidPurge(&Zoid[0]);
                                    memcopy(&IveSave[0], &IveSave[2], sizeof(GameSaveRecord));
                                    GameMode.map = IveSave[0].stage;
                                    IveSave[0].field_166E = GameMode.map;
                                    GameMode.map_no = menu_MisMapData[IveSave[0].stage].map;
                                    IveSave[4].stage = GameMode.map;
                                    IveSave[4].field_166E = GameMode.map;
                                    IveSave[0].win = 0;
                                    GameMode.country = IveSave[0].country;
                                    ttlMenuAllPurgeMission();
                                    TeaBgm(GameMode.country + 22);
                                    HSD_VIWaitEFBFlush();
                                    GameZoid[1].type = IveSave[0].partner_zoid;
                                    IveSave[0].partner_zoid = -1;
                                    IveSave[0].partner_person = -1;
                                    ttlMenuLoadBack(6);
                                    ttlMenuLoadZoidBanner();
                                    ttlMenuLoadPersonBanner();
                                    ttlMenuLoadZoid();
                                    OSReport(sLogManZoidStage, Tea_persondat[IveSave[0].selected_person].name, Tea_zoiddat[IveSave[0].selected_zoid].name, GameMode.map, IveSave[0].stage);
                                    ZoidInitC(&Zoid[0], IveSave[0].selected_zoid, (s8)IveSave[0].zoid_colors[IveSave[0].selected_zoid_slot]);
                                    ZoidSetAnim(&Zoid[0], 103);
                                    ttl_WeaponAllMount(IveSave[0].selected_zoid_slot);
                                    menu_StageUpDownFlag = 0;
                                    menu_sDispBattleStageDown(1);
                                    rdMapInfo(1, GameMode.map);
                                    menuSetTitle(menufarmcl[0] + 2);
                                    menu_sDispSetButton();
                                    menu_sDispSaveLoadMenuSet(-1);
                                    menu_sDispMisFarm();
                                    menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                    menu_sDispMisFarm();
                                    menu_StageUpDownFlag = 0;
                                    while (menu_sDispBattleStageDown(0) == 0)
                                        menu_sDispMisFarm();
                                } else {
                                    menuSetTitle(menufarmcl[0] + 2);
                                    menu_sDispSetButton();
                                    menu_sDispSaveLoadMenuSet(-1);
                                    menu_sDispMisFarm();
                                    menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                    menu_sDispMisFarm();
                                }
                            }
                            IveSave[0].field_166B = 0;
                            if (menufarmcl[menumode] == 2) {
                                menu_sDispSetButton();
                                TeaBgm(-1);
                                menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                                menu_sDispMisFarm();
                                menufncZoid_ConfigMenu();
                                {
                                    s16 b2;
                                    b2 = bgm;
                                    TeaBgm(b2);
                                }
                            }
                        }
                        if (sPad1->pressed_up != 0 || sPad2->pressed_up != 0)
                            menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                        if (sPad1->pressed_down != 0 || sPad2->pressed_down != 0)
                            menu_sDispSaveLoadMenuSet(menufarmcl[menumode]);
                    }
                    menumode = 0;
                    menu_sDispSaveLoadMenuSet(-2);
                    menu_TITLE_dispMis(0);
                    menuSetTitle(0);
                    menu_TITLE_dispMis(1);
                }
                break;
            case 1:
                if (menufarmcl[1] != 0)
                    continue;
                SeRet();
                menuanmend = 0;
                OSReport(sLogMenuZoidBattleEntryOn);
                menumode = -1;
                menuHiddenTitle();
                menu_TITLE_dispMis(0);
                OSReport(sLogMenuZoidBattleEntryOk);
                menufarmmode = 1;
                ttl_WeaponAllUnMount(IveSave[0].selected_zoid_slot);
                HSD_VIWaitEFBFlush();
                HSD_VIWaitEFBFlush();
                return 105;
            case 2:
                if (menufarmcl[1] == 0)
                    menumode = 3;
                else
                    menumode = 4;
                TEA_HotReset(0);
                break;
            }
        }
        if ((sPad1->pressed_up != 0 || sPad2->pressed_up != 0) && menumode == 0 && menufarmcl[0] == 0) {
            menufarmsl[0] = 1;
            menufarmcl[0] = 1;
        }
        if ((sPad1->left != 0 || sPad2->left != 0) && menumode == 0) {
            OSReport(sLogMenuZoidBattleEntry);
            menumode = 1;
            menufarmcl[menumode] = 0;
            menufarmsl[menumode] = 0;
            menufarmst[menumode] = 0;
        }
        if ((sPad1->right != 0 || sPad2->right != 0) && menumode != 0) {
            OSReport(sLogMenuZoidBattleFarm);
            if (menumode > 1) {
                menuerasewait(0);
                menuSetTitle(0);
            }
            menumode = 0;
            menufarmmode = 0;
        }
    }
}
#pragma pop
#pragma readonly_strings off
#pragma push
#pragma dont_inline on
extern s32 enemyChara[2];
extern s32 enemyZoid[2];
extern void GXInvalidateVtxCache(void), GXInvalidateTexAll(void);

void menu_sDispBattleNextYokok(char *info, ModelArchive *picture, ModelArchive *background)
{
    s32 unused[2];
    HSD_JObj *root;
    s32 chara;
    GXColor color = {255, 255, 255, 255};
    GXColor shadow = {0, 0, 0, 0};
    HSD_JObj *pos;
    HSD_JObj *jobj;

    GXInvalidateVtxCache();
    GXInvalidateTexAll();
    root = menu1p->models[25];
    if (root == 0)
        return;
    jobjAnim(root);
    sMakeMatrix(root);
    HSD_SetZSortMode(1, 1);
    HSD_SetZSortMode(1, 1);
    HSD_SetZSortMode(0, 0);
    if (HSD_CObjSetCurrent(menu1p->camera) != 0) {
        HSD_LObjSetCurrentAll(menu1p->lights);
        HSD_LObjSetupInit(menu1p->camera);
        GXSetCullMode(0);
        if (background != 0)
            jobjDispAll(background->models[0]);
        jobjDisp(GetChild(root, 0, 0, -1, -1, -1));
        putAscJobj(GetChild(root, 0, 0, 0, -1, -1), 3, info + 10884);
        jobjDisp(GetChild(root, 0, 3, -1, -1, -1));
        pos = GetChild(root, 0, 3, 0, -1, -1);
        jobj = GetChild(root, 0, 3, 0, 0, -1);
        sPutFontRect(info + 300, pos, jobj, color, shadow, 0, 2);
        if (picture != 0) {
            jobjCopyPos(GetChild(root, 0, 3, 1, -1, -1), picture->models[0]);
            jobjDispAll(picture->models[0]);
        }
        chara = enemyChara[0];
        if (chara != -1) {
            pos = GetChild(root, 0, 1, 0, -1, -1);
            jobj = GetChild(menu_personp[chara]->models[0], 0, 1, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
            pos->matrix[0][3] += 1.0f;
            putAscJobj(pos, 0, Tea_persondat[chara].name);
            pos = GetChild(root, 0, 1, -1, -1, -1);
            jobj = GetChild(menu_zoidp[enemyZoid[0]]->models[0], 0, 0, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
        }
        chara = enemyChara[1];
        if (chara > 0 && chara < 57) {
            pos = GetChild(root, 0, 2, 0, -1, -1);
            jobj = GetChild(menu_personp[chara]->models[0], 0, 1, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
            pos->matrix[0][3] += 1.0f;
            putAscJobj(pos, 0, Tea_persondat[chara].name);
            pos = GetChild(root, 0, 2, -1, -1, -1);
            jobj = GetChild(menu_zoidp[enemyZoid[1]]->models[0], 0, 0, -1, -1, -1);
            jobjCopyPos(pos, jobj);
            HSD_JObjDispAll(jobj, 0, 7, 0);
        }
        HSD_CObjEndCurrent();
    (void)(root == 0);
        GXSetCullMode(2);
    }
    HSD_EndRender();
    debugmenudraw();
    vsyncN++;
}
#pragma pop

}
