#include "core/Alphabet.h"
#include <iostream>
#include <random>

void Alphabet::initialize(const Matrix& matrix) {
    clear();
    
    // Initialize random generator
    std::random_device rd;
    rng.seed(rd());
    
    // Load alphabets
    loadLatinAlphabet();
    loadCyrillicAlphabet();
    
    std::cout << "Generating " << ROUTES_PER_LETTER << " routes for " 
              << letters.size() << " letters..." << std::endl;
    std::cout << "Points per route: 1-100 (random)" << std::endl;
    
    // Generate routes for each letter
    for (char32_t letter : letters) {
        generateRoutesForLetter(letter, matrix);
    }
    
    int totalRoutes = letters.size() * ROUTES_PER_LETTER;
    std::cout << "Done! Generated " << totalRoutes << " routes." << std::endl;
}

void Alphabet::clear() {
    letters.clear();
    letterRoutes.clear();
}

void Alphabet::loadLatinAlphabet() {
    std::vector<char32_t> latin = {
        U'A', U'B', U'C', U'D', U'E', U'F', U'G', U'H', U'I', U'J',
        U'K', U'L', U'M', U'N', U'O', U'P', U'Q', U'R', U'S', U'T',
        U'U', U'V', U'W', U'X', U'Y', U'Z'
    };
    letters.insert(letters.end(), latin.begin(), latin.end());
}

void Alphabet::loadCyrillicAlphabet() {
    std::vector<char32_t> cyrillic = {
        U'А', U'Б', U'В', U'Г', U'Д', U'Е', U'Ё', U'Ж', U'З', U'И',
        U'Й', U'К', U'Л', U'М', U'Н', U'О', U'П', U'Р', U'С', U'Т',
        U'У', U'Ф', U'Х', U'Ц', U'Ч', U'Ш', U'Щ', U'Ъ', U'Ы', U'Ь',
        U'Э', U'Ю', U'Я'
    };
    letters.insert(letters.end(), cyrillic.begin(), cyrillic.end());
}

void Alphabet::generateRoutesForLetter(char32_t letter, const Matrix& matrix) {
    std::vector<Route> routes;
    routes.reserve(ROUTES_PER_LETTER);
    
    for (int i = 0; i < ROUTES_PER_LETTER; i++) {
        routes.push_back(Route::generateRandom(matrix));
    }
    
    letterRoutes[letter] = routes;
}

bool Alphabet::isLetter(char32_t c) const {
    for (char32_t letter : letters) {
        if (letter == c) {
            return true;
        }
    }
    return false;
}

char32_t Alphabet::toUpper(char32_t c) const {
    if (c >= U'a' && c <= U'z') {
        return c - U'a' + U'A';
    }
    if (c >= U'а' && c <= U'я') {
        return c - U'а' + U'А';
    }
    if (c == U'ё') {
        return U'Ё';
    }
    return c;
}

const Route& Alphabet::getRandomRoute(char32_t letter) const {
    static std::uniform_int_distribution<> dis(0, ROUTES_PER_LETTER - 1);
    const auto& routes = letterRoutes.at(letter);
    return routes[dis(rng)];
}

bool Alphabet::findLetterByRoute(const Route& route, char32_t& outLetter) const {
    for (const auto& pair : letterRoutes) {
        for (const Route& storedRoute : pair.second) {
            if (storedRoute.matches(route.getPoints())) {
                outLetter = pair.first;
                return true;
            }
        }
    }
    return false;
}

size_t Alphabet::getTotalRoutes() const {
    return letters.size() * ROUTES_PER_LETTER;
}