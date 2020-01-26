#include "UGVNavigator.hpp"

void UGVNavigator::receive_msg_data(DataMessage* t_msg, int t_channel_id)
{
    if(t_channel_id == msg_broadcast_channel)
    {
        if(t_msg->getType() == msg_type::INTEGER)
        {
            if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::WARMINGUP)
            {
                Logger::getAssignedLogger()->log("UGV Is Still Warming Up, please wait", LoggerLevel::Warning);
            }
            else
            {
                switch ((UGVNavState)((IntegerMsg*)t_msg)->data)
                {
                case UGVNavState::IDLE: {
                    //TODO: add a function to kill the ugv movement and reset states
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::IDLE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To IDLE", LoggerLevel::Warning);
                    break; }

                case UGVNavState::UTILITY: {
                    //TODO: add a function to kill the ugv movement
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::UTILITY);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Utility", LoggerLevel::Warning);
                    break; }

                case UGVNavState::HEADINGTOWARDSENTRANCE: {
                    Vector2DMsg needed_pos;
                    needed_pos.data = m_Entrance;
                    this->emit_message((DataMessage*) &needed_pos);
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::HEADINGTOWARDSENTRANCE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Heading Towards Entrance", LoggerLevel::Warning);
                    break; }

                case UGVNavState::RETURNINGTOBASE: {
                    Vector2DMsg needed_pos;
                    needed_pos.data = m_HomePosition;
                    this->emit_message((DataMessage*) &needed_pos);
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::RETURNINGTOBASE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Returning To Base", LoggerLevel::Warning);
                    break; }

                default:
                    break;
                }
            }
        }
    }

    else if(t_channel_id ==  12)
    {
        if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::WARMINGUP)
        {
            mainUGVNavMissionStateManager.updateMissionState(UGVNavState::IDLE);
        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::IDLE)
        {

        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::UTILITY)
        {

        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::HEADINGTOWARDSENTRANCE)
        {
            //if(t_msg->getType() == msg_type::)
        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::SEARCHINGFORFIRE)
        {

        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::HEADINGTOWARDSFIRE)
        {

        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::UGVALIGNINGWITHTARGET)
        {

        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::UGVALIGNEDWITHTARGET)
        {

        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::EXTINGUISHINGFIRE)
        {

        }
        else if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::RETURNINGTOBASE)
        {

        }
    }
}

void UGVNavigator::setHomeBaseLocation(Vector2D<double> t_pos)
{
    m_HomePosition = t_pos;
}

void UGVNavigator::setEntranceLocation(Vector2D<double> t_pos)
{
    m_Entrance = t_pos;
}