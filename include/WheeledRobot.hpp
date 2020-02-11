#pragma once

#include "MsgEmitter.hpp"
#include "UGVNavMissionStateManager.hpp"
#include "EmptyMsg.hpp"
#include "Vector2DMsg.hpp"
#include "Vector3DMessage.hpp"
#include "FloatMsg.hpp"
#include "GoalStatus.hpp"
#include "Line2D.hpp"
#include "logger.hpp"
#include "QuaternionMessage.hpp"

class WheeledRobot : public msg_receiver, public msg_emitter
{
    public:
        void setGoal(std::vector<Vector3D<float>>);
        void setGoal(Vector3D<float>);
        Vector2D<float> getGoalPosition(); //TODO: this gives the last goal position, to be split into last and current
        float getGoalHeading();
        Vector2D<float> getCurrentPosition();
        float getCurrentHeading();
        void move();
        void stop();
        bool reachedPosition();
        void receive_msg_data(DataMessage*);
        void receive_msg_data(DataMessage*, int);

    private:
        Vector2D<float> m_CurrentPosition;
        std::vector<Vector2D<float>> m_GoalPosition;
        std::vector<float> m_GoalHeading;
        actionlib_msgs::GoalStatus m_status;
        float m_CurrentHeading;
};