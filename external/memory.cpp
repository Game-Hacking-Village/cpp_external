#include "memory.h"

BYTE *mem::resolve_pointer_chain(const HANDLE proc, const uintptr_t base_addr, const PointerChain *chain) {
    uintptr_t cursor = base_addr + chain->init_offset;
    for (const unsigned int offset: chain->offsets) {
        ReadProcessMemory(proc, reinterpret_cast<BYTE *>(cursor), &cursor, sizeof(cursor), nullptr);
        cursor += offset;
    }
    return reinterpret_cast<BYTE *>(cursor);
}
