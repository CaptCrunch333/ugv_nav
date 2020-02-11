#include "ROSUnitActClnt_MoveBase.hpp"

ROSUnitActClnt_MoveBase::ROSUnitActClnt_MoveBase(std::string t_name, ros::NodeHandle& t_nh) : ROSUnit(t_nh) 
{
    m_MoveBaseGoalActClnt = new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>(t_name, true);
}

ROSUnitActClnt_MoveBase::~ROSUnitActClnt_MoveBase(){ }

void ROSUnitActClnt_MoveBase::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::VECTOR2D) {
        Vector2DMsg* t_positionmsg = ((Vector2DMsg*) t_msg);

        m_goal.target_pose.header.frame_id = "map";
        m_goal.target_pose.header.seq = ++m_goalID;
        m_goal.target_pose.header.stamp = ros::Time();
        m_goal.target_pose.pose.position.x = t_positionmsg->data.x;
        m_goal.target_pose.pose.position.y = t_positionmsg->data.y;
        m_goal.target_pose.pose.position.z = 0;
    }
    else if(t_msg->getType() == msg_type::QUATERNION)
    {
        QuaternionMessage* t_quat_msg = (QuaternionMessage*) t_msg;
        m_goal.target_pose.pose.orientation.w = t_quat_msg->getData().w;
        m_goal.target_pose.pose.orientation.x = t_quat_msg->getData().x;
        m_goal.target_pose.pose.orientation.y = t_quat_msg->getData().y;
        m_goal.target_pose.pose.orientation.z = t_quat_msg->getData().z;
        m_MoveBaseGoalActClnt->sendGoal(m_goal);
    }
}