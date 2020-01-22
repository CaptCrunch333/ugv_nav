#include "Quat_to_Euler.hpp"

void QuatToEuler::receive_msg_data(DataMessage* t_msg)
{
    if(t_msg->getType() == msg_type::QUATERNION)
    {
        QuaternionMessage q = *((QuaternionMessage*) t_msg);
        Vector3D<float> _euler;

        HeadingMsg t_headingmsg;


        // roll (x-axis rotation)
        double sinr_cosp = +2.0 * (q.getData().w * q.getData().x + q.getData().y * q.getData().z);
        double cosr_cosp = +1.0 - 2.0 * (q.getData().x * q.getData().x + q.getData().y * q.getData().y);
        _euler.x = atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        double sinp = +2.0 * (q.getData().w * q.getData().y - q.getData().z * q.getData().x);
        if (fabs(sinp) >= 1)
            _euler.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            _euler.y = asin(sinp);

        // yaw (z-axis rotation)
        double siny_cosp = +2.0 * (q.getData().w * q.getData().z + q.getData().x * q.getData().y);
        double cosy_cosp = +1.0 - 2.0 * (q.getData().y * q.getData().y + q.getData().z * q.getData().z);  
        _euler.z = atan2(siny_cosp, cosy_cosp);
        
        t_headingmsg.yaw = _euler.z;

        emit_message((DataMessage*) & t_headingmsg);
    }

} 