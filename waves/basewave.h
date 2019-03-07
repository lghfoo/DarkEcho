#ifndef BASEWAVE_H
#define BASEWAVE_H
#include"../world.h"
class BaseWave :public QGraphicsItem
{
public:
    BaseWave(World* const _world);
    QRectF boundingRect()const;
    void setMaxLen(const double& _maxLen);
    void setStartPoint(const QPointF& _startPoint);
    void setStartXita(const double& _startXita);
    void setMaxTime(const double& _maxTime);
    void setMaxDis(const double& _maxDis);
    void setStepLen(const double& _stepLen);
    virtual void createPointList() = 0;
protected:
    QPen pen;
    QList<QPointF>pointList;
    QPointF startPoint;
    double startXita;
    double maxLen;
    double maxDis;
    double maxTime;
    double curLen;
    double curDis;
    double curTime;
    double stepLen;
    int listHead;
    int listTail;
    World* const world;
};
#endif
