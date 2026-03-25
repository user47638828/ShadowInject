#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

DWORD GetProcessIdByName(const char* processName) {
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (!_stricmp(processEntry.szExeFile, processName)) {
                CloseHandle(snapshot);
                return processEntry.th32ProcessID;
            }
        } while (Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);
    return 0;
}

int main() {
    const char* processName = "GTA5.exe";
    const char* dllPath = "mod.dll";

    DWORD processId = GetProcessIdByName(processName);

    if (!processId) {
        std::cout << "Process not found\n";
        return 0;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    LPVOID allocatedMemory = VirtualAllocEx(
        hProcess,
        NULL,
        strlen(dllPath) + 1,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    WriteProcessMemory(
        hProcess,
        allocatedMemory,
        dllPath,
        strlen(dllPath) + 1,
        NULL
    );

    HANDLE hThread = CreateRemoteThread(
        hProcess,
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)LoadLibraryA,
        allocatedMemory,
        0,
        NULL
    );

    WaitForSingleObject(hThread, INFINITE);

    VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    std::cout << "Done\n";
    return 0;
}
