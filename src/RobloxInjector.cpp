#include "../include/Types.h"
#include <Windows.h>
#include <TlHelp32.h>

RobloxInjector::RobloxInjector() : injected(false), processHandle(nullptr) {}

DWORD RobloxInjector::FindProcess() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pe{}; pe.dwSize = sizeof(pe);
    DWORD pid = 0;
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, L"RobloxPlayerBeta.exe") == 0) { pid = pe.th32ProcessID; break; }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return pid;
}

bool RobloxInjector::Inject() {
    DWORD pid = FindProcess();
    if (!pid) return false;
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    return processHandle != nullptr;
}

void RobloxInjector::Eject() {
    if (processHandle) { CloseHandle(processHandle); processHandle = nullptr; }
    injected = false;
}
