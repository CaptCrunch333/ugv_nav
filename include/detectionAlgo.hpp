#pragma once
#include "Vector3D.hpp"
#include "MsgReceiver.hpp"
#include "MsgEmitter.hpp"
#include "AttitudeMsg.hpp"
#include "HeadingMsg.hpp"
#include "PositionMsg.hpp"
#include "DarknetMessage.hpp"
#include "FireLineDescription.hpp"
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include "RotationMatrix3by3.hpp"
#include "Matrix3by3.hpp"

class detectionAlgo : public msg_emitter , public msg_receiver {

private:
    //static detectionAlgo* _instance_ptr;
    AttitudeMsg _att_msg;
    HeadingMsg _heading_msg;
    PositionMsg _position_msg;
    DarknetMessage _darknet_msg;
    FireLineDescription _fire_line;
    Vector3D<float>  intersectPoint(Vector3D<float>, Vector3D<float> , Vector3D<float> , Vector3D<float> );
    void detection_algo();
    Vector3D<float> curr_position;
    float yaw=0;
    float pitch=0, roll=0;

    float hztl_fov = 69.4;
    float vrtl_fov = 42.5;
    //double focalP = 1.93; //mm
    int cam_width = 640;
    int cam_height = 480;

    cv::Mat distCoeffs = (cv::Mat_<double>(1,5) << 0.030549194476291067, 0.88924607665253474, 0., 0., -3.8699568663945501);
    cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) << 607.40120119822132, 0., 320., 0., 607.40120119822132, 240., 0., 0., 1.);


public:
    detectionAlgo();
    ~detectionAlgo();
    void receive_msg_data(DataMessage* t_msg);
    float prob;
    int target_x;
    int target_y;
   
};