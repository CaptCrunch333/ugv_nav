#pragma once
#include "ros/ros.h"
#include "ROSUnit.hpp"
#include "Vector2DMsg.hpp"
#include "QuaternionMessage.hpp"
#include <geometry_msgs/PoseWithCovarianceStamped.h>

class ROSUnit_AMCLPose : public ROSUnit {

private:
    static ROSUnit_AMCLPose* _instance_ptr;
    ros::Subscriber _sub_pose;
    static Vector2DMsg _position_msg;
    static QuaternionMessage _quat_msg;
    static void callbackPose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
    void receive_msg_data(DataMessage* t_msg){};  
public:
    ROSUnit_AMCLPose(ros::NodeHandle&);
    ~ROSUnit_AMCLPose();
};