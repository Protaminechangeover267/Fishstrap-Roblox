#include "../include/FastFlagsManager.h"
#include <fstream>
#include <shlobj.h>

bool FastFlagsManager::Load(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) return false;
    std::string line;
    while (std::getline(f, line)) {
        size_t c = line.find(':');
        if (c != std::string::npos) {
            std::string k = line.substr(0, c), v = line.substr(c + 1);
            k.erase(remove_if(k.begin(), k.end(), isspace), k.end());
            v.erase(remove_if(v.begin(), v.end(), isspace), v.end());
            flags[k] = v;
        }
    }
    return !flags.empty();
}

void FastFlagsManager::Apply() {
    char appData[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appData);
    std::string dir = std::string(appData) + "\\Roblox\\ClientSettings\\";
    CreateDirectoryA(dir.c_str(), NULL);
    std::ofstream f(dir + "ClientAppSettings.json");
    f << "{\n";
    for (auto it = flags.begin(); it != flags.end(); ++it) {
        f << "  \"" << it->first << "\": " << it->second;
        if (next(it) != flags.end()) f << ",";
        f << "\n";
    }
    f << "}\n";
}
