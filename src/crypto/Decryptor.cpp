#include "crypto/Decryptor.h"
#include "utils/StringUtils.h"
#include <sstream>

Decryptor::Decryptor(Matrix& mat, const Alphabet& alph) 
    : matrix(mat), alphabet(alph) {}

std::string Decryptor::decrypt(const std::string& ciphertext) {
    if (matrix.isExpired()) {
        std::cout << "Matrix lifetime expired! Creating new matrix..." << std::endl;
        matrix.createNew();
        // Note: Alphabet would need reinitialization here
    }
    
    std::string plaintext;
    size_t pos = 0;
    
    while (pos < ciphertext.length()) {
        if (ciphertext[pos] == '{') {
            // Find the matching closing brace
            size_t endPos = ciphertext.find('}', pos);
            if (endPos != std::string::npos) {
                std::string routeStr = ciphertext.substr(pos + 1, endPos - pos - 1);
                auto points = parseRoute(routeStr);
                
                if (!points.empty()) {
                    Route route(points);
                    char32_t letter;
                    
                    if (alphabet.findLetterByRoute(route, letter)) {
                        plaintext += StringUtils::char32ToUtf8(letter);
                    } else {
                        plaintext += '?';
                    }
                }
                pos = endPos + 1;
                continue;
            }
        }
        plaintext += ciphertext[pos];
        pos++;
    }
    
    matrix.incrementOperation();
    std::cout << "Matrix operations used: " << matrix.getOperationCount() 
              << "/" << Matrix::MAX_LIFETIME << std::endl;
    
    return plaintext;
}

std::vector<std::pair<int, int>> Decryptor::parseRoute(const std::string& routeStr) const {
    std::vector<std::pair<int, int>> points;
    std::stringstream ss(routeStr);
    std::string point;
    
    while (std::getline(ss, point, ',')) {
        size_t sepPos = point.find(';');
        if (sepPos != std::string::npos) {
            int row = std::stoi(point.substr(0, sepPos));
            int col = std::stoi(point.substr(sepPos + 1));
            points.push_back({row, col});
        }
    }
    
    return points;
}