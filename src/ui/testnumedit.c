#include "game_pad.h"
#include "gx_tev.h"

extern PadState *sPad3;
extern s32 sprintf(char *buffer, const char *format, ...);
extern void sPadAll(void);
extern s32 Tea_atoi(char *text);
extern void debugmenudraw(void);
extern void sPutString2(char *text, s32 x, s32 y, s32 z, GXColor color, GXColor shadow, s32 alpha,
                        s32 flags);

s32 testnumedit(s32 x, s32 y, s32 value)
{
    char text[20];
    s32 frame_padding[2];
    s32 cursor;
    s32 number;
    s8 digit;

    number = value;
    cursor = 0;
    while (1) {
        sprintf(text, "%06d", number);
        sPadAll();
        if (sPad3->pressed_dpad_left != 0)
            cursor--;
        if (sPad3->pressed_dpad_right != 0)
            cursor++;
        if (cursor > 5)
            cursor = 0;
        if (cursor < 0)
            cursor = 5;
        digit = text[cursor] - '0';
        if (sPad3->pressed_dpad_up != 0)
            digit++;
        if (sPad3->pressed_dpad_down != 0)
            digit--;
        if (digit < 1)
            digit = 10;
        if (digit > 10)
            digit = 1;
        text[cursor] = digit + '0';
        number = Tea_atoi(text);
        if (sPad3->pressed_b != 0)
            return value;
        if (sPad3->pressed_a != 0)
            return number;
        sprintf(text, "%06d", number);
        sPutString2(text, x, y, -450, (GXColor){ 255, 255, 255, 255 }, (GXColor){ 255, 255, 255, 0 }, 0, 2);
        sPutString2("\x81\xab", x + cursor * 13 - 4, y + 20, -450, (GXColor){ 255, 255, 255, 255 },
                    (GXColor){ 0, 255, 255, 0 }, 0, 2);
        debugmenudraw();
    }
}
