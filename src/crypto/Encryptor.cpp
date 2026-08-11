#include "crypto/Encryptor.h"
#include "utils/StringUtils.h"
#include <random>

Encryptor::Encryptor(Matrix& mat, const Alphabet& alph) 
    : matrix(mat), alphabet(alph) {}

std::string Encryptor::encrypt(const std::string& plaintext) {
    if (matrix.isExpired()) {
        std::cout << "Matrix lifetime expired! Creating new matrix..." << std::endl;
        matrix.createNew();
        // Note: Alphabet would need reinitialization here
    }
    
    std::string ciphertext;
    size_t pos = 0;
    
    while (pos < plaintext.length()) {
        char32_t c = StringUtils::utf8ToChar32(plaintext, pos);
        
        if (shouldProcessCharacter(c)) {
            ciphertext += processCharacter(c);
            ciphertext += " ";
        } else {
            // Keep non-letter characters as is
            size_t charLen = StringUtils::getUtf8CharLength(plaintext[pos]);
            ciphertext.append(plaintext, pos - charLen + 1, charLen);
        }
    }
    
    matrix.incrementOperation();
    std::cout << "Matrix operations used: " << matrix.getOperationCount() 
              << "/" << Matrix::MAX_LIFETIME << std::endl;
    
    return ciphertext;
}

std::string Encryptor::processCharacter(char32_t c) {
    char32_t upper = alphabet.toUpper(c);
    const Route& route = alphabet.getRandomRoute(upper);
    return "{" + route.toCompactString() + "}";
}

bool Encryptor::shouldProcessCharacter(char32_t c) const {
    return alphabet.isLetter(alphabet.toUpper(c));
}