#pragma once

#include <string>
#include <vector>

namespace FileUtils {
    bool readTextFile(const std::string& filename, std::string& content);
    bool writeTextFile(const std::string& filename, const std::string& content);
    bool fileExists(const std::string& filename);
    std::string generateTimestampFilename(const std::string& prefix, const std::string& extension);
}