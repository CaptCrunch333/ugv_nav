#include "UGVNavigator.hpp"

void UGVNavigator::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::VECTOR2D)
    {
        m_current_pos = ((Vector2DMsg*)t_msg)->data;
    }
    else if(t_msg->getType() == msg_type::HEADING)
    {
        m_current_heading = ((FloatMsg*)t_msg)->data;
    }
    switch (mainUGVNavMissionStateManager.getMissionState())
    {
    case UGVNavState::SEARCHINGFORFIRE:
        {
            if(m_FireDirectionFound)
            {
                m_FireDirection;
            }
        }
        break;
    
    case UGVNavState::HEADINGTOWARDSFIRE:
        {
            if(m_FireLocationFound)
            {
                //TODO: add map and location emitter
            }
        }
        break;

    default:
        break;
    }
}

void UGVNavigator::receive_msg_data(DataMessage* t_msg, int t_channel_id)
{
    if(t_channel_id == (int)CHANNELS::INTERNAL_STATE_UPDATER)
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
                    needed_pos.data = m_EntrancePosition;
                    this->emit_message((DataMessage*) &needed_pos);
                    Vector3DMessage needed_orientation;
                    needed_orientation.setVector3DMessage({0.f,0.f,m_EntranceHeading});
                    this->emit_message((DataMessage*) &needed_orientation);
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::HEADINGTOWARDSENTRANCE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Heading Towards Entrance", LoggerLevel::Warning);
                    break; }

                case UGVNavState::RETURNINGTOBASE: {
                    Vector2DMsg needed_pos;
                    needed_pos.data = m_HomePosition;
                    this->emit_message((DataMessage*) &needed_pos);
                    Vector3DMessage needed_orientation;
                    needed_orientation.setVector3DMessage({0.f,0.f,m_HomeHeading});
                    this->emit_message((DataMessage*) &needed_orientation);
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::RETURNINGTOBASE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Returning To Base", LoggerLevel::Warning);
                    break; }

                default:
                    break;
                }
            }
        }
    }
    else if(t_channel_id ==  (int)CHANNELS::DIRECTION_UPDATER)
    {
        if(t_msg->getType() == msg_type::POINTS)
        {
            PointsMsg* t_points_msg = (PointsMsg*)t_msg;
            m_FireDirection.setPoint1(t_points_msg->points.at(0).project_xy());
            m_FireDirection.setPoint2(t_points_msg->points.at(1).project_xy());
            m_FireDirectionFound = true;
        }
    }
    else if(t_channel_id == (int)CHANNELS::POSITION_UPDATER)
    {
        if(t_msg->getType() == msg_type::POINT)
        {
            Vector3DMessage* t_direction_msg = (Vector3DMessage*)t_msg;
            m_FireLocation = t_direction_msg->getData().project_xy();
            m_FireLocationFound = true;
            mainUGVNavMissionStateManager.updateMissionState(UGVNavState::HEADINGTOWARDSFIRE);
        }
    }
}

void UGVNavigator::setHomeBaseLocation(Vector2D<double> t_pos, float t_heading)
{
    m_HomePosition = t_pos;
    m_HomeHeading = t_heading;
}

void UGVNavigator::setEntranceLocation(Vector2D<double> t_pos, float t_heading)
{
    m_EntrancePosition = t_pos;
    m_EntranceHeading = t_heading;
}

void UGVNavigator::setScanningPath(std::vector<Vector2D<float>> t_pos)
{
    m_scanning_pos = t_pos;
    m_PathGenerator.setTrack(t_pos);
}