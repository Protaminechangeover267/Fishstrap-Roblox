#pragma once
#include <string>
#include <unordered_map>

class FastFlagsManager {
    std::unordered_map<std::string, std::string> flags;
public:
    bool Load(const std::string& path);
    void Apply();
    void Set(const std::string& key, const std::string& val) { flags[key] = val; }
    std::string Get(const std::string& key) const {
        auto it = flags.find(key); return it != flags.end() ? it->second : "";
    }
    int Count() const { return (int)flags.size(); }
};
