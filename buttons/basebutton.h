#ifndef BASEBUTTON_H
#define BASEBUTTON_H
#include"../allheader.h"
class BaseButton :public QObject, public QGraphicsItem
{
        Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
        BaseButton(const QRectF& rect);
        bool mouseIsHovering()const;
        void setRect(const QRectF& rect);
        QRectF boundingRect()const;
protected:
        bool m_mouseIsHovering;
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void checkHover();
private:
        QRectF m_rect;
        virtual void checkMethod(const QPointF& posInItem) = 0;
signals:
        void clicked();
};

#endif
