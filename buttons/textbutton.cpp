#include"textbutton.h"
#include"../scenes/basescene.h"
#include"../game.h"
TextButton::TextButton(const QRectF& rect)
    :BaseButton(rect)
{
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(march()));
    timer->start(100);
    m_x = rect.x();
    m_y = rect.y();
    m_width = rect.width();
    m_height = rect.height();
    m_leftPoint = QPointF(m_x, m_y);
    m_rightPoint = QPointF(m_x + m_width,
        m_y+m_height);
}

QString TextButton::text()const
{
    return m_text;
}

void TextButton::setText(const QString& _text)
{
    m_text = _text;
    update();
}

void TextButton::paint(QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QColor compCol = QColor(255 - textColor.red(), 255 - textColor.green(), 255 - textColor.blue(), 150);
    painter->setBrush(compCol);
    painter->drawRoundedRect(boundingRect(), 15, 30, Qt::RelativeSize);
    painter->restore();
    if (mouseIsHovering())
    {
        painter->setOpacity(0.8);
    }
    else
    {
        painter->setOpacity(0.5);
    }
    QFont font;
    font.setPixelSize(m_height * 75 / 100);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(textColor);
    painter->drawText(QRectF(m_x, m_y,
        m_width, m_height),
        Qt::AlignCenter, m_text);
}

void TextButton::checkMethod(const QPointF& posInItem)
{

#define pii posInItem
#define lp m_leftPoint
#define rp m_rightPoint
    if (pii.x() >= lp.x() && pii.x() <= rp.x()
        && pii.y() >= lp.y() &&pii.y() <= rp.y())
    {
        m_mouseIsHovering = true;
        return;
    }
#undef pii
#undef lp
#undef rp
    m_mouseIsHovering = false;
    return;
}

void TextButton::march()
{
    checkHover();
    update();
}

void TextButton::setTextColor(const QColor& c)
{
    textColor = c;
}

TextButton::~TextButton()
{
    delete timer;
}
