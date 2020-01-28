#include "ROSUnit_Factory.hpp"
#include "ROSUnit_UGVMoveBase.hpp"
#include "ROSUnit_AMCLPose.hpp"
#include "QuatToEuler.hpp"
#include "EulerToQuat.hpp"
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
    Map2D* mainMap = new Map2D();
    //Vector2D<double> mapOrigin({0,0});
    //mainMap->MoveMap(mapOrigin);
    // ********************************************************************************
    // ******************************** UGV NAVIGATOR *********************************
    WheeledRobot* mainUGV = new WheeledRobot;
    //mainUGV->setTolerance(0.1, 0.175);
    mainUGV->setTolerance(0.1, 175);
    UGVNavigator* mainUGVNavigator = new UGVNavigator(mainUGV);
    Vector2D<double> HomeBaseLodaction({0,0});
    float HomeBaseHeading = 0;
    mainUGVNavigator->setHomeBaseLocation(HomeBaseLodaction, HomeBaseHeading);
    Vector2D<double> EntraceLocation({6,7}); 
    float EntranceHeading = 0;
    mainUGVNavigator->setEntranceLocation(EntraceLocation, EntranceHeading);
    mainUGVNavigator->setMap(mainMap);
    std::vector<Vector2D<float>> mainScanPath;
    mainScanPath.push_back(Vector2D<float>({6, 7}));
    mainScanPath.push_back(Vector2D<float>({9, 11}));
    mainScanPath.push_back(Vector2D<float>({11, 6}));
    mainScanPath.push_back(Vector2D<float>({10, 4}));
    mainUGVNavigator->setScanningPath(mainScanPath);
    // ********************************************************************************
    // ********************************** ROS UNITS  **********************************
    //ROSFactory Units
    ROSUnit_Factory* mainROSFactory = new ROSUnit_Factory(nh);
    ROSUnit* FireDirectionUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Vector, "ugv_nav/set_fire_direction");
    ROSUnit* FirePositionUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Point, "ugv_nav/set_fire_location");
    ROSUnit* InternalStateUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Int, "ugv_nav/set_mission_state");
    ROSUnit* IntertialPositionPub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Point2D, "ugv_nav/inertial_position");
    ROSUnit* IntertialHeadingPub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Float, "ugv_nav/inertial_heading");
    ROSUnit* DistanceToFirePub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Float, "ugv_nav/distance_to_fire");
    ROSUnit* StateChangerUpdaterClnt = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Client, ROSUnit_Int, "gf_indoor_fire_mm/update_water_ext_state");
    // Package Specific Units
    ROSUnit_AMCLPose* ROS_AMCLPose = new ROSUnit_AMCLPose(nh);
    ROSUnit_UGVMoveBase* BaseCommandsClnt = new ROSUnit_UGVMoveBase(nh);
    // ********************************************************************************
    // ***************************** ROS PACKAGES BRIDGE ******************************
    QuatToEuler* QTE = new QuatToEuler();
    EulerToQuat* ETQ = new EulerToQuat();
    // ********************************************************************************
    // ****************************** SYSTEM CONNECTIONS ******************************
    ROS_AMCLPose->add_callback_msg_receiver((msg_receiver*) QTE);
    ROS_AMCLPose->add_callback_msg_receiver((msg_receiver*) IntertialPositionPub);
    QTE->add_callback_msg_receiver((msg_receiver*) IntertialHeadingPub);
    ROS_AMCLPose->add_callback_msg_receiver((msg_receiver*) mainUGV);
    QTE->add_callback_msg_receiver((msg_receiver*) mainUGV);
    QTE->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);

    FireDirectionUpdaterSrv->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    FireDirectionUpdaterSrv->setEmittingChannel((int)CHANNELS::FIRE_DIRECTION_UPDATER);

    FirePositionUpdaterSrv->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    FirePositionUpdaterSrv->setEmittingChannel((int)CHANNELS::FIRE_POSITION_UPDATER);

    InternalStateUpdaterSrv->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    InternalStateUpdaterSrv->setEmittingChannel((int)CHANNELS::INTERNAL_STATE_UPDATER);

    mainUGVNavigator->add_callback_msg_receiver((msg_receiver*) DistanceToFirePub);
    mainUGVNavigator->add_callback_msg_receiver((msg_receiver*) StateChangerUpdaterClnt);
    
    mainUGV->add_callback_msg_receiver((msg_receiver*) BaseCommandsClnt);
    mainUGV->add_callback_msg_receiver((msg_receiver*) ETQ);
    ETQ->add_callback_msg_receiver((msg_receiver*) BaseCommandsClnt);
    // ********************************************************************************
    while (ros::ok()){
    
        ros::spinOnce();
        //loop_rate.sleep();
    }
    return 0;
}