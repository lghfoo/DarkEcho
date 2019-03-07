#include"soundwave.h"
#include"../scenes/basescene.h"
SoundWave::SoundWave(World* const _world)
    :world(_world)
{
    maxDis = maxLen = 100.0;
    maxCollideTimes = 4;
    curLen = curDis = curTime = 0.0;
    stepLen = 3.5;
    firstFall = secondFall = 0;
}
void SoundWave::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
    QWidget* widget)
{
    if (pointList.isEmpty())
    {
        return;
    }
    painter->setOpacity(1 - curTime / maxTime);
    if (waveFlags&CHOICEWAVE
        || waveFlags&CASTWAVE)
    {
        painter->setPen(pen);
    }
    static int _counter = 0;
    if (listHead < pointList.size())
    {
        QPointF temp = pointList[listHead];
        if (waveFlags&REFLECTWAVE)
        {
            if (pointColorList[listHead] == Qt::black)
            {
                pen.setColor(Qt::white);
                pen.setWidth(8);
            }
            else
            {
                pen.setWidth(3);
                pen.setColor(pointColorList[listHead]);
            }
            painter->setPen(pen);
        }
        for (int i = turnHead; i < turnTail; i++)
        {
            if (i < turnList.size())
            {
                painter->drawLine(temp, turnList[i]);
                temp = turnList[i];
                if (waveFlags&REFLECTWAVE)
                {
                    if (turnColorList[i] == Qt::black)
                    {
                        pen.setColor(Qt::white);
                        pen.setWidth(8);
                    }
                    else
                    {
                        pen.setWidth(3);
                        pen.setColor(turnColorList[i]);
                    }
                    painter->setPen(pen);
                }
            }
        }
        if (listTail < pointList.size())
        {
            painter->drawLine(temp, pointList[listTail]);
        }
    }
}

QRectF SoundWave::boundingRect()const
{
    return QRectF(-0xffff, -0xffff, 2*0xffff, 2*0xffff);
}

void SoundWave::advance(int phase)
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
            if (turnHead < turnList.size())
            {
                QPointF temp1 = turnList[turnHead];
                QPointF temp2 = pointList[listHead];
                double dx = qAbs(temp1.x() - temp2.x());
                double dy = qAbs(temp1.y() - temp2.y());
                if (dx < stepLen&&dy < stepLen)
                {
                    turnHead++;
                }
            }
            listHead++;
        }
    }
    if (curDis < maxDis)
    {
        curDis += stepLen;
        if (listTail < pointList.size())
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
    if (waveFlags&CASTWAVE)
    {
        if (listTail == firstFall)
        {
            BaseScene* _scene = static_cast<BaseScene*>(scene());
    //		_scene->addCircleWave(pointList[listTail], 15,
    //			300, 500, 2500, 4);
        }
        if (listTail == secondFall)
        {
            BaseScene* _scene = static_cast<BaseScene*>(scene());
    //		_scene->addCircleWave(pointList[listTail], 10,
    //			300, 500, 2000, 4);
        }
    }
    curTime += 15.0;
    update();
}

void SoundWave::setMaxLen(const double& _maxLen)
{
    maxLen = _maxLen;
}

void SoundWave::setMaxCollideTimes(const int& _maxCollideTimes)
{
    maxCollideTimes = _maxCollideTimes;
}

void SoundWave::setMaxTime(const double& _maxTime)
{
    maxTime = _maxTime;
}

void SoundWave::setMaxDis(const double& _maxDis)
{
    maxDis = _maxDis;
}

void SoundWave::createPointList()
{
    int** area = world->area();
    QPointF _startPoint = mapFromParent(startPoint);
    pointList.push_back(_startPoint);
    QPoint p;
    QColor curCol, nextCol;
    if (waveFlags&REFLECTWAVE)
    {
        p = World::mapPoint(_startPoint);
        curCol = World::colorArr[area[p.x()][p.y()]];
        pointColorList.push_back(curCol);
    }
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
                    || qAbs(p1.y() -collidePoint.y()) > 0.0000001)
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
                        < qAbs(nearestPoint.x() - p1.x())||
                        qAbs(collidePoints[i].y()-p1.y())
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
            if (waveFlags&REFLECTWAVE)
            {
                curCol = pointColorList.last();
                p = World::mapPoint(tempPoint);
                nextCol = World::colorArr[area[p.x()][p.y()]];
                if (nextCol != curCol)
                {
                    turnList.push_back(tempPoint);
                    turnColorList.push_back(nextCol);
                }
                pointColorList.push_back(nextCol);
            }
            pointList.push_back(tempPoint);
            tempPoint = QPointF(tempPoint.x() + dx,
                tempPoint.y() + dy);
            if (waveFlags&CASTWAVE)
            {
                _dis += stepLen;
                if (_dis >= maxDis / 2.0 && !firstFall)
                {
                    firstFall = pointList.size()-1;
                }
            }

        }
        if (waveFlags&CASTWAVE)
        {
            secondFall = pointList.size()-1;
            if (!firstFall)
            {
                firstFall = secondFall;
            }
        }
        pointList.push_back(collidePoint);
        turnList.push_back(collidePoint);
        if (waveFlags&REFLECTWAVE)
        {
            p = World::mapPoint(collidePoint);
            turnColorList.push_back(World::colorArr[area[p.x()][p.y()]]);
            pointColorList.push_back(World::colorArr[area[p.x()][p.y()]]);
        }
        if (waveFlags&CASTWAVE)
        {
            break;
        }
    }

    if (waveFlags&CHOICEWAVE)
    {
        pen.setWidth(5);
        pen.setColor(Qt::black);
    }
    else
    {
        pen.setWidth(3);
        if (waveFlags&CASTWAVE)
        {
            pen.setColor(Qt::white);
        }
    }
}


void SoundWave::setStartPoint(const QPointF& _startPoint)
{
    startPoint = _startPoint;
}

void SoundWave::setStartXita(const double& _startXita)
{
    startXita = _startXita;
}

void SoundWave::setWaveFalgs(const int& _flags)
{
    waveFlags = _flags;
}
