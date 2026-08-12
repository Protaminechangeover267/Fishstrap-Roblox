#include "../include/FPSUnlocker.h"
#include <TlHelp32.h>

DWORD FPSUnlocker::FindRoblox() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pe{}; pe.dwSize = sizeof(pe);
    DWORD pid = 0;
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, L"RobloxPlayerBeta.exe") == 0) { pid = pe.th32ProcessID; break; }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap); return pid;
}

bool FPSUnlocker::Initialize() {
    DWORD pid = FindRoblox();
    if (!pid) return false;
    m_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    return m_process != nullptr;
}

bool FPSUnlocker::PatchCap() {
    BYTE nop[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
    SIZE_T written;
    // Pattern: 89 3D ?? ?? ?? ?? (mov [fps_addr], edi) -> NOP
    return WriteProcessMemory(m_process, m_patchAddr, nop, sizeof(nop), &written);
}

void FPSUnlocker::SetTargetFPS(int fps) { m_targetFPS = fps; }
int FPSUnlocker::GetTargetFPS() const { return m_targetFPS; }
