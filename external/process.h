#pragma once
#include "std_headers.h"

#include <stdexcept>

HANDLE get_proc_handle(const wchar_t *processName);

DWORD get_proc_id(const wchar_t *procName);

uintptr_t get_base_addr(DWORD procId, const wchar_t *modName);
