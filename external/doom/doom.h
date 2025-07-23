#pragma once
#include "../std_headers.h"
#include "../memory.h"
#include "../process.h"

#include "offsets.h"

#define DOOM_PROC_NAME L"gzdoom.exe"

class DoomProc {
private:
    // process
    int pid;
    HANDLE proc_handle;
    uintptr_t base_address;

public:
    DoomProc();

    int get_pid() const;

    uintptr_t get_base_address() const;

    BYTE *resolve_pointer_map(const mem::PointerMap *pm) const;

    int read(const BYTE *addr) const;

    void write(BYTE *addr, int newval) const;

    // calculate memory addresses
    void resolve_memory_addresses();

    // mem addresses (set in resolve_memory_addresses during construction)
    BYTE *addr_ammopistol;
    BYTE *addr_health;
    BYTE *addr_armor;
};
