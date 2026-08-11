#include "core/Route.h"
#include "core/Matrix.h"
#include <random>
#include <sstream>

Route::Route(const std::vector<std::pair<int, int>>& pts) : points(pts), sum(0) {}

void Route::addPoint(int row, int col) {
    points.push_back({row, col});
}

void Route::clear() {
    points.clear();
    sum = 0;
}

long long Route::calculateSum(const Matrix& matrix) const {
    sum = 0;
    for (const auto& p : points) {
        sum += matrix.getValue(p.first, p.second);
    }
    return sum;
}

std::string Route::toCompactString() const {
    std::string result;
    for (size_t i = 0; i < points.size(); i++) {
        result += std::to_string(points[i].first) + ";" + std::to_string(points[i].second);
        if (i < points.size() - 1) result += ",";
    }
    return result;
}

bool Route::matches(const std::vector<std::pair<int, int>>& otherPoints) const {
    if (points.size() != otherPoints.size()) {
        return false;
    }
    
    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].first != otherPoints[i].first || 
            points[i].second != otherPoints[i].second) {
            return false;
        }
    }
    return true;
}

Route Route::generateRandom(const Matrix& matrix) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> disCoord(0, matrix.getSize() - 1);
    std::uniform_int_distribution<> disPoints(1, 100);
    
    Route route;
    int numPoints = disPoints(gen);
    
    for (int i = 0; i < numPoints; i++) {
        route.addPoint(disCoord(gen), disCoord(gen));
    }
    
    route.calculateSum(matrix);
    return route;
}