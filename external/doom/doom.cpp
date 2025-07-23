#include "doom.h"

DoomProc::DoomProc() {
    // acquire proc
    pid = proc::get_pid(DOOM_PROC_NAME);
    proc_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
    base_address = proc::get_baseaddr(pid, DOOM_PROC_NAME);

    resolve_memory_addresses();
}

int DoomProc::get_pid() const {
    return pid;
}

uintptr_t DoomProc::get_base_address() const {
    return base_address;
}

BYTE *DoomProc::resolve_pointer_map(const mem::PointerMap *pm) const {
    return mem::resolve_PointerMap(proc_handle, base_address, pm);
}

int DoomProc::read(const BYTE *addr) const {
    int val;
    ReadProcessMemory(proc_handle, addr, &val, sizeof(val), nullptr);
    return val;
}

void DoomProc::write(BYTE *addr, const int newval) const {
    WriteProcessMemory(proc_handle, addr, &newval, sizeof(newval), nullptr);
}

void DoomProc::resolve_memory_addresses() {
    addr_ammopistol = this->resolve_pointer_map(&ammo_pistol);
    addr_health = this->resolve_pointer_map(&health);
    addr_armor = this->resolve_pointer_map(&armor);
}
