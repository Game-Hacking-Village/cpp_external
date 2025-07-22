#include "doom.h"

DoomProc::DoomProc() {
    pid = proc::get_pid(DOOM_PROC_NAME);
    proc_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
    base_address = proc::get_baseaddr(pid, DOOM_PROC_NAME);
}

int DoomProc::get_pid() const {
    return pid;
}

uintptr_t DoomProc::get_base_address() const {
    return base_address;
}

int DoomProc::read(const mem::PointerChain &pc) const {
    const auto target_addr = mem::resolve_pointer_chain(proc_handle, base_address, &pc);
    int val;
    ReadProcessMemory(proc_handle, target_addr, &val, sizeof(val), nullptr);
    return val;
}

void DoomProc::write(const mem::PointerChain &pc, const int newval) const {
    const auto target_addr = mem::resolve_pointer_chain(proc_handle, base_address, &pc);
    WriteProcessMemory(proc_handle, target_addr, &newval, sizeof(newval), nullptr);
}
