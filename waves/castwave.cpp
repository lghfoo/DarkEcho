#include"castwave.h"
#include"../scenes/basescene.h"
CastWave::CastWave(World* const _world)
    :BaseWave(_world)
{
    firstFall = secondFall = 0;
    pen.setWidth(3);
    pen.setColor(Qt::white);
}

void CastWave::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (pointList.isEmpty())return;
    painter->setOpacity(1 - curTime / maxTime);
    painter->setPen(pen);
    if (listHead < pointList.size()
        && listTail < pointList.size())
    {
        painter->drawLine(pointList[listHead],
            pointList[listTail]);
    }
}

void CastWave::advance(int phase)
{
    if (!phase)return;
    if (!scene())return;
    if (qAbs(curTime - (maxTime)) <= 15.0)
    {
        setParentItem(NULL);
        delete this;
        return;
    }
    if (curLen < maxLen)
    {
        curLen += stepLen;
    }
    else
    {
        if (listHead < pointList.size())
        {
            listHead++;
        }
    }
    if (curDis < maxDis)
    {
        curDis += stepLen;
        if (listTail < pointList.size() - 1)
        {
            listTail++;
        }
    }
    if (listTail == firstFall)
    {
        BaseScene* _scene = static_cast<BaseScene*>(scene());
        _scene->addCircleReflectWave(pointList[listTail], 17,
            350, 700, 3000, 4, true, 3, startXita);
    }
    if (listTail == secondFall)
    {
        BaseScene* _scene = static_cast<BaseScene*>(scene());
        _scene->addCircleReflectWave(pointList[listTail], 13,
            250, 500, 2500, 4, true, 3, startXita);
    }
    curTime += 15.0;
    update();
}

void CastWave::createPointList()
{
    QPointF _startPoint = mapFromParent(startPoint);
    pointList.push_back(_startPoint);
    QList<Wall*>wall = world->wall();
    QList<QPointF>collidePoints;
    QPointF p1 = _startPoint, p2, collidePoint, nearestPoint, tempPoint;
    double dx, dy;
    double cosStartXita = qCos(startXita);
    double sinStartXita = qSin(startXita);
    listHead = listTail = 0;
    collidePoints.clear();
    dx = maxDis * cosStartXita;
    dy = -maxDis * sinStartXita;
    p2 = QPointF(p1.x() + dx, p1.y() + dy);
    for (int i = 0; i < wall.size(); i++)
    {
        if (wall[i]->collideWith(mapToParent(p1),
            mapToParent(p2), collidePoint))
        {
            collidePoints.push_back(collidePoint);
        }
    }
    if (!collidePoints.isEmpty())
    {
        nearestPoint = collidePoints[0];
        for (int i = 1; i < collidePoints.size(); i++)
        {
            if (qAbs(collidePoints[i].x() - p1.x())
                < qAbs(nearestPoint.x() - p1.x()) ||
                qAbs(collidePoints[i].y() - p1.y())
                < qAbs(nearestPoint.y() - p1.y()))
            {
                nearestPoint = collidePoints[i];
            }
        }
        collidePoint = mapFromParent(nearestPoint);
    }
    else
    {
        collidePoint = p2;
    }
    dx = stepLen * cosStartXita;
    dy = -stepLen * sinStartXita;
    tempPoint = QPointF(p1.x() + dx, p1.y() + dy);
    double _dis = 0;
    while (!(qAbs(tempPoint.x() - collidePoint.x()) < stepLen
        &&qAbs(tempPoint.y() - collidePoint.y()) < stepLen))
    {

        pointList.push_back(tempPoint);
        tempPoint = QPointF(tempPoint.x() + dx,
            tempPoint.y() + dy);
        _dis += stepLen;
        if (_dis >= maxDis / 2.0 && !firstFall)
        {
            firstFall = pointList.size() - 1;
        }
    }
    secondFall = pointList.size() - 1;
    if (!firstFall)
    {
        firstFall = secondFall;
    }
    pointList.push_back(collidePoint);
}
