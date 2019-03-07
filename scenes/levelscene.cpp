#include"levelscene.h"
#include"../game.h"
const QString LevelScene::romanNumber[LevelScene::LEVEL_NUM+1]=
{
    "","I","II","III","IV","V","VI","VII","VIII","IX","X",
    "XI","XII","XIII","XIV","XV","XVI","XVII"
};
const QString LevelScene::levelName[LevelScene::LEVEL_NUM + 1] =
{
    "","Blind","Breakout","Death","Fear","Hunt","Serenity","Slink","Splash","Jarless","Stunt",
    "Violate","Pull","Push","Taunt","Distract","Lorn","Demo"
};
LevelScene::LevelScene(const QRect& rect, const int& _curLevel)
    :BaseScene(rect)
{
    setCurLevel(_curLevel);
    createAndPlaceButton();
    setBackgroundBrush(Qt::black);
    setForegroundBrush(Qt::black);
}

void LevelScene::enterProgress()
{
    if (!start())
    {
        setStart(true);
        if (forwardEnter())
        {
            mapCanvas->setPos(mapCanvas->rightX(),
                -height() / 2.0);
            double dx = -(height() / 2.0)*(curLevel() - 1);
            mapCanvas->slide(dx, 0, QEasingCurve::InOutBack, 2000);
            appear(750, Qt::black);
        }
        else
        {
            mapCanvas->setPos(-(width() / 2.0 + (Game::chosenLevel() - 1)*(height() / 2.0)),
                -height() / 2.0);
            QPointF p = m_levelButton[Game::chosenLevel() - 1]->pos();
            m_levelButton[Game::chosenLevel() - 1]->setPos(p.x(), height() * 3.0 / 8.0);
            m_levelButton[Game::chosenLevel() - 1]->setIsFloating(true);
            m_levelButton[Game::chosenLevel() - 1]->setFloat(qrand() % 20 + 40);
            for (int i = 0; i <LEVEL_NUM; i++)
            {
                if (i != Game::chosenLevel() - 1)
                {
                    double posY = height()*(qrand() % 50 + 15) / 100.0;
                    double floatY = qrand() % 20 + 40;
                    double _x = m_levelButton[i]->pos().x();
                    m_levelButton[i]->setPos(_x, posY);
                    m_levelButton[i]->setFloat(floatY);
                    m_levelButton[i]->setIsFloating(true);
                }
            }
            m_baseCanvas->zoom(5.0, 1.0, 1200);
            appear(1200, Qt::black);
        }
        Game::enableMouse(false);

    }
    if (start() && opaAni().state() != QAbstractAnimation::Running)
    {
        setStart(false);
        enter(false);
        stay(true);
    }
}

void LevelScene::stayProgress()
{
    if (mapCanvas->sliAni()->state() != QAbstractAnimation::Running)
    {
        Game::enableMouse(true);
    }
}

void LevelScene::leaveProgress()
{
    if (!start() && mapCanvas->sliAni()->state() != QAbstractAnimation::Running)
    {
        m_baseCanvas->zoom(1.0, 5.0, 1200);
        disappear(1200);
        setStart(true);
    }
    if (start() && opaAni().state() != QAbstractAnimation::Running)
    {
        setStart(false);
        leave(false);
        emit(sceneEnd(nextScene(), true));
    }
}

int LevelScene::levelNum()const
{
    return m_levelNum;
}

void LevelScene::setCurLevel(const int& _curLevel)
{
    m_curLevel = _curLevel;
}

int LevelScene::curLevel()const
{
    return m_curLevel;
}

void LevelScene::createAndPlaceButton()
{
    double btnD = height() / 4.0;
    double disBetweenBtn = 2 * btnD;


    double btnCanW = LEVEL_NUM* btnD
        + (LEVEL_NUM - 1)*(disBetweenBtn - btnD) + width() - btnD;
    double btnCanH = height();

    double baseCanW = (2 * LEVEL_NUM - 1)*btnD
        + (2 * LEVEL_NUM - 2)*(disBetweenBtn - btnD) + width() - btnD;
    double baseCanH = height();

    m_baseCanvas->setRect(QRectF(-baseCanW / 2.0, -baseCanH / 2.0, baseCanW, baseCanH));
    m_baseCanvas->setPos(width() / 2.0, height() / 2.0);
    mapCanvas->setRect(QRectF(0, 0, btnCanW, btnCanH));
    mapCanvas->setMoveable(true);
    mapCanvas->setLeftX(-baseCanW / 2.0);
    mapCanvas->setRightX(-width() / 2.0);
    QRectF btnRect = QRectF(0, 0, btnD, btnD);
    double x = width() / 2.0 - btnD / 2.0;
    for (int i = 0; i < LEVEL_NUM; i++)
    {
        double posY = height()*(qrand() % 50 + 15) / 100.0;
        double floatY = qrand() % 20+40;
        m_levelButton[i] = new LevelButton(btnRect);
        m_levelButton[i]->setText(romanNumber[i + 1] +
            QString('\n') + levelName[i + 1]);
        m_levelButton[i]->setPos(x, posY);
        m_levelButton[i]->setFloat(floatY);
        m_levelButton[i]->setIsFloating(true);
        m_levelButton[i]->setParentItem(mapCanvas);
        m_levelButton[i]->setLevel(i + 1);
        if (i + 1 > curLevel())
        {
            m_levelButton[i]->setIsLocked(true);
        }
        else
        {
            m_levelButton[i]->setIsLocked(false);
        }
        connect(m_levelButton[i], SIGNAL(clicked(const int&)),
            this, SLOT(toGameScene(const int&)));
        if (i)
        {
            m_buttonLine[i-1] = new ButtonLine(m_levelButton[i - 1],
                m_levelButton[i]);
            m_buttonLine[i-1]->setParentItem(mapCanvas);
        }
        x += disBetweenBtn;
    }
}


void LevelScene::toGameScene(const int& _level)
{
    if (_level > curLevel())return;
    setNextScene(Game::GAME_SCENE);
    Game::setChosenLevel(_level);
    if (mapCanvas->sliAni()->state() == QAbstractAnimation::Running)
    {
        mapCanvas->fix();
    }
    double cenX = width() / 2.0;
    double cenY = height() / 2.0;
    QPointF btnPos = m_levelButton[_level - 1]->cenScenePos();
    double dx = cenX - btnPos.x();
    double dy = cenY - btnPos.y();
    mapCanvas->slide(dx, dy, QEasingCurve::Linear, 2 * hypot(dx, dy) + 100);

    stay(false);
    leave(true);
    Game::enableMouse(false);
}

void LevelScene::createWorld()
{
}

bool LevelScene::isLocked(const int& _level)
{
    return m_levelButton[_level - 1]->isLocked();
}

void LevelScene::unlockLevel(const int& _level)
{
    m_levelButton[_level - 1]->setIsLocked(false);
    QFile file("curLevel.dat");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        abort();
    }
    QDataStream out(&file);
    out << _level;
}
