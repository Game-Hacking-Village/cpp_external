#include "std_headers.h"
#include "process.h"
#include "memory.h"

#include "offsets/doom.h"

#define DOOM_PROC_NAME L"gzdoom.exe"

[[noreturn]] int main(int argc, char *argv[]) {
    // open doom
    wcout << "Getting proc handle..." << endl;
    const int procid = get_proc_id(DOOM_PROC_NAME);

    // open proc
    const HANDLE ph = OpenProcess(PROCESS_ALL_ACCESS, 0, procid);
    if (ph != INVALID_HANDLE_VALUE) {
        wcout << "Process Handle created" << endl;
    } else {
        wcout << "Process Handle creation failed" << endl;
        return 1;
    }

    // print menu
    wcout << "[ : set pistol ammo to 100" << endl;
    wcout << "] : set health to 100" << endl;
    wcout << "\\ : set armor to 200" << endl;

    // get base address
    const uintptr_t base_addr = get_base_addr(procid, DOOM_PROC_NAME);

    // get addrs
    const auto ammo_addr = reinterpret_cast<BYTE *>(resolve_pointer_chain(
        ph, base_addr + doom::ammo::base_addr, doom::ammo::pointer_chain));
    const auto health_addr = reinterpret_cast<BYTE *>(resolve_pointer_chain(
        ph, base_addr + doom::health::base_addr, doom::health::pointer_chain));
    const auto armor_addr = reinterpret_cast<BYTE *>(resolve_pointer_chain(
        ph, base_addr + doom::armor::base_addr, doom::armor::pointer_chain));

    const int new_ammo = 100;
    const int new_health = 100;
    const int new_armor = 200;

    while (true) {
        Sleep(25);

        // write ammo
        if (GetAsyncKeyState(VK_OEM_4) & 1) {
            // read old ammo
            int previous_ammo;
            ReadProcessMemory(ph, ammo_addr, &previous_ammo, sizeof(previous_ammo), nullptr);
            wcout << "Previous ammo: " << previous_ammo << endl;

            // write new ammo
            WriteProcessMemory(ph, ammo_addr, &new_ammo, sizeof(new_ammo), nullptr);

            // re-read and print new value
            ReadProcessMemory(ph, ammo_addr, &previous_ammo, sizeof(previous_ammo), nullptr);
            wcout << "New ammo: " << previous_ammo << endl;
        }

        // write health
        if (GetAsyncKeyState(VK_OEM_6) & 1) {
            // read old health
            int previous_health;
            ReadProcessMemory(ph, health_addr, &previous_health, sizeof(previous_health), nullptr);
            wcout << "Previous health: " << previous_health << endl;

            // write new health
            WriteProcessMemory(ph, health_addr, &new_health, sizeof(new_health), nullptr);

            // re-read and print new value
            ReadProcessMemory(ph, health_addr, &previous_health, sizeof(previous_health), nullptr);
            wcout << "New health: " << previous_health << endl;
        }

        // write armor
        if (GetAsyncKeyState(VK_OEM_5) & 1) {
            // read old armor
            int previous_armor;
            ReadProcessMemory(ph, armor_addr, &previous_armor, sizeof(previous_armor), nullptr);
            wcout << "Previous armor: " << previous_armor << endl;

            // write new armor
            WriteProcessMemory(ph, armor_addr, &new_armor, sizeof(new_armor), nullptr);

            // re-read and print new value
            ReadProcessMemory(ph, armor_addr, &previous_armor, sizeof(previous_armor), nullptr);
            wcout << "New armor: " << previous_armor << endl;
        }
    }

    system("pause");
    return 0;
}
