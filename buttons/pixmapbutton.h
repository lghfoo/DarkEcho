#ifndef PIXMAPBUTTON_H
#define PXIMAPBUTTON_H
#include"basebutton.h"

class PixmapButton :public BaseButton
{
    Q_OBJECT
public:
    PixmapButton(const QRectF& rect);
    ~PixmapButton();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void setPixmap(const QPixmap& pix);
    public slots:
    void march();
private:
    QTimer* timer;
    QPixmap* pixmap;
    virtual void checkMethod(const QPointF& posInItem);
};

#endif
