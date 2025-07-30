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
    addr_AmmoPistol = this->resolve_PointerMap(&ammo_pistol);
	//addr_Ammo2;								//*** For Participants to Build!
	//addr_Ammo3;
	//addr_Ammo4;
	addr_Health = this->resolve_PointerMap(&health);
    addr_Armor = this->resolve_PointerMap(&armor);
}

/*********
// mods //
*********/
// pistol ammo getter
int DoomProc::get_AmmoPistol() const {
    int val;
    ReadProcessMemory(proc_handle, addr_AmmoPistol, &val, sizeof(val), nullptr);
    return val;
}

// pistol ammo setter
void DoomProc::set_AmmoPistol(const int val) const {
    WriteProcessMemory(proc_handle, addr_AmmoPistol, &val, sizeof(val), nullptr);
}

// ammo #2 getter										//*** For Participants to Build!***
// int DoomProc::get_Ammo2() const {
// 	int val;
// 	ReadProcessMemory(proc_handle, addr_Ammo2, &val, sizeof(val), nullptr);
// 	return val;
// }

// ammo #2 setter										//*** For Participants to Build!***
// void DoomProc::set_Ammo2(const int val) const {
// 	WriteProcessMemory(proc_handle, addr_Ammo2, &val, sizeof(val), nullptr);
// }


// ammo #3 getter and setter								//*** For Participants to Build!***

// ammo #4 getter and setter								//*** For Participants to Build!***

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
