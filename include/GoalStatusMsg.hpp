#pragma once

#include "DataMessage.hpp"
#include <actionlib_msgs/GoalStatus.h>

class GoalStatusMsg : public DataMessage
{

public:

    GoalStatusMsg();
    ~GoalStatusMsg();
    msg_type getType();
    const int getSize();
    actionlib_msgs::GoalStatus goalStatus;
};