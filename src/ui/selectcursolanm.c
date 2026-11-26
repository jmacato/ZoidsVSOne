#include "model_archive.h"

extern ModelArchive *menu1p;
extern s8 menucuranm;
extern s32 jobjAnim(HSD_JObj *joint);

void selectcursolanm(s16 model)
{
    if (menucuranm == 1) {
        SetAnimArc2(menu1p, model, 0);
        menucuranm = 2;
    }
    if (menucuranm == 2) {
        if (jobjAnim(menu1p->models[model]) != 0)
            menucuranm = 3;
    } else if (menucuranm == 3) {
        SetAnimArc2(menu1p, model, 0);
        jobjAnim(menu1p->models[model]);
        menucuranm = 2;
    }
}
