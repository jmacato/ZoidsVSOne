#pragma auto_inline off
#include "types.h"
#include "card_status.h"
#include "game_save.h"
#include "os_time.h"
#include "model_archive.h"
#include "shadow.h"
#include "cobj.h"
#include "lobj.h"

extern u32 __OSBusClock : 0x800000F8;
extern s32 MemCardStatus[2];
extern s32 MemCardOn[2];
extern s32 MemCardError;
extern s32 MemcardNowSlot;
extern s32 MemCardSectorSize;
extern s32 MemCardLength;
extern s32 MemCardFreeSize;
extern s32 MemCardFreeDir;
extern GameSaveRecord IveSaveFlag;
extern char menusaveloadcommentname[];
extern char menusaveloadfilename[];
extern char *strcpy(char *destination, const char *source);
extern void *memcpy(void *destination, const void *source, u32 size);
extern void ZeroMemory(void *address, u32 size);
extern s32 MemCardFileFnNo;
extern s32 menu_SlotOn[];
extern s32 TEA_mcChkSlot(s32 slot);
extern s32 TEA_mcChkSector(s32 slot);
extern s32 TEA_mcMount(s32 slot);
extern s32 TEA_mcUnMount(s32 slot);
extern s32 TEA_mcFileExist(s32 slot, char *name);
extern ModelArchive *menu_saveloadiconp;
extern void *searchTObj(HSD_JObj *joint);
extern void MemCpy(void *destination, const void *source, u32 size);
extern s32 ZoidFileBroken;
extern s32 TEA_mcError(s32 slot, s32 result);
extern s32 TEA_mcResult(s32 result);
extern s32 TEA_mcFileOpen(s32 slot, char *name);
extern s32 TEA_mcFileClose(void);
extern s32 TEA_mcBusyWait(s32 slot, s32 result);
extern s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo *fileInfo);
extern s32 TEA_mcFileCreat0(s32 slot, char *name, s32 size);
s32 TEA_mcFileMakeSystemIcon(s32 slot);
s32 TEA_mcFileWriteGather(s32 slot, void *buffer, s32 size, s32 sector);
s32 TEA_mcFileWrite(s32 slot, void *buffer, s32 size);
s32 TEA_mcFileStatus(s32 slot, s32 file);
s32 TEA_mcFileReadGather(s32 slot, s32 sector, void *destination);
void LoadIconC8(void *buffer, CARDStat *stat);
s32 TEA_mcFileMake(s32 slot, s32 sector, void *source, s32 size);

static const char sShadowHeaderFile[] = "shadow.h";
static const char sShadowAllocError[] = "shadow alloc error\n";
static const char s481[] = "unmatch versions between system(%d) and ptcl-file(%d)";
static const char s499[] = "MemCardInit\n";
static const char s538[] = "MemCard%d SECTOR \n";
static const char s566[] = "MemCard Mount \215\317\n";
static const char s567[] = "MemCard Mount set \n";
static const char s568[] = "MemCard Mount Ok :";
static const char s569[] = "\t\217C\225\2341\216\270\224s. (%d)\n";
static const char s570[] = "\tCardUnMount. (%d)\n";
static const char s571[] = "\t\217C\225\234 Ok \n";
static const char s572[] = "\tMount %d \n";
static const char s573[] = "MemCard Mount End \n";
static const char s605[] = "\t\217C\225\2342\216\270\224s. (%d)\n";
static const char s625[] = "\t\217C\225\2343\216\270\224s. (%d)\n";
static const char s655[] = "MemCard Mountnochk \n";
static const char s667[] = "Memcard EncErr\n";
static const char s669[] = "Memcard EncErr1End\n";
static const char s685[] = "MemCard FormatOk \n";
static const char s707[] = "MemCard \216g\227p\202\305\202\253\202\310\202\242\203J\201[\203h \n";
static const char s715[] = "MemCard%d mcerrIO\203G\203\211\201[ \n";
static const char s716[] = "MemCard%d mcerr\203\201\203\202\203\212\203J\201[\203h\202\305\202\310\202\242 \n";
static const char s717[] = "MemCard%d mcerr\224j\211\363\n";
static const char s741[] = "MemCard freesize=%d freedir=%d \n";
static const char s743[] = "NEED FILENUM";
static const char s753[] = "\tLeave StartCheck\n";
static const char s763[] = "\tUnMount \216\270\224s\n";
static const char s776[] = "CARD Format :";
static const char s777[] = "\t\217\211\212\372\211\273\216\270\224s 1st . (%d)\n";
static const char s778[] = "\t\217\211\212\372\211\273\216\270\224s 2nd . (%d)\n";
static const char s779[] = "\t\217\211\212\372\211\273 done. (%d)\n";
static const char s783[] = "GetStatus \n";
static const char s784[] = "failed. (%d)\n";
static const char s785[] = "\tGameName:%.4s Company:%.2s Fno:%d\n";
static const char s786[] = "\tSaveSize:%d Time:%d \n";
static const char s787[] = "\tfileName[%.32s] MSG[ADR=%d] \n";
static const char s788[] = "\tFreeSize:%d FreeDir:%d \n";
static const char s807[] = "\tCARDGetSectorSize() failed. (%d)\n";
static const char s808[] = "File:%s Delete \n";
static const char s809[] = "MemCard \215\354\220\254 1st\t";
static const char s810[] = "done. (%d:%d:%d)\n";
static const char s811[] = "TypeStart\n%sTypeEnd\n";
static const char s812[] = "CARDWriteSize \203f\201[\203^\203T\203C\203Y%dByte \203Z\201[\203u\203T\203C\203Y%dByte\n";
static const char s813[] = "\203\201\203\202\203\212\223]\221\227 %d Byte %x\n";
static const char s814[] = "CARD CLOSE OK\n";
static const char s815[] = "CARD \203\201\203\202\203\212\212J\225\372OK\n";
static const char s832[] = "CARDWrite %dByte SaveSize=%d \n";
static const char s833[] = "failedwrite_a. (%d)\n";
static const char s834[] = "\tWriteByte(%8d)\n";
static const char s835[] = "failedwrite_b. (%d)\n";
static const char s836[] = "done. (%d)\n";
static const char s847[] = "MemCardOpen\t%s ";
static const char s849[] = "MemCard ReOpen\t%s \n";
static const char s861[] = "MemCardClose\t";
static const char s874[] = "\245\245Busy\245\245";
static const char s910[] = "\t\203\201\203\202\203\212\201[SizeErr1:%d %x\n";
static const char s911[] = "\t\203\201\203\202\203\212\201[SizeErr2:%d %x\n";
static const char s912[] = "MemCardRead %dByte %dByte \n";
static const char s913[] = "\t\203\201\203\202\203\212\201[\212m\225\333:%d %x\n";
static const char s914[] = "Read:failed. (%d)\n";
static const char s915[] = "\tReadByte(%d)\n";
static const char s916[] = "failedB. (%d)\n";
static const char s917[] = "done. (%d) %d Byte\n";
static const char s918[] = "\t\203\201\203\202\203\212\201[ReadSizeErr:%d %x\n";
static const char s922[] = "/etc/zoidvs.tga";
static const char s923[] = "/etc/ci.tpl";
/* addresses of s922, s923 and the "" literal (ELF @684) */
static const u8 s924[12] = {0x80, 0x0E, 0xE7, 0xC8, 0x80, 0x0E, 0xE7, 0xD8, 0x80, 0x2A, 0x00, 0x70};
static const char s971[] = "Memcpy St\n";
static const char sIconGameTitle[] = "\203]\203C\203h\203o\201[\203T\203X                                   ";
static const char s973[] = "ICON NO IMG\n";
static const char s974[] = "CLUT ERR\n";
static const char s975[] = "CLUT OK\n";
static const char s976[] = "ICON NO CLUT\n";
static const char s977[] = "Status set\217\200\224\365 memcpy\n";
static const char s1011[] = "MemFile SaveSt slot=%d fname=[%s] iveno=%d\n";
static const char s1066[] = "Load1:End Stage=%d Mapno=%d Single=%d NowZoid=%d NowCust=%d \220l\225\250=%d \213\340=%d\n";
static const char s1067[] = "Zoid\202\314\203f\201[\203^\202\305\202\310\202\242\n";
static const char s1068[] = "Zoid\202\314\203f\201[\203^\201F\203`\203F\203b\203N\203T\203\200\203G\203\211\201[\n";
static const char s1145[] = "Memcard MsgWaitPut:SLOT=%d MSGNO=%d\n";
static const char s1172[] = "Memcard MsgWaitPutNotSlotChk:SLOT=%d MSGNO=%d\n";
static const char s1184[] = "MSG WAIT";
static const char s1194[] = "MSG WAIT NoChkSlot";
static const char sSaveFileComment[] = "\203v\203\214\203C\203f\201[\203^\201@\201@                                 ";
static const char sSaveFileName[] = "ZOIDSVS.TEA";
static const char s1210[] = "MemCardFileMake\226\263\202\265 \203t\203@\203C\203\213\203N\203\212\203G\203C\203g\212J\216n\n";
static const char s1211[] = "MemCardFileMake\226\263\202\265 \203t\203@\203C\203\213\203N\203\212\203G\203C\203g\216\270\224s\n";
static const char s1212[] = "MemCardFileICON\217\356\225\361\220\266\220\254\216\270\224s \n";
static const char s1213[] = "MemCardFileICON\217\356\225\361\220\266\220\254 \220\254\214\367 \n";
static const char s1221[] = "CARDMakeIconSize \203f\201[\203^\203T\203C\203Y%dByte \203Z\201[\203u\203T\203C\203Y%dByte\n";
static const char s1222[] = "CARDMakeIconSize \216\270\224s\n";
static const char s1223[] = "CARDMakeIconSize \220\254\214\367\n";
static const char s1240[] = "CARDWriteG %dByte SaveSize=%d no=%d \n";
static const char s1257[] = "\t\203\201\203\202\203\212\201[\203t\203@\203C\203\213\203\212\201[\203h\203M\203\203\203U\216\270\224s \n";
static const char s1258[] = "\t\203\201\203\202\203\212\201[\212m\225\333RG:%d %x no=%d \n";
static const char s1259[] = "\tReadByteRG(%d)\n";
static const char s1260[] = "done.RG (%d) %d Byte size=%d\n";
static const char s1297[] = "\n\n\nLoad\213\214:Start Stage=%d Mapno=%d Single=%d NowZoid=%d NowCust=%d\n \220l\225\250=%d \213\340=%d partsnum=%d posh=%d %s \225\252\212\204%d SaveSize=%d\n";
static const char s1298[] = "MemSaveFile0 EndSUM:%d %s \n";
static const char s1350[] = "\n\nLoadGather:End1 Stage=%d Mapno=%d Single=%d NowZoid=%d NowCust=%d\n \220l\225\250=%d \213\340=%d partsnum=%d posh=%d %s \225\252\212\204%d\n";
static const char s1351[] = "\n\nLoadGather:End2 \203o\203g\203N\203\212\203A=%d Stage=%d Mapno=%d Single=%d NowZoid=%d NowCust=%d\n \220l\225\250=%d \213\340=%d partsnum=%d posh=%d %s \225\252\212\204%d\n";
static const char s1354[] = "Zoid\202\314\203f\201[\203^\201F\203`\203F\203b\203N\203T\203\200\203G\203\211\201[ SUM=%d \n";
static const char s1382[] = "File1:%s Delete \n";
static const char s1383[] = "\203t\203@\203C\203\213\215\354\220\2540\216\270\224sIOERR\n";
static const char s1440[] = "MCC Enum ...";
static const char s1442[] = "MCCEnumDevices() error\nTerminated\n";
static const char s1443[] = "MCCEnum %d\n";
static const char s1444[] = "\tMCC.NG\tUSB Server\202\306\202\314\222\312\220M\202\311\216\270\224s\n";
static const char s1445[] = "\tMCC.OK\t\n";
static const char s1446[] = "MccOpen Ok\n";
static const char s1447[] = "MccOpen Err\n";
static const char s1448[] = "MCC Fail\n";
static const char s1449[] = "TTY Init .";
static const char s1459[] = "FIO Init .";
static const char s1461[] = " Host\222\342\216~\222\206!\t\n";
static const char s1462[] = " Active\t\n";
static const char s1483[] = "\tUSBAdapter EXI=%d\t";
static const char s1494[] = "MCC PING Recv \n";
static const char s1495[] = "MCC RePING Recv \n";
static const char s1527[] = "mcc\203f\201[\203^\216\363\220M\217I\227\271\n";
static const char s1528[] = "XFB BMP\221\227\220M\227v\213\201\223\301\214\240\226\275\227\337\216\363\220M ADR=%08X\n";
static const char s1540[] = "mcc\203R\203\223\203g\203\215\201[\203\213\203R\201[\203h\216\363\220M\n";
static const char s1541[] = "Recive 1stProc\217I\227\271\n";
static const char s1542[] = " ApiCodex=%04X SubCode=%04X Size=%8X \n";
static const char s1543[] = " ApiCoded=%04d SubCode=%04d Size=%8d \n";
static const char s1544[] = "\217I\227\271\203R\201[\203h\212m\224F\n";
static const char s1573[] = "usbSendBuf:\203X\203\214\203b\203h\215\354\220\254\225s\211\302\n";
static const char s1589[] = "usbSendBufApi:\203X\203\214\203b\203h\215\354\220\254\225s\211\302\n";
static const char s1590[] = "usbSendBufApiLeave:\203X\203\214\203b\203h\215\354\220\254\225s\211\302\n";
static const char s1668[] = "XFB BMP\221\227\220M\227v\213\201\216\363\220M ADR=%08X\n";
static const char s1676[] = "NowTime %d/%d/%d %02d:%02d:%02d \n";
static const char s1678[] = "\212m\224F\203R\201[\203h\221\227\220M\n";
static const char s1701[] = "mccwrite st1 size=%8d \227]\202\350=%04d adiv=%d rest=%d\n";
static const char s1702[] = "mccwrite err count=%d\n";
static const char s1703[] = "mccwrite ok\n";
static const char s1705[] = "mccwrite End\n";
static const char s1708[] = "mcchiowritemailbox\n";
static const char s1723[] = "audio/se/se";
static const char s1738[] = "SE Restore %d=%s\n";
static const char s1757[] = "SE Load Num=%d fn=%s\n";
static const char s1762[] = "SE UnLoaded POP POP POP now=%d\n";
static const char s1955[] = "voice/%02d/V%02d_%02d.adp";
static const char s1977[] = "SEQ StopSeq \n";
static const char s1978[] = "SEQ Free \n";
static const char sBgmSonPathFormat[] = "audio/bgm/%s.son";
static const char s1980[] = "SEQ Play FileChk %s \n";
static const char sBgmPathFormat[] = "audio/bgm/%s";
static const char s1982[] = "SEQ LoadSfxOk \n";
static const char s1983[] = "SEQ PlayOk %s \n";

typedef struct SfxName {
    char name[0x50];
    s16 group;
    u8 reserved_52[2];
    s32 loaded;
} SfxName;

u8 CardWorkArea[0xA000] __attribute__((aligned(32)));
CARDStat MemCardStatInfo;
u8 MemCardAdr[24582] __attribute__((aligned(32)));
CARDFileInfo MemCardFileInfo __attribute__((aligned(8)));

u8 MemCardSaveArea0[0x16000] __attribute__((aligned(32)));
u8 tea_usbsend[68];
u8 tea_usbrecv[68];
u8 hioRecvBuf[0x2000];
u8 hioSendBuf[0x8000] __attribute__((aligned(32)));
u8 apiSendBuf[0x8000] __attribute__((aligned(32)));
u8 thread[784] __attribute__((aligned(8)));
u8 ThreadStack[0x1000];
u8 TEA_mccbuf[0x1000] __attribute__((aligned(32)));

extern void __assert(const char *file, u32 line, const char *condition);

HSD_Shadow *makeShadow(HSD_LObj *light)
{
    HSD_Shadow *shadow = HSD_ShadowAlloc();

    if (shadow == 0)
        OSReport(sShadowAllocError);
    if (shadow == 0)
        __assert(sShadowHeaderFile, 117, "shadow");
    shadow->user_data = light;
    switch (light->flags & LOBJ_TYPE_MASK) {
    case LOBJ_INFINITE:
        HSD_CObjSetProjectionType(shadow->camera, PROJ_ORTHO);
        break;
    case LOBJ_POINT:
    case LOBJ_SPOT:
        HSD_CObjSetProjectionType(shadow->camera, PROJ_FRUSTUM);
        break;
    default:
        __assert("Sub.c", 143, "0");
        break;
    }
    HSD_ShadowSetSize(shadow, 512, 512);
    HSD_CObjSetNear(shadow->camera, 0.1f);
    HSD_CObjSetFar(shadow->camera, 1000.0f);
    return shadow;
}

s32 TEA_mcUnMount(s32 slot)
{
    s64 time = OSGetTime();
    s32 result;
    s32 frame_padding[4];

    MemcardNowSlot = slot;
    CARDUnmount(0);
    do {
        result = CARDGetResultCode(slot);
    } while (result == CARD_RESULT_BUSY);
    MemCardOn[slot] = 0;
    if (result < 0) {
        OSReport(s763);
        return 0;
    }
    return 1;
}

extern s32 TEA_mcBadEncFormatEnc(s32 slot);
extern s32 TEA_mcSetEnc(s32 slot);

s32 TEA_mcMount(s32 slot)
{
    s32 check;
    s32 result;
    s32 frame_padding[2];

    MemcardNowSlot = slot;
    if (MemCardOn[slot] == 1) {
        OSReport(s566);
        return 1;
    }
    OSReport(s567);
    CARDMountAsync(slot, CardWorkArea, 0, 0);
    do {
        result = CARDGetResultCode(slot);
    } while (result == CARD_RESULT_BUSY);
    MemCardStatus[slot] = result;
    switch (result) {
    case CARD_RESULT_ENCODING:
        TEA_mcBadEncFormatEnc(slot);
        return 0;
    case CARD_RESULT_NOCARD:
        MemCardOn[slot] = 0;
        return 0;
    case CARD_RESULT_BROKEN:
    case CARD_RESULT_READY:
        MemCardError = 0;
        OSReport(s568);
        check = CARDCheckAsync(slot, 0);
        if (check == CARD_RESULT_ENCODING)
            return TEA_mcSetEnc(slot);
        if (check < 0) {
            OSReport(s569, check);
            if (TEA_mcError(slot, check) == 1) {
                TEA_mcSetEnc(slot);
                OSReport(s570, check);
                CARDUnmount(slot);
                return 0;
            }
            CARDUnmount(slot);
            return 0;
        }
        OSReport(s571);
        MemCardError = 0;
        return 1;
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_WRONGDEVICE:
        MemCardOn[slot] = 0;
        TEA_mcResult(result);
        TEA_mcError(slot, result);
        return 0;
    default:
        OSReport(s572, result);
        OSReport(s573);
        return 1;
    }
}

s32 TEA_mcMountNoChk(s32 slot)
{
    s32 result;
    s32 frame_padding[2];
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;

    MemcardNowSlot = slot;
    if (MemCardOn[slot] == 1) {
        OSReport(s566);
    }
    OSReport(s655);
    CARDMountAsync(slot, CardWorkArea, 0, 0);
    while (1) {
        result = CARDGetResultCode(slot);
        if (result != CARD_RESULT_BUSY) {
            break;
        }
        if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
    }
    MemCardStatus[slot] = result;
    switch (result) {
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_WRONGDEVICE:
        TEA_mcError(slot, result);
    case CARD_RESULT_NOCARD:
        MemCardOn[slot] = 0;
    case CARD_RESULT_ENCODING:
        return 0;
    case CARD_RESULT_BROKEN:
    case CARD_RESULT_READY:
        MemCardError = 0;
        MemCardOn[slot] = 1;
        return 1;
    default:
        OSReport(s572, result);
        return 0;
    }
}

s32 TEA_mcFileStatus(s32 slot, s32 file)
{
    s32 result;

    MemcardNowSlot = slot;
    OSReport(s783);
    result = CARDGetStatus(slot, file, &MemCardStatInfo);
    if (result < 0) {
        OSReport(s784, result);
        return 0;
    }
    OSReport(s785, MemCardStatInfo.gameName, MemCardStatInfo.company, file);
    OSReport(s786, MemCardStatInfo.length, MemCardStatInfo.time);
    OSReport(s787, MemCardStatInfo.fileName, MemCardStatInfo.commentAddr);
    CARDFreeBlocks(slot, &MemCardFreeSize, &MemCardFreeDir);
    OSReport(s788, MemCardFreeSize, MemCardFreeDir);
    return 1;
}

typedef struct McIconData {
    char game_title[32];
    char file_comment[32];
    u8 icon_image[1024];
    u8 icon_tlut[512];
} McIconData;

void LoadIconC8(void *buffer, CARDStat *stat)
{
    u32 frame_padding[2];
    McIconData icon;
    u32 unused;
    s8 work[2048];
    HSD_TObj *tobj;
    s16 i;
    void *data;

    OSReport(s971);
    stat->commentAddr = 0;
    stat->iconAddr = 64;
    /* icon 0 is a slow C8 frame; icon 1 speed END stops the animation there */
    stat->bannerFormat = stat->bannerFormat & ~CARD_STAT_BANNER_MASK;
    stat->bannerFormat = stat->bannerFormat & ~CARD_STAT_ANIM_MASK;
    stat->iconFormat = (stat->iconFormat & ~CARD_STAT_ICON_MASK) | CARD_STAT_ICON_C8;
    stat->iconSpeed = (stat->iconSpeed & ~CARD_STAT_SPEED_MASK) | CARD_STAT_SPEED_SLOW;
    stat->iconSpeed = stat->iconSpeed & ~(CARD_STAT_SPEED_MASK << 2);
    memcpy(icon.game_title, sIconGameTitle, 32);
    strcpy((char *)work, menusaveloadcommentname);
    memcpy(icon.file_comment, work, 32);
    for (i = 0; i < 2048; i++) {
        work[i] = i;
    }
    memcpy(icon.icon_image, work, 1024);
    for (i = 0; i < 255; i++) {
        work[i] = i;
    }
    memcpy(icon.icon_tlut, work, 512);
    tobj = (HSD_TObj *)searchTObj(menu_saveloadiconp->models[0]);
    if (tobj != 0) {
        if (tobj->imagedesc != 0) {
            if ((data = tobj->imagedesc->image_ptr, data != 0)) {
                memcpy(icon.icon_image, data, 1024);
            } else {
                OSReport(s973);
            }
        }
        if (tobj->tlut == 0) {
            OSReport(s974);
        } else {
            OSReport(s975);
        }
        if (tobj->tlut->lut != 0) {
            memcpy(icon.icon_tlut, tobj->tlut->lut, 512);
        } else {
            OSReport(s976);
        }
    }
    memcpy(buffer, &icon, sizeof(McIconData));
    OSReport(s977);
}

s32 TEA_mcFileMake(s32 slot, s32 sector, void *source, s32 size)
{
    s64 time = OSGetTime();
    u8 frame_padding[0x18];

    strcpy(menusaveloadcommentname, sSaveFileComment);
    strcpy(menusaveloadfilename, sSaveFileName);
    MemcardNowSlot = slot;
    if (TEA_mcFileOpen(slot, menusaveloadfilename) == 0) {
        OSReport(s1210);
        if (TEA_mcFileCreat0(slot, menusaveloadfilename, 0x14000) == 0) {
            OSReport(s1211);
            return 0;
        }
        if (TEA_mcFileMakeSystemIcon(0) == 0) {
            OSReport(s1212);
        } else {
            OSReport(s1213);
        }
    }
    MemCardSectorSize = 8192;
    MemCardLength = 8192;
    memcpy(MemCardAdr, source, sizeof(GameSaveRecord));
    OSReport(s810, 0, MemCardFileInfo.chan, MemCardFileInfo.fileNo);
    if (TEA_mcFileWriteGather(slot, MemCardAdr, MemCardLength, sector) == 0) {
        TEA_mcFileClose();
        return 0;
    }
    TEA_mcFileClose();
    return 1;
}

s32 TEA_mcFileMakeSystemIcon(s32 slot)
{
    s64 time = OSGetTime();
    s32 *file;
    u8 frame_padding[0x10];

    u8 *buffer;

    MemCardSectorSize = 8192;
    buffer = MemCardAdr;
    strcpy(menusaveloadcommentname, sSaveFileComment);
    strcpy(menusaveloadfilename, sSaveFileName);
    memcpy(buffer, &IveSaveFlag, sizeof(GameSaveRecord));
    MemcardNowSlot = 0;
    if (TEA_mcFileOpen(slot, menusaveloadfilename) == 0) {
        return 0;
    }
    file = &MemCardFileInfo.fileNo;
    /* icon, size word and record (0x644 + 0x1694 bytes) rounded up to a sector */
    MemCardLength = (MemCardSectorSize + 7383) & ~(MemCardSectorSize - 1);
    TEA_mcFileStatus(0, *file);
    *(s32 *)(buffer + sizeof(McIconData)) = sizeof(GameSaveRecord);
    OSReport(s1221, sizeof(GameSaveRecord), MemCardLength);
    memcpy(MemCardAdr + 0x644, &IveSaveFlag, sizeof(GameSaveRecord));
    LoadIconC8(MemCardAdr, &MemCardStatInfo);
    CARDSetStatus(slot, *file, &MemCardStatInfo);
    if (TEA_mcFileWrite(slot, MemCardAdr, MemCardLength) == 0) {
        OSReport(s1222);
        TEA_mcFileClose();
        return 0;
    }
    OSReport(s1223);
    TEA_mcFileClose();
    return 1;
}

#pragma push
#pragma opt_propagation off
s32 TEA_mcFileWriteGather(s32 slot, void *buffer, s32 size, s32 sector)
{
    s32 result;
    s32 start;
    s32 previous;
    s32 current;
    s32 length;
    s32 frame_padding[2];
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;

    length = 8192;
    if (length > 8192) {
        length = 8192;
    }
    if (size > 8192) {
        size = 8192;
    }
    MemcardNowSlot = slot;
    MemCardSectorSize = 8192;
    OSReport(s1240, size, length, sector);
    OSReport((char *)MemCardAdr);
    start = CARDGetXferredBytes(slot);
    previous = current = start;
    CARDWrite(&MemCardFileInfo, MemCardAdr, length, MemCardSectorSize * sector);
    while ((result = CARDGetResultCode(slot)) == CARD_RESULT_BUSY) {
        current = CARDGetXferredBytes(slot);
        if (current != previous) {
            OSReport(s834, current - start);
            previous = current;
        }
        if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
    }
    if (result < 0) {
        OSReport(s784, result);
        return 0;
    }
    OSReport(s836, result);
    return 1;
}

#pragma pop

#pragma push
#pragma opt_propagation off
s32 TEA_mcFileReadGather(s32 slot, s32 sector, void *destination)
{
    s32 result;
    s32 length;
    s32 start;
    s32 current;
    s32 previous;
    s32 frame_padding[2];
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;

    MemcardNowSlot = slot;
    MemCardSectorSize = 8192;
    length = sizeof(GameSaveRecord);
    ZeroMemory(MemCardAdr, 0x6000);
    OSReport(s1257);
    if (TEA_mcFileOpen(slot, menusaveloadfilename) == 0) {
        return 0;
    }
    OSReport(s1258, length, sizeof(GameSaveRecord), sector);
    start = CARDGetXferredBytes(slot);
    previous = current = start;
    ZeroMemory(MemCardAdr, 0x6000);
    CARDRead(&MemCardFileInfo, MemCardAdr, 8192, sector * 8192);
    while ((result = CARDGetResultCode(slot)) == CARD_RESULT_BUSY) {
        current = CARDGetXferredBytes(0);
        if (current != previous) {
            OSReport(s1259, current - start);
            previous = current;
        }
        if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            TEA_mcFileClose();
            return 0;
        }
    }
    if (result < 0) {
        OSReport(s916, result);
        TEA_mcFileClose();
        return 0;
    }
    OSReport(s1260, result, current - start, sizeof(GameSaveRecord));
    if (length > 8192 || length < 0) {
        OSReport(s918, length, sizeof(GameSaveRecord));
        length = 8192;
    }
    MemCpy(MemCardAdr, destination, length);
    TEA_mcFileClose();
    return 1;
}

#pragma pop

s32 TEA_mcFileCreat0(s32 slot, char *name, s32 size)
{
    s32 result;
    s32 *file;
    u8 frame_padding[0x10];
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;

    MemcardNowSlot = slot;
    result = CARDGetSectorSize(slot, (u32 *)&MemCardSectorSize);
    if (result < 0) {
        OSReport(s807, result);
        return 0;
    }
    MemCardLength = (size + 1604 + MemCardSectorSize - 1) & ~(MemCardSectorSize - 1);
    if (MemCardLength > 0x14000) {
        MemCardLength = 0x14000;
    }
    CARDDelete(slot, name);
    OSReport(s1382, name);
    result = CARDCreateAsync(slot, name, MemCardLength, &MemCardFileInfo, 0);
    if (result < 0) {
        TEA_mcError(slot, result);
        OSReport(s784, result);
        return 0;
    }
    while ((result = CARDGetResultCode(slot)) == CARD_RESULT_BUSY) {
        if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
    }
    if (result < 0) {
        MemCardStatus[0] = result;
    }
    if (result == CARD_RESULT_IOERROR) {
        OSReport(s1383);
        return 0;
    }
    file = &MemCardFileInfo.fileNo;
    OSReport(s810, result, MemCardFileInfo.chan, MemCardFileInfo.fileNo);
    TEA_mcFileStatus(slot, *file);
    ZeroMemory(MemCardSaveArea0, 0x14000);
    CARDWriteAsync(&MemCardFileInfo, MemCardSaveArea0, 0x14000, 0, 0);
    while (CARDGetResultCode(0) == CARD_RESULT_BUSY) {
    }
    CARDClose(&MemCardFileInfo);
    OSReport(s814);
    return 1;
}

#pragma push
#pragma opt_unroll_loops off
s32 TEA_mcSaveFile0(s32 slot, s32 sector, s32 record)
{
    GameSaveRecord copy;
    GameSaveRecord data;
    s32 frame_padding;
    OSCalendarTime calendar;
    u8 *p;
    s16 i;
    u8 sum;
    s64 limit;

    OSGetTime();
    MemcardNowSlot = slot;
    MemCardFileFnNo = sector;
    strcpy(menusaveloadfilename, sSaveFileName);
    if (record <= -1) {
        memcpy(&data, &IveSaveFlag, sizeof(GameSaveRecord));
    } else {
        memcpy(&data, &IveSave[record], sizeof(GameSaveRecord));
    }
    strcpy(data.signature, "Tears");
    OSTicksToCalendarTime(OSGetTime(), &calendar);
    data.save_year = calendar.year;
    data.save_month = calendar.mon;
    data.save_day = calendar.mday;
    data.save_hour = calendar.hour;
    data.save_minute = calendar.min;
    data.save_second = calendar.sec;
    memcpy(&copy, &data, sizeof(GameSaveRecord));
    p = (u8 *)&copy;
    sum = 0;
    for (i = 0; i < 5770; i++) {
        sum += *p++;
    }
    data.checksum = sum;
    limit = OSGetTime() / (__OSBusClock / 4) + 30;
    while (1) {
        menu_SlotOn[slot] = TEA_mcChkSlot(slot);
        if (menu_SlotOn[slot] == 1) {
            if (TEA_mcChkSector(0) != 0) {
                if (TEA_mcMount(0) != 0) {
                    if (TEA_mcFileExist(slot, menusaveloadfilename) == 1) {
                        OSReport(s1297, data.stage, data.map_no, data.single_team, data.selected_zoid, data.selected_zoid_slot, data.selected_person, data.money, data.parts_num, data.field_1674, data.signature, data.vs_mode, sizeof(GameSaveRecord));
                        if (TEA_mcFileMake(slot, sector, &data, sizeof(GameSaveRecord)) == 1) {
                            return 1;
                        }
                    } else if (TEA_mcFileMake(slot, sector, &data, sizeof(GameSaveRecord)) == 1) {
                        strcpy(menusaveloadfilename, sSaveFileName);
                        TEA_mcUnMount(slot);
                        return 1;
                    }
                    break;
                }
                return 0;
            }
        } else if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
    }
    OSReport(s1298, data.checksum, data.signature);
    TEA_mcUnMount(slot);
    return 0;
}
#pragma pop

#pragma push
#pragma opt_unroll_loops off
s32 TEA_mcLoadFile0(s32 slot, s32 sector, s32 record)
{
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;
    GameSaveRecord copy;
    GameSaveRecord data;
    u32 frame_padding[2];
    u8 *p;
    s16 i;
    u8 sum;
    s32 ok;

    strcpy(menusaveloadfilename, sSaveFileName);
    MemcardNowSlot = slot;
    MemCardFileFnNo = sector;
    ok = 0;
    while (1) {
        menu_SlotOn[slot] = TEA_mcChkSlot(slot);
        if (menu_SlotOn[slot] == 1) {
            if (TEA_mcChkSector(slot) == 0) {
                continue;
            }
            if (TEA_mcMount(slot) != 0) {
                if (TEA_mcFileExist(slot, menusaveloadfilename) == 1) {
                    if (TEA_mcFileReadGather(slot, sector, &data) == 1) {
                        ok = 1;
                    } else {
                        OSReport(s1350, data.stage, data.map_no, data.single_team, data.selected_zoid, data.selected_zoid_slot, data.selected_person, data.money, data.parts_num, data.field_1674, data.signature, data.vs_mode);
                        TEA_mcUnMount(slot);
                        return 0;
                    }
                    OSReport(s1351, (s8)data.system_flags[0], data.stage, data.map_no, data.single_team, data.selected_zoid, data.selected_zoid_slot, data.selected_person, data.money, data.parts_num, data.field_1674, data.signature, data.vs_mode);
                }
            } else {
                return 0;
            }
        } else if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
        break;
    }
    TEA_mcUnMount(slot);
    if (record != -1 && data.has_data == 0) {
        ok = 0;
    }
    memcpy(&copy, "Tears", 5);
    p = (u8 *)&copy;
    for (i = 0; i < 5; i++) {
        if (data.signature[i] != ((u8 *)&copy)[i]) {
            OSReport(s1067);
            memcpy(&copy, data.signature, 5);
            ((u8 *)&copy)[5] = 0;
            OSReport("Tears[");
            OSReport((char *)&copy);
            OSReport("]\n");
            ok = 0;
            break;
        }
    }
    memcpy(&copy, &data, sizeof(GameSaveRecord));
    sum = 0;
    for (i = 0; i < 5770; i++) {
        sum += *p++;
    }
    if (data.checksum != sum) {
        OSReport(s1354, data.checksum);
        return 0;
    }
    if (ok == 0) {
        ZoidFileBroken = 1;
        return 0;
    }
    if (record != -1) {
        memcpy(&IveSave[record], &data, sizeof(GameSaveRecord));
    } else {
        memcpy(&IveSaveFlag, &data, sizeof(GameSaveRecord));
    }
    return 1;
}
#pragma pop

s32 TEA_mcFileWrite(s32 slot, void *buffer, s32 size)
{
    s32 result;
    s32 start;
    s32 previous;
    s32 current;
    s32 length = (size + (MemCardSectorSize - 1)) & ~(MemCardSectorSize - 1);
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;

    MemcardNowSlot = slot;
    OSReport(s832, size, length);
    start = CARDGetXferredBytes(slot);
    previous = current = start;
    result = CARDWriteAsync(&MemCardFileInfo, buffer, length, 0, 0);
    TEA_mcResult(result);
    if (result < 0) {
        TEA_mcError(slot, result);
        OSReport(s833, result);
        return 0;
    }
    while ((result = CARDGetResultCode(slot)) == CARD_RESULT_BUSY) {
        current = CARDGetXferredBytes(slot);
        if (current != previous) {
            OSReport(s834, current - start);
            previous = current;
        }
        if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
    }
    if (result < 0) {
        OSReport(s835, result);
        return 0;
    }
    OSReport(s836, result);
    return 1;
}

s32 TEA_mcFileOpen(s32 slot, char *name)
{
    s32 result;
    s32 retry;
    s64 time;

    retry = 0;
    time = OSGetTime();
    MemcardNowSlot = slot;
    OSReport(s847, name);
    do {
        result = CARDOpen(slot, name, &MemCardFileInfo);
        if (result >= 0)
            goto opened;
        retry++;
    } while (retry < 5);
    OSReport(s784, result);
    TEA_mcResult(result);
    return 0;

opened:
    TEA_mcBusyWait(slot, result);
    TEA_mcResult(result);
    OSReport("Done\n");
    TEA_mcFileClose();
    OSReport(s849, name);
    CARDFastOpen(slot, MemCardFileInfo.fileNo, &MemCardFileInfo);
    TEA_mcFileStatus(slot, MemCardFileInfo.fileNo);
    return 1;
}

extern s32 bInitialfio;
extern s32 bInitialmcc;

s32 TEA_USBInit(void)
{
    bInitialmcc = 0;
    bInitialfio = 0;
    return 0;
}

s32 TEA_USBFileR2(void)
{
    (void)tea_usbsend;
    (void)tea_usbrecv;
    (void)hioRecvBuf;
    (void)hioSendBuf;
    (void)apiSendBuf;
    (void)thread;
    (void)ThreadStack;
    (void)TEA_mccbuf;
    (void)s1440;
    (void)s1442;
    (void)s1443;
    (void)s1444;
    (void)s1445;
    (void)s1446;
    (void)s1447;
    (void)s1448;
    (void)s1449;
    (void)s1459;
    (void)s1461;
    (void)s1462;
    (void)s1483;
    (void)s1494;
    (void)s1495;
    (void)s1527;
    (void)s1528;
    (void)s1540;
    (void)s1541;
    (void)s1542;
    (void)s1543;
    (void)s1544;
    (void)s1573;
    (void)s1589;
    (void)s1590;
    (void)s1668;
    (void)s1676;
    (void)s1678;
    (void)s1701;
    (void)s1702;
    (void)s1703;
    (void)s1705;
    (void)s1708;
    (void)s1723;
    (void)s1738;
    (void)s1762;
    (void)s1955;
    return 0;
}

s32 TEA_USBFileArchiveLoad(void)
{
    return 0;
}

s32 TEA_USBFileLenR2(void)
{
    return 0;
}

static u32 aram_block[16];
SfxName TeaSfxNamePush[10];

extern u8 TeaSoundSfxLoadNum;
extern void ARInit(u32 *stack, u32 count);
extern void ARQInit(void);
extern void AIInit(u8 *stack);
extern void *malloc2(u32 size);
extern void free(void *ptr);
extern void HSD_AudioSetHooks(void *(*alloc)(u32), void (*release)(void *));
extern void HSD_AudioInit(s32 voices, s32 music, s32 sfx, u32 aram);

void TEA_SoundInit(void)
{
    ARInit(aram_block, 16);
    ARQInit();
    AIInit(0);
    HSD_AudioSetHooks(malloc2, free);
    HSD_AudioInit(62, 48, 14, 0xC00000);
    TeaSoundSfxLoadNum = 0;
    TeaSfxNamePush[0].loaded = 0;
}

extern s32 sReadPre(void);
extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 fexist(char *name);
extern s32 HSD_AudioSFXLoad(char *name, s16 group);
extern s32 HSD_AudioSFXLoadCheck(void);

void TEA_SoundSfxLoad(char *name, s16 group)
{
    char path[80];

    sReadPre();
    sprintf(path, "%s.sam", name);
    if (fexist(path) != 0 && HSD_AudioSFXLoad(name, group) == 1) {
        if (HSD_AudioSFXLoadCheck() == 0)
            sReadPre();
        strcpy(TeaSfxNamePush[TeaSoundSfxLoadNum].name, name);
        TeaSfxNamePush[TeaSoundSfxLoadNum].group = group;
        TeaSfxNamePush[TeaSoundSfxLoadNum].loaded = 1;
        TeaSoundSfxLoadNum++;
        TeaSfxNamePush[TeaSoundSfxLoadNum].loaded = 0;
        OSReport(s1757, TeaSoundSfxLoadNum, name);
    }
}

s32 TeaVoiceFlag[64];
u32 TeaVoiceId[64];

extern u8 TeaVoiceNum;
extern u32 HSD_AudioSFXStart(u16 id, s32 volume, s32 pan);
extern u8 TEA_VoiceNumChk(void);
extern void TEA_SePosition(u32 id, s16 px, s16 pz);

u32 TEA_SeOn(u16 sfx, s16 x, s16 z)
{
    u32 id;
    s32 i;

    if (sfx == -1) {
        return -1;
    }
    id = HSD_AudioSFXStart(sfx, 127, 64);
    if (id == -1) {
        TEA_VoiceNumChk();
        return -1;
    }
    TEA_SePosition(id, x, z);
    TEA_VoiceNumChk();
    for (i = 0; i < 64; i++) {
        if (TeaVoiceFlag[i] == 0) {
            TeaVoiceId[i] = id;
            TeaVoiceFlag[i] = 1;
            TeaVoiceNum++;
            return id;
        }
    }
    return -1;
}

typedef struct TeaSoundEntry {
    u16 group;
    u16 song;
    char name[40];
} TeaSoundEntry;

extern TeaSoundEntry TeaSound[];
extern s16 TEA_BGMNO;
extern s32 TeaSeqPlayFlag;
extern void TEA_AudioSeqStop(void);
extern void TEA_AudioSeqFree(void);
extern void TEA_BgmSfxLoad(char *path, s32 group);
extern void TEA_SeqPlay(s32 group, s32 song, char *name);

void TeaBgm(s16 no)
{
    char path[80];
    s32 frame_padding;

    if (no == -1) {
        TEA_AudioSeqStop();
        TEA_AudioSeqFree();
        TEA_BGMNO = -1;
        TeaSeqPlayFlag = 0;
        return;
    }
    if (TEA_BGMNO == no)
        return;
    if (TEA_BGMNO != -1) {
        TEA_AudioSeqStop();
        OSReport(s1977);
        TEA_AudioSeqFree();
        OSReport(s1978);
        TeaSeqPlayFlag = 0;
    }
    TEA_BGMNO = no;
    sprintf(path, sBgmSonPathFormat, TeaSound[no].name);
    OSReport(s1980, path);
    sReadPre();
    if (fexist(path) == 0) {
        TEA_AudioSeqStop();
        TEA_AudioSeqFree();
        TEA_BGMNO = -1;
        TeaSeqPlayFlag = 0;
        return;
    }
    sReadPre();
    sprintf(path, sBgmPathFormat, TeaSound[no].name);
    TEA_BgmSfxLoad(path, TeaSound[no].group);
    OSReport(s1982);
    sReadPre();
    sprintf(path, sBgmSonPathFormat, TeaSound[no].name);
    TEA_SeqPlay(TeaSound[no].group, TeaSound[no].song, path);
    OSReport(s1983, path);
}
