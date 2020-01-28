#pragma once
#include "ros/ros.h"
#include "ROSUnit.hpp"
#include "Vector2DMsg.hpp"
#include "QuaternionMessage.hpp"
#include <geometry_msgs/PoseStamped.h>
#include "logger.hpp"

class ROSUnit_UGVMoveBase : public ROSUnit {

private:
    static ROSUnit_UGVMoveBase* _instance_ptr;
    ros::Publisher _pub_pose;
    geometry_msgs::PoseStamped m_PoseStamped;
    void receive_msg_data(DataMessage*);
public:
    ROSUnit_UGVMoveBase(ros::NodeHandle&);
    ~ROSUnit_UGVMoveBase();
};