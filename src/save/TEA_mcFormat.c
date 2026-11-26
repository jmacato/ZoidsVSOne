#pragma readonly_strings on
#include "card.h"

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
static const char s715[] = "MemCard%d mcerrIO\203G\203\211\201[ \n";
static const char s716[] = "MemCard%d mcerr\203\201\203\202\203\212\203J\201[\203h\202\305\202\310\202\242 \n";
static const char s717[] = "MemCard%d mcerr\224j\211\363\n";
static const char s741[] = "MemCard freesize=%d freedir=%d \n";
static const char s743[] = "NEED FILENUM";
static const char s753[] = "\tLeave StartCheck\n";
static const char s763[] = "\tUnMount \216\270\224s\n";

extern u32 __OSBusClock : 0x800000F8;
extern s32 MemCardStatus[2];
extern s32 MemCardError;
extern s32 MemcardNowSlot;
extern s64 OSGetTime(void);
extern s32 CARDFormatAsync(s32 channel, void *callback);
extern void OSReport(const char *format, ...);
extern s32 TEA_mcError(s32 slot, s32 result);

s32 TEA_mcFormat(s32 slot)
{
    s32 result;
    s64 limit = OSGetTime() / (__OSBusClock / 4) + 60;

    MemcardNowSlot = slot;
    OSReport("CARD Format :");
    result = CARDFormatAsync(slot, 0);
    if (result < 0) {
        OSReport("\t\217\211\212\372\211\273\216\270\224s 1st . (%d)\n", result);
        return 0;
    }
    while ((result = CARDGetResultCode(slot)) == CARD_RESULT_BUSY) {
        if (OSGetTime() / (__OSBusClock / 4) > limit) {
            MemCardStatus[slot] = CARD_RESULT_FATAL_ERROR;
            return 0;
        }
    }
    if (result < 0) {
        TEA_mcError(slot, result);
        OSReport("\t\217\211\212\372\211\273\216\270\224s 2nd . (%d)\n", result);
        return 0;
    }
    OSReport("\t\217\211\212\372\211\273 done. (%d)\n", result);
    MemCardError = 0;
    return 1;
}
