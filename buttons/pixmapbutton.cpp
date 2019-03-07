#include"pixmapbutton.h"
PixmapButton::PixmapButton(const QRectF& rect)
    :BaseButton(rect)
{
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(march()));
    timer->start(100);
    pixmap = NULL;
}

void PixmapButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    QRectF rect = boundingRect();
    if (mouseIsHovering())
    {
        painter->setPen(QPen(Qt::white));
        painter->drawRect(rect);
    }
    if (pixmap)
    {
        painter->drawPixmap(rect.width() / 2.0 - pixmap->width() / 2.0,
            rect.height() / 2.0 - pixmap->height() / 2.0, *pixmap);
    }
}

void PixmapButton::setPixmap(const QPixmap& pix)
{
    if (pixmap)
    {
        delete pixmap;
        pixmap = NULL;
    }
    pixmap = new QPixmap(pix);
}

void PixmapButton::checkMethod(const QPointF& posInItem)
{
#define pii posInItem
#define tR tempRect
    QRectF tempRect = boundingRect();
    if (pii.x() >= tR.x() && pii.x() <= tR.x() + tR.width()
        && pii.y() >= tR.y() && pii.y() <= tR.y() + tR.height())
    {
        m_mouseIsHovering = true;
        return;
    }
#undef pii
#undef tR
    m_mouseIsHovering = false;
    return;
}

void PixmapButton::march()
{
    checkHover();
    update();
}

PixmapButton::~PixmapButton()
{
    delete timer;
    if (!pixmap)delete pixmap;
}




