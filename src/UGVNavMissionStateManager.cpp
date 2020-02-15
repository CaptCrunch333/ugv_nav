#include "UGVNavMissionStateManager.hpp"

UGVNavMissionStateManager mainUGVNavMissionStateManager;

void UGVNavMissionStateManager::updateMissionState(UGVNavState t_current_state)
{
    m_current_state = t_current_state;
    IntegerMsg state_msg;
    state_msg.data = (int)t_current_state;
    emit_message((DataMessage*) &state_msg);
    displayStateChange();
}

UGVNavState UGVNavMissionStateManager::getMissionState()
{
    return m_current_state;
}

void UGVNavMissionStateManager::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::INTEGER)
    {
        updateMissionState((UGVNavState) ((IntegerMsg*)t_msg)->data);
    }
}

void UGVNavMissionStateManager::displayStateChange()
{
    switch (m_current_state)
    {
    case UGVNavState::WARMINGUP:
        Logger::getAssignedLogger()->log("UGV Nav State To Warming Up", LoggerLevel::Info);
        break;

    case UGVNavState::IDLE:
        Logger::getAssignedLogger()->log("UGV Nav State To Idle", LoggerLevel::Info);
        break;

    case UGVNavState::UTILITY:
        Logger::getAssignedLogger()->log("UGV Nav State Changed To Utility", LoggerLevel::Info);
        break;

    case UGVNavState::MOVING:
        Logger::getAssignedLogger()->log("UGV Nav State To Moving", LoggerLevel::Info);
        break;
    
    case UGVNavState::REACHEDGOAL:
        Logger::getAssignedLogger()->log("UGV Nav State To Reached Goal ", LoggerLevel::Info);
        break;

    default:
        break;
    }
}