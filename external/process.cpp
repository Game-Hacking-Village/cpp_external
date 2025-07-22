#include "process.h"

HANDLE proc::get_handle(const wchar_t *processName) {
    if (const DWORD id = proc::get_pid(processName); id != 0) {
        return OpenProcess(PROCESS_ALL_ACCESS, 0, id);
    }
    throw std::runtime_error("Error opening process");
}

DWORD proc::get_pid(const wchar_t *procName) {
    // create proc snapshot
    const HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("CreateToolhelp32Snapshot failed to create snapshot");
    }

    // init process struct
    PROCESSENTRY32W procEntry;
    procEntry.dwSize = sizeof(procEntry);

    // get first process
    if (!Process32FirstW(snap, &procEntry)) {
        CloseHandle(snap);
        throw std::runtime_error("Error enumerating processes");
    }

    // iter processes
    do {
        // compare proc name with target proc name, returns 0 if same
        if (!_wcsicmp(procEntry.szExeFile, procName)) {
            // return found proc
            const DWORD id = procEntry.th32ProcessID;
            CloseHandle(snap);
            return id;
        }
    } while (Process32NextW(snap, &procEntry));

    // no id found
    CloseHandle(snap);
    throw std::runtime_error("Error getting process id, ensure target proc is open");
}

uintptr_t proc::get_baseaddr(const DWORD procId, const wchar_t *modName) {
    // create handle to proc
    const HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (snap == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("CreateToolhelp32Snapshot failed to create snapshot with procId");
    }

    // init MODULE ENTRY struct
    MODULEENTRY32W modEntry;
    modEntry.dwSize = sizeof(modEntry);

    // get fist module
    if (!Module32FirstW(snap, &modEntry)) {
        throw std::runtime_error("Error enumerating modules");
    }

    // iter modules of proc
    do {
        // compare module name
        if (!_wcsicmp(modEntry.szModule, modName)) {
            // return found base address
            const auto base_addr = reinterpret_cast<uintptr_t>(modEntry.modBaseAddr);
            CloseHandle(snap);
            return base_addr;
        }
    } while (Module32NextW(snap, &modEntry));

    // no base address found
    CloseHandle(snap);
    throw std::runtime_error("Error getting base address of proc.");
}
