#include "BlockPatternLoader.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <sampapi/CChat.h>

namespace samp = sampapi::v037r1;
using json = nlohmann::json;

std::vector<BlockPattern> BlockPatternLoader::loadBlockPatterns(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        samp::RefChat()->AddMessage(0xFF00FF00, "No puedo abrir el archivo");
        throw std::runtime_error("No puedo abrir el archivo " + filename);
    }
    json j = json::parse(file);
    std::vector<BlockPattern> patterns;
    for (auto& p : j["patterns"]) {
        unsigned long color = 0;
        bool isColor = false;
        if (p.contains("color")) {
            color = p["color"].get<unsigned long>();
            isColor = true;
        }
        patterns.emplace_back(p["pattern"], color, isColor);
    }
    return patterns;
}