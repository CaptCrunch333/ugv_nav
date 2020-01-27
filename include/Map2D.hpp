#pragma once
#include "Rectangle.hpp"
#include "logger.hpp"

class Map2D {
    public:
        Map2D();
        ~Map2D();
        void MoveMap(Vector2D<double>);
        void setObjectLocation(Vector2D<double>);
        Vector3D<double> getNormalToObject();

    private:
        Vector2D<double> m_ObjectLocation;
        Rectangle* m_ObjectRectangle;
        Vector2D<double> r1l1p1;
        Vector2D<double> r1l1p2;
        Vector2D<double> r1l2p1;
        Vector2D<double> r1l2p2;
        Vector2D<double> r2l1p1;
        Vector2D<double> r2l1p2;
        Vector2D<double> r2l2p1;
        Vector2D<double> r2l2p2;
        Line2D r1l1, r1l2, r2l1, r2l2;
        Rectangle r1, r2;
};