#include "Map2D.hpp"

Map2D::Map2D() {
    //TODO: remove after file change
    Vector2D<double> t_point;
    t_point.x = 9.05;
    t_point.y = 5.55;
    MoveMap(t_point);
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
    //TODO: make it (+,+) to all
    r1l1p1 = t_point;

    r1l1p2.x = r1l1p1.x;
    r1l1p2.y =  r1l1p1.y + 0.75;

    r1l2p1 = r1l1p1;

    r1l2p2.x = r1l1p1.x + 0.81;
    r1l2p2.y =  r1l2p1.y;

    r2l1p1.x = r1l1p1.x - 2.55;
    r2l1p1.y =  r1l1p1.y - 3.25;

    r2l1p2.x = r2l1p1.x;
    r2l1p2.y = r2l1p1.y + 9.8;

    r2l2p1 = r2l1p1;

    r2l2p2.x = r2l2p1.x + 5.8;
    r2l2p2.y = r2l2p1.y;


    r1l1.setPoint1(r1l1p1);
    r1l1.setPoint2(r1l1p2);

    r1l2.setPoint1(r1l2p1);
    r1l2.setPoint2(r1l2p2);

    r2l1.setPoint1(r2l1p1);
    r2l1.setPoint2(r2l1p2);

    r2l2.setPoint1(r2l2p1);
    r2l2.setPoint2(r2l2p2);

    r1.updateRectangleSides(r1l1, r1l2);
    r2.updateRectangleSides(r2l1, r2l2);
}