#include "ROSUnit_Factory.hpp"
#include "ROSUnit_UGVMoveBase.hpp"
#include "ROSUnit_AMCLPose.hpp"
#include "QuatToEuler.hpp"
#include "EulerToQuat.hpp"
#include "UGV_FireMap.hpp"
#include "std_logger.hpp"
#include "UGVNavigator.hpp"
#include <vector>

int main(int argc, char **argv){

    ros::init(argc, argv, "ugv_nav");
    ros::NodeHandle nh;
    //ros::Rate loop_rate(100);
    // ************************************ LOGGER ************************************
    Logger::assignLogger(new StdLogger());
    Logger::getAssignedLogger()->log("start of logger", LoggerLevel::Info);
    //Logger::getAssignedLogger()->enableFileLog(LoggerLevel::Error);
    // ********************************************************************************
    // *********************************** FIRE MAP ***********************************
    //TODO: add function to take map vertices as a txt
    UGV_FireMap* m_map = new UGV_FireMap;
    Vector2D<double> mapOrigin;
    mapOrigin = {0,0};
    m_map->MoveMap(mapOrigin);
    // ********************************************************************************
    // ********************************** ROS UNITS  **********************************
    //ROSFactory Units
    ROSUnit_Factory* mainROSFactory = new ROSUnit_Factory(nh);
    ROSUnit* FireDirectionUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Vector, "/ugv_nav/set_fire_direction");
    ROSUnit* FirePositionUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Point, "/ugv_nav/set_fire_location");
    ROSUnit* InternalStateUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Int, "/ugv_nav/set_mission_state");
    ROSUnit* IntertialPositionPub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Point2D, "/ugv_nav/inertial_position");
    ROSUnit* IntertialHeadingPub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Float, "/ugv_nav/inertial_heading");
    ROSUnit* DistanceToFirePub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Float, "/ugv_nav/distance_to_fire");
    ROSUnit* StateChangerUpdaterClnt = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Client, ROSUnit_Int, "/gf_indoor_fire_mm/update_water_ext_state");
    // Package Specific Units
    ROSUnit_AMCLPose* ROS_AMCLPose = new ROSUnit_AMCLPose(nh);
    ROSUnit_UGVMoveBase* BaseCommandsClnt = new ROSUnit_UGVMoveBase(nh);
    // ********************************************************************************
    // ******************************** UGV NAVIGATOR *********************************
    UGVNavigator* mainUGVNavigator = new UGVNavigator;
    mainUGVNavigator->setEntranceLocation({6,7});
    mainUGVNavigator->setHomeBaseLocation({0,0});
    // ********************************************************************************
    // ***************************** ROS PACKAGES BRIDGE ******************************
    QuatToEuler* QTE = new QuatToEuler();
    EulerToQuat* ETQ = new EulerToQuat();
    // ********************************************************************************
    // ****************************** SYSTEM CONNECTIONS ******************************
    ROS_AMCLPose->add_callback_msg_receiver((msg_receiver*) QTE);
    ROS_AMCLPose->add_callback_msg_receiver((msg_receiver*) IntertialPositionPub);
    QTE->add_callback_msg_receiver((msg_receiver*) IntertialHeadingPub);
    ROS_AMCLPose->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    QTE->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);

    FireDirectionUpdaterSrv((msg_receiver*) mainUGVNavigator);
    FireDirectionUpdaterSrv->setEmittingChannel(CHANNELS::DIRECTION_UPDATER);

    FirePositionUpdaterSrv((msg_receiver*) mainUGVNavigator);
    FirePositionUpdaterSrv->setEmittingChannel(CHANNELS::POSITION_UPDATER);

    InternalStateUpdaterSrv->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    InternalStateUpdaterSrv->setEmittingChannel(CHANNELS::INTERNAL_STATE_UPDATER);

    mainUGVNavigator->add_callback_msg_receiver((msg_receiver*) DistanceToFirePub);
    mainUGVNavigator->add_callback_msg_receiver((msg_receiver*) StateChangerUpdaterClnt);
    mainUGVNavigator->add_callback_msg_receiver((msg_receiver*) );
    // ********************************************************************************
    while (ros::ok()){
    
        ros::spinOnce();
        //loop_rate.sleep();
    }

    return 0;
}