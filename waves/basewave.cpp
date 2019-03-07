#include"basewave.h"
#include"../scenes/basescene.h"
BaseWave::BaseWave(World* const _world)
    :world(_world)
{
    maxDis = maxLen = 100.0;
    curLen = curDis = curTime = 0.0;
    stepLen = 3.5;
}

QRectF BaseWave::boundingRect()const
{
    return QRectF(-0xffff, -0xffff, 2 * 0xffff, 2 * 0xffff);
}

void BaseWave::setMaxLen(const double& _maxLen)
{
    maxLen = _maxLen;
}

void BaseWave::setMaxTime(const double& _maxTime)
{
    maxTime = _maxTime;
}

void BaseWave::setMaxDis(const double& _maxDis)
{
    maxDis = _maxDis;
}

void BaseWave::setStartPoint(const QPointF& _startPoint)
{
    startPoint = _startPoint;
}

void BaseWave::setStartXita(const double& _startXita)
{
    startXita = _startXita;
}

void BaseWave::setStepLen(const double& _stepLen)
{
    stepLen = _stepLen;
}
