#include "UGVNavigator.hpp"

UGVNavigator::UGVNavigator(WheeledRobot* t_robot, block_frequency t_bf) : TimedBlock(t_bf) {
    m_robot = t_robot;
}

void UGVNavigator::loopInternal() {
    switch (mainUGVNavMissionStateManager.getMissionState()) {
        case UGVNavState::WARMINGUP: {
            //TODO: add idle check
            //TODO: add utility check
            mainUGVNavMissionStateManager.updateMissionState(UGVNavState::IDLE);
            break;
        }
        case UGVNavState::MOVING: {
            if(m_robot->reachedPosition()) {
                mainUGVNavMissionStateManager.updateMissionState(UGVNavState::REACHEDGOAL);
            }
            break;
        }
        case UGVNavState::REACHEDGOAL: {
            break;
        }
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
                    this->reset();
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::IDLE);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To IDLE", LoggerLevel::Info);
                    break; 
                }
                case UGVNavState::UTILITY: {
                    m_robot->stop();
                    mainUGVNavMissionStateManager.updateMissionState(UGVNavState::UTILITY);
                    Logger::getAssignedLogger()->log("MM Changed UGV Nav State To Utility", LoggerLevel::Warning);
                    break;
                }
                default:
                    break;
                }
            }
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
    else if(t_channel_id == (int)CHANNELS::POSITION_ADJUSTMENT) { //TODO: check functionality
        if(t_msg->getType() == msg_type::FLOAT) {
            FloatMsg* t_float_msg = (FloatMsg*) t_msg;
            Logger::getAssignedLogger()->log("Adjustment Command Received: %f", t_float_msg->data, LoggerLevel::Info);
            double t_step_size = double(t_float_msg->data);
            m_robot->setGoal(m_PathGenerator.generateParametricPath(m_robot->getCurrentPosition(), t_step_size));
            m_robot->move();
            mainUGVNavMissionStateManager.updateMissionState(UGVNavState::MOVING);
        }
    }
    else if(t_channel_id == (int)CHANNELS::CHANGE_POSE) {
        if(t_msg->getType() == msg_type::POSE) {
            PoseMsg* t_pose_msg = (PoseMsg*) t_msg;
            m_robot->setGoal({t_pose_msg->pose.x, t_pose_msg->pose.y, t_pose_msg->pose.yaw});
            m_robot->move();
            mainUGVNavMissionStateManager.updateMissionState(UGVNavState::MOVING);
        }
    }
    else if(t_channel_id == (int)CHANNELS::GO_TO_FIRE) {
        m_robot->setGoal({m_ExtLocation.x, m_ExtLocation.y, m_ExtHeading});
        m_robot->move();
        mainUGVNavMissionStateManager.updateMissionState(UGVNavState::MOVING);
    }
}

void UGVNavigator::setScanningPath(Rectangle* t_rect) {
    m_PathGenerator.setTrack(*t_rect);
}

void UGVNavigator::setMap(Map2D* t_map) {
    m_Map = t_map;
}

void UGVNavigator::reset() {
    m_robot->stop();
}