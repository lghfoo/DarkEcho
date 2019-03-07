#include"monster.h"
#include"./scenes/basescene.h"
Monster::Monster(World* const _world)
    :world(_world)
{
    isActivate = false;
    isMoving = false;
    stepLen = 1.8;
    counter = 0;
}

QRectF Monster::boundingRect()const
{
    return QRectF(-25, -25, 50, 50);
}

bool Monster::getIsMoving()const
{
    return isMoving;
}
void Monster::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    return;
}

void Monster::advance(int phase)
{
    if (!phase)return;
    if (isMoving)
    {
        QPointF nextP;
        if (qAbs(pos().x() - target.x()) < stepLen
            &&qAbs(pos().y() - target.y()) < stepLen)
        {
            nextP = target;
            isMoving = false;
            counter = 0;
        }
        else
        {
            double dx = stepLen * qCos(marchXita);
            double dy = -stepLen * qSin(marchXita);
            nextP = QPointF(pos().x() + dx,
                pos().y() + dy);
            counter++;
        }
        setPos(nextP);
        if (!(counter % 15))
        {
            BaseScene* bs = static_cast<BaseScene*>(scene());
            double baseR = 10, ddis, lightXita = qrand() % 10, dx, dy;
            QPointF temp;
            for (int i = 0; i < 6; i++)
            {
                ddis = ((double)(qrand() % 20)) / 10.0;
                dx = (baseR + ddis)*qCos(lightXita);
                dy = -(baseR + ddis)*qSin(lightXita);
                temp = QPointF(pos().x() + dx, pos().y() + dy);
                bs->addLineCustomWave(temp, lightXita, 75, 40,
                    1000, 2, 3, Qt::red, 2.0);
                lightXita += (2 * M_PI / 6.0);
            }

            for (int i = 0; i < 5; i++)
            {
                ddis = ((double)(qrand() % 20)) / 10.0;
                dx = (baseR + ddis)*qCos(lightXita);
                dy = -(baseR + ddis)*qSin(lightXita);
                temp = QPointF(pos().x() + dx, pos().y() + dy);
                bs->addLineCustomWave(temp, lightXita, 75, 45,
                    1000, 2, 3, Qt::red, 2.0);
                lightXita += (2 * M_PI / 5.0);
            }
        }
    }
    if (isActivate)
    {
        if (!(counter % 15))
        {
            BaseScene* bs = static_cast<BaseScene*>(scene());
            double baseR = 10, ddis, lightXita = qrand() % 10, dx, dy;
            QPointF temp;
            for (int i = 0; i < 6; i++)
            {
                ddis = ((double)(qrand() % 20)) / 10.0;
                dx = (baseR + ddis)*qCos(lightXita);
                dy = -(baseR + ddis)*qSin(lightXita);
                temp = QPointF(pos().x() + dx, pos().y() + dy);
                bs->addLineCustomWave(temp, lightXita, 75, 40,
                    1000, 2, 3, Qt::red, 2.0);
                lightXita += (2 * M_PI / 6.0);
            }

            for (int i = 0; i < 5; i++)
            {
                ddis = ((double)(qrand() % 20)) / 10.0;
                dx = (baseR + ddis)*qCos(lightXita);
                dy = -(baseR + ddis)*qSin(lightXita);
                temp = QPointF(pos().x() + dx, pos().y() + dy);
                bs->addLineCustomWave(temp, lightXita, 75, 45,
                    1000, 2, 3, Qt::red, 2.0);
                lightXita += (2 * M_PI / 5.0);
            }
        }
        counter++;
    }
    update();
}

void Monster::setIsActivate(const bool& a)
{
    isActivate = a;
}

void Monster::moveTo(const QPointF& tar)
{
    target = tar;
    isMoving = true;
    computeXita(tar);
}

void Monster::computeXita(const QPointF& tar)
{
    double dis = hypot(pos().x() - tar.x(), pos().y() - tar.y());
    double dy = -tar.y() + pos().y();
    double dx = tar.x() - pos().x();
    double cosXita = dx / dis;
    double _xita = qAcos(cosXita);
    if (dy < 0)_xita = 2 * M_PI - _xita;
    marchXita = _xita;
}
