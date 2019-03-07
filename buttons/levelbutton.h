#ifndef LEVELBUTTON_H
#define LEVELBUTTON_H
#include"basebutton.h"

class LevelButton :public BaseButton
{
    Q_OBJECT
public:
    LevelButton(const QRectF& rect);
    bool isLocked()const;
    void setIsLocked(const bool& _isLocked);
    QString text()const;
    void setText(const QString& _text);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    virtual void advance(int phase);
    QPointF flowUp()const;
    QPointF flowDown()const;
    void setIsFloating(const bool& _isFloating);
    bool isFloating()const;
    void setFloat(const double& _dy);
    QPointF cenPos()const;
    QPointF cenScenePos();
    int level()const;
    void setLevel(const int& _level);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
private:
    virtual void checkMethod(const QPointF& posInItem);
    bool m_isLocked;
    QString m_text;
    QPointF m_flowUp;
    QPointF m_flowDown;
    bool m_isFloating;
    double m_delta;
    int m_level;
signals:
    void clicked(const int& _level);
};

#endif
