#include "GoalStatus.hpp"

GoalStatus::GoalStatus()
{

}

GoalStatus::~GoalStatus()
{

}

msg_type GoalStatus::getType()
{
    return msg_type::GOALSTATUS;
}

const int GoalStatus::getSize()
{
    return sizeof(*this);
}