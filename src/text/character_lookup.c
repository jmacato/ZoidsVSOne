#include "game_text.h"

#pragma auto_inline off
s32 getAscNum(char *text)
{
    s8 first = text[0], second = text[1];
    u32 lead = first & 0xE0;
    s8 *characters;
    s32 index;

    if (lead != 0xE0 && lead != 0x80)
        return getAscNum1(first);
    characters = asc00;
    if (first == 0)
        return -1;
    if (second == 0)
        return -1;
    index = 0;
    while (*characters) {
        if (first == characters[0] && second == characters[1])
            return index;
        characters += 2;
        index++;
    }
    return -1;
}

f32 getAscH_sp(s32 font, char *text, f32 spacing)
{
    f32 *widths;
    f32 width;
    s32 index;

    if (font >= ASC_FONT_COUNT)
        return 0.0F;
    widths = ascH[font];
    width = 0.0F;
    while (*text) {
        index = getAscNum(text);
        if (index >= ASC_GLYPH_MAX)
            index = -1;
        if (index != -1) {
            width += widths[index];
            if (isKanji(*text))
                text += 2;
            else
                text++;
        } else {
            if (isKanji(*text))
                text += 2;
            else
                text++;
            continue;
        }
        width += spacing;
    }
    return width;
}
