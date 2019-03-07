#ifndef NORMALWAVE_H
#define NORMALWAVE_H
#include"basewave.h"
class NormalWave :public BaseWave
{
public:
        NormalWave(World* const _world);
        void setMaxCollideTimes(const int& _maxCollideTimes);
        void advance(int phase);
protected:
        QList<QPointF>turnList;
        int turnHead;
        int turnTail;
        int maxCollideTimes;
};
#endif
