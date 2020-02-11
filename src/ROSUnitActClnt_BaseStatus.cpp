#include "ROSUnitActClnt_BaseStatus.hpp"

ROSUnitActClnt_BaseStatus* ROSUnitActClnt_BaseStatus::instance_ptr;

ROSUnitActClnt_BaseStatus::ROSUnitActClnt_BaseStatus(std::string t_name, ros::NodeHandle& t_nh) : ROSUnit(t_nh) 
{
    m_sub = t_nh.subscribe(t_name,1, BaseStatusCB);
    ROSUnitActClnt_BaseStatus::instance_ptr = this;
}

ROSUnitActClnt_BaseStatus::~ROSUnitActClnt_BaseStatus(){ }

void ROSUnitActClnt_BaseStatus::BaseStatusCB(const actionlib_msgs::GoalStatusArrayConstPtr& t_msg) 
{
    IntegerMsg t_int_msg;
    t_int_msg.data = t_msg->status_list.back().status;
    instance_ptr->emit_message((DataMessage*) &t_int_msg);
}

void ROSUnitActClnt_BaseStatus::receive_msg_data(DataMessage* t_msg) {
}