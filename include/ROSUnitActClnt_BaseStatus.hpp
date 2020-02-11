#pragma once

#include "ROSUnit.hpp"
#include <actionlib_msgs/GoalStatusArray.h>
#include "EmptyMsg.hpp"
#include "GoalStatusMsg.hpp"
#include "logger.hpp"

class ROSUnitActClnt_BaseStatus : public ROSUnit
{
    public:
        ROSUnitActClnt_BaseStatus(std::string, ros::NodeHandle&);
        ~ROSUnitActClnt_BaseStatus();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:
        ros::Subscriber m_sub;
        static ROSUnitActClnt_BaseStatus* instance_ptr;
        static void BaseStatusCB(const actionlib_msgs::GoalStatusArrayConstPtr&);
};