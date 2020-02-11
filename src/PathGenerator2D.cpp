#include "PathGenerator2D.hpp"

void PathGenerator2D::setTrack(std::vector<Vector2D<float>> t_track)
{
    m_track = t_track;
    m_current_vertex = m_track.begin();
}

int PathGenerator2D::getTrackLength()
{
    return m_track.size()-1;
}

Vector3D<float> PathGenerator2D::getNextPose(Line2D t_fire_dir)
{  
    m_current_vertex = getNextVertex();

    Line2D line;
    line.setPoint1(*m_current_vertex);
    line.setPoint2(*(getNextVertex()));
    return {(*m_current_vertex).x, (*m_current_vertex).y, (float)line.getAngle()};
}

 std::vector<Vector2D<float>>::iterator PathGenerator2D::getNextVertex()
{
    if(m_current_vertex == (m_track.end()-1) && direction == 1)
    {
        return m_track.begin()+1;
    }
    else if (m_current_vertex == m_track.begin()+1 && direction == -1)
    {
        return (m_track.end()-1);
    }
    else
    {
        return m_current_vertex + direction;
    }
}