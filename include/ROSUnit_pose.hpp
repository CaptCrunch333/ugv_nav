#pragma once
#include "ros/ros.h"
#include "ROSUnit.hpp"
#include "PositionMsg.hpp"
#include "QuaternionMessage.hpp"
#include <geometry_msgs/PoseWithCovarianceStamped.h>



class ROSUnit_pose : public ROSUnit {

private:
    static ROSUnit_pose* _instance_ptr;
    ros::Subscriber _sub_pose;
    static PositionMsg _position_msg;
    static QuaternionMessage _quat_msg;
    static void callbackPose(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
    void receive_msg_data(DataMessage* t_msg){};  
public:
    ROSUnit_pose(ros::NodeHandle&);
    ~ROSUnit_pose();
};