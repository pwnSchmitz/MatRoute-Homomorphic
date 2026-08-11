#include "core/Matrix.h"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

Matrix::Matrix() : size(DEFAULT_SIZE), operationCounter(0) {
    data.resize(size * size, 0);
}

bool Matrix::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    resize(DEFAULT_SIZE);
    int index = 0;
    int value;
    
    while (file >> value && index < size * size) {
        data[index] = value;
        index++;
    }
    file.close();
    
    // Fill missing values if file is incomplete
    if (index < size * size) {
        std::cout << "File contains only " << index << " numbers, adding random ones..." << std::endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        
        for (int i = index; i < size * size; i++) {
            data[i] = dis(gen);
        }
    }
    
    return true;
}

void Matrix::createNew() {
    generateRandom();
    operationCounter = 0;
}

void Matrix::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not save matrix to " << filename << std::endl;
        return;
    }
    
    for (int i = 0; i < size * size; i++) {
        file << data[i] << " ";
        if ((i + 1) % size == 0) {
            file << "\n";
        }
    }
    file.close();
}

int Matrix::getValue(int row, int col) const {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        return data[row * size + col];
    }
    return 0;
}

void Matrix::generateRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    for (int i = 0; i < size * size; i++) {
        data[i] = dis(gen);
    }
}

void Matrix::resize(int newSize) {
    size = newSize;
    data.assign(size * size, 0);
}