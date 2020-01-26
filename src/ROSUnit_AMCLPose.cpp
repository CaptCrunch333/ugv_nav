#include "ROSUnit_AMCLPose.hpp"

ROSUnit_AMCLPose* ROSUnit_AMCLPose::_instance_ptr = NULL;
Vector2DMsg ROSUnit_AMCLPose::_position_msg;
QuaternionMessage ROSUnit_AMCLPose::_quat_msg;

ROSUnit_AMCLPose::ROSUnit_AMCLPose(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler){

    //TODO: check topic names
    _sub_pose = t_main_handler.subscribe("/amcl_pose", 1, callbackPose);
    _instance_ptr = this;
}

ROSUnit_AMCLPose::~ROSUnit_AMCLPose() {

}

void ROSUnit_AMCLPose::callbackPose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    _position_msg.data.x = msg->pose.pose.position.x;
    _position_msg.data.y = msg->pose.pose.position.y;
    _instance_ptr->emit_message((DataMessage*) &_position_msg); 

    Quaternion t_quat;
    t_quat.x = msg->pose.pose.orientation.x;
    t_quat.y = msg->pose.pose.orientation.y;
    t_quat.z = msg->pose.pose.orientation.z;
    t_quat.w = msg->pose.pose.orientation.w;
    _quat_msg.setQuaternionMessage(t_quat);
    _instance_ptr->emit_message((DataMessage*) &_quat_msg); 
}
