#include "UGVNavigator.hpp"

UGVNavigator::UGVNavigator(WheeledRobot* t_robot, block_frequency t_bf) : TimedBlock(t_bf) {
    m_robot = t_robot;
}

void UGVNavigator::loopInternal() {
    switch (mainUGVNavMissionStateManager.getMissionState()) {
        case UGVNavState::WARMINGUP: {
            mainUGVNavMissionStateManager.updateMissionState(UGVNavState::IDLE);
        }
            break;
        case UGVNavState::HEADINGTOWARDSENTRANCE: {
            if(m_robot->reachedPosition()) {
                mainUGVNavMissionStateManager.updateMissionState(UGVNavState::SEARCHINGFORFIRE);
            }
        }
            break;
        case UGVNavState::SEARCHINGFORFIRE: {
            if(m_PatrolState != UGVPatrolState::IDLE) {
                if(m_robot->reachedPosition()) {
                    // Vector3D<float> tmp = m_PathGenerator.getNextPose(m_FireDirection);
                    // // m_robot->setGoalPosition(tmp.project_xy());
                    // // m_robot->setGoalHeading(tmp.z);
                    // m_robot->move();
                    std::vector<Vector3D<float>> t_path;
                    for(int i = 0; i < m_PathGenerator.getTrackLength(); i++) {
                        Line2D t_line;
                        t_path.push_back(m_PathGenerator.getNextPose(t_line));
                        Logger::getAssignedLogger()->log("UGV Path appended: %f, %f, with orientation: %f", t_path.front().x, t_path.front().y, t_path.front().z, LoggerLevel::Info);
                    }
                    m_robot->setGoal(t_path);
                    m_robot->move();
                }
            }
            else if(m_PatrolState == UGVPatrolState::IDLE) {
                m_robot->stop();
            }
        }
            break;
        case UGVNavState::HEADINGTOWARDSFIRE: {
            if(m_robot->reachedPosition()) {
                mainUGVNavMissionStateManager.updateMissionState(UGVNavState::UGVALIGNEDWITHTARGET);
            }
        }
            break;
        case UGVNavState::RETURNINGTOBASE: {
            if(m_robot->reachedPosition()) {
                mainUGVNavMissionStateManager.updateMissionState(UGVNavState::REACHEDBASE);
            }
        }
            break;
        default:
            break;
    }
}

void UGVNavigator::receive_msg_data(DataMessage* t_msg) {} // NOT IMPLEMENTED, LEGACY FUNCTION

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
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To IDLE", LoggerLevel::Info);
                    break; }

                case UGVNavState::UTILITY: {
                    //TODO: add a function to kill the ugv movement
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::UTILITY);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Utility", LoggerLevel::Warning);
                    break; }

                case UGVNavState::HEADINGTOWARDSENTRANCE: {
                    m_robot->setGoal(Vector3D<float>({m_EntrancePosition.x, m_EntrancePosition.y, m_EntranceHeading}));
                    m_robot->move();
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::HEADINGTOWARDSENTRANCE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Heading Towards Entrance", LoggerLevel::Info);
                    break; }

                 case UGVNavState::HEADINGTOWARDSFIRE: {
                    // m_robot->setGoalPosition(m_ExtLocation);
                    // m_robot->setGoalHeading(m_ExtHeading);
                    m_robot->move();
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::HEADINGTOWARDSFIRE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Heading Towards Fire", LoggerLevel::Info);
                    break; }   

                case UGVNavState::EXTINGUISHINGFIRE: {
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::EXTINGUISHINGFIRE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Extinguishing Fire", LoggerLevel::Info);
                    break; }    

                case UGVNavState::RETURNINGTOBASE: {
                    // m_robot->setGoalPosition(m_HomePosition);
                    // m_robot->setGoalHeading(m_HomeHeading);
                    m_robot->move();
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::RETURNINGTOBASE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Returning To Base", LoggerLevel::Info);
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
        }
    }
    else if(t_channel_id == (int)CHANNELS::FIRE_POSITION_UPDATER) {
        if(t_msg->getType() == msg_type::VECTOR3D) {
            Logger::getAssignedLogger()->log("Fire Position Received",LoggerLevel::Info);
            Vector3DMessage* t_direction_msg = (Vector3DMessage*)t_msg;
            m_FireLocation = t_direction_msg->getData().project_xy();
            m_Map->setObjectLocation(m_FireLocation);
            Vector3D<float> t_vec = m_Map->getNormalToObject();
            m_ExtLocation = t_vec.project_xy();
            m_ExtHeading = t_vec.z;
        }
    }
    else if(t_channel_id == (int)CHANNELS::PATROL_UPDATER) {
        if(t_msg->getType() == msg_type::INTEGER) {
            Logger::getAssignedLogger()->log("Patrol Command Received",LoggerLevel::Info);
            IntegerMsg* t_patrol_msg = (IntegerMsg*)t_msg;
            if(t_patrol_msg->data == (int) UGVPatrolState::HEADINGTOWARDSFIREDIRECTION) {
                m_PatrolState = UGVPatrolState::HEADINGTOWARDSFIREDIRECTION;
                Vector3D<float> tmp = m_PathGenerator.getNextPose(m_FireDirection);
                // m_robot->setGoalPosition(tmp.project_xy());
                // m_robot->setGoalHeading(tmp.z);
                m_robot->move();
            }
        }
    }
    else if(t_channel_id == (int)CHANNELS::POSITION_ADJUSTMENT) {
        if(t_msg->getType() == msg_type::FLOAT) {
            FloatMsg* t_float_msg = (FloatMsg*) t_msg;
            Logger::getAssignedLogger()->log("Adjustment Command Received: %f", t_float_msg->data, LoggerLevel::Info);
            //m_robot->slide(t_float_msg->data);
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

void UGVNavigator::setSearchTimeOut(int t_val) {
    m_SearchTimeOut = t_val;
}

void UGVNavigator::setReachingGoalPositionTimeOut(int t_val) {
    m_ReachingGoalPositionTimeOut = t_val;
}