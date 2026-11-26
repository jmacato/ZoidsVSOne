/* Reference:
 * https://github.com/doldecomp/melee/blob/master/src/sysdolphin/baselib/initialize.c.
 */
#include "initialize.h"
#include "objalloc.h"
#include "mwcc_stdarg.h"
#include "gx_pixel.h"
extern void OSReport(const char *format, ...);
typedef struct HSD_MemReport {
    u32 total;
    u32 system;
    u32 xfb;
    u32 gxfifo;
    u32 heap;
} HSD_MemReport;
typedef struct GXLightObj {
    u32 words[16];
} GXLightObj;
struct GXFifoObj;
extern GXRenderModeObj GXNtsc480IntDf;
struct HSD_VIDataState;
extern struct HSD_VIDataState HSD_VIData;
extern void HSD_VIInit(HSD_VIStatus *status, void *first, void *second, void *third);
extern void HSD_IDSetup(void);
extern void VIWaitForRetrace(void);
extern void DVDInit(void);
extern void *OSAllocFromArenaLo(u32 size, u32 alignment);
extern void *OSGetArenaLo(void);
extern void *OSGetArenaHi(void);
extern u32 OSGetPhysicalMemSize(void);
extern s32 OSCreateHeap(void *lo, void *hi);
extern s32 OSSetCurrentHeap(s32 heap);
extern void OSDestroyHeap(s32 heap);
extern void OSSetArenaLo(void *lo);
extern void HSD_ObjSetHeap(u32 size, void *heap);
extern void HSD_ObjGetHeap(u32 *size, void **heap);
extern struct GXFifoObj *GXInit(void *fifo, u32 size);
extern void HSD_Panic(const char *file, u32 line, const char *message);
extern void GXInitLightPos(GXLightObj *light, f32 x, f32 y, f32 z);
extern void GXInitLightDir(GXLightObj *light, f32 x, f32 y, f32 z);
extern void GXInitLightAttn(GXLightObj *light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1,
                            f32 k2);
extern void GXInitLightColor(GXLightObj *light, GXColor color);
extern void GXLoadLightObjImm(GXLightObj *light, int id);
extern int HSD_Index2LightID(int index);
extern void HSD_StateInvalidate(u32 flags);
extern void GXSetFieldMode(u8 field, u8 half_aspect);
extern void GXInvalidateVtxCache(void);
extern void GXInvalidateTexAll(void);
extern void hsdForgetClassLibrary(const char *library);
extern void _HSD_AObjForgetMemory(void *lo, void *hi);
extern void _HSD_DispForgetMemory(void *lo, void *hi);
extern void _HSD_IDForgetMemory(void *lo, void *hi);
extern void _HSD_ObjAllocForgetMemory(void *lo, void *hi);
extern void _HSD_RandForgetMemory(void *lo, void *hi);
extern void _HSD_RObjForgetMemory(void *lo, void *hi);
extern void HSD_ListInitAllocData(void);
extern void HSD_AObjInitAllocData(void);
extern void HSD_FObjInitAllocData(void);
extern void HSD_IDInitAllocData(void);
extern void HSD_VecInitAllocData(void);
extern void HSD_MtxInitAllocData(void);
extern void HSD_RObjInitAllocData(void);
extern void HSD_RenderInitAllocData(void);
extern void HSD_ShadowInitAllocData(void);
extern void HSD_ZListInitAllocData(void);
static void *FrameBuffer[3];
static HSD_MemReport memReport;
static volatile s32 hsd_heap = -1;
static void *hsd_heap_arena_lo;
static void *hsd_heap_arena_hi;
static void *hsd_heap_next_arena_lo;
static void *hsd_heap_next_arena_hi;
static GXRenderModeObj *rmode = &GXNtsc480IntDf;
static int current_render_pass;
static struct GXFifoObj *DefaultFifoObj;
static int current_pix_fmt;
static int current_z_fmt = GX_ZC_MID;
static s32 init_done;
static u32 iparam_fifo_size = 256 * 1024;
static int iparam_xfb_max_num = 2;
static int iparam_heap_size;
int need_invalidate;
void HSD_OSInit(void);
void HSD_GXInit(void);
void HSD_DVDInit(void);
void HSD_ObjInit(void);
void HSD_InitComponent(void)
{
    HSD_OSInit();
    {
        HSD_VIStatus vi_status;
        GXColor black = {0, 0, 0, 0};
        vi_status.rmode = *rmode;
        vi_status.black = 1;
        vi_status.vf = 1;
        vi_status.gamma = 0;
        vi_status.clear_clr = black;
        vi_status.clear_z = 0xFFFFFF;
        vi_status.update_clr = 1;
        vi_status.update_alpha = 1;
        vi_status.update_z = 1;
        HSD_VIInit(&vi_status, FrameBuffer[0], FrameBuffer[1], FrameBuffer[2]);
    }
    HSD_GXInit();
    HSD_DVDInit();
    HSD_IDSetup();
    VIWaitForRetrace();
    HSD_ObjInit();
    init_done = 1;
}
void **HSD_AllocateXFB(s32 count, GXRenderModeObj *mode);
void *HSD_AllocateFIFO(u32 size);
void HSD_Init(void)
{
    void *fifo;
    struct GXFifoObj *object;
    DVDInit();
    HSD_AllocateXFB(iparam_xfb_max_num, rmode);
    fifo = HSD_AllocateFIFO(iparam_fifo_size);
    object = GXInit(fifo, iparam_fifo_size);
    memReport.gxfifo = iparam_fifo_size;
    DefaultFifoObj = object;
    HSD_InitComponent();
}
void HSD_DVDInit(void)
{
}
void **HSD_AllocateXFB(s32 count, GXRenderModeObj *mode)
{
    s32 i;
    u32 size;
    if (mode == 0)
        return 0;
    size = (u16)((mode->fbWidth + 0xF) & ~0xF) * mode->xfbHeight * 2;
    memReport.xfb = size * count;
    for (i = 0; i < count; i++) {
        if ((FrameBuffer[i] = OSAllocFromArenaLo(size, 32)) == 0)
            HSD_Panic("initialize.c", 232, "No memory space remains for XFB.\n");
    }
    for (i = count; i < 3; i++)
        FrameBuffer[i] = 0;
    return FrameBuffer;
}
void *HSD_AllocateFIFO(u32 size)
{
    void *fifo = OSAllocFromArenaLo(size, 32);
    if (fifo == 0)
        HSD_Panic("initialize.c", 251, "no space remains for gx fifo.\n");
    return fifo;
}
#pragma push
#pragma force_active on
/* The release retains these unused SDK diagnostic strings. */
static char missing_argument[] = "missing argument.\n";
#pragma pop

void HSD_GXInit(void)
{
    GXLightObj light;
    int i;
    static GXColor black = {0};
    GXInitLightPos(&light, 1, 0, 0);
    GXInitLightDir(&light, 1, 0, 0);
    GXInitLightAttn(&light, 1, 0, 0, 1, 0, 0);
    GXInitLightColor(&light, black);
    for (i = 0; i < 8; i++)
        GXLoadLightObjImm(&light, HSD_Index2LightID(i));
    HSD_StateInvalidate(-1);
}
void HSD_OSInit(void)
{
    u32 lo = (u32)OSGetArenaLo();
    u32 hi = (u32)OSGetArenaHi();
    memReport.total = OSGetPhysicalMemSize();
    memReport.system = memReport.total - (u32)OSGetArenaHi() + (u32)OSGetArenaLo() -
                       memReport.xfb - memReport.gxfifo;
    if (hsd_heap_next_arena_lo != 0 && hsd_heap_next_arena_hi != 0) {
        hsd_heap_arena_lo = hsd_heap_next_arena_lo;
        hsd_heap_arena_hi = hsd_heap_next_arena_hi;
        hsd_heap_next_arena_lo = 0;
        hsd_heap_next_arena_hi = 0;
        hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
        OSSetCurrentHeap(hsd_heap);
        memReport.heap = (u32)hsd_heap_arena_hi - (u32)hsd_heap_arena_lo;
        HSD_ObjSetHeap(memReport.heap, 0);
    } else {
        lo = ((u32)OSGetArenaLo() + 31) & ~31;
        hi = (u32)OSGetArenaHi();
        hsd_heap_arena_lo = (void *)lo;
        if (iparam_heap_size > 0) {
            hsd_heap_arena_hi = (void *)(lo + iparam_heap_size);
            if ((u32)hsd_heap_arena_hi > hi)
                hsd_heap_arena_hi = (void *)hi;
            hsd_heap_arena_hi = (void *)((u32)hsd_heap_arena_hi & ~31);
        } else
            hsd_heap_arena_hi = (void *)(hi & ~31);
        hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
        OSSetCurrentHeap(hsd_heap);
        memReport.heap = (u32)hsd_heap_arena_hi - (u32)hsd_heap_arena_lo;
        HSD_ObjSetHeap(memReport.heap, 0);
        OSSetArenaLo(hsd_heap_arena_hi);
    }
}
s32 HSD_GetHeap(void)
{
    return hsd_heap;
}
void HSD_GetCurrentArena(void **lo, void **hi)
{
    if (lo != 0)
        *lo = hsd_heap_arena_lo;
    if (hi != 0)
        *hi = hsd_heap_arena_hi;
}
void HSD_ClearHeap(void)
{
    int i;
    void (*cb_table[])(void *lo, void *hi) = {_HSD_AObjForgetMemory,
                                              _HSD_DispForgetMemory,
                                              _HSD_IDForgetMemory,
                                              _HSD_ObjAllocForgetMemory,
                                              _HSD_RandForgetMemory,
                                              _HSD_RObjForgetMemory,
                                              0};
    void *heap;
    hsdForgetClassLibrary("sysdolphin_base_library");
    HSD_ObjInit();
    for (i = 0; cb_table[i] != 0; i++)
        cb_table[i](hsd_heap_arena_lo, hsd_heap_arena_hi);
    OSDestroyHeap(hsd_heap);
    if (hsd_heap_next_arena_lo != 0 && hsd_heap_next_arena_hi != 0) {
        hsd_heap_arena_lo = hsd_heap_next_arena_lo;
        hsd_heap_arena_hi = hsd_heap_next_arena_hi;
        hsd_heap_next_arena_lo = 0;
        hsd_heap_next_arena_hi = 0;
    }
    hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
    OSSetCurrentHeap(hsd_heap);
    memReport.heap = (u32)hsd_heap_arena_hi - (u32)hsd_heap_arena_lo;
    HSD_ObjGetHeap(0, &heap);
    if (heap == 0)
        HSD_ObjSetHeap(memReport.heap, 0);
}
#pragma push
#pragma force_active on
/* The release retains this unused pixel-format assertion. */
static char pixel_format_condition[] = "pix_fmt != GX_PF_RGB565_Z16";
#pragma pop

int HSD_GetCurrentRenderPass(void)
{
    return current_render_pass;
}
void HSD_StartRender(int pass)
{
    GXRenderModeObj *mode = (GXRenderModeObj *)&HSD_VIData;
    current_render_pass = pass;
    if (mode->aa)
        GXSetPixelFmt(GX_PF_RGB565_Z16, current_z_fmt);
    else
        GXSetPixelFmt(current_pix_fmt, GX_ZC_LINEAR);
    GXSetFieldMode(mode->field_rendering, mode->xfbHeight < mode->viHeight);
    if (need_invalidate) {
        if (need_invalidate & 1)
            GXInvalidateVtxCache();
        if (need_invalidate & 2)
            GXInvalidateTexAll();
        need_invalidate = 0;
    }
}
void HSD_EndRender(void)
{
    /* The release retains only the render-pass comparison. */
    if (current_render_pass == 3)
        current_render_pass == 0;
}
void _HSD_NeedCacheInvalidate(int flags)
{
    need_invalidate |= flags;
}
void HSD_ObjInit(void)
{
    HSD_ListInitAllocData();
    HSD_AObjInitAllocData();
    HSD_FObjInitAllocData();
    HSD_IDInitAllocData();
    HSD_VecInitAllocData();
    HSD_MtxInitAllocData();
    HSD_RObjInitAllocData();
    HSD_RenderInitAllocData();
    HSD_ShadowInitAllocData();
    HSD_ZListInitAllocData();
}

extern HSD_ObjAllocData *HSD_AObjGetAllocData(void);
extern HSD_ObjAllocData *HSD_FObjGetAllocData(void);
extern HSD_ObjAllocData *HSD_IDGetAllocData(void);
extern HSD_ObjAllocData *HSD_SListGetAllocData(void);
extern HSD_ObjAllocData *HSD_DListGetAllocData(void);
extern HSD_ObjAllocData *HSD_VecGetAllocData(void);
extern HSD_ObjAllocData *HSD_MtxGetAllocData(void);
extern HSD_ObjAllocData *HSD_RObjGetAllocData(void);
extern HSD_ObjAllocData *HSD_RvalueObjGetAllocData(void);
extern HSD_ObjAllocData *HSD_ShadowGetAllocData(void);
extern HSD_ObjAllocData *HSD_RenderGetAllocData(void);
extern HSD_ObjAllocData *HSD_ChanGetAllocData(void);
extern HSD_ObjAllocData *HSD_TevRegGetAllocData(void);
static inline u32 HSD_ObjAllocGetUsing(HSD_ObjAllocData *data)
{
    if (data == 0)
        __assert("objalloc.h", 205, "data");
    return data->used;
}
static inline u32 HSD_ObjAllocGetFreed(HSD_ObjAllocData *data)
{
    if (data == 0)
        __assert("objalloc.h", 221, "data");
    return data->free;
}
static inline u32 HSD_ObjAllocGetPeak(HSD_ObjAllocData *data)
{
    if (data == 0)
        __assert("objalloc.h", 237, "data");
    return data->peak;
}
struct HSD_ObjDumpStat_types {
    HSD_ObjAllocData *(*func)(void);
    char *label;
};
void HSD_ObjDumpStat(void)
{
    struct HSD_ObjDumpStat_types types[] = {
        {HSD_AObjGetAllocData, "aobj"},      {HSD_FObjGetAllocData, "fobj"},
        {HSD_IDGetAllocData, "id"},          {HSD_SListGetAllocData, "slist"},
        {HSD_DListGetAllocData, "dlist"},    {HSD_VecGetAllocData, "vec"},
        {HSD_MtxGetAllocData, "mtx"},        {HSD_RObjGetAllocData, "robj"},
        {HSD_RvalueObjGetAllocData, "rval"}, {HSD_ShadowGetAllocData, "shadow"},
        {HSD_RenderGetAllocData, "render"},  {HSD_ChanGetAllocData, "chan"},
        {HSD_TevRegGetAllocData, "tevreg"},  {0, 0}};
    u32 used, peak, freed;
    struct HSD_ObjDumpStat_types *entry;

    for (entry = types; entry->label; entry++) {
        peak = HSD_ObjAllocGetPeak(entry->func());
        freed = HSD_ObjAllocGetFreed(entry->func());
        used = HSD_ObjAllocGetUsing(entry->func());
        OSReport("objalloc: %s\tusing %d\tfreed %d\tpeak %d\n", entry->label, used,
                 freed, peak);
    }
}

int HSD_SetInitParameter(HSD_InitParam param, ...)
{
    va_list ap;
    int ok = 0;
    static s32 shown;
    if (init_done) {
        if (!shown) {
            OSReport("init parameter should be set before invoking HSD_Init().\n");
            shown = 1;
        }
        return 0;
    }
    va_start(ap, param);
    switch (param) {
    case HSD_INIT_FIFO_SIZE: {
        u32 size = va_arg(ap, u32);
        if (size > 0) {
            iparam_fifo_size = size;
            ok = 1;
        }
        break;
    }
    case HSD_INIT_XFB_MAX_NUM: {
        u32 count = va_arg(ap, u32);
        if (count > 0) {
            iparam_xfb_max_num = count;
            ok = 1;
        }
        break;
    }
    case HSD_INIT_HEAP_SIZE: {
        u32 size = va_arg(ap, u32);
        if (size < OSGetPhysicalMemSize()) {
            iparam_heap_size = size;
            ok = 1;
        }
        break;
    }
    case HSD_INIT_HEAP_ARENA: {
        void *lo = va_arg(ap, void *);
        void *hi = va_arg(ap, void *);
        hsd_heap_next_arena_lo = lo;
        hsd_heap_next_arena_hi = hi;
        ok = 1;
        break;
    }
    case HSD_INIT_RENDER_MODE_OBJ: {
        GXRenderModeObj *mode = va_arg(ap, GXRenderModeObj *);
        if (mode != 0) {
            rmode = mode;
            ok = 1;
        }
        break;
    }
    case HSD_INIT_HEAP_MAX_NUM:
        OSReport("ERROR in HSD_SetInitParameter():\n");
        OSReport("  HSD_INIT_HEAP_MAX_NUM is obsolete since 1.3.0.0. \n");
        if (va_arg(ap, int) == 0)
            ok = 1;
        break;
    case HSD_INIT_AUDIO_HEAP_SIZE:
        OSReport("ERROR in HSD_SetInitParameter():\n");
        OSReport("  HSD_INIT_AUDIO_HEAP_SIZE is obsolete since 1.3.0.0. \n");
        break;
    }
    va_end(ap);
    return ok;
}
