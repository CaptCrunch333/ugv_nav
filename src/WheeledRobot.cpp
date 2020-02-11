#include "WheeledRobot.hpp"

void WheeledRobot::setGoal(std::vector<Vector3D<float>> t_goal) {
    m_GoalPose.clear();
    m_GoalPose = t_goal;
}

void WheeledRobot::setGoal(Vector3D<float> t_goal) {
    m_GoalPose.clear();
    m_GoalPose.push_back(t_goal);
}

Vector2D<float> WheeledRobot::getGoalPosition() {
    return m_GoalPose.back().project_xy();
}

float WheeledRobot::getGoalHeading() {
    return m_GoalPose.back().z;
}

Vector2D<float> WheeledRobot::getCurrentPosition() {
    return m_CurrentPosition;
}

float WheeledRobot::getCurrentHeading() {
    return m_CurrentHeading;
}

void WheeledRobot::move() {
    m_queue = m_GoalPose;
}

void WheeledRobot::stop() {
    EmptyMsg t_msg;
    this->emit_message((DataMessage*) &t_msg);
}

bool WheeledRobot::reachedPosition() {
    if(m_status.status == actionlib_msgs::GoalStatus::SUCCEEDED) {
        return true;
    }
    else {
        return false;
    }
    std::string t_txt_msg = "Goal ";
    t_txt_msg.append(m_status.text);
    t_txt_msg.append(" has status of: %f");
    Logger::getAssignedLogger()->log(t_txt_msg.c_str(), (float) m_status.status, LoggerLevel::Info);
}

void WheeledRobot::receive_msg_data(DataMessage* t_msg) {
    if(t_msg->getType() == msg_type::VECTOR2D) {
        m_CurrentPosition = ((Vector2DMsg*)t_msg)->data;
    }
    else if(t_msg->getType() == msg_type::HEADING) {
        m_CurrentHeading = ((FloatMsg*)t_msg)->data;
    }
}

void WheeledRobot::receive_msg_data(DataMessage* t_msg,int t_channel_id) {
    if(t_channel_id == (int)CHANNELS::GOAL_STATUS) {
        if(m_queue.size() == 0) {
            m_status = ((GoalStatusMsg*) t_msg)->goalStatus;
        }
        else if(((GoalStatusMsg*) t_msg)->goalStatus.status == actionlib_msgs::GoalStatus::SUCCEEDED) {
            this->clearQueue();
        }
    }
}

void WheeledRobot::clearQueue() {
    if(m_queue.size() > 0) {
        Vector2DMsg t_GoalPosMsg;
        t_GoalPosMsg.data = m_queue.front().project_xy();
        Vector3DMessage t_GoalHeadingMsg;
        t_GoalHeadingMsg.setVector3DMessage(Vector3D<float>({0,0, m_queue.front().z}));
        this->emit_message((DataMessage*) &t_GoalPosMsg);
        this->emit_message((DataMessage*) &t_GoalHeadingMsg);
        Logger::getAssignedLogger()->log("UGV Path appended: %f, %f, with orientation: %f", m_queue.front().x, m_queue.front().y, m_queue.front().z, LoggerLevel::Info);
        m_queue.erase(m_queue.begin());
    }
}