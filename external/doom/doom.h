#pragma once
#include "../std_headers.h"
#include "../memory.h"
#include "../process.h"

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

    int read(const mem::PointerChain &pc) const;

    void write(const mem::PointerChain &pc, int newval) const;

    const mem::PointerChain ammo_pistol = {0x00A21ED0, {0x438, 0x6D0, 0x618}};
    const mem::PointerChain health = {0x00A21ED0, {0x438, 0x610, 0x298}};
    const mem::PointerChain armor = {0x00A21ED0, {0x420, 0x618}};
};
