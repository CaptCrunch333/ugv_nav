#pragma once

#include "Line2D.hpp"
#include "logger.hpp"
#include "Rectangle.hpp"
#include "print_utility.hpp"
#include <vector>

class PathGenerator2D
{
    public:
        void setTrack(Rectangle);
        double getTrackLength();
        //gets the next pose 
        std::vector<Vector3D<double>> generateParametricPath(Vector2D<double>,double parameter); //+: ccw | -:cw
        Vector3D<double> getNextPose();
        void clearPath();
    private:
        std::vector<Vector3D<double>> add_heading_for_waypoints(std::vector<Vector2D<double>>);
        Rectangle in_building_track;
        std::vector<Vector3D<double>> waypoints_with_heading;
        int waypoint_counter=0;
};