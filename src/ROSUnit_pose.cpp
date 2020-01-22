#include "ROSUnit_pose.hpp"


ROSUnit_pose* ROSUnit_pose::_instance_ptr = NULL;
PositionMsg ROSUnit_pose::_position_msg;
QuaternionMessage ROSUnit_pose::_quat_msg;

ROSUnit_pose::ROSUnit_pose(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler){

    //TODO: check topic names
    _sub_pose = t_main_handler.subscribe("/amcl_pose", 1, callbackPose);
    _instance_ptr = this;
}

ROSUnit_pose::~ROSUnit_pose() {

}

void ROSUnit_pose::callbackPose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    std::cout<<"msg received" << std::endl;
    _position_msg.x = msg->pose.pose.position.x;
    _position_msg.y = msg->pose.pose.position.y;
    _position_msg.z = msg->pose.pose.position.z;

    _instance_ptr->emit_message((DataMessage*) &_position_msg); 

    Quaternion t_quat;
    t_quat.x = msg->pose.pose.orientation.x;
    t_quat.y = msg->pose.pose.orientation.y;
    t_quat.z = msg->pose.pose.orientation.z;
    t_quat.w = msg->pose.pose.orientation.w;
    _quat_msg.setQuaternionMessage(t_quat);
    _instance_ptr->emit_message((DataMessage*) &_quat_msg); 
}
