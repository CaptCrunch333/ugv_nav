#pragma once

#include "UGVNavMissionStateManager.hpp"
#include "MsgEmitter.hpp"
#include "logger.hpp"
#include "Vector2DMsg.hpp"

class UGVNavigator : public msg_emitter, public msg_receiver
{
    public:
        void setHomeBaseLocation(Vector2D<double>);
        void setEntranceLocation(Vector2D<double>);
        void receive_msg_data(DataMessage* t_msg,int t_channel_id);

    private:
        Vector2D<double> m_HomePosition, m_Entrance;
};