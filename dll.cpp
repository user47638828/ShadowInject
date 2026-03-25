#include <windows.h>

DWORD WINAPI MainThread(LPVOID param) {
    MessageBoxA(0, "Injected", "ShadowInject", MB_OK);

    while (true) {
        Sleep(1000);
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }
    return TRUE;
}
