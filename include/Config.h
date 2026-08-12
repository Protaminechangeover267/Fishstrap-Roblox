#pragma once
#include <string>
#include "../include/Types.h"

namespace Config {
    inline void Load(const std::string& path) { Settings::Load(path); }
    inline void Save(const std::string& path) { Settings::Save(path); }
    inline std::string Get(const std::string& key, const std::string& def = "") { return Settings::Get(key, def); }
    inline int GetInt(const std::string& key, int def = 0) { return Settings::GetInt(key, def); }
    inline bool GetBool(const std::string& key, bool def = false) { return Settings::GetBool(key, def); }
}
