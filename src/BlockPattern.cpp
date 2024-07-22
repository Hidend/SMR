#include "BlockPattern.h"
#include <regex>
#include <stdexcept>
#include <iostream>
#include <sampapi/CChat.h>
namespace samp = sampapi::v037r1;

BlockPattern::BlockPattern(std::string pattern, unsigned long color, bool isColor)
    : pattern(std::move(pattern)), color(color), isColor(isColor) {
    try {
        regex = std::regex(this->pattern);
    } catch (const std::regex_error& e) {
        samp::RefChat()->AddMessage(0xFF00FF00, ("Error en el regex: " + this->pattern).c_str());
    }
}

bool BlockPattern::isMatch(const std::string_view str, unsigned long msgColor) const {
    if (isColor && msgColor != color) {
        return false;
    }
    return std::regex_search(str.begin(), str.end(), regex);
}