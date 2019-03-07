#include"levelbutton.h"
#include"../game.h"
LevelButton::LevelButton(const QRectF& rect)
    :BaseButton(rect)
{
    if (qrand() % 3)m_delta = 0.8;
    else m_delta = -0.8;
}

void LevelButton::checkMethod(const QPointF& posInItem)
{
#define tR tempRect
#define pii posInItem
#define cp centrePoint
    QRectF tempRect = boundingRect();
    QPointF centrePoint = QPointF(tR.x() + tR.width() / 2.0,
        tR.y() + tR.height() / 2.0);
    double r = tR.width() / 2.0;
    if (hypot(pii.x() - cp.x(), pii.y() - cp.y()) <= r)
    {
        m_mouseIsHovering = true;
        return;
    }
#undef cp
#undef tR
#undef pii
    m_mouseIsHovering = false;
}

bool LevelButton::isLocked()const
{
    return m_isLocked;
}

void LevelButton::setIsLocked(const bool& _isLocked)
{
    m_isLocked = _isLocked;
}

QString LevelButton::text()const
{
    return m_text;
}

void LevelButton::setText(const QString& _text)
{
    m_text = _text;
}

void LevelButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QRectF tempRect = boundingRect();
    QPen pen;
    if (!mouseIsHovering())
    {
        pen.setWidthF(1.0);
    }
    else
    {
        pen.setWidthF(3.5);
    }
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->setBrush(Qt::black);
    painter->drawEllipse(tempRect.x(), tempRect.y(),
        tempRect.width(), tempRect.height());
    QFont font;
    font.setPixelSize(tempRect.width() / 5.0);
    painter->setFont(font);
    if(isLocked())
    {
        painter->drawText(tempRect.x(), tempRect.y(),
            tempRect.width(), tempRect.height() / 2.0,
            Qt::AlignBottom | Qt::AlignCenter, text());
        painter->translate(45.3125, 62.5);
        pen.setWidthF(1.5);
        pen.setColor(Qt::white);
        painter->setPen(pen);
        painter->drawRoundedRect(QRect(4, 19.5, 20, 20), 30, 30, Qt::RelativeSize);
        painter->drawLine(9, 9, 9, 19);
        painter->drawLine(19, 9, 19, 19);
        painter->drawArc(9, 4, 10, 15, 0, 2880);
        painter->setBrush(Qt::white);
        painter->drawEllipse(12, 24, 4, 4);
        pen.setWidthF(3.0);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);
        painter->drawLine(14, 26, 14, 34);
    }
    else
    {
        painter->drawText(tempRect.x(), tempRect.y(),
            tempRect.width(), tempRect.height(),
            Qt::AlignCenter, text());
    }
}

void LevelButton::advance(int phase)
{
    if (!phase)return;
    checkHover();
    if (isFloating())
    {
        double y = pos().y() + m_delta;
        setPos(pos().x(), y);
        if (y <= flowUp().y() || y >= flowDown().y())
        {
            m_delta = -m_delta;
        }
    }
    update();
}

bool LevelButton::isFloating()const
{
    return m_isFloating;
}

void LevelButton::setIsFloating(const bool& _isFloating)
{
    m_isFloating = _isFloating;
}

QPointF LevelButton::flowUp()const
{
    return m_flowUp;
}

QPointF LevelButton::flowDown()const
{
    return m_flowDown;
}

void LevelButton::setFloat(const double& _dy)
{
    double uY, dY;
    uY = pos().y() - _dy;
    dY = pos().y() + _dy;
    m_flowUp = QPointF(pos().x(), uY);
    m_flowDown = QPointF(pos().x(), dY);
}

QPointF LevelButton::cenPos()const
{
    return QPointF(pos().x() + boundingRect().width() / 2.0,
        pos().y() + boundingRect().height() / 2.0);
}

int LevelButton::level()const
{
    return m_level;
}

void LevelButton::setLevel(const int& _level)
{
    m_level = _level;
}

void LevelButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (Game::mouseIsEnabled()
        && event->button() == Qt::LeftButton
        && !isLocked()
        && mouseIsHovering())
    {
        setIsFloating(false);
        emit(clicked(level()));
    }
    BaseButton::mouseReleaseEvent(event);
}

QPointF LevelButton::cenScenePos()
{
    QRectF br = boundingRect();
    return mapToScene(QPointF(br.x() + br.width() / 2.0,
        br.y() + br.height() / 2.0));
}
