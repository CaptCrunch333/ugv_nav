#pragma once

#include "ROSUnit.hpp"
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"
#include <move_base_msgs/MoveBaseAction.h>
#include "Vector2DMsg.hpp"
#include "QuaternionMessage.hpp"

class ROSUnitActClnt_MoveBase : public ROSUnit
{
    public:
        ROSUnitActClnt_MoveBase(std::string, ros::NodeHandle&);
        ~ROSUnitActClnt_MoveBase();
        //Change the receive_msg_data code to reflect your system
        void receive_msg_data(DataMessage* t_msg);

    private:
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>* m_MoveBaseGoalActClnt;
		int m_goalID = 0;
		move_base_msgs::MoveBaseGoal m_goal;
};