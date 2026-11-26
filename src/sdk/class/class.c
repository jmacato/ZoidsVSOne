/* Based on
 * https://github.com/doldecomp/melee/blob/master/src/sysdolphin/baselib/class.c. */
#include "class_memory.h"
#define HSD_CLASS_INFO_INITIALIZED 1
void _hsdClassInfoInit(void);
HSD_ClassInfo hsdClass = {_hsdClassInfoInit};

/* Keep the original out-of-line class-info call. */
#pragma push
#pragma dont_inline on
void ClassInfoInit(HSD_ClassInfo *info)
{
    if ((info->head.flags & HSD_CLASS_INFO_INITIALIZED) == 0) {
        (*info->head.initialize_info)();
    }
}

#pragma pop

void hsdInitClassInfo(HSD_ClassInfo *class_info, HSD_ClassInfo *parent_info,
                      char *base_class_library, char *type, s32 info_size,
                      s32 class_size)
{
    class_info->head.flags = HSD_CLASS_INFO_INITIALIZED;
    class_info->head.library_name = base_class_library;
    class_info->head.class_name = type;
    class_info->head.object_size = (s16)class_size;
    class_info->head.info_size = (s16)info_size;
    class_info->head.parent = parent_info;
    class_info->head.child = 0;
    class_info->head.next = 0;
    class_info->head.live_count = 0;
    class_info->head.peak_count = 0;

    if (parent_info != 0) {
        if ((parent_info->head.flags & HSD_CLASS_INFO_INITIALIZED) == 0) {
            (*parent_info->head.initialize_info)();
        }
        if (class_info->head.object_size < parent_info->head.object_size) {
            __assert("class.c", 95,
                     "class_info->head.obj_size >= parent_info->head.obj_size");
        }
        if (class_info->head.info_size < parent_info->head.info_size) {
            __assert("class.c", 96,
                     "class_info->head.info_size >= parent_info->head.info_size");
        }
        memcpy(&class_info->allocate, &parent_info->allocate,
               parent_info->head.info_size - sizeof(HSD_ClassInfoHead));
        class_info->head.next = parent_info->head.child;
        parent_info->head.child = class_info;
    }
}

/* Retain the unused SDK diagnostics in the original data pool. */
#pragma push
#pragma force_active on
static char entry_missing[] = "entry %d <null>\n";
static char entry_range_missing[] = "entry %d - %d <null>\n";
static char entry_header[] = "entry %d(%d)";
static char entry_counts[] = "  nb_alloc %d nb_free %d\n";
#pragma pop

#define OSRoundDown32B(size) ((u32)(size) & ~31u)
#define OSRoundUp32B(size) (((u32)(size) + 31u) & ~31u)

HSD_MemoryEntry *GetMemoryEntry(s32 index)
{

    if (index < 0) {
        __assert("class.c", 174, "idx >= 0");
    }

    if (index >= nb_memory_list) {
        if (nb_memory_list == 0) {
            s32 new_count;

            for (new_count = 32; index >= new_count; new_count *= 2) {
            }
            memory_list = HSD_Alloc(new_count * sizeof(*memory_list));
            if (memory_list == 0) {
                return 0;
            }
            memset(memory_list, 0, new_count * sizeof(*memory_list));
            nb_memory_list = new_count;
        } else {
            HSD_MemoryEntry **old_entries;
            HSD_MemoryEntry **new_entries;
            s32 old_size, new_count;

            new_count = nb_memory_list * 2;
            while (index >= new_count) {
                new_count *= 2;
            }

            new_entries = HSD_Alloc(sizeof(*memory_list) * new_count);
            if (new_entries == 0) {
                return 0;
            }

            memcpy(new_entries, memory_list, sizeof(*memory_list) * nb_memory_list);
            memset(&new_entries[nb_memory_list], 0, 4 * (new_count - nb_memory_list));

            old_size = OSRoundDown32B(nb_memory_list * sizeof(*memory_list));
            old_entries = memory_list;
            nb_memory_list = new_count;
            memory_list = new_entries;

            hsdFreeMemPiece(old_entries, old_size);
            memory_list[OSRoundUp32B(old_size) / 32 - 1]->allocated += 1;
        }
    }

    {
        s32 neighbor;
        s32 found;
        HSD_MemoryEntry *entry;
        if (memory_list[index] == 0) {
            entry = HSD_Alloc(sizeof(HSD_MemoryEntry));
            if (entry == 0) {
                return 0;
            }
            memset(entry, 0, sizeof(HSD_MemoryEntry));
            entry->size = (index + 1) * 32;
            memory_list[index] = entry;

            found = 0;
            for (neighbor = index - 1; neighbor >= 0; --neighbor) {
                if (memory_list[neighbor] != 0) {
                    found = 1;
                    entry->next = memory_list[neighbor]->next;
                    memory_list[neighbor]->next = entry;
                    break;
                }
            }
            if (found == 0) {
                for (neighbor = index + 1; neighbor < nb_memory_list; neighbor++) {
                    if (memory_list[neighbor] != 0) {
                        entry->next = memory_list[neighbor];
                        break;
                    }
                }
            }
        }
        return memory_list[index];
    }
}

void *hsdAllocMemPiece(s32 size)
{
    HSD_FreeList *piece;
    HSD_FreeList *remainder;
    HSD_FreeList *remainder_piece;
    HSD_FreeList *split_piece;
    HSD_MemoryEntry *entry;
    HSD_MemoryEntry *remainder_entry;
    HSD_MemoryEntry *larger_entry;
    HSD_MemoryEntry *new_remainder_entry;
    s32 index;
    void *memory;

    index = (size + 0x1F) / 32 - 1;
    entry = GetMemoryEntry((size + 0x1F) / 32 - 1);
    if (entry == 0) {
        return 0;
    }
    if ((piece = entry->free_list)) {
        entry->free_list = piece->next;
        entry->freed -= 1;
        return piece;
    }
    larger_entry = entry->next;
    while (larger_entry != 0) {
        if (larger_entry->free_list != 0) {
            remainder_entry =
                GetMemoryEntry((s32)(larger_entry->size - entry->size + 0x1F) / 32 - 1);
            if (remainder_entry == 0) {
                return 0;
            }
            split_piece = larger_entry->free_list;
            larger_entry->free_list = larger_entry->free_list->next;
            larger_entry->freed -= 1;
            larger_entry->allocated -= 1;
            remainder_piece = (void *)((char *)split_piece + entry->size);
            remainder_piece->next = remainder_entry->free_list;
            remainder_entry->free_list = remainder_piece;
            remainder_entry->allocated += 1;
            remainder_entry->freed += 1;
            entry->allocated += 1;
            return split_piece;
        }
        larger_entry = larger_entry->next;
    }
    /* The duplicate assignment preserves the original compiler register layout. */
    index = index = (nb_memory_list - index) - 2;
    if (index >= 0) {
        new_remainder_entry = GetMemoryEntry(index);
        if (new_remainder_entry == 0) {
            return 0;
        }
    }
    memory = HSD_Alloc(nb_memory_list * 32);
    if (memory == 0) {
        return 0;
    }
    if (index >= 0) {
        remainder = (void *)((char *)memory + entry->size);
        remainder->next = new_remainder_entry->free_list;
        new_remainder_entry->free_list = remainder;
        new_remainder_entry->allocated += 1;
        new_remainder_entry->freed += 1;
    }
    entry->allocated += 1;
    return memory;
}

void hsdFreeMemPiece(void *memory, s32 size)
{
    HSD_MemoryEntry *entry;
    HSD_FreeList *piece = (HSD_FreeList *)memory;

    if (memory != 0) {
        entry = GetMemoryEntry((size + 31) / 32 - 1);
        piece->next = entry->free_list;
        entry->free_list = piece;
        entry->freed += 1;
    }
}

HSD_Class *_hsdClassAlloc(HSD_ClassInfo *info)
{
    HSD_Class *memory = hsdAllocMemPiece(info->head.object_size);
    if (memory != 0) {
        info->head.live_count += 1;
        if (info->head.live_count > info->head.peak_count) {
            info->head.peak_count = info->head.live_count;
        }
    }
    return memory;
}

int _hsdClassInit(HSD_Class *object)
{
    return 0;
}

void _hsdClassRelease(HSD_Class *object)
{
}

void _hsdClassDestroy(HSD_Class *object)
{
    HSD_ClassInfo *info = object->class_info;
    info->head.live_count -= 1;
    hsdFreeMemPiece(object, info->head.object_size);
}

void _hsdClassAmnesia(HSD_ClassInfo *info)
{
    info->head.live_count = 0;
    info->head.peak_count = 0;
    if (info == &hsdClass) {
        nb_memory_list = 0;
        memory_list = 0;
        info_hash = 0;
    }
}

void _hsdClassInfoInit(void)
{
    hsdInitClassInfo(&hsdClass, 0, "sysdolphin_base_library", "hsd_class",
                     sizeof(HSD_ClassInfo), sizeof(HSD_Class));
    hsdClass.allocate = _hsdClassAlloc;
    hsdClass.initialize = _hsdClassInit;
    hsdClass.release = _hsdClassRelease;
    hsdClass.destroy = _hsdClassDestroy;
    hsdClass.forget = _hsdClassAmnesia;
}

void *hsdNew(HSD_ClassInfo *index)
{
    HSD_ClassInfo *info = index;
    HSD_ClassInfo *allocation_info = info;
    HSD_Class *object;
    if (!(allocation_info->head.flags & HSD_CLASS_INFO_INITIALIZED)) {
        allocation_info->head.initialize_info();
    }
    object = info->allocate(allocation_info);
    if (object == 0) {
        return 0;
    }
    ClassInfoInit(info);
    memset(object, 0, info->head.object_size);
    object->class_info = info;
    if (info->initialize(object) < 0) {
        info->destroy(object);
        return 0;
    }
    return object;
}

static inline void class_set_flags(HSD_ClassInfo *class_info, s32 add_flags,
                                   s32 clear_flags)
{
    class_info->head.flags = (class_info->head.flags & ~clear_flags) | add_flags;
}

void ForgetClassLibraryReal(HSD_ClassInfo *class_info)
{
    HSD_ClassInfo *child = class_info->head.child;
    HSD_ClassInfo *next;
    while (child != 0) {
        next = child->head.next;
        child->head.next = 0;
        ForgetClassLibraryReal(child);
        child = next;
    }
    class_info->forget(class_info);
    class_info->head.child = 0;
    class_info->head.parent = 0;
    class_set_flags(class_info, 0, HSD_CLASS_INFO_INITIALIZED);
}

static inline void ForgetClassLibraryChild(const char *library_name,
                                           HSD_ClassInfo *class_info)
{
    HSD_ClassInfo **cur = &class_info->head.child;
    while (*cur != 0) {
        if (strcmp(library_name, (*cur)->head.library_name) == 0) {
            ForgetClassLibraryReal(*cur);
            *cur = (*cur)->head.next;
        } else {
            cur = &(*cur)->head.next;
        }
    }
}

void hsdForgetClassLibrary(const char *library_name)
{
    if (library_name == 0) {
        library_name = "sysdolphin_base_library";
    }
    if (!(hsdClass.head.flags & HSD_CLASS_INFO_INITIALIZED)) {
        return;
    }
    if (strcmp(library_name, hsdClass.head.library_name) == 0) {
        info_hash = 0;
        ForgetClassLibraryReal(&hsdClass);
    } else {
        ForgetClassLibraryChild(library_name, &hsdClass);
    }
}

HSD_ClassInfo *hsdSearchClassInfo(const char *class_name)
{
    if (info_hash != 0) {
        return HSD_HashSearch(info_hash, (void *)class_name, 0);
    }
    return 0;
}
