#include <windows.h>

uintptr_t targetAddress = 0x00000000;
int targetValue = 0;

DWORD WINAPI MainThread(LPVOID param) {
    while (true) {
        if (targetAddress != 0x00000000) {
            *(int*)targetAddress = targetValue;
        }

        Sleep(100);
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }
    return TRUE;
}
