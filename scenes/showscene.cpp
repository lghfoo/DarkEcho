#include"showscene.h"
#include"../game.h"
ShowScene::ShowScene(const QRect& rect)
    :BaseScene(rect)
{
    m_png[QT] = new QGraphicsPixmapItem;
    m_png[RAC7] = new QGraphicsPixmapItem;

    m_qtPng.load(":/images/qt.png");
    m_rac7Png.load(":/images/rac7.png");

    m_png[QT]->setPixmap(m_qtPng);
    m_png[RAC7]->setPixmap(m_rac7Png);

    m_png[QT]->setPos((width() - m_qtPng.width()) / 2,
        (height() - m_qtPng.height()) / 2);
    m_png[RAC7]->setPos((width() - m_rac7Png.width()) / 2,
        (height() - m_rac7Png.height()) / 2);

    addItem(m_png[QT]);
    addItem(m_png[RAC7]);
    m_png[QT]->setVisible(false);
    m_png[RAC7]->setVisible(false);

    setCurPng(QT);
}



int ShowScene::curPng()const
{
    return m_curPng;
}

void ShowScene::setCurPng(const int& pro)
{
    m_curPng = pro;
}

void ShowScene::enterProgress()
{
    if (!start())
    {
        setStart(true);
        m_png[m_curPng]->setVisible(true);
        appear(750);
        return;
    }
    if (start()	&& opaAni().state() != QAbstractAnimation::Running)
    {
        setStart(false);
        enter(false);
        leave(true);
    }
}

void ShowScene::stayProgress()
{
    //nothing
}

void ShowScene::leaveProgress()
{
    if (!start())
    {
        setStart(true);
        disappear(150);
        return;
    }
    if (start() && opaAni().state() != QAbstractAnimation::Running)
    {
        m_png[m_curPng]->setVisible(false);
        setStart(false);
        enter(true);
        leave(false);
        if (m_curPng == QT)
        {
            setCurPng(RAC7);
            return;
        }
        if (m_curPng == RAC7)
        {
            emit(sceneEnd(Game::CHOICE_SCENE, true));
        }
    }
}

void ShowScene::createWorld()
{
}
