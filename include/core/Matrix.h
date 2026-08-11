#pragma once

#include <vector>
#include <string>

class Matrix {
public:
    static const int DEFAULT_SIZE = 200;
    static const int MAX_LIFETIME = 2;

    Matrix();
    ~Matrix() = default;

    bool loadFromFile(const std::string& filename);
    void createNew();
    void saveToFile(const std::string& filename) const;
    
    int getValue(int row, int col) const;
    int getSize() const { return size; }
    int getOperationCount() const { return operationCounter; }
    int getRemainingOperations() const { return MAX_LIFETIME - operationCounter; }
    bool isExpired() const { return operationCounter >= MAX_LIFETIME; }
    void incrementOperation() { operationCounter++; }
    void resetOperationCounter() { operationCounter = 0; }

    const std::vector<int>& getData() const { return data; }

private:
    std::vector<int> data;
    int size;
    int operationCounter;
    
    void generateRandom();
    void resize(int newSize);
};