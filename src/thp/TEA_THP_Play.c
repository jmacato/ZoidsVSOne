#pragma readonly_strings on
#include "game_pad.h"
#include "video.h"
#include "thp_player.h"

extern GXRenderModeObj GXNtsc480IntDf;
extern s32 __OSCurrHeap;
extern PadState *sPad1;
extern void OSReport(const char *format, ...);
extern void GXSetDispCopyGamma(s32 gamma);
extern void GXSetCopyFilter(u8 aa, void *samples, u8 vertical, void *filter);
extern void GXSetCopyClear(GXColor color, u32 depth);
extern s32 THPPlayerInit(void);
extern void AudioInit(void);
extern void chkVS(void);
extern void sPadAll(void);
extern void VIWaitForRetrace(void);
extern void THPPlayerDrawDone(void);
extern s32 THPPlayerGetState(void);
extern void THPPlayerStop(void);
extern s32 THPPlayerClose(void);
extern void OSFreeToHeap(s32 heap, void *ptr);
extern void *OSAllocFromHeap(s32 heap, u32 size);
extern char *strcpy(char *dst, const char *src);
extern s32 THPPlayerOpen(char *name, s32 onMemory);
extern s32 THPPlayerGetVideoInfo(THPVideoInfo *info);
extern u32 THPPlayerCalcNeedMemory(void);
extern s32 THPPlayerSetBuffer(void *buffer);
extern s32 THPPlayerPrepare(s32 frame, s32 loop);
extern s32 THPPlayerPlay(void);
extern void THPPlayerQuit(void);
extern void THP_AudioEnd(void);

void TEA_THP_Play(char *filename, s32 loop)
{
    GXColor clear;
    THPVideoInfo info;
    char name[56];
    u32 x;
    u32 y;
    void *buffer;
    GXRenderModeObj *rmode;
    s32 loopMode;
    s32 open;
    s32 playing;
    s32 onMemory;
    s32 first;
    s32 cancel;
    s32 state;
    u32 size;

    loopMode = 0;
    first = 1;
    cancel = 0;
    clear.r = 0;
    clear.g = 0;
    clear.b = 0;
    clear.a = 255;
    OSReport("PlayMovieInit:THP\n");
    GXSetDispCopyGamma(0);
    GXSetCopyFilter(0, 0, 0, 0);
    GXSetCopyClear(clear, 0xFFFFFF);
    rmode = &GXNtsc480IntDf;
    THPPlayerInit();
    AudioInit();
    open = 0;
    playing = 0;
    onMemory = 0;
    chkVS();
    for (;;) {
        sPadAll();
        if (sReadPre() != 0)
            cancel = 1;
        HSD_StartRender(HSD_RP_SCREEN);
        if (playing != 0)
            THPPlayerDrawCurrentFrame(rmode, x, y, info.xSize, info.ySize);
        THPPlayerDrawDone();
        HSD_EndRender();
        HSD_VICopyXFB(HSD_RP_SCREEN);
        HSD_VISetXFBDrawDone();
        VIWaitForRetrace();
        state = THPPlayerGetState();
        if (state == THP_PLAYER_ERROR || state == THP_PLAYER_PLAYED) {
            THPPlayerStop();
            THPPlayerClose();
            OSFreeToHeap(__OSCurrHeap, buffer);
            OSReport("PlayMovieEnd:THP\n");
            break;
        }
        if (first == 1) {
            strcpy(name, filename);
            if (loop == 1)
                loopMode = THP_PLAY_LOOP;
            else
                loopMode = 0;
            open = 1;
            onMemory = 0;
            first = 0;
        }
        if (sPad1->start != 0 || sPad1->pressed_a != 0 || sPad1->pressed_b != 0 || cancel != 0) {
            if (playing == 0)
                break;
            THPPlayerStop();
            THPPlayerClose();
            OSFreeToHeap(__OSCurrHeap, buffer);
            OSReport("PlayMovieStop:THP\n");
            break;
        }
        if (open != 0 && playing != 0) {
            THPPlayerStop();
            THPPlayerClose();
            OSFreeToHeap(__OSCurrHeap, buffer);
            playing = 0;
        }
        if (open == 0)
            continue;
        if (playing != 0)
            continue;
        if (sReadPre() != 0)
            cancel = 1;
        if (THPPlayerOpen(name, onMemory) == 0)
            return;
        OSReport("file(%s) \n", name);
        THPPlayerGetVideoInfo(&info);
        x = (rmode->fbWidth - info.xSize) / 2;
        y = (rmode->efbHeight - info.ySize) / 2;
        size = THPPlayerCalcNeedMemory();
        buffer = OSAllocFromHeap(__OSCurrHeap, size);
        if (buffer == 0)
            return;
        THPPlayerSetBuffer(buffer);
        if (THPPlayerPrepare(0, loopMode) == 0)
            return;
        THPPlayerPlay();
        open = 0;
        playing = 1;
    }
    OSReport("PlayMovieQuit:THP\n");
    THPPlayerQuit();
    THP_AudioEnd();
    VIWaitForRetrace();
}
