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

class UGVNavigator : public msg_emitter, public msg_receiver {
    public:
        UGVNavigator(WheeledRobot*);
        void setHomeBaseLocation(Vector2D<double>, float);
        void setEntranceLocation(Vector2D<double>, float);
        //SetScanPath takes the scan path under the following conditions:
        //The first point is the entrance point
        //The following points should be the scan path in order
        //The Final Point Should have a path to the initial Point
        void setScanningPath(std::vector<Vector2D<float>>);
        void setMap(Map2D*);
        void setSearchTimeOut(int);
        void receive_msg_data(DataMessage*);
        void receive_msg_data(DataMessage* ,int);

    private:
        WheeledRobot* m_robot;
        Map2D* m_Map;
        PathGenerator2D m_PathGenerator;
        Timer m_Timer;
        Line2D m_FireDirection;
        Vector2D<double> m_HomePosition, m_EntrancePosition, m_FireLocation;
        int m_SerchTimeOut = 5000;
        float m_HomeHeading, m_EntranceHeading, m_FireHeading;
};