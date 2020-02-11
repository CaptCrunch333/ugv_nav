#include "GoalStatusMsg.hpp"

GoalStatusMsg::GoalStatusMsg()
{

}

GoalStatusMsg::~GoalStatusMsg()
{

}

msg_type GoalStatusMsg::getType()
{
    return msg_type::GOALSTATUS;
}

const int GoalStatusMsg::getSize()
{
    return sizeof(*this);
}