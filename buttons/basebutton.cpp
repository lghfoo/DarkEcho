#include"basebutton.h"
#include"../scenes/basescene.h"
#include"../game.h"
BaseButton::BaseButton(const QRectF& rect)
{
    m_mouseIsHovering = false;
    setFlag(QGraphicsItem::ItemIsSelectable);
    setRect(rect);
}

bool BaseButton::mouseIsHovering()const
{
    return m_mouseIsHovering;
}

void BaseButton::setRect(const QRectF& rect)
{
    prepareGeometryChange();
    m_rect = rect;
    update();
}

QRectF BaseButton::boundingRect()const
{
    return QRectF(m_rect);
}


void BaseButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (Game::mouseIsEnabled()
        && event->button() == Qt::LeftButton)
    {
        emit(clicked());
    }
}

//Œì²éÊó±êÊÇ·ñÐüÍ£
void BaseButton::checkHover()
{
    if (!Game::mouseIsEnabled())return;
    QGraphicsScene* _scene = scene();
    if (!_scene)
    {
        m_mouseIsHovering = false;
        return;
    }
    BaseScene* bs = static_cast<BaseScene*>(_scene);
    QPointF posInSce = bs->cursorPos();
    QPointF posInItem = mapFromScene(posInSce);
    checkMethod(posInItem);
    if (m_mouseIsHovering)
    {
        setCursor(Qt::PointingHandCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}
