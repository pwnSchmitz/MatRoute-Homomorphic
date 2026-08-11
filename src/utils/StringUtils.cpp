#include "utils/StringUtils.h"
#include <cstring>

namespace StringUtils {

std::string char32ToUtf8(char32_t c) {
    std::string result;
    
    if (c < 0x80) {
        result.push_back(static_cast<char>(c));
    } else if (c < 0x800) {
        result.push_back(static_cast<char>(0xC0 | (c >> 6)));
        result.push_back(static_cast<char>(0x80 | (c & 0x3F)));
    } else if (c < 0x10000) {
        result.push_back(static_cast<char>(0xE0 | (c >> 12)));
        result.push_back(static_cast<char>(0x80 | ((c >> 6) & 0x3F)));
        result.push_back(static_cast<char>(0x80 | (c & 0x3F)));
    } else {
        result.push_back(static_cast<char>(0xF0 | (c >> 18)));
        result.push_back(static_cast<char>(0x80 | ((c >> 12) & 0x3F)));
        result.push_back(static_cast<char>(0x80 | ((c >> 6) & 0x3F)));
        result.push_back(static_cast<char>(0x80 | (c & 0x3F)));
    }
    
    return result;
}

char32_t utf8ToChar32(const std::string& str, size_t& pos) {
    if (pos >= str.length()) {
        return 0;
    }
    
    unsigned char first = str[pos];
    size_t len = getUtf8CharLength(first);
    
    if (pos + len > str.length()) {
        pos++;
        return 0;
    }
    
    char32_t c = 0;
    
    if (len == 1) {
        c = first;
    } else if (len == 2) {
        c = ((str[pos] & 0x1F) << 6) | (str[pos+1] & 0x3F);
    } else if (len == 3) {
        c = ((str[pos] & 0x0F) << 12) | ((str[pos+1] & 0x3F) << 6) | (str[pos+2] & 0x3F);
    } else if (len == 4) {
        c = ((str[pos] & 0x07) << 18) | ((str[pos+1] & 0x3F) << 12) | 
            ((str[pos+2] & 0x3F) << 6) | (str[pos+3] & 0x3F);
    }
    
    pos += len;
    return c;
}

size_t getUtf8CharLength(unsigned char firstByte) {
    if (firstByte < 0x80) return 1;
    if ((firstByte & 0xE0) == 0xC0) return 2;
    if ((firstByte & 0xF0) == 0xE0) return 3;
    if ((firstByte & 0xF8) == 0xF0) return 4;
    return 1;
}

std::vector<char32_t> toChar32(const std::string& str) {
    std::vector<char32_t> result;
    size_t pos = 0;
    
    while (pos < str.length()) {
        char32_t c = utf8ToChar32(str, pos);
        if (c != 0) {
            result.push_back(c);
        }
    }
    
    return result;
}

std::string fromChar32(const std::vector<char32_t>& chars) {
    std::string result;
    for (char32_t c : chars) {
        result += char32ToUtf8(c);
    }
    return result;
}

} // namespace StringUtils