#pragma once
#include "../std_headers.h"
#include "../memory.h"
#include "../process.h"

#include "offsets.h"
#include "sigs.h"

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

    ~DoomProc();

    // proc
    int get_pid() const;

    uintptr_t get_base_address() const;

    void resolve_memory_addresses();

    // mem addresses (set in resolve_memory_addresses during construction)
    // data
    BYTE *addr_AmmoHeldWeapon;
    BYTE *addr_AmmoPistol;

    //BYTE *addr_Ammo2;			//*** For Participants to Build!***
    //BYTE *addr_Ammo3;
    //BYTE *addr_Ammo4;

	BYTE *addr_Health;
    BYTE *addr_Armor;
    // code
    BYTE *addr_code_setAmmo;

    /**************
    // data mods //
    **************/
    // held ammo
    int get_AmmoHeldWeapon() const;

    void set_AmmoHeldWeapon(int val) const;

    // pistol ammo
    int get_AmmoPistol() const;

    void set_AmmoPistol(int val) const;

	// ammo #2	getter and setter				//*** For Participants to Build***
	// ammo #3  getter and setter
	// ammo #4  getter and setter

    // health
    int get_Health() const;

    void set_Health(int val) const;

    // armor
    int get_Armor() const;

    void set_Armor(int val) const;

    /**************
    // code mods //
    **************/
    // unlimited ammo
    bool status_unlimited_ammo = false;

    bool toggle_unlimited_ammo();
};
