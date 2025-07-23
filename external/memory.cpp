#include "memory.h"

BYTE *mem::resolve_PointerMap(const HANDLE proc, const uintptr_t base_addr, const PointerMap *chain) {
    uintptr_t cursor = base_addr + chain->base_offset;
    for (const unsigned int offset: chain->offsets) {
        ReadProcessMemory(proc, reinterpret_cast<BYTE *>(cursor), &cursor, sizeof(cursor), nullptr);
        cursor += offset;
    }
    return reinterpret_cast<BYTE *>(cursor);
}
