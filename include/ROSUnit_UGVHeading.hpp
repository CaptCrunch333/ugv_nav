#pragma once
#include "ros/ros.h"
#include "ROSUnit.hpp"
#include "HeadingMsg.hpp"
#include <std_msgs/Float32.h>

class ROSUnit_UGVHeading : public ROSUnit {

private:
    static ROSUnit_UGVHeading* _instance_ptr;
    ros::Publisher _pub_heading;
    void receive_msg_data(DataMessage*);  
public:
    ROSUnit_UGVHeading(ros::NodeHandle&);
    ~ROSUnit_UGVHeading();
};