#pragma once
#include "Rectangle.hpp"
#include "logger.hpp"

class Map2D {
    public:
        Map2D(std::vector<Rectangle>);
        ~Map2D();
        void MoveMap(Vector2D<double>);
        void setObjectLocation(Vector2D<double>);
        Vector3D<double> getNormalToObject();

    private:
        Vector2D<double> m_ObjectLocation;
        Rectangle* m_ObjectRectangle;
        Rectangle r1, r2;
};