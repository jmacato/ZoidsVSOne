#ifndef ZOIDS_TTL_MAIN_BSS_H
#define ZOIDS_TTL_MAIN_BSS_H

#include "model_archive.h"
#include "game_save.h"
#include "matrix.h"
#include "game_zoid_data.h"
#include "game_part_data.h"
#include "game_person_data.h"
#include "game_zoid_entry.h"

typedef struct BatMapEntry {
    s16 reserved_00[3];
    s16 map;
    s16 first;
    s16 first_zoid;
    s16 second;
    s16 second_zoid;
} BatMapEntry;

typedef struct DemoMsg {
    s16 cmd;
    s16 who0;
    s16 cha0;
    s16 who1;
    s16 cha1;
    s16 bg;
    s16 msg;
    s16 bgm;
    s16 vno;
    s16 field_12;
    s16 field_14;
} DemoMsg;

typedef struct TitleAnim {
    u8 mode;
    u8 state;
    u8 next;
    u8 reserved;
} TitleAnim;

typedef struct SaveLoadWindow {
    s16 active;
    s16 anim;
} SaveLoadWindow;

typedef struct ButtonAnim {
    u8 state;
    u8 cur;
    u8 old;
} ButtonAnim;

#pragma force_active on
static u8 dtMain[64];
static Mtx dspMtx;
ModelArchive *menu_zoidp[100];
ModelArchive *menu_personp[58];
GameZoidEntry GameZoid[16];
GameSaveRecord IveSave[9];
GameSaveRecord IveSaveFlag;
GameSaveRecord IveSaveFlagBak;
ZoidData Tea_zoiddat[101];
PartData Tea_partsdat[451];
BulletDat Tea_bulletdat[131];
PersonData Tea_persondat[59];
EffectDat Tea_effectdat[111];
u8 TXT_Menu_dat[101712];
ModelArchive *menudemo[4];
s8 menuZoidMountPointDsip[28];
s16 menuwepdispmount[28];
char menudispyesnostr1[180];
char menudispyesnostr2[180];
SaveLoadWindow menudispslwindow[3];
s32 menudispwinstr[45];
s16 menutitleguide[8];
TitleAnim menutitleanm[20];
s16 menuSLPos[5];
s32 menu_SlotDataOn[5];
s32 menusaveloadSlotButtonanm[3];
s16 menusaveloadfilename[15];
s32 menusaveloadcommentname[17];
u8 menufarmanm[20];
u8 menumodeanm[20];
u8 menufarmanmold[20];
ButtonAnim menubackanm[20];
s16 menufarmst[20];
s16 menufarmmh[20];
s16 menufarmsl[20];
s16 menufarmcl[20];
s16 menufarmmn[20];
s16 menusetst[20];
s16 menusetsl[20];
s16 menusetmh[20];
ButtonAnim menusetbtanm[12];
s16 menusetcl[20];
s16 menusetmn[20];
static Vec3 lookCam;
u8 menufarmjfl[20];
char menuyesnoshopmsg[80];
DemoMsg Tea_demomsg[100];
s16 menudemocha[6];
s16 Tea_demomenu[11];
static s32 voiceSn2[20];
#pragma force_active off

#endif
