#pragma once
#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/BoundingBox.h>
#include "ROSUnit.hpp"
#include "Vector3D.hpp"
#include "DarknetMessage.hpp"
#include <math.h>

class ROSUnit_dark : public ROSUnit{

    private:
        static ROSUnit_dark* _instance_ptr;
        ros::Subscriber _sub_darknet;
        static DarknetMessage darknet_msg;
        static void callbackDarknet(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg);
        void receive_msg_data(DataMessage* t_msg);  
    public:
        ROSUnit_dark(ros::NodeHandle&);
        ~ROSUnit_dark();
};