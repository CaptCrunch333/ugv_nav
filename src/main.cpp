#include "ROSUnit_pose.hpp"
#include "ROSUnit_UGVHeading.hpp"
#include "ROSUnit_UGVPose.hpp"
#include "Quat_to_Euler.hpp"
#include "UGV_FireMap.hpp"
#include "std_logger.hpp"
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
    //Logger::getAssignedLogger()->log("val: %f , %f", mapOrigin.x, mapOrigin.y, LoggerLevel::Info);
    m_map->MoveMap(mapOrigin);
    // ********************************** ROS UNITS  **********************************
    ROSUnit_UGVHeading* ROS_UGVHeading = new ROSUnit_UGVHeading(nh);
    ROSUnit_pose* ROS_pose = new ROSUnit_pose(nh);
    ROSUnit_UGVPose* ROS_UGVPose = new ROSUnit_UGVPose(nh);
    QuatToEuler* QTE = new QuatToEuler();
    
    // ********************************************************************************
    // ****************************** SYSTEM CONNECTIONS ******************************
    ROS_pose->add_callback_msg_receiver((msg_receiver*) QTE);
    ROS_pose->add_callback_msg_receiver((msg_receiver*) ROS_UGVPose);
    QTE->add_callback_msg_receiver((msg_receiver*) ROS_UGVHeading);

    // while (ros::ok()){
    
    //     ros::spinOnce();
    //     loop_rate.sleep();
    // }

    return 0;
}

