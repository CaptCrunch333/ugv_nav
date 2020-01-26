#pragma once
#include "MsgEmitter.hpp"
#include "IntegerMsg.hpp"
#include "logger.hpp"

enum class UGVNavState {WARMINGUP, IDLE, UTILITY, HEADINGTOWARDSENTRANCE, SEARCHINGFORFIRE, HEADINGTOWARDSFIRE, 
                        UGVALIGNINGWITHTARGET, UGVALIGNEDWITHTARGET, EXTINGUISHINGFIRE, RETURNINGTOBASE};

class UGVNavMissionStateManager : public msg_emitter, public msg_receiver
{
public:
    void updateMissionState(UGVNavState);
    UGVNavState getMissionState();
    void receive_msg_data(DataMessage*);

private:
    UGVNavState m_current_state = UGVNavState::IDLE;
    void displayStateChange();
};

extern UGVNavMissionStateManager mainUGVNavMissionStateManager;