#include"bezierwall.h"
bool BezierWall::collideWith(const QPointF& _p1, const QPointF& _p2,
    QPointF& collidePoint)
{
    double dxp = _p2.x() - _p1.x();
    double dyp = _p2.y() - _p1.y();
    double tArr[2];
    int tLen = 0;
    double a, b, c, delta,
        x1, y1, t1, x2, y2, t12;
    if (qAbs(dxp) > 0.0001)
    {
        double k = dyp / dxp;
        a = k*aX - aY;
        b = k*bX - bY;
        c = k*cX - cY + _p1.y() - k*_p1.x();
    }
    else
    {
        a = aX;
        b = bX;
        c = cX - _p1.x();
    }
    if (qAbs(a) < 0.0001)
    {
        if (qAbs(b) < 0.0001)return false;
        double t2 = -c / b;
        y1 = getYVal(t2);
        x1 = getXVal(t2);
        if (qAbs(dxp) < 0.0001)
        {
            t1 = (y1 - _p1.y()) / dyp;
        }
        else
        {
            t1 = (x1 - _p1.x()) / dxp;
        }
        if (t1 < 0 || t1>1)return false;
        collidePoint = QPointF(x1, y1);
        return true;
    }
    delta = b*b - 4.0 * a*c;
    if (delta < 0)return false;
    double sqrtDel = qSqrt(delta);
    double t21 = (-b + sqrtDel) / (2.0*a);
    double t22 = (-b - sqrtDel) / (2.0*a);
    if (!(t21 < 0 || t21>1))tArr[tLen++] = t21;
    if (!(t22 < 0 || t22>1))tArr[tLen++] = t22;
    if (tLen == 0)return false;
    x1 = getXVal(tArr[0]);
    y1 = getYVal(tArr[0]);
    if (qAbs(dxp) < 0.0001)
    {
        t1 = (y1 - _p1.y()) / dyp;
    }
    else
    {
        t1 = (x1 - _p1.x()) / dxp;
    }
    if (tLen == 1 &&
        ((t1 < 0 || t1>1)
            || qAbs(t1) < 0.0000001))return false;;
    collidePoint = QPointF(x1, y1);
    if (tLen == 1)return true;
    x2 = getXVal(tArr[1]);
    y2 = getYVal(tArr[1]);
    if (qAbs(dxp) < 0.0000001)
    {
        t12 = (y2 - _p1.y()) / dyp;
    }
    else
    {
        t12 = (x2 - _p1.x()) / dxp;
    }
    if (t1 < 0 || t1>1
        || qAbs(t1) < 0.0000001)
    {

        if (t12 < 0 || t12>1
            || qAbs(t12) < 0.0000001)return false;
        collidePoint = QPointF(x2, y2);
        return true;
    }
    if (t12 < 0 || t12>1
        || (qAbs(t12) < 0.0000001))return true;
    if (qAbs(x2 - _p1.x()) < qAbs(x1 - _p1.x())
        || qAbs(y2 - _p1.y()) < qAbs(y1 - _p1.y()))
    {
        collidePoint = QPointF(x2, y2);
    }
    return true;
}

void BezierWall::tangentialEquation(const QPointF& point, double& A, double& B, double& C)
{
    A = B = C = 0;
    double x = point.x(),
        y = point.y(), t;
    if (qAbs(aX) < 0.0001)
    {
        t = (x - cX) / bX;
    }
    else
    {
        double k = aY / aX;
        t = (k*x - y - k*cX + cY) / (k*bX - bY);
    }
    double dx = 2 * aX*t + bX;
    double dy = 2 * aY*t + bY;
    if (qAbs(dx) < 0.0001)
    {
        A = 1.0;
        B = 0.0;
        C = -x;
        return;
    }
    double k = dy / dx;
    A = k;
    B = 1.0;
    C = k*x + y;
    return;
}

void BezierWall::setBezier(const QPointF& _p1, const QPointF& _p2, const QPointF& _p3)
{
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    aX = p1.x() - 2 * p2.x() + p3.x();
    bX = 2 * (p2.x() - p1.x());
    cX = p1.x();
    aY = p1.y() - 2 * p2.y() + p3.y();
    bY = 2 * (p2.y() - p1.y());
    cY = p1.y();
}

double BezierWall::getXVal(const double& _t)
{
    return aX*_t*_t + bX*_t + cX;
}

double BezierWall::getYVal(const double& _t)
{
    return aY*_t*_t + bY*_t + cY;
}
