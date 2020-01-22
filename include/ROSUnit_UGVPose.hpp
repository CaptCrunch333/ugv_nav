#pragma once
#include "ros/ros.h"
#include "ROSUnit.hpp"
#include "PositionMsg.hpp"
//#include "HeadingMsg.hpp"
#include <geometry_msgs/Point.h>

class ROSUnit_UGVPose : public ROSUnit {

private:
    static ROSUnit_UGVPose* _instance_ptr;
    ros::Publisher _pub_pose;
    //ros::Publisher _pub_heading;
    void receive_msg_data(DataMessage*);  
public:
    ROSUnit_UGVPose(ros::NodeHandle&);
    ~ROSUnit_UGVPose();
};