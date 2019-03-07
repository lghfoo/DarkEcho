#include"buttonline.h"
#include"levelbutton.h"
ButtonLine::ButtonLine(BaseButton* const _fromBtn,
    BaseButton* const _toBtn)
{
    m_fromButton = _fromBtn;
    m_toButton = _toBtn;
    setZValue(-1);
    QPen pen;
    pen.setColor(Qt::white);
    setPen(pen);
}

const BaseButton* ButtonLine::fromButton()const
{
    return m_fromButton;
}

const BaseButton* ButtonLine::toButton()const
{
    return m_toButton;
}

void ButtonLine::advance(int pahse)
{
    const LevelButton* fB = static_cast<const LevelButton*>(fromButton());
    const LevelButton* tB = static_cast<const LevelButton*>(toButton());
    setLine(QLineF(fB->cenPos(), tB->cenPos()));
}

