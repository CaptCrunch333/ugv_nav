#pragma once

#include "Line2D.hpp"

class PathGenerator2D
{
    public:
        void setTrack(std::vector<Vector2D<float>>);
        //gets the next pose 
        Vector3D<float> getNextPose(Vector3D<float>);
    private:
        std::vector<Vector2D<float>>::iterator m_current_vertex;
        int direction = 0;
        float tolerance = 0.05;
        std::vector<Vector2D<float>> m_track;
        std::vector<Vector2D<float>>::iterator getNextVertex();
};