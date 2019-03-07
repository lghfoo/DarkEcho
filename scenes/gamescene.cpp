#include"gamescene.h"
#include"../game.h"
#include"levelscene.h"
#include"../monster.h"
GameScene::GameScene(const QRect& rect)
    :BaseScene(rect)
{
    setBackgroundBrush(Qt::black);
    setForegroundBrush(Qt::black);
    m_areaType = 0;
    setLevel(-1);
    world = new World;
    QPixmap p(":/images/pause.png");
    m_pauseButton = new PixmapButton(QRectF(0, 0, p.width(), p.height()));
    m_pauseButton->setPixmap(p);
    m_pauseButton->setPos(width() - p.width(), 0);
    connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(popupPauseDialog()));
    QRectF _rect = QRectF(0, 0, width() * 7 / 24.0, height() / 8.0);
    m_continueButton = new TextButton(_rect);
    m_restartButton = new TextButton(_rect);
    m_exitButton = new TextButton(_rect);
    m_continueButton->setTextColor(Qt::white);
    m_restartButton->setTextColor(Qt::white);
    m_exitButton->setTextColor(Qt::white);

    addItem(m_continueButton);
    addItem(m_restartButton);
    addItem(m_exitButton);
    addItem(m_pauseButton);
    m_continueButton->setVisible(false);
    m_restartButton->setVisible(false);
    m_exitButton->setVisible(false);
    m_pauseButton->setVisible(false);

    m_levelNumber = new QGraphicsTextItem;
    m_levelName = new QGraphicsTextItem;
    m_continueButton->setText("Continue");
    m_restartButton->setText("Restart");
    m_exitButton->setText("Exit");
    m_levelNumber->setDefaultTextColor(Qt::white);
    m_levelName->setDefaultTextColor(Qt::white);

    addItem(m_levelName);
    addItem(m_levelNumber);
    m_levelName->setVisible(false);
    m_levelNumber->setVisible(false);

    double x = width() / 2.0 - _rect.width() / 2.0;
    m_continueButton->setPos(x, height() / 4.0);
    m_restartButton->setPos(x, height() / 4.0 + height() / 8.0 + height() / 16.0);
    m_exitButton->setPos(x, height() - height() / 4.0 - height() / 8.0);

    connect(m_continueButton, SIGNAL(clicked()),
        this, SLOT(continueAction()));
    connect(m_restartButton, SIGNAL(clicked()),
        this, SLOT(restartAction()));
    connect(m_exitButton, SIGNAL(clicked()),
        this, SLOT(exitAction()));
    setStart(false);
    m_enableMouseLater = m_connectLater = false;
}


void GameScene::setLevel(const int& _level)
{
    m_level = _level;
    m_enableMouseLater = false;
}

void GameScene::initialize()
{
    m_xita = 0;
    m_isStanding = true;
    mapCanvas->fix();
    m_hasRightClicked = m_standBeforeCreep
        = m_isWalking = m_isRunning = m_hasClicked
        = m_readyToStep = m_hasStood = m_isPausing
        = m_markTime = false;
    m_runCounter = m_creepCounter
        = m_standCounter = m_walkCounter = 0;
    m_footState = Footprint::FEET;
    if (m_connectLater)
    {
        m_connectLater = false;
        connect(m_timer, SIGNAL(timeout()), this, SLOT(advance()));
    }
}

void GameScene::enterProgress()
{
    if (!start() && opaAni().state() != QAbstractAnimation::Running)
    {
        clearItem();
        setLevel(Game::chosenLevel());
        levelName = LevelScene::levelName[m_level];
        int _scale = 3;
        m_levelNumber->setScale(_scale);
        m_levelName->setScale(_scale);
        m_levelNumber->setPlainText(LevelScene::romanNumber[m_level]);
        m_levelName->setPlainText(LevelScene::levelName[m_level]);
        QRectF numRect = m_levelNumber->boundingRect();
        QRectF nameRect = m_levelName->boundingRect();
        m_levelNumber->setPos(width() / 2.0 - numRect.width() * _scale / 2.0,
            height() / 2.0 - numRect.height() * _scale);
        m_levelName->setPos(width() / 2.0 - nameRect.width() * _scale / 2.0,
            height() / 2.0);

        m_levelNumber->setVisible(true);
        m_levelName->setVisible(true);

        appear(750,Qt::black);
        setStart(true);
        Game::enableMouse(false);
    }
    if (start() && opaAni().state() != QAbstractAnimation::Running)
    {
        disappear(750);
        enter(false);
        stay(true);
    }
}

void GameScene::leaveProgress()
{
    if (opaAni().state() != QAbstractAnimation::Running)
    {
        if (m_exit)
        {
            clearItem();
            m_exit = false;
            emit(sceneEnd(nextScene(), false));
        }
        stay(false);
        leave(false);
        setStart(false);
    }
}

void GameScene::stayProgress()
{
    if (start() && opaAni().state() != QAbstractAnimation::Running)
    {
        setBackgroundBrush(Qt::black);
        setForegroundBrush(Qt::black);
        clearItem();
        initialize();
        createWorld();
        setForeOpa(0.0);
        m_pauseButton->setVisible(true);
        if (m_levelNumber->isVisible())
        {
            m_levelNumber->setVisible(false);
            m_levelName->setVisible(false);
        }
        setStart(false);
    }
    if (!start() && !m_isPausing)
    {
        if (check())return;
        if (m_enableMouseLater)
        {
            Game::enableMouse(true);
            m_enableMouseLater = false;
        }
        if (m_isRunning)
        {
            if ((m_areaType == World::WATER&&m_runCounter < 40)
                || (m_areaType != World::WATER&&m_runCounter < 30))
            {
                m_runCounter++;
            }
            else
            {
                run();
                m_isWalking = m_isStanding = false;
                m_standCounter = m_walkCounter = m_runCounter = 0;
            }
        }
        else
            if (m_isStanding)
            {
                if (m_isWalking)
                {
                    if (m_areaType == World::WATER&&m_standCounter == 45)
                    {
                        m_isWalking = false;
                    }
                    else
                        if (m_areaType != World::WATER&&m_standCounter == 40)
                        {
                            m_isWalking = false;
                        }
                }
                if (m_standCounter < 50)
                {
                    m_standCounter++;
                }
                else
                {
                    m_footState = Footprint::FEET;
                    stand();
                    if (!m_hasClicked)
                    {
                        Game::enableMouse(true);
                    }
                    m_standBeforeCreep = true;
                    m_isStanding = false;
                    m_standCounter = 0;
                }
            }
    }
}

void GameScene::popupPauseDialog()
{
    m_isPausing = true;
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(advance()));
    m_pauseButton->setVisible(false);
    m_continueButton->setVisible(true);
    m_restartButton->setVisible(true);
    m_exitButton->setVisible(true);
}

void GameScene::continueAction()
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(advance()));
    m_isPausing = false;
    Game::enableMouse(false);
    m_enableMouseLater = true;
    m_pauseButton->setVisible(true);
    m_continueButton->setVisible(false);
    m_restartButton->setVisible(false);
    m_exitButton->setVisible(false);
}

void GameScene::restartAction()
{
    disappear(750);
    Game::enableMouse(false);
    m_enableMouseLater = m_connectLater = true;
    setStart(true);
}

void GameScene::exitAction()
{
    disappear(750);
    Game::enableMouse(false);
    m_enableMouseLater = true;
    setNextScene(Game::LEVEL_SCENE);
    m_exit = true;
    stay(false);
    leave(true);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);
    if (!Game::mouseIsEnabled())return;
    if (!m_isPausing)
    {
        int temp = QTime::currentTime().msecsSinceStartOfDay();
        if (!m_hasClicked)
        {
            m_mousePressTime = temp;
            m_hasClicked = true;
        }
        else
        {
            if (m_areaType != World::WATER&&temp - m_mousePressTime < 300)
            {
                return;
            }
            else
                if (m_areaType == World::WATER&&temp - m_mousePressTime < 500)
                {
                    return;
                }
                else
                {
                    m_mousePressTime = temp;
                }
        }
        if (event->button() == Qt::LeftButton)
        {
            QPointF curPos = event->scenePos();
            double dis = hypot(cenPos().x() - curPos.x(), cenPos().y() - curPos.y());
            if (dis <= 15.0)
            {
                m_readyToStep = true;
                m_readyTime = QTime::currentTime().msecsSinceStartOfDay();
            }
            else
            {
                computeXita(curPos);
                if (m_isWalking)
                {
                    walk();
                }
                else
                {
                    if (m_creepCounter < 2)
                    {
                        creep();
                        m_creepCounter++;
                    }
                    else
                    {
                        m_isWalking = true;
                        walk();
                        m_creepCounter = 0;
                    }
                }
                m_isRunning = true;
                m_isStanding = false;
                m_runCounter = m_standCounter = 0;
            }
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (!Game::mouseIsEnabled())return;
    if (m_isPausing)return;
    if (event->buttons() == Qt::LeftButton)
    {
        m_readyToStep = false;
        QPointF curPos = event->scenePos();
        double dis = hypot(cenPos().x() - curPos.x(), cenPos().y() - curPos.y());
        if (dis <= 5.0)
        {
            m_runDis = 0.0;
            m_markTime = true;
        }
        else
        {
            m_markTime = false;
            computeXita(curPos);
            if (!m_isRunning)
            {
                m_isRunning = true;
                m_isStanding = false;
                m_standCounter = m_runCounter = 0;
            }
        }
    }
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (!Game::mouseIsEnabled())return;
    QGraphicsScene::mouseReleaseEvent(event);
    if (!m_isPausing&&event->button() == Qt::LeftButton)
    {
        if (m_readyToStep && !m_isRunning)
        {
            int interval = QTime::currentTime().msecsSinceStartOfDay() - m_readyTime;
            int waveNum = qBound(13, interval / 30, 80);
            addCircleReflectWave(cenPosInMap(), waveNum, 300,
                1000, qBound(1500, interval * 3 , 6000), 4, true, 3);

            m_readyToStep = false;
        }
        if (m_isRunning)
        {
            m_isRunning = false;
            m_runCounter = 0;
        }
        if (!m_hasStood)
        {
            m_isStanding = true;
            m_standCounter = 0;
        }
    }
    if (!m_isPausing&&event->button() == Qt::RightButton)
    {
        computeXita(event->scenePos());
        if (!m_hasRightClicked)
        {
            m_hasRightClicked = true;
            m_mouseRightPressTime = QTime::currentTime().msecsSinceStartOfDay();
        }
        else
        {
            int temp = QTime::currentTime().msecsSinceStartOfDay();
            if (temp - m_mouseRightPressTime < 1500)return;
            else m_mouseRightPressTime = temp;
        }
        computeXita(event->scenePos());
        addCastWave(cenPosInMap(), m_xita, 500, 700, 5000);
        creep();
        m_isStanding = true;
    }
}

void GameScene::computeXita(const QPointF& curPos)
{
    double dis = hypot(cenPos().x() - curPos.x(), cenPos().y() - curPos.y());
    double dy = -curPos.y() + cenPos().y();
    double dx = curPos.x() - cenPos().x();
    double cosXita = dx / dis;
    double _xita = qAcos(cosXita);
    if (dy < 0)_xita = 2 * M_PI - _xita;
    m_xita = _xita;
}

QPointF GameScene::cenPos()const
{
    return QPointF(width() / 2.0, height() / 2.0);
}

QPointF GameScene::cenPosInMap()
{
    QPointF p = mapCanvas->mapFromScene(cenPos());
    return mapCanvas->mapFromScene(cenPos());
}


void GameScene::createFootprint()
{
    if (m_hasClicked)
    {
        m_footprint->setBrush(World::colorArr[m_areaType]);
        m_footprint->setParentItem(mapCanvas);
        m_footprint->setPos(cenPosInMap());
    }
    m_footprint->setIsFading(true);
    m_footprint = new Footprint(m_footState, -m_xita / M_PI * 180);
}

void GameScene::shiftFoot()
{
    if (m_footState == Footprint::LEFTFOOT)
    {
        m_footState = Footprint::RIGHTFOOT;
    }
    else
    {
        m_footState = Footprint::LEFTFOOT;
    }
}

void GameScene::creep()
{
    if (m_standBeforeCreep)
    {
        m_standBeforeCreep = false;
        createFootprint();
    }
    shiftFoot();
    double dx, dy;
    getDxDy(m_creepDis, dx, dy);
    mapCanvas->slideAdvance(-dx, -dy, 300);
    m_hasStood = false;
}

void GameScene::walk()
{
    shiftFoot();
    createFootprint();
    double dx, dy;
    getDxDy(m_walkDis, dx, dy);
    m_hasStood = false;
    if (m_areaType == World::WATER)
    {
        mapCanvas->slideAdvance(-dx, -dy, 600);
        addCircleReflectWave(cenPosInMap(), 16, 380, 485,
            2000, 4, true, 3, m_xita);
        return;
    }
    mapCanvas->slideAdvance(-dx, -dy, 450);
    addCircleReflectWave(cenPosInMap(), 13, 150, 100,
        1000, 4, false, 3, m_xita);
}

void GameScene::run()
{
    shiftFoot();
    createFootprint();
    double dx, dy;
    getDxDy(m_runDis, dx, dy);
    m_hasStood = false;
    if (m_areaType == World::WATER)
    {
        mapCanvas->slideAdvance(-dx, -dy, 800);
        addCircleReflectWave(cenPosInMap(), 21, 400,
            530, 2500, 4, true, 3, m_xita);
        return;
    }
    mapCanvas->slideAdvance(-dx, -dy, 450);
    addCircleReflectWave(cenPosInMap(), 14, 150,
        360, 1800, 4, true, 3, m_xita);
}



void GameScene::stand()
{
    m_footprint = new Footprint(m_footState, -m_xita / M_PI * 180);
    m_footprint->setParentItem(mapCanvas);
    m_footprint->setPos(cenPosInMap());
    m_footprint->setBrush(World::colorArr[m_areaType]);
    m_hasStood = true;
}

void GameScene::createWorld()
{
    m_baseCanvas->setPos((sceneRect().width() - 60000) / 2.0,
        (sceneRect().height() - 30000) / 2.0);
    mapCanvas->setPos((60000 - 6000) / 2.0,
        (30000 - 3000) / 2.0);

    QList<Wall*> wallList;
    LineWall* lineWall;
    BezierWall* bezierWall;
    QFile mapFile(QString(":/maps/") + LevelScene::levelName[Game::chosenLevel()] +QString(".m"));
    if (!mapFile.open(QIODevice::ReadOnly))
    {
        exitAction();
        return;
    }
    QDataStream inData(&mapFile);
    inData.setVersion(QDataStream::Qt_5_7);
    int size;
    QPointF p1, p2, p3;
    inData >> size;
    for (int i = 0; i < size; i++)
    {
        lineWall = new LineWall;
        inData >> p1 >> p2;
        lineWall->setLine(p1.x(), p1.y(), p2.x(), p2.y());
        wallList.push_back(lineWall);
    }
    world->setArea(inData);
    inData >> size;
    for (int i = 0; i < size; i++)
    {
        bezierWall = new BezierWall;
        inData >> p1 >> p2 >> p3;
        bezierWall->setBezier(p1, p2, p3);
        wallList.push_back(bezierWall);
    }
    world->setWall(wallList);
    QList<Monster*>monsterList;
    Monster* m;
    inData >> size;
    for (int i = 0; i < size; i++)
    {
        m = new Monster(world);
        m->setParentItem(mapCanvas);
        inData >> p1;
        m->setPos(p1);
        monsterList.push_back(m);
    }
    world->setMonster(monsterList);
}

void GameScene::getDxDy(const double& dis,
    double& dx, double& dy)
{
    QPointF p = cenPosInMap();
    double _xita = m_xita + M_PI / 2.0;
    double cosXita = qCos(m_xita);
    double sinXita = qSin(m_xita);
    double cosXitaPlus = qCos(_xita);
    double sinXitaPlus = qSin(_xita);
    QPointF p0 = p + QPointF(10.0 * cosXita, -10.0 * sinXita);
    QPointF temp = QPointF(10.0 * cosXitaPlus, -10.0 * sinXitaPlus);
    QPointF p1 = p0 + temp;
    QPointF p2 = p0 - temp;
    double precision = 1;
    dx = dis*cosXita;
    dy = -dis*sinXita;
    QPointF p11 = p1 + QPointF(dx, dy);
    QPointF p22 = p2 + QPointF(dx, dy);
    if (!collide(p1, p11) && !collide(p2, p22)
        && !collide(p11, p22))
    {
        return;
    }
    else
    {
        double pre = hypot(dx, dy);
        double halfdx = dx / 2.0;
        double halfdy = dy / 2.0;
        double precision = 0.1;
        while (pre > precision)
        {
            if ((collide(p1, p11) || collide(p2, p22)
                || collide(p11, p22)))
            {
                dx -= halfdx;
                dy -= halfdy;
            }
            else
            {
                dx += halfdx;
                dy += halfdy;
            }
            halfdx /= 2.0;
            halfdy /= 2.0;
            pre /= 2.0;
            p11 = p1 + QPointF(dx, dy);
            p22 = p2 + QPointF(dx, dy);
        }
    }
    if (qAbs(dx) < 1.0)dx = 0.0;
    if (qAbs(dy) < 1.0)dy = 0.0;
}

bool GameScene::collide(const QPointF& p1, const QPointF& p2)
{
    QPointF temp;
    QList<Wall*>wall = world->wall();
    for (int i = 0; i < wall.size(); i++)
    {
        if (wall[i]->collideWith(p1, p2, temp))
        {
            return true;
        }
    }
    return false;
}

void GameScene::setTimer(QTimer* const _timer)
{
    m_timer = _timer;
}

bool GameScene::check()
{
    int** area = world->area();
    const QList<Monster*>& monsterList = world->monster();
    QPointF p0 = cenPosInMap();
    for (int i = 0; i < monsterList.size(); i++)
    {
        double dx = p0.x() - monsterList[i]->pos().x();
        double dy = p0.y() - monsterList[i]->pos().y();
        if ((monsterList[i]->getIsMoving() && qAbs(dx) < 50 && qAbs(dy) < 60)
            ||(!monsterList[i]->getIsMoving() && qAbs(dx) < 30 && qAbs(dy) < 30))
        {
            monsterList[i]->setIsActivate(true);
            fail();
            return true;
        }
    }
    QPoint p = World::mapPoint(cenPosInMap());
    m_areaType = area[p.x()][p.y()];
    switch (m_areaType)
    {
    case World::WAYOUT:
    {
        win();
        return true;
    }
    case World::TRAP:
    {
        fail();
        return true;
    }
    case World::WATER:
    {
        m_creepDis = 5.0;
        m_walkDis = 15.0;
        if(!m_markTime)m_runDis = 40.0;
        return false;
    }
    case World::NIL:
    {
        m_creepDis = 5.0;
        m_walkDis = 20.0;
        if(!m_markTime)m_runDis = 50.0;
        return false;
    }
    }
    return false;
}

void GameScene::clearItem()
{
    QList<QGraphicsItem*>itemList = items();
    for (int i = 0; i < itemList.size(); i++)
    {
        if (itemList[i] != m_levelName
            &&itemList[i] != m_levelNumber
            &&itemList[i] != m_pauseButton
            &&itemList[i] != m_restartButton
            &&itemList[i] != m_exitButton
            &&itemList[i] != m_continueButton
            &&itemList[i]!=m_baseCanvas
            &&itemList[i] != mapCanvas)
        {
            removeItem(itemList[i]);
            delete itemList[i];
        }
    }
    if (m_continueButton->isVisible())
    {
        m_continueButton->setVisible(false);
        m_restartButton->setVisible(false);
        m_exitButton->setVisible(false);
    }
    if (m_pauseButton->isVisible())
    {
        m_pauseButton->setVisible(false);
    }
    world->clear();
}

void GameScene::win()
{
    addCircleReflectWave(cenPosInMap(), 60, 700, 1500,
        4000, 6, false, 8, m_xita);
    disappear(3000);
    if (Game::chosenLevel() == LevelScene::LEVEL_NUM)
    {
        setNextScene(Game::LEVEL_SCENE);
        m_exit = true;
        stay(false);
        leave(true);
        return;
    }
    Game::setChosenLevel(m_level + 1);
    if (Game::chosenLevel() <= LevelScene::LEVEL_NUM)
    {
        if (levelScene->isLocked(Game::chosenLevel()))
        {
            levelScene->unlockLevel(Game::chosenLevel());
        }
    }
    Game::enableMouse(false);
    m_enableMouseLater = true;
    setStart(false);
    enter(true);
    stay(false);
}

void GameScene::fail()
{
    addCircleCustomWave(cenPosInMap(), 100, 700, 2000,
        4000, 6, 2, Qt::red, 3.5, m_xita);
    setForegroundBrush(QColor(255, 0, 0, 50));
    disappear(3000);
    Game::enableMouse(false);
    m_enableMouseLater = true;
    setStart(true);
    m_areaType = World::TRAP;
    createFootprint();
}

void GameScene::setLevelScene(LevelScene* const l)
{
    levelScene = l;
}

GameScene::~GameScene()
{
    clear();
    delete world;
}
