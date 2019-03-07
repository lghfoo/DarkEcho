#ifndef WALL_H
#define WALL_H
#include"allheader.h"
class Wall
{
public:
    virtual bool collideWith(const QPointF& p1, const QPointF& p2,
        QPointF& collidePoint) = 0;//»ñµÃÅö×²µã
    double reflectXita(const double& xita, const QPointF& point);//»ñµÃÅö×²·ŽÉäœÇ
    virtual void tangentialEquation(const QPointF& point,
        double &A, double& B, double& C) = 0;//»ñµÃÇÐÏß·œ³ÌAx+By+C=0
    void verticalEquation(const QPointF& point, double& A,
        double& B, double& C);//»ñµÃAx+By+C=0ÔÚµãpointŽŠµÄŽ¹Ïß·œ³Ì
};

#endif
