#pragma once

#include "Line2D.hpp"
#include "logger.hpp"
#include <vector>

class PathGenerator2D
{
    public:
        void setTrack(std::vector<Vector2D<float>>);
        //gets the next pose 
        Vector3D<float> getNextPose(Line2D);
    private:
        std::vector<Vector2D<float>>::iterator m_current_vertex;
        int direction = 0;
        std::vector<Vector2D<float>> m_track;
        std::vector<Vector2D<float>>::iterator getNextVertex();
};