#include"canvas.h"
#include"game.h"
Canvas::Canvas()
{
    setZValue(-1);
    m_isMoveable = false;

    m_zoomAni = m_sliAni = NULL;
    m_sliAni = new QPropertyAnimation;
    m_sliAni->setTargetObject(this);
    m_sliAni->setPropertyName("_pos");

    m_zoomAni = new QPropertyAnimation;
    m_zoomAni->setTargetObject(this);
    m_zoomAni->setPropertyName("_scale");
    m_boundingRect = QRectF(0, 0, 0, 0);
    setLeftX(-0xfffffff);
    setRightX(0xfffffff);
    lastMovePos = QPointF(0xfffff, 0xfffff);
    isSlideAdvancing = false;
}
void Canvas::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    return;
}
QRectF Canvas::boundingRect()const
{
    return QRectF(m_boundingRect);
}

void Canvas::setMoveable(const bool& isMoveable)
{
    m_isMoveable = isMoveable;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!Game::mouseIsEnabled())return;
    if (event->button() == Qt::LeftButton&&m_isMoveable)
    {
        QCursor tempCursor = cursor();
        tempCursor.setShape(Qt::OpenHandCursor);
        setCursor(tempCursor);
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (!Game::mouseIsEnabled())return;
    if (event->buttons() == Qt::LeftButton&&m_isMoveable)
    {
        if (m_sliAni->state() == QAbstractAnimation::Running
            &&m_sliAni->easingCurve() != QEasingCurve::InOutBack)
        {
            fix();
        }
        double dx = event->pos().x() - event->lastPos().x();
        QPointF point = pos();
        double x = qBound(m_leftX, point.x() + dx, m_rightX);
        point.setX(x);
        setPos(point);
        lastMovePos = event->pos();
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (!Game::mouseIsEnabled())return;
    if (event->button() == Qt::LeftButton&&m_isMoveable)
    {
        QCursor tempCursor = cursor();
        tempCursor.setShape(Qt::ArrowCursor);
        setCursor(tempCursor);
        if (qAbs(lastMovePos.x() - 0xfffff) < 0.0001
            || qAbs(lastMovePos.y() - 0xfffff) < 0.0001)return;//Ã»ÓÐMove
        double dx = lastMovePos.x() - event->pos().x();
        slide(dx*10.0, 0, QEasingCurve::Linear, 500);
        lastMovePos = QPointF(0xfffff, 0xfffff);
    }
}

void Canvas::setRect(const QRectF& rect)
{
    m_boundingRect = rect;
    prepareGeometryChange();
    update();
}

void Canvas::set_pos(const QPointF& __pos)
{
    setPos(__pos);
    update();
}

QPointF Canvas::_pos()const
{
    return pos();
}

void Canvas::setLeftX(const double& leftX)
{
    m_leftX = leftX;
}

void Canvas::setRightX(const double& rightX)
{
    m_rightX = rightX;
}

void Canvas::slide(const double& dx, const double& dy,
    QEasingCurve ec, const int& dur)
{
    if (sliAni()->state() == QAbstractAnimation::Running)
    {
        fix();
    }
    QPointF point = pos();
    point.setX(qBound(m_leftX, pos().x() + dx, m_rightX));
    point.setY(pos().y() + dy);
    m_sliAni->setKeyValueAt(0.0, pos());
    m_sliAni->setKeyValueAt(1.0, point);
    m_sliAni->setEasingCurve(ec);
    m_sliAni->setDuration(dur);
    m_sliAni->start(QAbstractAnimation::KeepWhenStopped);
}

double Canvas::_scale()const
{
    return scale();
}

void Canvas::set_scale(const double& __scale)
{
    setScale(__scale);
    update();
}

void Canvas::zoom(const double& from, const double& to, const int& dur)
{
    m_zoomAni->setKeyValueAt(0.0, from);
    m_zoomAni->setKeyValueAt(1.0, to);
    m_zoomAni->setDuration(dur);
    m_zoomAni->setEasingCurve(QEasingCurve::InExpo);
    m_zoomAni->start(QAbstractAnimation::KeepWhenStopped);
}

double Canvas::leftX()const
{
    return m_leftX;
}

double Canvas::rightX()const
{
    return m_rightX;
}

const QPropertyAnimation* Canvas::sliAni()const
{
    return m_sliAni;
}

void Canvas::fix()
{
    m_sliAni->stop();
    isSlideAdvancing = false;
}

void Canvas::advance(int phase)
{
    if (!phase)return;
    if (isSlideAdvancing)
    {
        if (qAbs(pos().x() - targetPoint.x()) < qAbs(xStepLen)
            && qAbs(pos().y() - targetPoint.y()) < qAbs(yStepLen))
        {
            setPos(targetPoint);
            isSlideAdvancing = false;
        }
        else
        {
            if (qAbs(pos().x() - targetPoint.x()) < qAbs(xStepLen))
            {
                setPos(targetPoint.x(), pos().y() + yStepLen);
            }
            else
            {
                if (qAbs(pos().y() - targetPoint.y()) < qAbs(yStepLen))
                {
                    setPos(pos().x() + xStepLen, targetPoint.y());
                }
                else
                {
                    setPos(pos().x() + xStepLen, pos().y() + yStepLen);
                }
            }
        }
    }
}

void Canvas::slideAdvance(const double& dx, const double& dy,
    const int& dur)
{
    isSlideAdvancing = true;
    targetPoint = QPointF(pos().x() + dx, pos().y() + dy);
    xStepLen = (dx / ((double)(dur)))*15.0;
    yStepLen = (dy / ((double)(dur)))*15.0;
}

Canvas::~Canvas()
{
    delete m_sliAni;
    delete m_zoomAni;
}
