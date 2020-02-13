#include "Map2D.hpp"

Map2D::Map2D(std::vector<Rectangle> t_rectangles) {
    // for(int i = 0; i < t_rectangles.size(); i++) {  
    // }
    r1 = t_rectangles.at(0);
    r2 = t_rectangles.at(1);
}

Map2D::~Map2D() {
    
}

void Map2D::setObjectLocation(Vector2D<double> t_point) {
    //TODO: make it read from a txt files
    //Logger::getAssignedLogger()->log("Detected Location is: %f and %f", t_point.x, t_point.y, LoggerLevel::Info);
    Vector2D<double> loc1, loc2;
    double dist1, dist2;
    loc1 = r1.getClosestPoint(t_point);
    //Logger::getAssignedLogger()->log("Closest Location 1 is: %f and %f", loc1.x,  loc1.y, LoggerLevel::Info);
    loc2 = r2.getClosestPoint(t_point);
    //Logger::getAssignedLogger()->log("Closest Location 2 is: %f and %f", loc2.x,  loc2.y, LoggerLevel::Info);
    dist1 = Vector2D<double>::getL2Norm(t_point,loc1);
    dist2 = Vector2D<double>::getL2Norm(t_point,loc2);
    //Logger::getAssignedLogger()->log("Detected distances are: %f and %f", dist1,  dist2, LoggerLevel::Info);
    if(dist1 < dist2)
    {
        m_ObjectLocation = loc1;
        m_ObjectRectangle = &r1;
    }
    else
    {
        m_ObjectLocation = loc2;
        m_ObjectRectangle = &r2;
    }
    //Logger::getAssignedLogger()->log("Fire location is: %f and %f", m_ObjectLocation.x,  m_ObjectLocation.y, LoggerLevel::Info);
}

Vector3D<double> Map2D::getNormalToObject() {
    Vector3D<double> t_ret;
    if(m_ObjectRectangle == &r1)
    {
        t_ret =  m_ObjectRectangle->getNormalOfPoint(m_ObjectLocation);
    }
    else if(m_ObjectRectangle == &r2)
    {
        t_ret =  m_ObjectRectangle->getNormalOfPoint(m_ObjectLocation, false);
    }
    //Logger::getAssignedLogger()->log("Fire ext position is: %f and %f , and heading is: %f", t_ret.x,  t_ret.y, t_ret.z, LoggerLevel::Info);
    return t_ret;
}

void Map2D::MoveMap(Vector2D<double> t_point) {
    // TODO: implement
}