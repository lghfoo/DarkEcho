#ifndef CANVAS_H
#define CANVAS_H
#include"allheader.h"
class Canvas :public QObject, public QGraphicsItem
{
        Q_OBJECT
        Q_INTERFACES(QGraphicsItem)
                Q_PROPERTY(QPointF _pos READ _pos WRITE set_pos)
                Q_PROPERTY(double _scale READ _scale WRITE set_scale)
public:
        Canvas();
        ~Canvas();
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        QRectF boundingRect()const;
        void setMoveable(const bool& isMoveable);
        void setRect(const QRectF& rect);
        void set_pos(const QPointF& __pos);
        void setLeftX(const double& leftX);
        void setRightX(const double& rightX);
        double leftX()const;
        double rightX()const;
        void slide(const double& dx,const double& dy,
                QEasingCurve ec, const int& dur);
        void slideAdvance(const double& dx, const double& dy,
                const int& dur);
        double _scale()const;
        void set_scale(const double& __scale);
        QPointF _pos()const;
        void zoom(const double& from, const double& to, const int& dur = 1000);//??¡¤?
        const QPropertyAnimation* sliAni()const;
        void fix();
        void advance(int phase);
private:
        bool m_isMoveable;
        QRectF m_boundingRect;
        double m_leftX;
        double m_rightX;
        QPropertyAnimation* m_sliAni;
        QPropertyAnimation* m_zoomAni;
        QPointF lastMovePos;
        bool isSlideAdvancing;
        QPointF targetPoint;
        double xStepLen;
        double yStepLen;
protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};

#endif
