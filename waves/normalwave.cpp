#include"normalwave.h"
NormalWave::NormalWave(World* const _world)
    :BaseWave(_world)
{
    setMaxCollideTimes(4);
}

void NormalWave::setMaxCollideTimes(const int& _maxCollideTimes)
{
    maxCollideTimes = _maxCollideTimes;
}

void NormalWave::advance(int phase)
{
    if (!phase)return;
    if (!scene())return;
    if (curLen < maxLen)
    {
        curLen += stepLen;
    }
    else
    {
        if (listHead < pointList.size())
        {
            if (turnHead < turnList.size())
            {
                QPointF temp1 = turnList[turnHead];
                QPointF temp2 = pointList[listHead];
                double dx = qAbs(temp1.x() - temp2.x());
                double dy = qAbs(temp1.y() - temp2.y());
                if (dx < stepLen&&dy < stepLen)
                {
                    turnHead++;
                }
            }
            listHead++;
        }
    }
}
