#pragma once

#include "MsgEmitter.hpp"
#include "UGVNavMissionStateManager.hpp"
#include "Vector2DMsg.hpp"
#include "Vector3DMessage.hpp"
#include "FloatMsg.hpp"
#include "Line2D.hpp"
#include "logger.hpp"
#include "QuaternionMessage.hpp"

class WheeledRobot : public msg_receiver, public msg_emitter
{
    public:
        void setTolerance(float, float);
        void setGoalPosition(Vector2D<float>);
        void setGoalHeading(float);
        Vector2D<float> getGoalPosition();
        float getGoalHeading();
        Vector2D<float> getCurrentPosition();
        float getCurrentHeading();
        void move();
        void slide(float);
        void stop();
        bool reachedPosition();
        void receive_msg_data(DataMessage*);
        void receive_msg_data(DataMessage*, int);

    private:
        Vector2D<float> m_CurrentPosition, m_GoalPosition;
        float m_CurrentHeading, m_GoalHeading;
        float  m_pos_tol, m_heading_tol;
};