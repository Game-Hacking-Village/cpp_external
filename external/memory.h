#pragma once
#include "std_headers.h"

#include <vector>
using std::vector;


namespace mem {
    typedef struct PointerChain {
        uintptr_t init_offset; // initial offset from base address of proc
        vector<uintptr_t> offsets;
    } PointerChain;

    BYTE *resolve_pointer_chain(HANDLE proc, uintptr_t base_addr, const PointerChain *chain);
}
