#include "memory.h"

uintptr_t resolve_pointer_chain(const HANDLE proc, const uintptr_t base_addr, const PointerChain &chain) {
    uintptr_t cursor = base_addr;
    for (const unsigned int offset : chain) {
        ReadProcessMemory(proc, reinterpret_cast<BYTE *>(cursor), &cursor, sizeof(cursor), nullptr);
        cursor += offset;
    }
    return cursor;
}