#include "WheeledRobot.hpp"

void WheeledRobot::setGoal(std::vector<Vector3D<float>> t_goal) {
    m_GoalPosition.clear();
    for(int i = 0; i < t_goal.size(); i++) {
        m_GoalPosition.push_back(t_goal.at(i).project_xy());
        m_GoalHeading.push_back(t_goal.at(i).z);
    }
}

void WheeledRobot::setGoal(Vector3D<float> t_goal) {
    m_GoalPosition.clear();
    m_GoalPosition.push_back(t_goal.project_xy());
    m_GoalHeading.push_back(t_goal.z);
}

Vector2D<float> WheeledRobot::getGoalPosition() {
    return m_GoalPosition.back();
}

float WheeledRobot::getGoalHeading() {
    return m_GoalHeading.back();
}

Vector2D<float> WheeledRobot::getCurrentPosition() {
    return m_CurrentPosition;
}

float WheeledRobot::getCurrentHeading() {
    return m_CurrentHeading;
}

void WheeledRobot::move() {
    for(int i = 0; i < m_GoalPosition.size(); i++) {
        Vector2DMsg t_GoalPosMsg;
        t_GoalPosMsg.data = m_GoalPosition.at(i);
        Vector3DMessage t_GoalHeadingMsg;
        t_GoalHeadingMsg.setVector3DMessage(Vector3D<float>({0,0, m_GoalHeading.at(i)}));
        this->emit_message((DataMessage*) &t_GoalPosMsg);
        this->emit_message((DataMessage*) &t_GoalHeadingMsg);
        Logger::getAssignedLogger()->log("UGV Path appended: %f, %f, with orientation: %f", m_GoalPosition.at(i).x, m_GoalPosition.at(i).y, m_GoalHeading.at(i), LoggerLevel::Info);
    }
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
        m_status = ((GoalStatus*) t_msg)->goalStatus;
    }
}