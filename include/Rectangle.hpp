#pragma once
#include "Line2D.hpp"
#include "Vector3D.hpp"
#include "RotationMatrix3by3.hpp"
#include <vector>
enum rect_sides {side1,side2};
class Rectangle {
public:
    double altitude=0; 
    Rectangle();
    ~Rectangle() = default;
    //Point1 from side1 and side2 must match. Lines must be perpendicular. return true if successful
    bool updateRectangleSides(Line2D side1,Line2D side2); 
    Vector2D<double> getCenter();
    //Point1 from side1 and side2 is the fixed point.
    void scaleBy(double);
    void scaleBy(double scale_factor,rect_sides t_side_to_scale);
    void translateBy(Vector2D<double>);
    Vector2D<double> getClosestPoint(Vector2D<double> input_pt);
    Vector3D<double> getNormalOfPoint(Vector2D<double> input_pt, bool = true, double = 1.0);
    Line2D rotateVector(Line2D, double);
    bool checkPointIntersection(Vector2D<double>);
    bool checkPointEnclosure(Vector2D<double>);
    std::vector<Vector2D<double>> generateClosedPathFromStartingPoint(Vector2D<double>);
    std::vector<Vector2D<double>> generatePathSegmentFromTwoPoint(Vector2D<double>,Vector2D<double>);
    Line2D getSide1();
    Line2D getSide2();
    Line2D getSide3();
    Line2D getSide4();
private:
    Line2D side1,side2;
};

