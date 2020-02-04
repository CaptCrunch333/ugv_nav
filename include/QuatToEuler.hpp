#include "MsgReceiver.hpp"
#include "MsgEmitter.hpp"
#include "QuaternionMessage.hpp"
#include "HeadingMsg.hpp"
#include "FloatMsg.hpp"
#include "Vector3D.hpp"
#include <math.h>

class QuatToEuler : public msg_emitter, public msg_receiver
{
    void receive_msg_data(DataMessage*);
};