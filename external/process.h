#pragma once
#include <memory>
#include <SDKDDKVer.h>
#include <windows.h>

#include <TlHelp32.h>
#include <tchar.h>

DWORD get_proc_id(const wchar_t *procName);

uintptr_t get_base_addr(DWORD procId, const wchar_t *modName);

HANDLE get_proc_handle(const wchar_t *processName);
