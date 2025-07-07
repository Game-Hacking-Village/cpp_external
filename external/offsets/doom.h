#pragma once
#include "../memory.h"

// todo cleanup and have better way to read/write
// make it easier to understand, idk why im using namespaces
// also these pointer maps are not good, they should work though

namespace doom {
    namespace ammo {
        inline uintptr_t base_addr = 0x00A21ED0;
        inline PointerChain pointer_chain = {0x438, 0x6D0, 0x618};
    }

    namespace health {
        inline uintptr_t base_addr = 0x00A21ED0;
        inline PointerChain pointer_chain = {0x438, 0x610, 0x298};
    }

    namespace armor {
        inline uintptr_t base_addr = 0x00A21ED0;
        inline PointerChain pointer_chain = {0x420, 0x618};
    }
}
