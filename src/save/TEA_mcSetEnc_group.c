#pragma readonly_strings on
#include "game_pad.h"
#include "menu_message.h"

extern s32 menudispyesnopoint;
extern s32 menudispyesnoflag;
extern s32 MemCardError;
extern s32 MemcardNowSlot;
extern PadState *sPad1;
extern s64 OSGetTime(void);
extern void clrYesNoMsg(void);
extern char *GetMenuMsgAdr(s16 message);
extern s32 menuYesNo(s32 selected, const char *first, const char *second);
extern void menu_sDispStartYesNo(void);
extern void OSReport(const char *format, ...);
extern void sPadAll(void);
extern void SeRet(void);
extern s32 TEA_mcChkSlot(s32 channel);
extern s32 TEA_mcFormat(s32 channel);

s32 TEA_mcBadEncFormatEnc(s32 slot)
{
    s64 time = OSGetTime();

    menudispyesnopoint = 1;
    clrYesNoMsg();
    menudispyesnoflag = 1;
    do {
        sPadAll();
        menu_sDispStartYesNo();
        if (TEA_mcChkSlot(slot) == 0) {
            clrYesNoMsg();
            return 0;
        }
        menudispyesnopoint = menuYesNo(menudispyesnopoint, "", GetMenuMsgAdr(MENU_MSG_FORMAT_PROMPT_A));
    } while (sPad1->pressed_a == 0);
    SeRet();
    if (menudispyesnopoint == 1) {
        menudispyesnopoint = 1;
        clrYesNoMsg();
        menudispyesnoflag = 1;
        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MENU_MSG_FORMATTING), "UN USE");
        menu_sDispStartYesNo();
        if (TEA_mcFormat(slot) == 1) {
            menudispyesnoflag = 0;
            OSReport("MemCard FormatOk \n");
            clrYesNoMsg();
            return 1;
        }
        menudispyesnoflag = 0;
    } else {
        menudispyesnoflag = 0;
        clrYesNoMsg();
        return 0;
    }
    return 0;
}

s32 TEA_mcSetEnc(s32 slot)
{
    s64 time = OSGetTime();

    menudispyesnopoint = 1;
    clrYesNoMsg();
    menudispyesnoflag = 1;
    if (MemCardError == 1) {
        return 0;
    }
    do {
        sPadAll();
        menu_sDispStartYesNo();
        if (TEA_mcChkSlot(slot) == 0) {
            clrYesNoMsg();
            return 0;
        }
        menudispyesnopoint = menuYesNo(menudispyesnopoint, "", GetMenuMsgAdr(MemcardNowSlot + MENU_MSG_FORMAT_PROMPT_A));
    } while (sPad1->pressed_a == 0);
    SeRet();
    menudispyesnoflag = 0;
    if (menudispyesnopoint == 1) {
        if (TEA_mcFormat(slot) == 1) {
            OSReport("MemCard FormatOk \n");
            clrYesNoMsg();
            return 0;
        }
    }
    OSReport("MemCard \216g\227p\202\305\202\253\202\310\202\242\203J\201[\203h \n");
    menudispyesnopoint = 1;
    clrYesNoMsg();
    menudispyesnoflag = 1;
    do {
        sPadAll();
        menu_sDispStartYesNo();
        menudispyesnopoint = menuYesNo(menudispyesnopoint, GetMenuMsgAdr(MemcardNowSlot + MENU_MSG_UNUSABLE_A), "UN USE");
    } while (sPad1->pressed_a == 0);
    SeRet();
    menudispyesnoflag = 0;
    clrYesNoMsg();
    return 0;
}
