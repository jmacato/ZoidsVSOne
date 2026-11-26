#pragma readonly_strings on
#include "game_pad.h"
#include "menu_message.h"

extern s32 menudispyesnopoint;
extern s32 menudispyesnoflag;
extern PadState *sPad1;
extern char menuyesnoshopmsg[];
extern s32 sprintf(char *buffer, const char *format, ...);
extern char *GetMenuMsgAdr(s16 message);
extern s32 menuYesNo(s32 selected, const char *first, const char *second);
extern void sPadAll(void);
extern void SeRet(void);
extern void menu_sDispBattleShop(void);

void menufncShopyesno(s32 buy)
{
    char text[200];

    menudispyesnoflag = 1;
    do {
        sPadAll();
        if (buy != 0)
            sprintf(text, "%s\n%s", menuyesnoshopmsg, GetMenuMsgAdr(MENU_MSG_BUY_PROMPT));
        else
            sprintf(text, "%s\n%s", menuyesnoshopmsg, GetMenuMsgAdr(MENU_MSG_SELL_PROMPT));
        menudispyesnopoint = menuYesNo(menudispyesnopoint, text, "");
        menu_sDispBattleShop();
    } while (sPad1->pressed_a == 0);
    SeRet();
    menudispyesnoflag = 0;
}
