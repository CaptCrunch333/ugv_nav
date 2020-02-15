#pragma once

#include <vector>

#include "UGVNavMissionStateManager.hpp"
#include "PathGenerator2D.hpp"
#include "MsgEmitter.hpp"
#include "Map2D.hpp"
#include "logger.hpp"
#include "FloatMsg.hpp"
#include "Vector3DMessage.hpp"
#include "PoseMsg.hpp"
#include "WheeledRobot.hpp"
#include "TimedBlock.hpp"

class UGVNavigator : public msg_emitter, public msg_receiver, public TimedBlock  {
    public:
        UGVNavigator(WheeledRobot*, block_frequency);
        void setScanningPath(Rectangle*);
        void setMap(Map2D*);
        void receive_msg_data(DataMessage*); 
        void receive_msg_data(DataMessage* ,int);
        void loopInternal();

    private:
        WheeledRobot* m_robot;
        Map2D* m_Map;
        PathGenerator2D m_PathGenerator;
        Line2D m_FireDirection;
        Vector2D<float> m_FireLocation, m_ExtLocation;
        float m_FireHeading, m_ExtHeading, m_stepSize;

        void reset();
};