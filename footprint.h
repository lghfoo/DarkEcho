#ifndef FOOTPRINT_H
#define FOOTPRINT_H
#include"allheader.h"
class Footprint :public QGraphicsItem
{
public:
    enum { LEFTFOOT, RIGHTFOOT, FEET };
    Footprint(const int& _type, const double& _dir);
    int type()const;
    QRectF boundingRect()const;
    void setType(const int& _type);
    void setIsFading(const bool& _isFading);
    void setBrush(const QColor& c);
    void advance(int phase);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
private:
    void setLeftFoot();
    int m_type;
    double m_direction;
    bool m_isFading;
    bool m_startFading;
    QPainterPath m_leftFoot;
    bool m_hadPaintedLeft;
    bool m_hadPaintedRight;
    int m_counter;
    int m_interval;
    QColor footColor;
};
#endif




