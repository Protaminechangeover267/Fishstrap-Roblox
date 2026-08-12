#include "../include/FastFlagsManager.h"
#include <fstream>

MultiInstance::MultiInstance() : enabled(false) {}

bool MultiInstance::Enable() {
    // Rename Roblox mutex to allow multiple instances
    HANDLE hMutex = OpenMutexA(SYNCHRONIZE, FALSE, "ROBLOX_singletonMutex");
    if (hMutex) { CloseHandle(hMutex); }
    enabled = true;
    return true;
}

void MultiInstance::Disable() { enabled = false; }

FontManager::FontManager() {}

bool FontManager::Load(const std::string& name) {
    std::string path = "config/fonts/" + name + ".ttf";
    int r = AddFontResourceA(path.c_str());
    if (r > 0) { activeFont = name; return true; }
    return false;
}

void FontManager::Unload() {
    if (!activeFont.empty()) {
        std::string path = "config/fonts/" + activeFont + ".ttf";
        RemoveFontResourceA(path.c_str());
        activeFont = "";
    }
}

ShaderLoader::ShaderLoader() {}

bool ShaderLoader::Load(const std::string& name) {
    std::ifstream f("shaders/" + name + ".glsl");
    if (!f.is_open()) return false;
    code = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    activeShader = name;
    return true;
}

std::string ShaderLoader::GetActive() const { return activeShader; }
void ShaderLoader::Unload() { code.clear(); activeShader = ""; }

Launcher::Launcher() {}

bool Launcher::Install() {
    char exe[MAX_PATH];
    GetModuleFileNameA(NULL, exe, MAX_PATH);
    installPath = exe;
    return true;
}

bool Launcher::LaunchRoblox() {
    STARTUPINFOA si{}; PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);
    std::string cmd = "RobloxPlayerBeta.exe";
    return CreateProcessA(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}
