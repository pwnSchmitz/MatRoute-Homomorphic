#pragma once

#include <string>
#include "core/Matrix.h"
#include "core/Alphabet.h"

class Decryptor {
public:
    Decryptor(Matrix& matrix, const Alphabet& alphabet);
    ~Decryptor() = default;

    std::string decrypt(const std::string& ciphertext);

private:
    Matrix& matrix;
    const Alphabet& alphabet;
    
    std::vector<std::pair<int, int>> parseRoute(const std::string& routeStr) const;
};