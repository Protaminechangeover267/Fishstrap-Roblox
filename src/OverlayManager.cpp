#include "../include/Types.h"
#include <Windows.h>
#include <fstream>
#include <iostream>

OverlayManager::OverlayManager() : visible(false), hwnd(nullptr) {}

bool OverlayManager::Initialize() {
    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "FishstrapOverlay";
    RegisterClassExA(&wc);

    hwnd = CreateWindowExA(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
        "FishstrapOverlay", "Fishstrap",
        WS_POPUP, 100, 100, 300, 100,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    return hwnd != nullptr;
}

void OverlayManager::Show() { if (hwnd) ShowWindow(hwnd, SW_SHOW); visible = true; }
void OverlayManager::Hide() { if (hwnd) ShowWindow(hwnd, SW_HIDE); visible = false; }
void OverlayManager::Toggle() { visible ? Hide() : Show(); }
bool OverlayManager::IsVisible() const { return visible; }

void OverlayManager::UpdateFPS(int fps) {
    currentFPS = fps;
    if (!hwnd) return;
    HDC hdc = GetDC(hwnd);
    if (!hdc) return;
    RECT rect; GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    SetTextColor(hdc, RGB(0, 255, 0));
    SetBkMode(hdc, TRANSPARENT);
    std::string text = "FPS: " + std::to_string(fps);
    DrawTextA(hdc, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ReleaseDC(hwnd, hdc);
}
