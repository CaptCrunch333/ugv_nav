#include "Vertex2D.hpp"

Vertex2D::Vertex2D(Vector2D<float> t_pos)
{
    m_pos = t_pos;
}

void Vertex2D::addNeighbor(Vector2D<float> t_neighbor)
{
    // Line2D t_line;
    // t_line.setPoint1(m_pos);
    // t_line.setPoint2(t_neighbor);
    // float t_dist = t_line.getLength();
    // neighbors.push_back(std::pair(t_neighbor,t_dist));
}

Vector2D<float> Vertex2D::findPath(Vector2D<float> t_path)
{
    // for(int i = 0; i < neighbors.size(); i++)
    // {
    //     // TODO: implement
    // }
}