#include "PathGenerator2D.hpp"

void PathGenerator2D::setTrack(std::vector<Vector2D<float>> t_track)
{
    m_track = t_track;
    m_current_vertex = m_track.begin();
}

Vector3D<float> PathGenerator2D::getNextPose(Vector3D<float> t_curr_pose)
{  
    if(m_current_vertex == m_track.begin())
    {
        Line2D line1, line2;
        line1.setPoint1(*m_current_vertex);
        line2.setPoint1(*m_current_vertex);
        line1.setPoint2(m_track.at(1));
        line2.setPoint2(*m_track.end());
        if(line1.getAngle() <= line2.getAngle())
        {
            m_current_vertex = m_track.begin()+1;
            direction = 1;
        }
        else
        {
            m_current_vertex = m_track.end();
            direction = -1;
        }
    }
    else
    {
        m_current_vertex = getNextVertex();
    }
    
    Line2D line;
    line.setPoint1(*m_current_vertex);
    line.setPoint2(*(getNextVertex()));
    return {(*m_current_vertex).x, (*m_current_vertex).x, (float)line.getAngle()};
}

 std::vector<Vector2D<float>>::iterator PathGenerator2D::getNextVertex()
{
    if(m_current_vertex == m_track.end() && direction == 1)
    {
        return m_track.begin();
    }
    else if (m_current_vertex == m_track.begin() && direction == -1)
    {
        return m_track.end();
    }
    else
    {
        return m_current_vertex + direction;
    }
}