#pragma once
#include <Windows.h>
#include <string>

class FPSUnlocker {
    HANDLE m_process = nullptr;
    void* m_patchAddr = nullptr;
    int m_targetFPS = 144;
    DWORD FindRoblox();
    bool PatchCap();
public:
    bool Initialize();
    void SetTargetFPS(int fps);
    int GetTargetFPS() const;
    HANDLE GetProcess() const { return m_process; }
};
