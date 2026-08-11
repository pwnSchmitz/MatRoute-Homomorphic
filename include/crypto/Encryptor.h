#pragma once

#include <string>
#include "core/Matrix.h"
#include "core/Alphabet.h"

class Encryptor {
public:
    Encryptor(Matrix& matrix, const Alphabet& alphabet);
    ~Encryptor() = default;

    std::string encrypt(const std::string& plaintext);

private:
    Matrix& matrix;
    const Alphabet& alphabet;
    
    std::string processCharacter(char32_t c);
    bool shouldProcessCharacter(char32_t c) const;
};