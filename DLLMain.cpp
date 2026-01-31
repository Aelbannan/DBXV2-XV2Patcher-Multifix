#include "exports.h"
#include <windows.h>
#include "MinHook.h"

// 2. MinHook Mutex Detour
typedef HANDLE(WINAPI* CREATE_MUTEX_A)(LPSECURITY_ATTRIBUTES, BOOL, LPCSTR);
CREATE_MUTEX_A fpCreateMutexA = NULL;

HANDLE WINAPI DetourCreateMutexA(LPSECURITY_ATTRIBUTES lpAttributes, BOOL bInitialOwner, LPCSTR lpName) {
    if (lpName && strcmp(lpName, "XV2PATCHER_INSTANCE") == 0) {
        // We set the last error to success so the patcher thinks it created it
        SetLastError(ERROR_SUCCESS);
        return (HANDLE)0xDEADBEEF;
    }
    return fpCreateMutexA(lpAttributes, bInitialOwner, lpName);
}

void StartHook() {
    if (MH_Initialize() == MH_OK) {
        // Hooking kernel32!CreateMutexA
        MH_CreateHookApi(L"kernel32", "CreateMutexA", &DetourCreateMutexA, reinterpret_cast<LPVOID*>(&fpCreateMutexA));
        MH_EnableHook(MH_ALL_HOOKS);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        // Start the hook. Since version.dll loads before dinput8.dll, 
        // the hook will be active when the patcher tries to create the mutex.
        StartHook();
    }
    return TRUE;
}
