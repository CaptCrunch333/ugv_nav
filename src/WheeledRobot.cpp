#include "WheeledRobot.hpp"

void WheeledRobot::setTolerance(float t_val, float t_val_heading) {
    m_pos_tol = t_val;
    m_heading_tol = t_val_heading;
}

void WheeledRobot::setGoalPosition(Vector2D<float> t_pos) {
    m_GoalPosition = t_pos;
}

void WheeledRobot::setGoalHeading(float t_val) {
    m_GoalHeading = t_val;
}

Vector2D<float> WheeledRobot::getGoalPosition() {
    return m_GoalPosition;
}

float WheeledRobot::getGoalHeading() {
    return m_GoalHeading;
}

Vector2D<float> WheeledRobot::getCurrentPosition() {
    return m_CurrentPosition;
}

float WheeledRobot::getCurrentHeading() {
    return m_CurrentHeading;
}

void WheeledRobot::move() {
    Vector2DMsg t_GoalPosMsg;
    t_GoalPosMsg.data = m_GoalPosition;
    Vector3DMessage t_GoalHeadingMsg;
    t_GoalHeadingMsg.setVector3DMessage(Vector3D<float>({0,0, m_GoalHeading}));
    this->emit_message((DataMessage*) &t_GoalPosMsg);
    this->emit_message((DataMessage*) &t_GoalHeadingMsg);
    Logger::getAssignedLogger()->log("UGV Moving to: %f, %f, with orientation: %f", m_GoalPosition.x, m_GoalPosition.y, m_GoalHeading, LoggerLevel::Info);
}

void WheeledRobot::stop() {
    Vector2DMsg t_GoalPosMsg;
    t_GoalPosMsg.data = m_CurrentPosition;
    QuaternionMessage t_GoalHeadingMsg;
    Quaternion t_GoalHeading;
    t_GoalHeading.x = 0;
    t_GoalHeading.y = 0;
    t_GoalHeading.z = 0;
    t_GoalHeading.w = 0;
    t_GoalHeadingMsg.setQuaternionMessage(t_GoalHeading);
    this->emit_message((DataMessage*) &t_GoalPosMsg);
    this->emit_message((DataMessage*) &t_GoalHeadingMsg);
}

bool WheeledRobot::reachedPosition() {
    Line2D line;
    line.setPoint1(m_CurrentPosition);
    line.setPoint2(m_GoalPosition);
    if(line.getLength() <= m_pos_tol) {
        if(fabs(m_CurrentHeading - m_GoalHeading) <= m_heading_tol) {
            return true;
        }
    }
    return false;
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

}