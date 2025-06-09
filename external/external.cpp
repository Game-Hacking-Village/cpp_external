#include "process.h"
#include <cstdio>
#include <string>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: ./external <address>\n");
		return 1;
	}

	// get target addr from cli arg
	uintptr_t target_addr = reinterpret_cast<uintptr_t>(std::stoull(argv[1], nullptr, 16));
	printf("Target addr: %p\n", target_addr);

	// Get ProcId of the target process
	printf("Getting proc id\n");
	DWORD procId = get_proc_id(L"game.exe");
	printf("procid: %lu\n", procId);

	// base addr
	printf("Getting base addr\n");
	uintptr_t base_addr = get_base_addr(procId, L"game.exe");
	printf("base addr: %llu\n", base_addr);

	// get proc handle
	HANDLE game_handle = 0;
	if ((game_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, procId))) {
		printf("game handle found\n");
	} else {
		printf("game handle not found\n");
		return 2;
	}

	// read current val
	int old_val = 0;
	printf("reading value\n");
	ReadProcessMemory(game_handle, (BYTE *)target_addr, &old_val, sizeof(old_val), nullptr);
	printf("Old Val: %u\n", old_val);

	// write new val
	int new_val = 0;
	printf("writing value\n");
	WriteProcessMemory(game_handle, (BYTE *)target_addr, &new_val, sizeof(new_val), nullptr);
	ReadProcessMemory(game_handle, (BYTE *)target_addr, &old_val, sizeof(old_val), nullptr);
	printf("New Val: %u\n", old_val);

	return 0;
}
