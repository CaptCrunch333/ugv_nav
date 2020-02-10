#include "ROSUnit_Factory.hpp"
#include "ROSUnit_UGVMoveBase.hpp"
#include "ROSUnit_AMCLPose.hpp"
#include "QuatToEuler.hpp"
#include "EulerToQuat.hpp"
#include "std_logger.hpp"
#include "UGVNavigator.hpp"
#include "looper.hpp"
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
    mainUGV->setTolerance(1.0, 0.3);
    UGVNavigator* mainUGVNavigator = new UGVNavigator(mainUGV, block_frequency::hz10);
    Vector2D<double> HomeBaseLodaction({-1,0});
    float HomeBaseHeading = 0;
    mainUGVNavigator->setHomeBaseLocation(HomeBaseLodaction, HomeBaseHeading);
    Vector2D<double> EntraceLocation({8,3});
    float EntranceHeading = 0;
    mainUGVNavigator->setEntranceLocation(EntraceLocation, EntranceHeading);
    mainUGVNavigator->setMap(mainMap);
    std::vector<Vector2D<float>> mainScanPath;
    mainScanPath.push_back(Vector2D<float>({8, 3}));
    mainScanPath.push_back(Vector2D<float>({9, 3}));
    mainScanPath.push_back(Vector2D<float>({10, 3}));
    mainScanPath.push_back(Vector2D<float>({11, 3}));
    mainScanPath.push_back(Vector2D<float>({11, 4}));
    mainScanPath.push_back(Vector2D<float>({11, 5}));
    mainScanPath.push_back(Vector2D<float>({11, 6}));
    mainScanPath.push_back(Vector2D<float>({11, 7}));
    mainScanPath.push_back(Vector2D<float>({10, 7}));
    mainScanPath.push_back(Vector2D<float>({9, 7}));
    mainScanPath.push_back(Vector2D<float>({8, 7}));
    mainScanPath.push_back(Vector2D<float>({8, 6}));
    mainScanPath.push_back(Vector2D<float>({8, 5}));
    mainScanPath.push_back(Vector2D<float>({8, 4}));
    mainUGVNavigator->setScanningPath(mainScanPath);
    mainUGVNavigator->setSearchTimeOut(1000000000);
    mainUGVNavigator->setReachingGoalPositionTimeOut(1000000000);
    // ********************************************************************************
    // ********************************** ROS UNITS  **********************************
    //ROSFactory Units
    ROSUnit_Factory* mainROSFactory = new ROSUnit_Factory(nh);
    ROSUnit* FireDirectionUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Vector, "ugv_nav/set_fire_direction");
    ROSUnit* FirePositionUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Point, "ugv_nav/set_fire_location");
    ROSUnit* InternalStateUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Int, "ugv_nav/set_mission_state");
    ROSUnit* UGVPatrolUpdaterSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Int, "ugv_nav/set_patrol_mode");
    ROSUnit* UGVPositionAdjustmentSrv = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Server, ROSUnit_Float, "ugv_nav/set_position_adjustment"); // TODO: add to IF
    ROSUnit* IntertialPositionPub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Point2D, "ugv_nav/inertial_position");
    ROSUnit* IntertialHeadingPub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Float, "ugv_nav/inertial_heading");
    ROSUnit* DistanceToFirePub = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Publisher, ROSUnit_Float, "ugv_nav/distance_to_fire");
    ROSUnit* StateUpdaterClnt = mainROSFactory->CreateROSUnit(ROSUnit_tx_rx_type::Client, ROSUnit_Int, "gf_indoor_fire_mm/update_ugv_nav_state");
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

    UGVPatrolUpdaterSrv->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    UGVPatrolUpdaterSrv->setEmittingChannel((int)CHANNELS::PATROL_UPDATER);

    InternalStateUpdaterSrv->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    InternalStateUpdaterSrv->setEmittingChannel((int)CHANNELS::INTERNAL_STATE_UPDATER);

    UGVPositionAdjustmentSrv->add_callback_msg_receiver((msg_receiver*) mainUGVNavigator);
    UGVPositionAdjustmentSrv->setEmittingChannel((int)CHANNELS::POSITION_ADJUSTMENT);

    mainUGVNavigator->add_callback_msg_receiver((msg_receiver*) DistanceToFirePub);

    mainUGV->add_callback_msg_receiver((msg_receiver*) BaseCommandsClnt);
    mainUGV->add_callback_msg_receiver((msg_receiver*) ETQ);
    ETQ->add_callback_msg_receiver((msg_receiver*) BaseCommandsClnt);

    (&mainUGVNavMissionStateManager)->add_callback_msg_receiver((msg_receiver*) StateUpdaterClnt);
    // ********************************************************************************
    // ****************************** SYSTEM CONNECTIONS ******************************
    pthread_t loop10hz_func_id;
    Looper* main_looper = new Looper();
    main_looper->addTimedBlock((TimedBlock*) mainUGVNavigator);
    pthread_create(&loop10hz_func_id, NULL, &Looper::Loop10Hz, NULL);
    // ********************************************************************************
    while (ros::ok()) {
        ros::spinOnce();
        //loop_rate.sleep();
    }
    return 0;
}

//TODO: add time out functionallity