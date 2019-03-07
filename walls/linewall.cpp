#include"linewall.h"
bool LineWall::collideWith(const QPointF& _p1, const QPointF& _p2,
    QPointF& collidePoint)
{
    return (intersect(QLineF(_p1, _p2), &collidePoint)
        == BoundedIntersection);
}

void LineWall::tangentialEquation(const QPointF& point, double& A, double& B, double& C)
{
    A = B = C = 0;
    if (p1() == p2())
    {
        return;
    }
    if (p1().x() == p2().x())
    {
        A = 1;
        B = 0;
        C = -p1().x();
        return;
    }
    A = (p1().y() - p2().y()) / (p1().x() - p2().x());
    B = 1.0;
    C = A*p1().x() + p1().y();
    return;
}
