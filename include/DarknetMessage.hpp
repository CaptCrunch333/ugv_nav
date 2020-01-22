#pragma once
#include "DataMessage.hpp"

class DarknetMessage : public DataMessage{

public:
    float probability;
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    msg_type getType();
    const int getSize();
    void setDarknetMessage(float, int, int, int, int);
    DarknetMessage();
    ~DarknetMessage();
};