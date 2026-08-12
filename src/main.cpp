#include <Windows.h>
#include <iostream>
#include "../include/FPSUnlocker.h"
#include "../include/FastFlagsManager.h"
#include "../include/Config.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    Config::Load("config/settings.json");
    FPSUnlocker unlocker;
    unlocker.Initialize();
    unlocker.SetTargetFPS(Config::Get("targetFPS", 144));
    FastFlagsManager ff;
    ff.Load("config/fast_flags.json");
    ff.Apply();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
    return 0;
}
