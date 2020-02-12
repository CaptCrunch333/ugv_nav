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
        void setGoal(std::vector<Vector3D<double>>);
        void setGoal(Vector3D<double>);
        Vector2D<double> getGoalPosition(); //TODO: this gives the last goal position, to be split into last and current
        double getGoalHeading();
        Vector2D<double> getCurrentPosition();
        double getCurrentHeading();
        void move();
        void stop();
        bool reachedPosition();
        void receive_msg_data(DataMessage*);
        void receive_msg_data(DataMessage*, int);

    private:
        Vector2D<double> m_CurrentPosition;
        std::vector<Vector3D<double>> m_GoalPose;
        actionlib_msgs::GoalStatus m_status;
        std::vector<Vector3D<double>> m_queue;
        double m_CurrentHeading;

        bool clearQueue();
};