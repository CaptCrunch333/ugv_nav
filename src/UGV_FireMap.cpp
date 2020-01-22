#include "UGV_FireMap.hpp"
#include <iostream>

UGV_FireMap::UGV_FireMap()
{
    Vector2D<double> t_point;
    t_point.x = 9.05;
    t_point.y = 5.55;
    MoveMap(t_point);
}

UGV_FireMap::~UGV_FireMap()
{
    
}

void UGV_FireMap::setFireLocation(Vector2D<double> t_point)
{
    std::cout << "Detected Location is: " << t_point.x << " " << t_point.y << std::endl;
    Vector2D<double> loc1, loc2;
    double dist1, dist2;
    loc1 = r1.getClosestPoint(t_point);
    std::cout << "Closest Location 1 is: " << loc1.x << " " << loc1.y << std::endl;
    loc2 = r2.getClosestPoint(t_point);
    std::cout << "Closest Location 2 is: " << loc2.x << " " << loc2.y << std::endl;
    dist1 = Vector2D<double>::getL2Norm(t_point,loc1);
    dist2 = Vector2D<double>::getL2Norm(t_point,loc2);
    std::cout << "Detected distances are: " << dist1 << " " << dist2 << std::endl;
    if(dist1 < dist2)
    {
        m_FireLocation = loc1;
        m_FireRectangle = &r1;
    }
    else
    {
        m_FireLocation = loc2;
        m_FireRectangle = &r2;
    }
    std::cout << "Fire Location is: " << m_FireLocation.x << " " << m_FireLocation.y << std::endl;
}

Vector3D<double> UGV_FireMap::getNormalToFire()
{
    Vector3D<double> t_ret;
    if(m_FireRectangle == &r1)
    {
        t_ret =  m_FireRectangle->getNormalOfPoint(m_FireLocation);
    }
    else if(m_FireRectangle == &r2)
    {
        t_ret =  m_FireRectangle->getNormalOfPoint(m_FireLocation, false);
    }
    std::cout << "Fire ext position is: " << t_ret.x << " " << t_ret.y << " " << t_ret.z << std::endl;
    return t_ret;
}

void UGV_FireMap::MoveMap(Vector2D<double> t_point)
{
    r1l1p1 = t_point;
    //std::cout << "box 1 Point 1: " << r1l1p1.x << " " << r1l1p1.y << std::endl;
    r1l1p2.x = r1l1p1.x;
    r1l1p2.y =  r1l1p1.y + 0.75;
    //std::cout << "box 1 Point 2: " << r1l1p2.x << " " << r1l1p2.y << std::endl;
    r1l2p1 = r1l1p1;
    //std::cout << "box 1 Point 3: " << r1l2p1.x << " " << r1l2p1.y << std::endl;
    r1l2p2.x = r1l1p1.x + 0.81;
    r1l2p2.y =  r1l2p1.y;
    //std::cout << "box 1 Point 4: " << r1l2p2.x << " " << r1l2p2.y << std::endl;

    r2l1p1.x = r1l1p1.x - 2.55;
    r2l1p1.y =  r1l1p1.y - 3.25;
    //std::cout << "box 2 Point 1: " << r2l1p1.x << " " << r2l1p1.y << std::endl;
    r2l1p2.x = r2l1p1.x;
    r2l1p2.y = r2l1p1.y + 9.8;
    //std::cout << "box 2 Point 2: " << r2l1p2.x << " " << r2l1p2.y << std::endl;
    r2l2p1 = r2l1p1;
    //std::cout << "box 2 Point 3: " << r2l2p1.x << " " << r2l2p1.y << std::endl;
    r2l2p2.x = r2l2p1.x + 5.8;
    r2l2p2.y = r2l2p1.y;
    //std::cout << "box 2 Point 4: " << r2l2p2.x << " " << r2l2p2.y << std::endl;

    r1l1.setPoint1(r1l1p1);
    r1l1.setPoint2(r1l1p2);

    r1l2.setPoint1(r1l2p1);
    r1l2.setPoint2(r1l2p2);

    r2l1.setPoint1(r2l1p1);
    r2l1.setPoint2(r2l1p2);

    r2l2.setPoint1(r2l2p1);
    r2l2.setPoint2(r2l2p2);

    r1.updateRectangleSides(r1l1, r1l2);
    //std::cout << "r1 fine" << std::endl;
    r2.updateRectangleSides(r2l1, r2l2);
    //std::cout << "r2 fine" << std::endl;
}

void UGV_FireMap::receive_msg_data(DataMessage*)
{

}