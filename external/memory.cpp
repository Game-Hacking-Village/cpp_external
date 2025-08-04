#include "memory.h"

BYTE *mem::resolve_PointerMap(const HANDLE proc, const uintptr_t base_addr, const PointerMap *chain) {
    uintptr_t cursor = base_addr + chain->base_offset;
    for (const unsigned int offset: chain->offsets) {
        ReadProcessMemory(proc, reinterpret_cast<BYTE *>(cursor), &cursor, sizeof(cursor), nullptr);
        cursor += offset;
    }
    return reinterpret_cast<BYTE *>(cursor);
}

bool mem::CompareSignatureToBytes(const mem::Signature &sig, const BYTE *bytes) {
    for (int i = 0; i < sig.size(); i++) {
        // check if sig[i] is a value (not masked) and matches bytes
        if (sig.at(i).has_value() && sig.at(i).value() != bytes[i]) {
            // is not a mask and doesn't match bytes
            return false;
        }
    }
    return true;
}

BYTE *mem::ScanExecMemory(const HANDLE proc, const mem::Signature &sig) {
    // state
    MEMORY_BASIC_INFORMATION cur_mbi;
    BYTE *page_base_addr = 0;

    // iterate through proc memory pages
    while (VirtualQueryEx(proc, page_base_addr, &cur_mbi, sizeof(cur_mbi))) {
        // check if the page is executable
        if (cur_mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)) {
            // create buffer to hold current page data
            std::vector<BYTE> cur_memory(cur_mbi.RegionSize);
            SIZE_T bytesRead;

            // Read the memory region
            if (ReadProcessMemory(proc, cur_mbi.BaseAddress, cur_memory.data(), cur_mbi.RegionSize, &bytesRead)) {
                // iter through copied memory (without checking end of memory where sig is too long)
                for (int mem_idx = 0; mem_idx < (bytesRead - sig.size()); mem_idx++) {
                    // check if first byte matches
                    if (sig.at(0).value() == cur_memory.at(mem_idx)) {
                        // check if subsequent values match
                        if (mem::CompareSignatureToBytes(sig, &cur_memory.at(mem_idx))) {
                            // return found addr
                            return page_base_addr + mem_idx;
                        }
                    }
                }
            } else {
                std::cerr << "Failed to read memory at " << std::hex << cur_mbi.BaseAddress << std::endl;
            }
        }

        // iterate to next page
        page_base_addr += cur_mbi.RegionSize;
    }

    std::cerr << "Failed to find signature in signature search" << endl;
    return 0;
}

void mem::PatchInstructions(const HANDLE proc, BYTE *target, const BYTE *new_insts, const unsigned int size) {
    DWORD old_protect_val;
    // set protections to r/w
    VirtualProtectEx(proc, target, size, PAGE_EXECUTE_READWRITE, &old_protect_val);
    // patch insts
    WriteProcessMemory(proc, target, new_insts, size, nullptr);
    // restore protections
    VirtualProtectEx(proc, target, size, old_protect_val, &old_protect_val);
}
