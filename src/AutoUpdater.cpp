#include "../include/Types.h"
#include <Windows.h>
#include <shellapi.h>
#include <fstream>
#include <iostream>

AutoUpdater::AutoUpdater() : updateAvailable(false) {}

bool AutoUpdater::CheckForUpdate() {
    // Check Fishstrap version file
    std::string currentVersion = Settings::Get("version", "2.9.0");
    // In production: fetch latest version from GitHub API
    // std::string latest = FetchURL("https://api.github.com/repos/.../releases/latest");
    return false;
}

bool AutoUpdater::DownloadUpdate() {
    if (!updateAvailable) return false;
    // Download new Fishstrap.zip from GitHub releases
    return true;
}

bool AutoUpdater::ApplyUpdate() {
    if (!DownloadUpdate()) return false;
    // Extract new version, restart Fishstrap
    char exe[MAX_PATH];
    GetModuleFileNameA(NULL, exe, MAX_PATH);
    std::string cmd = std::string(exe) + " --updated";
    ShellExecuteA(NULL, "runas", exe, "", NULL, SW_SHOW);
    return true;
}

void AutoUpdater::CheckRobloxVersion() {
    // Check if Roblox updated since last Fishstrap run
    char appData[MAX_PATH];
    GetEnvironmentVariableA("LOCALAPPDATA", appData, MAX_PATH);
    std::string versionFile = std::string(appData) + "\\Roblox\\Versions\\version.txt";
    std::ifstream f(versionFile);
    if (f.is_open()) {
        std::getline(f, robloxVersion);
        f.close();
    }
    std::string lastKnown = Settings::Get("lastRobloxVersion", "");
    if (!lastKnown.empty() && lastKnown != robloxVersion) {
        std::cout << "[AutoUpdater] Roblox updated! Version: " << robloxVersion << "\n";
        std::cout << "[AutoUpdater] Fishstrap may need an update.\n";
    }
    Settings::Set("lastRobloxVersion", robloxVersion);
}
