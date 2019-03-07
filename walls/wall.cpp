#include"wall.h"
double Wall::reflectXita(const double& xita, const QPointF& point)
{
    double A, B, C, verticalXita, retXita;
    verticalEquation(point, A, B, C);
    if (qAbs(B) < 0.01)
    {
        verticalXita = M_PI / 2.0;
    }
    verticalXita = qAtan(-A / B);
    return (retXita = 2 * verticalXita - xita + M_PI);
}

void Wall::verticalEquation(const QPointF& point, double& A, double& B, double& C)
{
    double _A, _B, _C;
    tangentialEquation(point, _A, _B, _C);
    A = -_B;
    B = _A;
    C = _B*point.x() - _A*point.y();
    return;
}
