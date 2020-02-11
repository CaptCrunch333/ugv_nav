#pragma once

#include "ROSUnit.hpp"
#include <actionlib_msgs/GoalID.h>
#include "EmptyMsg.hpp"

class ROSUnitActClnt_StopBase : public ROSUnit
{
    public:
        ROSUnitActClnt_StopBase(std::string, ros::NodeHandle&);
        ~ROSUnitActClnt_StopBase();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage*);

    private:
        ros::Publisher m_StopBaseActClnt;
};