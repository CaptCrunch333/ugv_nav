#include "ROSUnit_UGVMoveBase.hpp"

ROSUnit_UGVMoveBase::ROSUnit_UGVMoveBase(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler) {
    _pub_pose = t_main_handler.advertise <geometry_msgs::PoseStamped> ("/move_base_simple/goal",1);
}

ROSUnit_UGVMoveBase::~ROSUnit_UGVMoveBase()
{

};

void ROSUnit_UGVMoveBase::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::POSITION)
    {
        PositionMsg t_positionmsg = *((PositionMsg*) t_msg);
        geometry_msgs::PoseStamped t_PoseStamped;

        t_PoseStamped.header.frame_id = "map";
        
        t_PoseStamped.pose.position.x = t_positionmsg.x;
        t_PoseStamped.pose.position.y = t_positionmsg.y;
        t_PoseStamped.pose.position.z = t_positionmsg.z;
        t_PoseStamped.pose.orientation.w = 1;
        _pub_pose.publish(t_PoseStamped);
    }
}