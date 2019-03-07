#ifndef CUSTOMWAVE_H
#define CUSTOMWAVE_H
#include"normalwave.h"
class CustomWave :public NormalWave
{
public:
        CustomWave(World* const _world);
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        void advance(int phase);
        void createPointList();
        void setDefaultWidth(const double& _w);
        void setDefaultColor(const QColor& _c);
};
#endif
