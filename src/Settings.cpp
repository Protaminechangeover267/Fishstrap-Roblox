#include "../include/FPSUnlocker.h"
#include <fstream>
#include <iostream>

Settings Settings::instance;

void Settings::Load(const std::string& path) {
    instance.data["targetFPS"] = "144";
    instance.data["shader"] = "none";
    instance.data["multiInstance"] = "false";
    instance.data["font"] = "default";
    instance.data["autoStart"] = "false";

    std::ifstream f(path);
    if (!f.is_open()) return;
    std::string line;
    while (std::getline(f, line)) {
        size_t c = line.find(':');
        if (c != std::string::npos) {
            std::string k = line.substr(0, c), v = line.substr(c + 1);
            k.erase(remove_if(k.begin(), k.end(), isspace), k.end());
            v.erase(remove_if(v.begin(), v.end(), isspace), v.end());
            instance.data[k] = v;
        }
    }
}

void Settings::Save(const std::string& path) {
    std::ofstream f(path);
    f << "{\n";
    for (auto it = instance.data.begin(); it != instance.data.end(); ++it) {
        f << "  \"" << it->first << "\": \"" << it->second << "\"";
        if (next(it) != instance.data.end()) f << ",";
        f << "\n";
    }
    f << "}\n";
}

std::string Settings::Get(const std::string& key, const std::string& def) {
    auto it = instance.data.find(key);
    return it != instance.data.end() ? it->second : def;
}

int Settings::GetInt(const std::string& key, int def) {
    std::string v = Get(key, "");
    return v.empty() ? def : std::stoi(v);
}

bool Settings::GetBool(const std::string& key, bool def) {
    return Get(key, def ? "true" : "false") == "true";
}

void Settings::Set(const std::string& key, const std::string& val) {
    instance.data[key] = val;
}
