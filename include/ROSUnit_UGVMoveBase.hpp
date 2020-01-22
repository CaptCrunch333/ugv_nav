#pragma once
#include "ros/ros.h"
#include "ROSUnit.hpp"
#include "PositionMsg.hpp"
#include <geometry_msgs/PoseStamped.h>

class ROSUnit_UGVMoveBase : public ROSUnit {

private:
    static ROSUnit_UGVMoveBase* _instance_ptr;
    ros::Publisher _pub_pose;
    //ros::Publisher _pub_heading;
    void receive_msg_data(DataMessage*);  
public:
    ROSUnit_UGVMoveBase(ros::NodeHandle&);
    ~ROSUnit_UGVMoveBase();
};