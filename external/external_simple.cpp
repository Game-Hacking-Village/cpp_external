#include "std_headers.h"
#include "process.h"
#include "memory.h"


int main(int argc, char *argv[]) {
    // get target proc
    wcout << "Enter target process name: ";
    wstring user_proc_name;
    wcin >> user_proc_name;

    // Get handle to proc
    wcout << "Getting proc handle..." << endl;
    const HANDLE proc_handle = proc::get_handle(user_proc_name.c_str());
    if (proc_handle != INVALID_HANDLE_VALUE) {
        wcout << "Process Handle created" << endl;
    } else {
        wcout << "Process Handle creation failed" << endl;
        return 1;
    }

    // get target addr
    wcout << "Enter Target Address: ";
    wstring input_target_addr;
    wcin >> input_target_addr;
    const auto target_addr = reinterpret_cast<BYTE *>(std::stoull(input_target_addr, nullptr, 16));

    // read current val
    int old_val = 0;
    ReadProcessMemory(proc_handle, target_addr, &old_val, sizeof(old_val), nullptr);
    wcout << "Target Address: " << target_addr << " Current Value: " << old_val << endl;

    // write new val
    int new_val = 0;
    wcout << "Enter Target Value: ";
    wcin >> new_val;
    WriteProcessMemory(proc_handle, target_addr, &new_val, sizeof(new_val), nullptr);

    // check write
    int final_val = 0;
    ReadProcessMemory(proc_handle, target_addr, &final_val, sizeof(final_val), nullptr);
    wcout << "Final Val: " << final_val << endl;

    system("pause");
    return 0;
}
