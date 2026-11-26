#include "missile.h"

extern s32 sprintf(char *buffer, const char *format, ...);
extern s32 fexist(char *path);
extern void ZeroMemory(void *dst, u32 size);

void sEffectPrologue(void)
{
    char path[256];
    s32 i;
    Effect *effect;

    for (i = 0; i < 110; i++) {
        sprintf(path, "effect/%s.dat", Tea_effectdat[i].name);
        efctFile[i] = 0;
        if (fexist(path) == 0)
            continue;
        efctFile[i] = LoadArc2(path);
        if (efctFile[i] != 0 && efctFile[i]->model_data != 0 && efctFile[i]->models == 0) {
            PurgeArc2(efctFile[i]);
            efctFile[i] = 0;
        }
    }
    for (i = 0; i < 100; i++) {
        effect = &sEffect[i];
        ZeroMemory(effect, sizeof(Effect));
        effect->root = 0;
    }
    sEfctLight = LoadArc2("effect/light.dat");
}
