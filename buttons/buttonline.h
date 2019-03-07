#ifndef BUTTONLINE_H
#define BUTTONLINE_H
#include"basebutton.h"
class ButtonLine :public QGraphicsLineItem
{
public:
    ButtonLine(BaseButton* const _fromBtn, BaseButton* const _toBtn);
    const BaseButton* fromButton()const;
    const BaseButton* toButton()const;
    virtual void advance(int phase);
private:
    BaseButton* m_fromButton;
    BaseButton* m_toButton;
};

#endif
