#pragma once
#include <string>
#include <fstream>
#include <algorithm>

class Settings {
    static Settings instance;
public:
    std::unordered_map<std::string, std::string> data;
    static void Load(const std::string& path);
    static void Save(const std::string& path);
    static std::string Get(const std::string& key, const std::string& def = "");
    static int GetInt(const std::string& key, int def = 0);
    static bool GetBool(const std::string& key, bool def = false);
    static void Set(const std::string& key, const std::string& val);
};

class MultiInstance {
    bool enabled;
public:
    MultiInstance();
    bool Enable();
    void Disable();
    bool IsEnabled() const { return enabled; }
};

class FontManager {
    std::string activeFont;
public:
    FontManager();
    bool Load(const std::string& name);
    void Unload();
    std::string GetActive() const { return activeFont; }
};

class ShaderLoader {
    std::string activeShader;
    std::string code;
public:
    ShaderLoader();
    bool Load(const std::string& name);
    void Unload();
    std::string GetActive() const;
    const std::string& GetCode() const { return code; }
};

class Launcher {
    std::string installPath;
public:
    Launcher();
    bool Install();
    bool LaunchRoblox();
    std::string GetInstallPath() const { return installPath; }
};
