#pragma once
#include "std_headers.h"

#include <vector>
using std::vector;


namespace mem {
    // our "PointerChain" has a base offset from the base address
    // this resulting address is followed, then each subsequent offset in offsets is added
    // to the resulting address and followed.
    typedef struct PointerMap {
        uintptr_t base_offset; // initial offset from base address
        vector<uintptr_t> offsets; // offsets followed from base_offset.
    } PointerMap;

    // follow a pointer chain and get the resulting offset
    BYTE *resolve_PointerMap(HANDLE proc, uintptr_t base_addr, const PointerMap *chain);
}
