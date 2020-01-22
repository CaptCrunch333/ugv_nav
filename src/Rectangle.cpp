#include "Rectangle.hpp"

Rectangle::Rectangle(){

}

bool Rectangle::updateRectangleSides(Line2D t_side1,Line2D t_side2){
    side1=t_side1;
    side2=t_side2;

}

Line2D Rectangle::getSide1(){
    return side1;
}
Line2D Rectangle::getSide2(){
    return side2;
}

Line2D Rectangle::getSide3(){
    Line2D side3=side1;
    side3.translateBy(side2.getPoint2()-side2.getPoint1());
    return side3;
}
Line2D Rectangle::getSide4(){
    Line2D side4=side2;
    side4.translateBy(side1.getPoint2()-side1.getPoint1());
    return side4;
}

Vector2D<double> Rectangle::getCenter(){
    Line2D side3=side1;
    side3.translateBy(side2.getPoint2()-side2.getPoint1());
    Vector2D<double> t_rect_center;
    t_rect_center.x=(side3.getCenter().x+side1.getCenter().x)/2.;
    t_rect_center.y=(side3.getCenter().y+side1.getCenter().y)/2.;
    return t_rect_center;
}

void Rectangle::scaleBy(double t_c){
    side1.scaleBy(t_c);
    side2.scaleBy(t_c);
}

void Rectangle::scaleBy(double scale_factor,rect_sides t_side_to_scale){
    if (t_side_to_scale==rect_sides::side1){
        side1.scaleBy(scale_factor);
    }
    else if (t_side_to_scale==rect_sides::side2){
        side2.scaleBy(scale_factor);
    }
}

void Rectangle::translateBy(Vector2D<double> t_d){
    side1.translateBy(t_d);
    side2.translateBy(t_d);
}

Vector2D<double> Rectangle::getClosestPoint(Vector2D<double> input_pt){
    //Workout all sides
    Line2D side3=side1;
    side3.translateBy(side2.getPoint2()-side2.getPoint1());
    Line2D side4=side2;
    side4.translateBy(side1.getPoint2()-side1.getPoint1());
    std::vector<Line2D> rect_sides;
    rect_sides.push_back(side1);
    rect_sides.push_back(side2);
    rect_sides.push_back(side3);
    rect_sides.push_back(side4);
    //Find the closest point based on shortest distance
    std::vector<double> dist_to_each_side;
    std::vector<Vector2D<double>> closest_point_at_each_side;
    for (std::vector<Line2D>::iterator it = rect_sides.begin() ; it != rect_sides.end(); ++it){
        closest_point_at_each_side.push_back(it->getClosestPoint(input_pt));
        dist_to_each_side.push_back(Vector2D<double>::getL2Norm(it->getClosestPoint(input_pt),input_pt));
    }
    auto min_dist_idx=std::min_element(dist_to_each_side.begin(),dist_to_each_side.end())-dist_to_each_side.begin();
    Vector2D<double> closest_point=closest_point_at_each_side[min_dist_idx];
    return closest_point;
}

Vector3D<double> Rectangle::getNormalOfPoint(Vector2D<double> input_pt, bool direction, double size)
{
    Line2D found_line;
    //Workout all sides
    Line2D side3=getSide3();
    Line2D side4=getSide4();
    if (side1.checkPointIntesection(input_pt)){ //TODO refactor
        found_line = side1;
        std::cout << "found, side 1\n";
    }
    if (side2.checkPointIntesection(input_pt)){
        found_line = side2;
        std::cout << "found, side 2\n";
    }
    if (side3.checkPointIntesection(input_pt)){
        found_line = side3;
        std::cout << "found, side 3\n";
    }
    if (side4.checkPointIntesection(input_pt)){
        found_line = side4;
        std::cout << "found, side 4\n";
    }
    found_line.scaleBy(0.5);
    found_line.translateBy(found_line.getPoint1() * -1 + input_pt);
    found_line = rotateVector(found_line, M_PI/2.0);
    if(checkPointEnclosure(found_line.getPoint2()))
    {
        std::cout << "Enclosed\n ";
        if(direction)
        {
            found_line = rotateVector(found_line, M_PI);
        }
    }
    else
    {
        if(!direction)
        {
            std::cout << "Rotate\n ";
            found_line = rotateVector(found_line, M_PI);
        }
    }
    found_line.scaleBy(size/found_line.getLength());
    Line2D ads_line;
    ads_line.setPoint1(found_line.getPoint2());
    ads_line.setPoint2(found_line.getPoint1());
    Vector3D<double> ret_vec;
    ret_vec.x = found_line.getPoint2().x;
    ret_vec.y = found_line.getPoint2().y;
    ret_vec.z = ads_line.getAngle();
    return ret_vec;
}



bool Rectangle::checkPointIntersection(Vector2D<double> t_point){
    //Workout all sides
    Line2D side3=side1;
    side3.translateBy(side2.getPoint2()-side2.getPoint1());
    Line2D side4=side2;
    side4.translateBy(side1.getPoint2()-side1.getPoint1());
    if (side1.checkPointIntesection(t_point)){ //TODO refactor
        return true;
    }
    if (side2.checkPointIntesection(t_point)){
        return true;
    }
    if (side3.checkPointIntesection(t_point)){
        return true;
    }
    if (side4.checkPointIntesection(t_point)){
        return true;
    }
    return false;
}

std::vector<Vector2D<double>> Rectangle::generateClosedPathFromStartingPoint(Vector2D<double> t_point){
    std::vector<Vector2D<double>> wayPoints2D;
    wayPoints2D.push_back(t_point);
    //Workout all sides
    Line2D side3=side1;
    side3.translateBy(side2.getPoint2()-side2.getPoint1());
    Line2D side4=side2;
    side4.translateBy(side1.getPoint2()-side1.getPoint1());
    if (side1.checkPointIntesection(t_point)){//TODO: Refactor
        wayPoints2D.push_back(side1.getPoint2());
        wayPoints2D.push_back(side4.getPoint2());
        wayPoints2D.push_back(side3.getPoint1());
        wayPoints2D.push_back(side2.getPoint1());
        wayPoints2D.push_back(t_point);
    }
    else if (side2.checkPointIntesection(t_point)){
        wayPoints2D.push_back(side2.getPoint1());
        wayPoints2D.push_back(side1.getPoint2());
        wayPoints2D.push_back(side4.getPoint2());
        wayPoints2D.push_back(side3.getPoint1());
        wayPoints2D.push_back(t_point);
    }
    else if (side3.checkPointIntesection(t_point)){
        wayPoints2D.push_back(side3.getPoint1());
        wayPoints2D.push_back(side2.getPoint1());
        wayPoints2D.push_back(side1.getPoint2());
        wayPoints2D.push_back(side4.getPoint2());
        wayPoints2D.push_back(t_point);
    }
    else if (side4.checkPointIntesection(t_point)){
        wayPoints2D.push_back(side4.getPoint2());
        wayPoints2D.push_back(side3.getPoint1());
        wayPoints2D.push_back(side2.getPoint1());
        wayPoints2D.push_back(side1.getPoint2());
        wayPoints2D.push_back(t_point);
    }
    return wayPoints2D;
}

std::vector<Vector2D<double>> Rectangle::generatePathSegmentFromTwoPoint(Vector2D<double> t_point_start,Vector2D<double> t_point_end){
    std::vector<Vector2D<double>> wayPoints2D;
    wayPoints2D.push_back(t_point_start);
    //Workout all sides
    Line2D side3=side1;
    side3.translateBy(side2.getPoint2()-side2.getPoint1());
    Line2D side4=side2;
    side4.translateBy(side1.getPoint2()-side1.getPoint1());
    // Note that the waypoints are not fully optimized for shortest path
    if (side1.checkPointIntesection(t_point_start)){//TODO: Refactor
        if (side2.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side1.getPoint1());
        }
        else if (side3.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side4.getPoint1());
            wayPoints2D.push_back(side4.getPoint2());
        }
        else if (side4.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side1.getPoint2());
        }
    }
    else if (side2.checkPointIntesection(t_point_start)){
        if (side1.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side2.getPoint1());
        }
        else if (side3.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side2.getPoint2());
        }
        else if (side4.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side1.getPoint1());
            wayPoints2D.push_back(side1.getPoint2());
        }
    }
    else if (side3.checkPointIntesection(t_point_start)){
        if (side1.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side2.getPoint2());
            wayPoints2D.push_back(side2.getPoint1());
        }
        else if (side2.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side3.getPoint1());
        }
        else if (side4.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side3.getPoint2());
        }
    }
    else if (side4.checkPointIntesection(t_point_start)){
        if (side1.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side4.getPoint1());
        }
        else if (side2.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side3.getPoint2());
            wayPoints2D.push_back(side3.getPoint1());
        }
        else if (side3.checkPointIntesection(t_point_end)){
            wayPoints2D.push_back(side4.getPoint2());
        }
    }
    wayPoints2D.push_back(t_point_end);
    return wayPoints2D;
}

Line2D Rectangle::rotateVector(Line2D t_line, double t_ang)
{
    Vector2D<double> t_2DPointAfterRotation;
    Vector2D<double> original_pos = t_line.getPoint1();
    Vector3D<float> ang_vec;
    Vector3D<float> t_3DPointAfterRotation, t_3DPointBeforeRotation;
    RotationMatrix3by3 t_rotation_matrix;
    ang_vec.x = 0;
    ang_vec.y = 0;
    ang_vec.z = (float)t_ang;

    t_line.translateBy(t_line.getPoint1() * -1);
    t_rotation_matrix.Update(ang_vec);
    t_3DPointBeforeRotation.x = t_line.getPoint2().x;
    t_3DPointBeforeRotation.y = t_line.getPoint2().y;
    t_3DPointBeforeRotation.z = 0.f;
    t_3DPointAfterRotation = t_rotation_matrix.TransformVector(t_3DPointBeforeRotation);
    t_2DPointAfterRotation.x = t_3DPointAfterRotation.x;
    t_2DPointAfterRotation.y = t_3DPointAfterRotation.y;
    t_line.setPoint2(t_2DPointAfterRotation);
    t_line.translateBy(original_pos);
    return t_line;
}

bool Rectangle::checkPointEnclosure(Vector2D<double> t_point)
{
    Vector2D<double> t_clst_point = getSide1().getClosestPoint(t_point);
    if(t_clst_point.getL2Norm(t_clst_point, t_point) < getSide2().getLength())
    {
        t_clst_point = getSide3().getClosestPoint(t_point);
        if(t_clst_point.getL2Norm(t_clst_point, t_point) < getSide2().getLength())
        {
            t_clst_point = getSide2().getClosestPoint(t_point);
            if(t_clst_point.getL2Norm(t_clst_point, t_point) < getSide1().getLength())
            {
                t_clst_point = getSide4().getClosestPoint(t_point);
                if(t_clst_point.getL2Norm(t_clst_point, t_point) < getSide1().getLength())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// TODO: write a sorting algorithm to generate a path in elegant way
// void reorder_vec(vector<char>& vA, vector<size_t>& vOrder)  
// {   
//     assert(vA.size() == vOrder.size());

//     // for all elements to put in place
//     for( int i = 0; i < va.size() - 1; ++i )
//     { 
//         // while the element i is not yet in place 
//         while( i != vOrder[i] )
//         {
//             // swap it with the element at its final place
//             int alt = vOrder[i];
//             swap( vA[i], vA[alt] );
//             swap( vOrder[i], vOrder[alt] );
//         }
//     }
// }