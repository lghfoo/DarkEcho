#include"choicescene.h"
#include"../game.h"
ChoiceScene::ChoiceScene(const QRect& rect, QGraphicsView* view)
    :BaseScene(rect)
{
    world = new World;
    playButton = NULL;
    int wid = rect.width();
    int hei = height();
    int aveWid = wid ;
    int recWid = aveWid * 1 / 5;
    QRect _rect(0, 0, recWid, hei / 8);
    playButton = new TextButton(_rect);
    int dis = (aveWid - recWid) / 2;

    playButton->setPos(dis, hei * 78 / 100);
    playButton->setText("PLAY");
    playButton->setVisible(false);
    playButton->setTextColor(Qt::white);
    addItem(playButton);
    connect(playButton, SIGNAL(clicked()), this, SLOT(pressPlay()));

    setBackgroundBrush(Qt::black);
    setForegroundBrush(Qt::black);
}
void ChoiceScene::enterProgress()
{
    if (!start())
    {
        setStart(true);
        counter = 0;
        playButton->setVisible(true);
        createWorld();
        appear(750,Qt::black);
        return;
    }
    if (start()	&& opaAni().state() != QAbstractAnimation::Running)
    {
        setStart(false);
        enter(false);
        stay(true);
    }
}
void ChoiceScene::stayProgress()
{
    const double W = 4.0;
    const int T = 6000;
    const double S = 3.0;
    switch (counter)
    {
    case 0://1
        addLineCustomWave(QPointF(2661, 1440), M_PI / 4.0 , 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2759, 1446), M_PI / 4.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2830, 1448), -M_PI * 32 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2914, 1444), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3064, 1437), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3156, 1435), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3192, 1443), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3295, 1441), M_PI / 10.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 30://2
        addLineCustomWave(QPointF(2657, 1497), -M_PI / 3, 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2745, 1485), M_PI / 4.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2830, 1448), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2915, 1502), -M_PI * 75 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3064, 1437), M_PI * 30.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3122, 1450), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3192, 1443), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3295, 1441), -M_PI*90.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 60://3
        addLineCustomWave(QPointF(2705, 1449), M_PI / 13.0, 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2788, 1488), -M_PI / 6.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2829, 1491), -M_PI * 80 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2946, 1449), -M_PI * 75 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3059, 1511), M_PI * 20.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3122, 1450), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3194, 1499), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3276, 1471), M_PI*60 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 90://4
        addLineCustomWave(QPointF(2703, 1494), M_PI/17, 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2775, 1450), -M_PI / 6.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2874, 1447), M_PI * 40 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2950, 1501), M_PI * 75 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3041, 1496), M_PI * 20.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3138, 1508), M_PI * 0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3194, 1499), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3276, 1471), -M_PI * 40 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 120://5
        addLineCustomWave(QPointF(2659, 1472), M_PI / 4, 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2760, 1490), -M_PI*38 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2874, 1447), M_PI * 60 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2950, 1501), -M_PI * 40 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3041, 1496), -M_PI * 70.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3138, 1508), M_PI * 80 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3249, 1441), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3287, 1508), M_PI * 60 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 150://6
        addLineCustomWave(QPointF(2714, 1480), M_PI / 4, 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2734, 1515), -M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2865, 1498), M_PI * 60 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2913, 1477), -M_PI * 40 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3042, 1461), -M_PI * 70.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3112, 1479), M_PI * 80 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3249, 1441), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3287, 1508), -M_PI * 40 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 180://7
        addLineCustomWave(QPointF(2693, 1505), 0, 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2800, 1512), -M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2853, 1479), M_PI * 20 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2913, 1477), M_PI * 40 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3042, 1461), M_PI * 30.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3112, 1479), -M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3218, 1472), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3328, 1506), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 210://8
        addLineCustomWave(QPointF(2716, 1476), M_PI / 3.0 , 350,
            500, T, 100, W, Qt::white, S);//D
        addLineCustomWave(QPointF(2767, 1441), -M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//A
        addLineCustomWave(QPointF(2837, 1473), -M_PI * 70 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//R
        addLineCustomWave(QPointF(2929, 1475), M_PI * 40 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//K
        addLineCustomWave(QPointF(3059, 1472), M_PI * 30.0 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//E
        addLineCustomWave(QPointF(3119, 1504), -M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//C
        addLineCustomWave(QPointF(3218, 1472), M_PI * 30 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//H
        addLineCustomWave(QPointF(3339, 1463), M_PI * 50 / 100.0, 350,
            500, T, 100, W, Qt::white, S);//O
        break;
    case 240:
        counter = -1;
    }
    counter++;
}
void ChoiceScene::leaveProgress()
{
    if (!start())
    {
        setStart(true);
        disappear(750);
        return;
    }
    if (start() && opaAni().state() != QAbstractAnimation::Running)
    {
        playButton->setVisible(false);
        setStart(false);
        enter(false);
        stay(true);
        emit(sceneEnd(nextScene(), true));
    }
}

void ChoiceScene::pressPlay()
{
    setNextScene(Game::LEVEL_SCENE);
    Game::enableMouse(false);
    stay(false);
    leave(true);
}

void ChoiceScene::createWorld()
{
    m_baseCanvas->setPos((sceneRect().width() - 60000) / 2.0,
        (sceneRect().height() - 30000) / 2.0);
    mapCanvas->setPos((60000 - 6000) / 2.0,
        (30000 - 3000) / 2.0);

    QList<Wall*> wallList;
    LineWall* lineWall;
    BezierWall* bezierWall;
    QFile mapFile(":/maps/ChoiceScene.m");
    if (!mapFile.open(QIODevice::ReadOnly))
    {
        abort();
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
}

ChoiceScene::~ChoiceScene()
{
    delete world;
}


