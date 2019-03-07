#include"reflectwave.h"
#include"../monster.h"
ReflectWave::ReflectWave(World* const _world, QList<Monster*>* am,
    int*  _waveNum)
    :NormalWave(_world), attractiveMonster(am),
    waveNum(_waveNum)
{
    isAbsorbed = false;
    pen.setWidth(1);
    isAttractive = false;
}

void ReflectWave::setIsAttactive(const bool& a)
{
    isAttractive = a;
}

void ReflectWave::changeColor(const QColor& _color)
{
    if (_color == Qt::black)
    {
        pen.setColor(Qt::white);
        pen.setWidth(8);
    }
    else
    {
        pen.setWidth(oriWidth);
        pen.setColor(_color);
    }
}

void ReflectWave::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (pointList.isEmpty())return;
    painter->setOpacity(1 - curTime / maxTime);
    if (listHead <= listTail
        &&listHead < pointList.size())
    {
        QPointF temp = pointList[listHead];
        changeColor(pointColorList[listHead]);
        painter->setPen(pen);
        for (int i = turnHead; i < turnTail; i++)
        {
            if (i < turnList.size())
            {
                painter->drawLine(temp, turnList[i]);
                temp = turnList[i];
                changeColor(turnColorList[i]);
                painter->setPen(pen);
            }
        }
        if (listTail < pointList.size())
        {
            painter->drawLine(temp, pointList[listTail]);
        }
    }
}
void ReflectWave::advance(int phase)
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
        if (listTail +1 < pointList.size())
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
    if (!isAbsorbed)
    {
        checkAbsorbe();
    }
    curTime += 15.0;
    update();
}
void ReflectWave::createPointList()
{
    int** area = world->area();
    QPointF _startPoint = mapFromParent(startPoint);
    pointList.push_back(_startPoint);
    QColor curCol, nextCol;
    QPoint p = World::mapPoint(_startPoint);
    curCol = World::colorArr[area[p.x()][p.y()]];
    pointColorList.push_back(curCol);
    QList<Wall*>wall = world->wall();
    QList<QPointF>collidePoints;
    QList<int>collideItems;
    QPointF p1 = _startPoint, p2, collidePoint, nearestPoint, tempPoint;
    double _startXita = startXita, remainLen = maxDis,
        reflectXita, dx, dy, cosStartXita, sinStartXita;
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
        cosStartXita = qCos(_startXita);
        sinStartXita = qSin(_startXita);
        dx = remainLen*cosStartXita;
        dy = -remainLen*sinStartXita;
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
        dx = stepLen*cosStartXita;
        dy = -stepLen*sinStartXita;
        tempPoint = QPointF(p1.x() + dx, p1.y() + dy);
        double _dis = 0;
        while (!(qAbs(tempPoint.x() - collidePoint.x()) < stepLen
            &&qAbs(tempPoint.y() - collidePoint.y()) < stepLen))
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
            pointList.push_back(tempPoint);
            tempPoint = QPointF(tempPoint.x() + dx,
                tempPoint.y() + dy);

        }
        pointList.push_back(collidePoint);
        turnList.push_back(collidePoint);
        p = World::mapPoint(collidePoint);
        turnColorList.push_back(World::colorArr[area[p.x()][p.y()]]);
        pointColorList.push_back(World::colorArr[area[p.x()][p.y()]]);
    }
}

void ReflectWave::checkAbsorbe()
{
    if (listTail >= pointList.size())return;
    QPointF p = mapToParent(pointList[listTail]), temp, temp2;
    double dis;
    QList<Monster*>monster = world->monster();
    for (int i = 0; i < monster.size(); i++)
    {
        temp = monster[i]->pos();
        dis = (p.x() - temp.x())*(p.x() - temp.x())
            + (p.y() - temp.y())*(p.y() - temp.y());
        if (dis <= 50 * 50)
        {
            while (pointList.size() > listTail + 15)
            {
                if (!turnList.isEmpty())
                {
                    temp = pointList.last();
                    temp2 = turnList.last();
                    if (qAbs(temp.x() - temp2.x()) < stepLen
                    &&qAbs(temp.y() - temp2.y()) < stepLen)
                    {
                        turnColorList.pop_back();
                        turnList.pop_back();
                    }
                }
                pointList.pop_back();
                pointColorList.pop_back();
            }
            for (int j = listTail; j < pointList.size(); j++)
            {
                pointColorList[j] = Qt::red;
            }
            for (int j = turnTail; j < turnColorList.size(); j++)
            {
                turnColorList[j] = Qt::red;
            }
            if (turnTail < turnList.size())
            {
                turnList.insert(turnTail, p);
                turnColorList.insert(turnTail, Qt::red);
            }
            else
            {
                turnList.push_back(p);
                turnColorList.push_back(Qt::red);
            }
            turnTail++;
            isAbsorbed = true;
            if (isAttractive && !attractiveMonster->contains(monster[i]))
            {
                attractiveMonster->push_back(monster[i]);
                monster[i]->moveTo(startPoint);
            }
            break;
        }
    }
}

void ReflectWave::setOriWidth(const int& w)
{
    oriWidth = w;
    pen.setWidth(oriWidth);
}

ReflectWave::~ReflectWave()
{
    (*waveNum)--;
    if (!(*waveNum))
    {
        delete waveNum;
        waveNum = NULL;
        delete attractiveMonster;
        attractiveMonster = NULL;
    }
}
