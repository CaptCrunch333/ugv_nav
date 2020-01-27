#pragma once

#include <vector>

#include "UGVNavMissionStateManager.hpp"
#include "PathGenerator2D.hpp"
#include "MsgEmitter.hpp"
#include "logger.hpp"
#include "FloatMsg.hpp"
#include "Vector2DMsg.hpp"
#include "PointsMsg.hpp"
#include "Line2D.hpp"
#include "Vector3DMessage.hpp"

enum class CHANNELS {DIRECTION_UPDATER = 1, POSITION_UPDATER = 2, INTERNAL_STATE_UPDATER = 3};

class UGVNavigator : public msg_emitter, public msg_receiver
{
    public:
        void setHomeBaseLocation(Vector2D<double>, float);
        void setEntranceLocation(Vector2D<double>, float);
        //SetScanPath takes the scan path under the following conditions:
        //The first point is the entrance point
        //The following points should be the scan path in order
        //The Final Point Should have a path to the initial Point
        void setScanningPath(std::vector<Vector2D<float>>);
        void receive_msg_data(DataMessage*);
        void receive_msg_data(DataMessage* ,int);

    private:
        PathGenerator2D m_PathGenerator;
        std::vector<Vector2D<float>> m_scanning_pos;
        Line2D m_FireDirection;
        Vector2D<double> m_HomePosition, m_EntrancePosition, m_current_pos, m_FireLocation;
        bool m_FireDirectionFound = false, m_FireLocationFound = false;
        float m_current_heading, m_HomeHeading, m_EntranceHeading;
        Vector3DMessage m_msg;
};