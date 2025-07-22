#pragma once
#include "std_headers.h"

#include <stdexcept>

namespace proc {
    HANDLE get_handle(const wchar_t *processName);

    DWORD get_pid(const wchar_t *procName);

    uintptr_t get_baseaddr(DWORD procId, const wchar_t *modName);
}