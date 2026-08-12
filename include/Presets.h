#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct ShaderPreset {
    std::string name;
    std::string description;
    std::string glslPath;
    bool isBuiltIn;
};

struct FastFlagsPreset {
    std::string name;
    std::string description;
    std::unordered_map<std::string, std::string> flags;
};

struct FontPreset {
    std::string name;
    std::string fontFile;
    std::string description;
};

class ShaderPresets {
public:
    static std::vector<ShaderPreset> GetAll() {
        return {
            {"none", "No shader", "", true},
            {"realism", "Enhanced realistic lighting", "shaders/realism.glsl", true},
            {"cartoon", "Cel-shaded anime effect", "shaders/cartoon.glsl", true},
            {"vibrant", "Boosted color saturation", "shaders/vibrant.glsl", true},
            {"noir", "Black and white film effect", "shaders/noir.glsl", true},
            {"vaporwave", "Aesthetic 80s/90s effect", "shaders/vaporwave.glsl", true},
        };
    }
};

class FastFlagsPresets {
public:
    static FastFlagsPreset GetBalanced() {
        return {"balanced", "Recommended for most users", {
            {"FFlagDebugGraphicsPreferD3D11", "true"},
            {"DFIntTaskSchedulerTargetFps", "144"},
            {"FFlagBufferGeometricShapes", "true"},
        }};
    }
    static FastFlagsPreset GetPerformance() {
        return {"performance", "Max FPS on low-end PCs", {
            {"FFlagDebugGraphicsPreferD3D11", "true"},
            {"DFIntTaskSchedulerTargetFps", "9999"},
            {"FFlagBufferGeometricShapes", "true"},
            {"FFlagDebugDisableTelemetryEphemeralStatistics", "true"},
            {"FFlagDebugDisableTelemetryPoint", "true"},
        }};
    }
    static FastFlagsPreset GetQuality() {
        return {"quality", "Best visuals on high-end PCs", {
            {"FFlagDebugGraphicsPreferD3D11", "true"},
            {"DFIntTaskSchedulerTargetFps", "240"},
            {"FFlagFastGPULightCulling", "true"},
            {"FFlagImproveTextureQuality", "true"},
        }};
    }
};
