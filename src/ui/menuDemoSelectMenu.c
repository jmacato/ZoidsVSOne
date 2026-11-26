#include "game_pad.h"

extern PadState *sPad1;
extern void sPadAll(void);
extern void SeSelectB(void);

s32 menuDemoSelectMenu(s32 selected)
{
    sPadAll();
    if (sPad1->pressed_dpad_up != 0 || sPad1->pressed_stick_up != 0) {
        SeSelectB();
        return 0;
    }
    if (sPad1->pressed_dpad_down != 0 || sPad1->pressed_stick_down != 0) {
        SeSelectB();
        return 1;
    }
    return selected;
}
