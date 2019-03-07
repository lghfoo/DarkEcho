#ifndef LINEWALL_H
#define LINEWALL_H
#include"wall.h"

class LineWall :public Wall,public QLineF
{
public:
    virtual bool collideWith(const QPointF& p1, const QPointF& p2,
        QPointF& collidePoint);
    virtual void tangentialEquation(const QPointF& point, double& A, double& B, double& C);
};

#endif
