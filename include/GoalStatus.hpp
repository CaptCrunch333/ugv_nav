#pragma once

#include "DataMessage.hpp"
#include <actionlib_msgs/GoalStatus.h>

class GoalStatus : public DataMessage
{

public:

    GoalStatus();
    ~GoalStatus();
    msg_type getType();
    const int getSize();
    actionlib_msgs::GoalStatus goalStatus;
};