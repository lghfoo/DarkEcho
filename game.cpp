#include"game.h"
bool Game::s_mouseIsEnabled = true;
int Game::s_adjust = 1;
int Game::s_chosenLevel = -1;
bool Game::mouseIsEnabled()
{
    return s_mouseIsEnabled;
}

int Game::adjust()
{
    return s_adjust;
}

int Game::chosenLevel()
{
    return s_chosenLevel;
}

void Game::setChosenLevel(const int& _level)
{
    s_chosenLevel = _level;
}

void Game::enableMouse(const bool& _enable)
{
    s_mouseIsEnabled = _enable;
}
Game::Game()
{
    m_view = new QGraphicsView;
    m_timer = new QTimer;

    QDesktopWidget* desktop = QApplication::desktop();
    int dWidth = desktop->width();
    int dHeight = desktop->height();
    const int vWidth = 844;
    const int vHeight = 475;
    int adjust = s_adjust;
    int vX = (dWidth - (vWidth + 2 * adjust)) / 2;
    int vY = (dHeight - (vHeight + 2 * adjust)) / 2;
    m_view->setGeometry(vX, vY, vWidth + 2 * adjust, vHeight + 2 * adjust);
    m_view->setFixedSize(vWidth + 2 * adjust, vHeight + 2 * adjust);
    m_view->setWindowIcon(QIcon(":/images/DarkEcho.png"));
    setCurSce(NIL);
    m_view->setRenderHint(QPainter::Antialiasing);
    const QRect rect = QRect(0, 0, vWidth, vHeight);
    m_scene[SHOW_SCENE] = new ShowScene(rect);
    m_scene[CHOICE_SCENE] = new ChoiceScene(rect, m_view);
    int curLevel = readCurLevel();
    m_scene[LEVEL_SCENE] = new LevelScene(rect, curLevel);
    LevelScene* levelScene = static_cast<LevelScene*>(m_scene[LEVEL_SCENE]);
    levelScene->setCurLevel(curLevel);
    m_scene[GAME_SCENE] = new GameScene(rect);
    GameScene* gs = static_cast<GameScene*>(m_scene[GAME_SCENE]);
    gs->setTimer(m_timer);
    gs->setLevelScene(static_cast<LevelScene*>(m_scene[LEVEL_SCENE]));
    m_timer->setInterval(15);
}

void Game::run()
{
    toScene(SHOW_SCENE, true);
    m_view->show();
    m_timer->start();
}

const QTimer& Game::timer()const
{
    return *m_timer;
}

void Game::toScene(const int& sceneName, const bool& forward)
{
    if (curScene() != NIL)
    {
        QObject::disconnect(m_scene[curScene()], SIGNAL(sceneEnd(const int&, const bool&)), this, SLOT(toScene(const int&, const bool&)));
        QObject::disconnect(m_timer, SIGNAL(timeout()), m_scene[curScene()], SLOT(progress()));
        QObject::disconnect(m_timer, SIGNAL(timeout()), m_scene[curScene()], SLOT(advance()));
    }
    setCurSce(sceneName);
    m_view->setScene(m_scene[curScene()]);
    BaseScene* bs = static_cast<BaseScene*>(m_scene[curScene()]);
    bs->enter(true, forward);
    QObject::connect(m_scene[curScene()], SIGNAL(sceneEnd(const int&,const bool&)), this, SLOT(toScene(const int&,const bool&)));
    QObject::connect(m_timer, SIGNAL(timeout()), m_scene[curScene()], SLOT(progress()));
    QObject::connect(m_timer, SIGNAL(timeout()), m_scene[curScene()], SLOT(advance()));
    if (curScene() == LEVEL_SCENE)
    {
        m_timer->setInterval(30);
    }
    else m_timer->setInterval(15);
}

void Game::setCurSce(const int& curSce)
{
    m_curScene = curSce;
}

int Game::curScene()const
{
    return m_curScene;
}

int Game::readCurLevel()
{
    int curLevel;
    QFile file("curLevel.dat");
    if (!QFile::exists("curLevel.dat"))
    {
        if (!file.open(QIODevice::WriteOnly))
        {
            abort();
        }
        QDataStream out(&file);
        out << 1;
        file.close();
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        abort();
    }
    QDataStream in(&file);
    in >> curLevel;
    file.close();
    return curLevel;
}

Game::~Game()
{
    delete m_view;
    delete m_timer;
    for (int i = 0; i < SCENE_NUM; i++)
    {
        delete m_scene[i];
    }
}
