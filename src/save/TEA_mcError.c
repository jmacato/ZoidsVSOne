#pragma readonly_strings on
#include "card.h"
#include "menu_message.h"

static const char s382[] = "shadow.h";
static const char s395[] = "shadow alloc error\n";
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

extern s32 MemCardOn[2];
extern s32 MemCardError;
extern void OSReport(const char *format, ...);
extern void TEA_mcMsgNoChkSlot(s32 slot, s16 message);

s32 TEA_mcError(s32 slot, s32 result)
{
    switch (result) {
    case CARD_RESULT_IOERROR:
        OSReport("MemCard%d mcerrIO\203G\203\211\201[ \n", slot);
        MemCardError = 1;
        TEA_mcMsgNoChkSlot(slot, MENU_MSG_CARD_BROKEN_A);
        return 0;
    case CARD_RESULT_WRONGDEVICE:
        OSReport("MemCard%d mcerr\203\201\203\202\203\212\203J\201[\203h\202\305\202\310\202\242 \n", slot);
        MemCardError = 1;
        TEA_mcMsgNoChkSlot(slot, MENU_MSG_WRONG_DEVICE_A);
        return 0;
    case CARD_RESULT_BROKEN:
        OSReport("MemCard%d mcerr\224j\211\363\n", slot);
        MemCardError = 1;
        TEA_mcMsgNoChkSlot(slot, MENU_MSG_DATA_BROKEN);
        return 0;
    case CARD_RESULT_NOCARD:
        MemCardOn[slot] = 0;
        break;
    }
    return 1;
}
