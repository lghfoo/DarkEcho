#ifndef CASTWAVE_H
#define CASTWAVE_H
#include"basewave.h"
class CastWave :public BaseWave
{
public:
    CastWave(World* const _world);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void advance(int phase);
    void createPointList();//ŒûBaseWave.h
private:
    int firstFall;
    int secondFall;
};
#endif
