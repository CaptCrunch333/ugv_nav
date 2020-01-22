#pragma once
#include "Rectangle.hpp"
#include "MsgEmitter.hpp"
#include "MsgReceiver.hpp"

class UGV_FireMap : public msg_emitter, public msg_receiver 
{
    public:
        UGV_FireMap();
        ~UGV_FireMap();

        void receive_msg_data(DataMessage*);
        void MoveMap(Vector2D<double>);
        void setFireLocation(Vector2D<double>);
        Vector3D<double> getNormalToFire();

    private:
        Vector2D<double> m_FireLocation;
        Rectangle* m_FireRectangle;
        Vector2D<double> r1l1p1;
        Vector2D<double> r1l1p2;
        Vector2D<double> r1l2p1;
        Vector2D<double> r1l2p2;
        Vector2D<double> r2l1p1;
        Vector2D<double> r2l1p2;
        Vector2D<double> r2l2p1;
        Vector2D<double> r2l2p2;
        Line2D r1l1, r1l2, r2l1, r2l2;
        Rectangle r1, r2;
};