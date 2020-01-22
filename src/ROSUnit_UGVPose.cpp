#include "ROSUnit_UGVPose.hpp"

ROSUnit_UGVPose::ROSUnit_UGVPose(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler) {
    _pub_pose = t_main_handler.advertise <geometry_msgs::Point> ("/ugv_nav/inertial_pos",1);
}

ROSUnit_UGVPose::~ROSUnit_UGVPose()
{

};

void ROSUnit_UGVPose::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::POSITION)
    {
        PositionMsg t_positionmsg = *((PositionMsg*) t_msg);
        geometry_msgs::Point t_point;
        
        t_point.x = t_positionmsg.x;
        t_point.y = t_positionmsg.y;
        t_point.z = t_positionmsg.z;

        _pub_pose.publish(t_point);
    }

}