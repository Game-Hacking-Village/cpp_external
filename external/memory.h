#pragma once
#include "std_headers.h"

#include <optional>
#include <vector>
using std::vector;

namespace mem {
    /*********
    // DATA //
    *********/
    // our "PointerChain" has a base offset from the base address
    // this resulting address is followed, then each subsequent offset in offsets is added
    // to the resulting address and followed.
    typedef struct PointerMap {
        uintptr_t base_offset; // initial offset from base address
        vector<uintptr_t> offsets; // offsets followed from base_offset.
    } PointerMap;

    // follow a pointer chain and get the resulting offset
    BYTE *resolve_PointerMap(HANDLE proc, uintptr_t base_addr, const PointerMap *chain);

    /*********
    // CODE //
    *********/
    // signature type for finding code patterns
    // a byte in a signature may be optional in the same way "masked" sig searches work
    // this is usually so signature search won't break as much when a game is updated
    //
    // ex:
    // const mem::Signature sig = { 0xDE, 0xAD, std::nullopt, 0xEF};
    //
    // check if a signature BYTE is a value and not a mask with
    // Signature.at(x).has_value()
    typedef vector<std::optional<BYTE> > Signature;

    // unsafe (🤷) helper func to compare a signature to target bytes
    // returns true if match
    bool CompareSignatureToBytes(const Signature &sig, const BYTE *bytes);

    // executable memory scanner
    // searches for a signature in a given handle's executable memory
    BYTE *ScanExecMemory(HANDLE proc, const Signature &sig);

    // patch executable
    // writes new_insts of size to target*
    void PatchInstructions(HANDLE proc, BYTE *target, const BYTE *new_insts, unsigned int size);
}
