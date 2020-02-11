#include "ROSUnitActClnt_StopBase.hpp"

ROSUnitActClnt_StopBase::ROSUnitActClnt_StopBase(std::string t_name, ros::NodeHandle& t_nh) : ROSUnit(t_nh) 
{
    m_StopBaseActClnt = t_nh.advertise<actionlib_msgs::GoalID>(t_name, 1, false);
}

ROSUnitActClnt_StopBase::~ROSUnitActClnt_StopBase(){ }

void ROSUnitActClnt_StopBase::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::EMPTY) {
        actionlib_msgs::GoalID t_empty_goal;
        m_StopBaseActClnt.publish(t_empty_goal);
    }
}