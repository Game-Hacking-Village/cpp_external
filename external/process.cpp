#include "process.h"

DWORD get_proc_id(const wchar_t *procName) {
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD id = 0;
	if (snap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(snap, &procEntry)) {
			do {
				unsigned long long w_exe_len = sizeof(procEntry.szExeFile) + 1;
				wchar_t *w_exe = new wchar_t[w_exe_len];
				mbstowcs(w_exe, procEntry.szExeFile, w_exe_len);
				if (!_wcsicmp(w_exe, procName)) {
					id = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(snap, &procEntry));
		}
	}
	CloseHandle(snap);
	return id;
}

uintptr_t get_base_addr(DWORD procId, const wchar_t *modName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				unsigned long long w_module_size = sizeof(modEntry.szModule) + 1;
				wchar_t *w_module = new wchar_t[w_module_size];
				mbstowcs(w_module, modEntry.szModule, 250);
				if (!_wcsicmp(w_module, modName)) {
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}
