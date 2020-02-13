#include "PathGenerator2D.hpp"

void PathGenerator2D::setTrack(Rectangle t_in_building_track){
    in_building_track=t_in_building_track;
}

double PathGenerator2D::getTrackLength() {
    return 2*(in_building_track.getSide1().getLength() + in_building_track.getSide2().getLength());
}

//gets the next pose 
std::vector<Vector3D<double>> PathGenerator2D::generateParametricPath(Vector2D<double> initial_position, double parameter){
    clearPath();
    //Logger::getAssignedLogger()->log("init position is: %f , %f and step is: %f", initial_position.x, initial_position.y, parameter, LoggerLevel::Warning);
    std::vector<Vector2D<double>> waypoints=in_building_track.generatePathSegmentFromPointAndParameter(initial_position,parameter);
    waypoints_with_heading=add_heading_for_waypoints(waypoints);
    return waypoints_with_heading;
}

Vector3D<double> PathGenerator2D::getNextPose(){
    return waypoints_with_heading[waypoint_counter++];
}

void PathGenerator2D::clearPath(){
    if (waypoints_with_heading.size()>0){
        waypoints_with_heading.clear();
    }
    waypoint_counter=0;
}

std::vector<Vector3D<double>> PathGenerator2D::add_heading_for_waypoints(std::vector<Vector2D<double>> waypoints){
    std::vector<Vector3D<double>> result_wpts;
    if (waypoints.size()==1){
        Vector3D<double> waypoint_zero_heading;
        result_wpts.push_back(waypoint_zero_heading);
        return result_wpts;
    }
    for (int i= 0; i <(waypoints.size()-1);i++){
        Vector2D<double> diff_with_next_wp=waypoints[i+1]-waypoints[i];
        Vector3D<double> waypoint_with_heading;
        waypoint_with_heading.x=waypoints[i].x;
        waypoint_with_heading.y=waypoints[i].y;
        waypoint_with_heading.z=atan2(diff_with_next_wp.y,diff_with_next_wp.x);
        result_wpts.push_back(waypoint_with_heading);
    }
    Vector3D<double> waypoint_with_heading;
    waypoint_with_heading.x=(waypoints.end()-1)->x;
    waypoint_with_heading.y=(waypoints.end()-1)->y;
    result_wpts.push_back(waypoint_with_heading);
    result_wpts[waypoints.size()-1].z=result_wpts[waypoints.size()-2].z;
    return result_wpts;
}
