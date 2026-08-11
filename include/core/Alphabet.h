#pragma once

#include <map>
#include <vector>
#include <string>
#include "Route.h"

class Alphabet {
public:
    Alphabet() = default;
    ~Alphabet() = default;

    void initialize(const Matrix& matrix);
    void clear();
    
    bool isLetter(char32_t c) const;
    char32_t toUpper(char32_t c) const;
    
    const Route& getRandomRoute(char32_t letter) const;
    bool findLetterByRoute(const Route& route, char32_t& outLetter) const;
    
    size_t getLetterCount() const { return letters.size(); }
    size_t getTotalRoutes() const;
    const std::vector<char32_t>& getAllLetters() const { return letters; }
    
    static const int ROUTES_PER_LETTER = 150;

private:
    std::vector<char32_t> letters;
    std::map<char32_t, std::vector<Route>> letterRoutes;
    mutable std::mt19937 rng;
    
    void loadLatinAlphabet();
    void loadCyrillicAlphabet();
    void generateRoutesForLetter(char32_t letter, const Matrix& matrix);
};