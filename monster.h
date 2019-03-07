#ifndef MONSTER_H
#define MONSTRR_H
#include"allheader.h"
#include"world.h"
class Monster :public QGraphicsItem
{
public:
    Monster(World* const _world);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect()const;
    void moveTo(const QPointF& tar);
    void advance(int phase);
    void setIsActivate(const bool& a);
    bool getIsMoving()const;
private:
    bool isMoving;
    World* const world;
    QPointF target;
    double stepLen;
    void computeXita(const QPointF& tar);
    double marchXita;
    int counter;
    bool isActivate;
};

#endif
