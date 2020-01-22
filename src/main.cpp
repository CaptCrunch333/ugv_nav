#include "ROSUnit_pose.hpp"
#include "ROSUnit_UGVHeading.hpp"
#include "ROSUnit_UGVPose.hpp"
#include "Quat_to_Euler.hpp"
#include "UGV_FireMap.hpp"

int main(int argc, char **argv){

    ros::init(argc, argv, "ugv_nav");
    ros::NodeHandle nh;
    ros::Rate loop_rate(100);

    ROSUnit_UGVHeading* ROS_UGVHeading = new ROSUnit_UGVHeading(nh);
    ROSUnit_pose* ROS_pose = new ROSUnit_pose(nh);
    ROSUnit_UGVPose* ROS_UGVPose = new ROSUnit_UGVPose(nh);
    QuatToEuler* QTE = new QuatToEuler();
    
    ROS_pose->add_callback_msg_receiver((msg_receiver*) QTE);
    ROS_pose->add_callback_msg_receiver((msg_receiver*) ROS_UGVPose);
    QTE->add_callback_msg_receiver((msg_receiver*) ROS_UGVHeading);

    UGV_FireMap m_map;
    Vector2D<double> m_point;
    m_point.x = -100;
    m_point.y = 6;
    m_map.setFireLocation(m_point);
    m_map.getNormalToFire();
        
    // while (ros::ok()){
    
    //     ros::spinOnce();
    //     loop_rate.sleep();
    // }

    return 0;
}

