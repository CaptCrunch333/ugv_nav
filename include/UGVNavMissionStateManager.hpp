#pragma once
#include "MsgEmitter.hpp"
#include "IntegerMsg.hpp"
#include "logger.hpp"
#include "UGVNavState.hpp"

enum class CHANNELS {FIRE_DIRECTION_UPDATER = 1, FIRE_POSITION_UPDATER = 2, INTERNAL_STATE_UPDATER = 3, PATROL_UPDATER = 4, POSITION_ADJUSTMENT = 5, GOAL_STATUS = 6, CHANGE_POSE = 7, GO_TO_FIRE = 8};

class UGVNavMissionStateManager : public msg_emitter, public msg_receiver
{
public:
    void updateMissionState(UGVNavState);
    UGVNavState getMissionState();
    void receive_msg_data(DataMessage*);

private:
    UGVNavState m_current_state = UGVNavState::WARMINGUP;
    void displayStateChange();
};

extern UGVNavMissionStateManager mainUGVNavMissionStateManager;