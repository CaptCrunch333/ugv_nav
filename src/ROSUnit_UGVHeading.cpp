#include "ROSUnit_UGVHeading.hpp"

ROSUnit_UGVHeading::ROSUnit_UGVHeading(ros::NodeHandle& t_main_handler) : ROSUnit(t_main_handler) {
    _pub_heading = t_main_handler.advertise <std_msgs::Float32> ("/ugv_nav/inertial_heading",1);
}

ROSUnit_UGVHeading::~ROSUnit_UGVHeading()
{

};

void ROSUnit_UGVHeading::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::HEADING)
    {
        HeadingMsg t_headingmsg = *((HeadingMsg*) t_msg);
        std_msgs::Float32 t_heading;
        
        t_heading.data = t_headingmsg.yaw;

        _pub_heading.publish(t_heading);
    }

}