#pragma once

#include <string>
#include <vector>

namespace StringUtils {
    std::string char32ToUtf8(char32_t c);
    char32_t utf8ToChar32(const std::string& str, size_t& pos);
    size_t getUtf8CharLength(unsigned char firstByte);
    std::vector<char32_t> toChar32(const std::string& str);
    std::string fromChar32(const std::vector<char32_t>& chars);
}