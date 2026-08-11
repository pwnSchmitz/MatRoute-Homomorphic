#pragma once

#include <vector>
#include <string>
#include <utility>

class Route {
public:
    Route() = default;
    Route(const std::vector<std::pair<int, int>>& points);
    
    void addPoint(int row, int col);
    void clear();
    long long calculateSum(const class Matrix& matrix) const;
    
    const std::vector<std::pair<int, int>>& getPoints() const { return points; }
    size_t getPointCount() const { return points.size(); }
    long long getSum() const { return sum; }
    
    std::string toCompactString() const;
    bool matches(const std::vector<std::pair<int, int>>& otherPoints) const;
    
    static Route generateRandom(const Matrix& matrix);

private:
    std::vector<std::pair<int, int>> points;
    long long sum = 0;
};