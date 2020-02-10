#pragma once

#include <vector>

#include "UGVNavMissionStateManager.hpp"
#include "PathGenerator2D.hpp"
#include "MsgEmitter.hpp"
#include "Map2D.hpp"
#include "logger.hpp"
#include "FloatMsg.hpp"
#include "Vector2DMsg.hpp"
#include "VectorMsg.hpp"
#include "Line2D.hpp"
#include "Vector3DMessage.hpp"
#include "WheeledRobot.hpp"
#include "Timer.hpp"
#include "TimedBlock.hpp"
#include "UGVPatrolStates.hpp"

class UGVNavigator : public msg_emitter, public msg_receiver, public TimedBlock  {
    public:
        UGVNavigator(WheeledRobot*, block_frequency);
        void setHomeBaseLocation(Vector2D<double>, float);
        void setEntranceLocation(Vector2D<double>, float);
        //SetScanPath takes the scan path under the following conditions:
        //The first point is the entrance point
        //The following points should be the scan path in order
        //The Final Point Should have a path to the initial Point
        void setScanningPath(std::vector<Vector2D<float>>);
        void setMap(Map2D*);
        void setSearchTimeOut(int); //TODO: remove
        void setReachingGoalPositionTimeOut(int); //TODO: remove
        void receive_msg_data(DataMessage*); 
        void receive_msg_data(DataMessage* ,int);
        void loopInternal();

    private:
        WheeledRobot* m_robot;
        Map2D* m_Map;
        PathGenerator2D m_PathGenerator;
        Timer m_Timer;
        Line2D m_FireDirection;
        UGVPatrolState m_PatrolState = UGVPatrolState::IDLE;
        Vector2D<double> m_HomePosition, m_EntrancePosition, m_FireLocation, m_ExtLocation;
        int m_SearchTimeOut = 5000, m_ReachingGoalPositionTimeOut = 40000;
        float m_HomeHeading, m_EntranceHeading, m_FireHeading, m_ExtHeading;
};