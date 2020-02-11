#pragma once

#include "MsgEmitter.hpp"
#include "UGVNavMissionStateManager.hpp"
#include "EmptyMsg.hpp"
#include "Vector2DMsg.hpp"
#include "Vector3DMessage.hpp"
#include "FloatMsg.hpp"
#include "GoalStatusMsg.hpp"
#include "Line2D.hpp"
#include "logger.hpp"
#include "QuaternionMessage.hpp"

class WheeledRobot : public msg_receiver, public msg_emitter
{
    public:
        WheeledRobot();
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
        std::vector<Vector3D<float>> m_GoalPose;
        actionlib_msgs::GoalStatus m_status;
        std::vector<Vector3D<float>> m_queue;
        float m_CurrentHeading;

        bool clearQueue();
};