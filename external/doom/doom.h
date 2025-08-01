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
    // wrapper to resolve pointer map for this proc
    BYTE *resolve_PointerMap(const mem::PointerMap *pm) const;

public:
    DoomProc();

    int get_pid() const;
    uintptr_t get_base_address() const;

    // calculate memory addresses
    void resolve_memory_addresses();

    // mem addresses (set in resolve_memory_addresses during construction)
    BYTE *addr_AmmoHeldWeapon;
    BYTE *addr_AmmoPistol;
    BYTE *addr_Health;
    BYTE *addr_Armor;

    /*********
    // mods //
    *********/
    // held ammo
    int get_AmmoHeldWeapon() const;
    void set_AmmoHeldWeapon(int val) const;
    // pistol ammo
    int get_AmmoPistol() const;
    void set_AmmoPistol(int val) const;
    // health
    int get_Health() const;
    void set_Health(int val) const;
    // armor
    int get_Armor() const;
    void set_Armor(int val) const;

};
