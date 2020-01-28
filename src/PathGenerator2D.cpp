#include "PathGenerator2D.hpp"

void PathGenerator2D::setTrack(std::vector<Vector2D<float>> t_track)
{
    m_track = t_track;
    m_current_vertex = m_track.begin();
}

Vector3D<float> PathGenerator2D::getNextPose(Line2D t_fire_dir)
{  
    if(m_current_vertex == m_track.begin())
    {
        Line2D line1, line2;
        line1.setPoint1(*m_current_vertex);
        line2.setPoint1(*m_current_vertex);
        line1.setPoint2(m_track.at(1));
        line2.setPoint2(*(m_track.end()-1));
        Logger::getAssignedLogger()->log("m_current_vertex: %f, %f", (*m_current_vertex).x, (*m_current_vertex).y, LoggerLevel::Info);
        Logger::getAssignedLogger()->log("point 2 line 1: %f, %f", m_track.at(1).x, m_track.at(1).y, LoggerLevel::Info);
        Logger::getAssignedLogger()->log("point 2 line 2: %f, %f", (*(m_track.end()-1)).x, (*(m_track.end()-1)).y, LoggerLevel::Info);
        if((abs(line1.getAngle() - t_fire_dir.getAngle())) <= abs(line2.getAngle() - t_fire_dir.getAngle()))
        {
            m_current_vertex = m_track.begin()+1;
            direction = 1;
        }
        else
        {
            m_current_vertex = m_track.end()-1;
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