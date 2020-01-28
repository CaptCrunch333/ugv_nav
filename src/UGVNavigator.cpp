#include "UGVNavigator.hpp"

UGVNavigator::UGVNavigator(WheeledRobot* t_robot) {
    m_robot = t_robot;
}

void UGVNavigator::receive_msg_data(DataMessage* t_msg) {
    switch (mainUGVNavMissionStateManager.getMissionState()) {
        case UGVNavState::HEADINGTOWARDSENTRANCE: {
            if(m_robot->reachedPosition()) {
                m_robot->stop();
                mainUGVNavMissionStateManager.updateMissionState(UGVNavState::SEARCHINGFORFIRE);
                m_Timer.tick();
            }
        }
            break;
        case UGVNavState::SEARCHINGFORFIRE: {
            Logger::getAssignedLogger()->log("reached: %f", (float) m_robot->reachedPosition(), LoggerLevel::Info);
            Logger::getAssignedLogger()->log("goal position = %f, %f", m_robot->getGoalPosition().x, m_robot->getGoalPosition().y, LoggerLevel::Info);
            Logger::getAssignedLogger()->log("timer: %f", (float) m_Timer.tockMilliSeconds(), LoggerLevel::Info);
            if((m_robot->reachedPosition() && m_robot->getGoalPosition() != m_EntrancePosition) || (m_robot->getGoalPosition() == m_EntrancePosition && m_Timer.tockMilliSeconds() >= m_SerchTimeOut)){
                Vector3D<float> tmp = m_PathGenerator.getNextPose(m_FireDirection);
                m_robot->setGoalPosition(tmp.project_xy());
                m_robot->setGoalHeading(tmp.z);
                m_robot->move();
            }
        }
            break;
        case UGVNavState::HEADINGTOWARDSFIRE: {
            if(m_robot->reachedPosition()) {
                mainUGVNavMissionStateManager.updateMissionState(UGVNavState::EXTINGUISHINGFIRE);
            }
        }
            break;
        default:
            break;
    }
}

void UGVNavigator::receive_msg_data(DataMessage* t_msg, int t_channel_id) {
    if(t_channel_id == (int)CHANNELS::INTERNAL_STATE_UPDATER) {
        if(t_msg->getType() == msg_type::INTEGER) {
            if(mainUGVNavMissionStateManager.getMissionState() == UGVNavState::WARMINGUP) {
                Logger::getAssignedLogger()->log("UGV Is Still Warming Up, please wait", LoggerLevel::Warning);
            }
            else {
                switch ((UGVNavState)((IntegerMsg*)t_msg)->data) {
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
                    m_robot->setGoalPosition(m_EntrancePosition);
                    m_robot->setGoalHeading(m_EntranceHeading);
                    m_robot->move();
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::HEADINGTOWARDSENTRANCE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Heading Towards Entrance", LoggerLevel::Warning);
                    break; }

                case UGVNavState::RETURNINGTOBASE: {
                    m_robot->setGoalPosition(m_HomePosition);
                    m_robot->setGoalHeading(m_HomeHeading);
                    m_robot->move();
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::RETURNINGTOBASE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Returning To Base", LoggerLevel::Warning);
                    break; 
                    }

                default:
                    break;
                }
            }
        }
    }
    else if(t_channel_id ==  (int)CHANNELS::FIRE_DIRECTION_UPDATER) {
        if(t_msg->getType() == msg_type::VECTOR) {
            Logger::getAssignedLogger()->log("Fire Direction Received",LoggerLevel::Info);
            VectorMsg* t_points_msg = (VectorMsg*)t_msg;
            m_FireDirection.setPoint1(t_points_msg->p1.project_xy());
            m_FireDirection.setPoint2(t_points_msg->p2.project_xy());
            Vector3D<float> tmp = m_PathGenerator.getNextPose(m_FireDirection);
            m_robot->setGoalPosition(tmp.project_xy());
            m_robot->setGoalHeading(tmp.z);
            m_robot->move();
        }
    }
    else if(t_channel_id == (int)CHANNELS::FIRE_POSITION_UPDATER) {
        if(t_msg->getType() == msg_type::VECTOR3D) {
            Logger::getAssignedLogger()->log("Fire Position Received",LoggerLevel::Info);
            Vector3DMessage* t_direction_msg = (Vector3DMessage*)t_msg;
            m_FireLocation = t_direction_msg->getData().project_xy();
            mainUGVNavMissionStateManager.updateMissionState(UGVNavState::HEADINGTOWARDSFIRE);
            m_Map->setObjectLocation(m_FireLocation);
            Vector3D<float> t_vec = m_Map->getNormalToObject();
            m_robot->setGoalPosition(t_vec.project_xy());
            m_robot->setGoalHeading(t_vec.z);
            m_robot->move();
        }
    }
}

void UGVNavigator::setHomeBaseLocation(Vector2D<double> t_pos, float t_heading) {
    m_HomePosition = t_pos;
    m_HomeHeading = t_heading;
}

void UGVNavigator::setEntranceLocation(Vector2D<double> t_pos, float t_heading) {
    m_EntrancePosition = t_pos;
    m_EntranceHeading = t_heading;
}

void UGVNavigator::setScanningPath(std::vector<Vector2D<float>> t_pos) {
    m_PathGenerator.setTrack(t_pos);
}

void UGVNavigator::setMap(Map2D* t_map) {
    m_Map = t_map;
}

void UGVNavigator::setSearchTimeOut(int t_time) {
    m_SerchTimeOut = t_time;
}