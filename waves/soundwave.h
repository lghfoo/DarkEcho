#ifndef SOUNDWAVE_H
#define SOUNDWAVE_H
#include"../world.h"
class SoundWave :public QGraphicsItem
{
public:
    enum { REFLECTWAVE = 1, CASTWAVE = 2, CHOICEWAVE = 4 };
    SoundWave(World* const _world);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget);
    QRectF boundingRect()const;
    void advance(int phase);
    void setMaxLen(const double& _maxLen);
    void setMaxCollideTimes(const int& _maxCollideTimes);
    void setStartPoint(const QPointF& _startPoint);
    void setStartXita(const double& _startXita);
    void setMaxTime(const double& _maxTime);
    void setMaxDis(const double& _maxDis);
    void createPointList();
    void setWaveFalgs(const int& _flags);
private:
    QList<QPointF>pointList;
    QList<QColor>pointColorList;
    QList<QPointF>turnList;
    QList<QColor>turnColorList;
    QPointF startPoint;
    double startXita;
    double maxLen;
    double maxDis;
    double maxTime;
    int maxCollideTimes;
    double curLen;
    double curDis;
    double stepLen;
    QPen pen;
    int listHead;
    int listTail;
    int turnHead;
    int turnTail;
    double curTime;
    int waveFlags;
    World* const world;
    int firstFall;
    int secondFall;
};

#endif
