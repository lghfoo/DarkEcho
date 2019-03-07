#include"customwave.h"
CustomWave::CustomWave(World* const _world)
    :NormalWave(_world)
{
    setDefaultColor(Qt::black);
    setDefaultWidth(5.0);
}

void CustomWave::setDefaultWidth(const double& _w)
{
    pen.setWidth(_w);
}

void CustomWave::setDefaultColor(const QColor& _c)
{
    pen.setColor(_c);
}

void CustomWave::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (pointList.isEmpty())
    {
        return;
    }
    painter->setOpacity(1 - curTime / maxTime);
    painter->setPen(pen);
    if (listHead < pointList.size())
    {
        QPointF temp = pointList[listHead];
        for (int i = turnHead; i < turnTail; i++)
        {
            if (i < turnList.size())
            {
                painter->drawLine(temp, turnList[i]);
                temp = turnList[i];
            }
        }
        if (listTail < pointList.size())
        {
            painter->drawLine(temp, pointList[listTail]);
        }
    }
}
void CustomWave::advance(int phase)
{
    if (!phase)return;
    if (!scene())return;
    if (qAbs(curTime - (maxTime)) <= 15.0)
    {
        setParentItem(NULL);
        delete this;
        return;
    }
    NormalWave::advance(phase);
    if (curDis < maxDis)
    {
        curDis += stepLen;
        if (listTail < pointList.size() - 1)
        {
            if (turnTail < turnList.size())
            {
                QPointF temp1 = turnList[turnTail];
                QPointF temp2 = pointList[listTail];
                double dx = qAbs(temp1.x() - temp2.x());
                double dy = qAbs(temp1.y() - temp2.y());
                if (dx < stepLen&&dy < stepLen)
                {
                    turnTail++;
                }
            }
            listTail++;
        }
    }
    curTime += 15.0;
    update();
}
void CustomWave::createPointList()
{
    int** area = world->area();
    QPointF _startPoint = mapFromParent(startPoint);
    pointList.push_back(_startPoint);
    QPoint p;
    QColor curCol, nextCol;
    QList<Wall*>wall = world->wall();
    QList<QPointF>collidePoints;
    QList<int>collideItems;
    QPointF p1 = _startPoint, p2, collidePoint, nearestPoint, tempPoint;
    double _startXita = startXita, remainLen = maxDis,
        reflectXita, dx, dy;
    int remainTimes = maxCollideTimes, nearestItem;
    bool cover, start = true;
    listHead = listTail = turnHead = turnTail = 0;
    while (remainTimes && qAbs(remainLen) > 0.0000001)
    {
        if (!start)
        {
            _startXita = reflectXita;
            p1 = collidePoint;
        }
        start = false;
        collidePoints.clear();
        collideItems.clear();
        remainTimes--;
        dx = remainLen*qCos(_startXita);
        dy = -remainLen*qSin(_startXita);
        p2 = QPointF(p1.x() + dx, p1.y() + dy);
        cover = false;
        for (int i = 0; i < wall.size(); i++)
        {
            if (wall[i]->collideWith(mapToParent(p1),
                mapToParent(p2), collidePoint))
            {
                if (start || qAbs(p1.x() - collidePoint.x()) > 0.0000001
                    || qAbs(p1.y() - collidePoint.y()) > 0.0000001)
                {
                    collidePoints.push_back(collidePoint);
                    collideItems.push_back(i);
                }
            }
        }

        if (!collidePoints.isEmpty())
        {
            nearestPoint = collidePoints[0];
            nearestItem = collideItems[0];
            for (int i = 1; i < collidePoints.size(); i++)
            {
                if (qAbs(collidePoints[i].x()
                    - nearestPoint.x()) < 0.0000001
                    &&qAbs(collidePoints[i].y()
                        - nearestPoint.y()) < 0.0000001)
                {
                    cover = true;
                }
                else
                    if (qAbs(collidePoints[i].x() - p1.x())
                        < qAbs(nearestPoint.x() - p1.x()) ||
                        qAbs(collidePoints[i].y() - p1.y())
                        < qAbs(nearestPoint.y() - p1.y()))
                    {
                        nearestPoint = collidePoints[i];
                        nearestItem = collideItems[i];
                        cover = false;
                    }
            }
            collidePoint = mapFromParent(nearestPoint);
            if (remainTimes)
            {
                if (cover)
                {
                    reflectXita = _startXita + M_PI;
                }
                else
                {
                    reflectXita = wall[nearestItem]->reflectXita(_startXita, nearestPoint);
                }
                remainLen -= hypot(p1.x() - collidePoint.x(),
                    p1.y() - collidePoint.y());
            }
        }
        else
        {
            remainLen = 0.0;
            collidePoint = p2;
        }
        dx = stepLen*qCos(_startXita);
        dy = -stepLen*qSin(_startXita);
        tempPoint = QPointF(p1.x() + dx, p1.y() + dy);
        double _dis = 0;
        while (!(qAbs(tempPoint.x() - collidePoint.x()) < stepLen
            &&qAbs(tempPoint.y() - collidePoint.y()) < stepLen))
        {
            pointList.push_back(tempPoint);
            tempPoint = QPointF(tempPoint.x() + dx,
                tempPoint.y() + dy);
        }
        pointList.push_back(collidePoint);
        turnList.push_back(collidePoint);
    }
}
