#pragma once

#include "Line2D.hpp"
#include <vector>

class Vertex2D
{
    public:
        Vertex2D(Vector2D<float>);
        void addNeighbor(Vector2D<float>);
        Vector2D<float> findPath(Vector2D<float>);
    private:
        Vector2D<float> m_pos;
        std::vector<std::pair<Vector2D<float>,float>> neighbors;
};
