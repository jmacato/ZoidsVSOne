#include "types.h"
#include "menu_message.h"

extern s16 menusaveloadslot;
extern s32 menu_SlotOn;
extern s32 MemCardError;
extern void OSReport(const char *fmt, ...);
extern void ttlMenuLoadYesNo(void);
extern void ttlMenuSaveDataSetFileName(s32 slot, s32 mode);
extern s32 TEA_mcChkSlot(s32 channel);
extern s32 TEA_mcChkSector(s32 channel);
extern s32 TEA_mcChkRest(s32 channel);
extern s32 TEA_mcChkEncoding(s32 channel);
extern s32 TEA_mcFormat(s32 channel);
extern void TEA_mcMsgNoChkSlot(s32 channel, s32 message);
extern s32 TEA_mcMsgYesNo(s32 channel, s32 message);
extern void TEA_mcMsgDisp(s32 channel, s32 message);
extern void clrYesNoMsg(void);

s32 TeaMemCardChk(void)
{
    s32 frame_padding[2];

    ttlMenuLoadYesNo();
    ttlMenuSaveDataSetFileName(-1, 0);
    menusaveloadslot = 0;
retry:
    menu_SlotOn = TEA_mcChkSlot(0);
    if (menu_SlotOn == 0) {
        TEA_mcMsgNoChkSlot(0, MENU_MSG_NO_CARD_A);
        return 0;
    }
    OSReport("SLOT \x82\xa0\x82\xe8 \n");
    if (TEA_mcChkSector(0) == 0) {
        TEA_mcMsgNoChkSlot(0, MENU_MSG_UNSUPPORTED_CARD);
        return 0;
    }
    OSReport("SLOT \x83Z\x83N\x83^\x83T\x83" "C\x83Y ok\n");
    if (TEA_mcChkRest(0) == 0) {
        if (TEA_mcMsgYesNo(0, MENU_MSG_FORMAT_PROMPT_A) != 0) {
            if (TEA_mcChkSlot(0) == 0)
                goto retry;
            TEA_mcMsgDisp(0, MENU_MSG_SAVING);
            TEA_mcFormat(0);
            if (MemCardError == 1) {
                TEA_mcMsgNoChkSlot(0, MENU_MSG_UNUSABLE_A);
                return 0;
            }
        } else {
            return 0;
        }
    }
    if (TEA_mcChkSlot(0) == 0)
        goto retry;
    if (TEA_mcChkEncoding(0) == 0) {
        if (TEA_mcMsgYesNo(0, MENU_MSG_FORMAT_PROMPT_A) != 0) {
            if (TEA_mcChkSlot(0) == 0)
                goto retry;
            TEA_mcMsgDisp(0, MENU_MSG_SAVING);
            TEA_mcFormat(0);
            if (MemCardError == 1) {
                TEA_mcMsgNoChkSlot(0, MENU_MSG_UNUSABLE_A);
                return 0;
            }
        } else {
            return 0;
        }
    }
    clrYesNoMsg();
    if (TEA_mcChkSlot(0) == 0)
        goto retry;
    return 1;
}
