#include"footprint.h"
Footprint::Footprint(const int& _type, const double& _dir)
{
    setType(_type);
    footColor = Qt::white;
    m_direction = _dir;
    setIsFading(false);
    m_startFading = false;
    m_hadPaintedLeft = false;
    m_hadPaintedRight = false;
    m_counter = 0;
    setLeftFoot();
    m_interval = 20;
    setZValue(3);
}
void Footprint::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(footColor);
    painter->rotate(m_direction);
    switch (type())
    {
    case LEFTFOOT:
        painter->translate(0, -4);
        painter->drawPath(m_leftFoot);
        break;
    case RIGHTFOOT:
        painter->translate(0, 4);
        painter->scale(1, -1);
        painter->drawPath(m_leftFoot);
        break;
    case FEET:
        painter->translate(0, -8);
        painter->drawPath(m_leftFoot);
        m_hadPaintedLeft=true;
        if (m_isFading && !m_hadPaintedRight)
        {
            return;
        }
        if (m_counter == m_interval)
        {
            painter->translate(0, 16);
            painter->scale(1, -1);
            painter->drawPath(m_leftFoot);
            m_hadPaintedRight = true;
        }
        break;
    }
}

QRectF Footprint::boundingRect()const
{
    return QRectF(-25, -25, 50, 50);
}

int Footprint::type()const
{
    return m_type;
}

void Footprint::setType(const int& _type)
{
    m_type = _type;
}

void Footprint::advance(int phase)
{
    if (!phase)return;
    if (m_isFading)
    {
        if (!m_startFading)
        {
            setOpacity(0.5);
            m_startFading = true;
        }
        else
        {
            setOpacity(qBound(0.0, opacity() - 0.0005, 1.0));
        }
        if (qAbs(opacity() - 0.0) < 0.00001)
        {
            setParentItem(NULL);
            delete this;
            return;
        }
    }
    if (type() == FEET && m_hadPaintedLeft)
    {
        if (m_counter < m_interval)
        {
            m_counter++;
        }
        if (m_counter == m_interval)
        {
            update();
        }
    }
}

void Footprint::setIsFading(const bool& _isFading)
{
    m_isFading = _isFading;
}

void Footprint::setLeftFoot()
{
    m_leftFoot.moveTo(-5, -4);
    m_leftFoot.lineTo(-5, 4);
    m_leftFoot.cubicTo(-14, 6, -14, -4, -5, -4);
    m_leftFoot.moveTo(-2, -4);
    m_leftFoot.lineTo(-2, 4);
    m_leftFoot.cubicTo(15, 7, 15, -4, -2, -4);
}

void Footprint::setBrush(const QColor& c)
{
    if (c != Qt::black)
    {
        footColor = c;
    }
    else
    {
        footColor = Qt::white;
    }
    update();
}


