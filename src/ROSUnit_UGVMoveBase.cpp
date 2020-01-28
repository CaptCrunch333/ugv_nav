#include "ROSUnit_UGVMoveBase.hpp"

ROSUnit_UGVMoveBase::ROSUnit_UGVMoveBase(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler) {
    _pub_pose = t_main_handler.advertise <geometry_msgs::PoseStamped> ("/move_base_simple/goal",1);
}

ROSUnit_UGVMoveBase::~ROSUnit_UGVMoveBase()
{

};

void ROSUnit_UGVMoveBase::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::VECTOR2D)
    {
        Vector2DMsg* t_positionmsg = ((Vector2DMsg*) t_msg);

        m_PoseStamped.header.frame_id = "map";
        
        m_PoseStamped.pose.position.x = t_positionmsg->data.x;
        m_PoseStamped.pose.position.y = t_positionmsg->data.y;
        m_PoseStamped.pose.position.z = 0;
        Logger::getAssignedLogger()->log("received pos", LoggerLevel::Info);
    }
    else if(t_msg->getType() == msg_type::QUATERNION)
    {
        QuaternionMessage* t_quat_msg = (QuaternionMessage*) t_msg;
        m_PoseStamped.pose.orientation.w = t_quat_msg->getData().w;
        m_PoseStamped.pose.orientation.x = t_quat_msg->getData().x;
        m_PoseStamped.pose.orientation.y = t_quat_msg->getData().y;
        m_PoseStamped.pose.orientation.z = t_quat_msg->getData().z;
        Logger::getAssignedLogger()->log("received quat", LoggerLevel::Info);
        _pub_pose.publish(m_PoseStamped);
    }
}