#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H
#include"basebutton.h"
class TextButton :public BaseButton
{
    Q_OBJECT
public:
    TextButton(const QRectF& rect);
    ~TextButton();
    void setText(const QString& _text);
    QString text()const;
    void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget);
    void setTextColor(const QColor& c);
    public slots:
    void march();
private:
    QString m_text;
    double m_x;
    double m_y;
    double m_width;
    double m_height;
    QPointF m_leftPoint;
    QPointF m_rightPoint;
    QColor textColor;
    QTimer* timer;
    virtual void checkMethod(const QPointF& posInItem);
};

#endif
