#pragma once
#include <string>
#include <regex>

class BlockPattern {
public:
    BlockPattern(std::string pattern, unsigned long color, bool isColor);
    bool isMatch(const std::string_view str, unsigned long msgColor) const;

private:
    std::string pattern;
    unsigned long color;
    bool isColor;
    std::regex regex;
};