#pragma once
#include <SDKDDKVer.h>
#include <windows.h>

#include <TlHelp32.h>
#include <string.h>
#include <tchar.h>

DWORD get_proc_id(const wchar_t *procName);

uintptr_t get_base_addr(DWORD procId, const wchar_t *modName);
