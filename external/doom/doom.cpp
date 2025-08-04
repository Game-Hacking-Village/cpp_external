#include "doom.h"

DoomProc::DoomProc() {
    // acquire proc
    pid = proc::get_pid(DOOM_PROC_NAME);
    proc_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
    base_address = proc::get_baseaddr(pid, DOOM_PROC_NAME);

    resolve_memory_addresses();
}

// proc getters
int DoomProc::get_pid() const { return pid; }
uintptr_t DoomProc::get_base_address() const { return base_address; }

// resolve mem addrs
BYTE *DoomProc::resolve_PointerMap(const mem::PointerMap *pm) const {
    return mem::resolve_PointerMap(proc_handle, base_address, pm);
}

void DoomProc::resolve_memory_addresses() {
    addr_AmmoHeldWeapon = this->resolve_PointerMap(&ammo_held_weapon);
    addr_AmmoPistol = this->resolve_PointerMap(&ammo_pistol);
    addr_Health = this->resolve_PointerMap(&health);
    addr_Armor = this->resolve_PointerMap(&armor);

    // addr_inst_write_held_ammo = addr_AmmoPistol - 0x103601ed;
    addr_code_setAmmo = mem::ScanExecMemory(proc_handle, sig_setammo);
}

/*********
// mods //
*********/
// held ammo
int DoomProc::get_AmmoHeldWeapon() const {
    int val;
    ReadProcessMemory(proc_handle, addr_AmmoHeldWeapon, &val, sizeof(val), nullptr);
    return val;
}

void DoomProc::set_AmmoHeldWeapon(const int val) const {
    WriteProcessMemory(proc_handle, addr_AmmoHeldWeapon, &val, sizeof(val), nullptr);
}

// pistol ammo
int DoomProc::get_AmmoPistol() const {
    int val;
    ReadProcessMemory(proc_handle, addr_AmmoPistol, &val, sizeof(val), nullptr);
    return val;
}

void DoomProc::set_AmmoPistol(const int val) const {
    WriteProcessMemory(proc_handle, addr_AmmoPistol, &val, sizeof(val), nullptr);
}

// health
int DoomProc::get_Health() const {
    int val;
    ReadProcessMemory(proc_handle, addr_Health, &val, sizeof(val), nullptr);
    return val;
}

void DoomProc::set_Health(const int val) const {
    WriteProcessMemory(proc_handle, addr_Health, &val, sizeof(val), nullptr);
}

// armor
int DoomProc::get_Armor() const {
    int val;
    ReadProcessMemory(proc_handle, addr_Armor, &val, sizeof(val), nullptr);
    return val;
}

void DoomProc::set_Armor(const int val) const {
    WriteProcessMemory(proc_handle, addr_Armor, &val, sizeof(val), nullptr);
}

// unlimited ammo
bool DoomProc::toggle_unlimited_ammo() {
    BYTE *target_insts = nullptr;
    if (status_unlimited_ammo) {
        // toggle unlimited ammo on->off, restore original code
        target_insts = (BYTE *) "\x44\x89\x1A";
        status_unlimited_ammo = false;
    } else {
        // toggle unlimited ammo off->on, nop out code
        target_insts = (BYTE *) "\x90\x90\x90";
        status_unlimited_ammo = true;
    }

    // write new target insts
    mem::PatchInstructions(proc_handle, addr_code_setAmmo, target_insts, 3);

    // return new status
    return status_unlimited_ammo;
}
