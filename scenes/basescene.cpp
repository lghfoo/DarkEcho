#include"basescene.h"
#include"../monster.h"
#include"../game.h"
BaseScene::BaseScene(const QRect& rect)
{
    setSceneRect(rect);
    m_baseCanvas = new Canvas;
    mapCanvas = new Canvas;
    m_isEntering = m_isStaying = m_isLeaving = false;
    m_opaAni = new QPropertyAnimation;
    m_opaAni->setTargetObject(this);
    m_opaAni->setPropertyName("foreOpa");
    setForeOpa(0.0);
    enter(false);
    stay(false);
    leave(false);
    setStart(false);
    mapCanvas->setParentItem(m_baseCanvas);
    addItem(m_baseCanvas);
}

void BaseScene::enter(const bool& _isEntering, const bool& forward)
{
    m_isEntering = _isEntering;
    m_forwardEnter = forward;
}

void BaseScene::stay(const bool& _isStaying)
{
    m_isStaying = _isStaying;
}

void BaseScene::leave(const bool& _isLeaving)
{
    m_isLeaving = _isLeaving;
}

const QPropertyAnimation& BaseScene::opaAni()const
{
    return *m_opaAni;
}

void BaseScene::disappear(const int& dur)
{
    m_opaAni->setDuration(dur);
    m_opaAni->setKeyValueAt(0.0, 0.0);
    m_opaAni->setKeyValueAt(1.0, 1.0);
    m_opaAni->start();
}

void BaseScene::appear(const int& dur,
    const QColor& oriCol)
{
    setForegroundBrush(QBrush(oriCol));
    m_opaAni->setDuration(dur);
    m_opaAni->setKeyValueAt(0.0, 1.0);
    m_opaAni->setKeyValueAt(1.0, 0.0);
    m_opaAni->start();
}

double BaseScene::foreOpa()const
{
    return m_foreOpa;
}

void BaseScene::setForeOpa(const double& _foreOpa)
{
    m_foreOpa = _foreOpa;
    QBrush brush = foregroundBrush();
    QColor foreCol = brush.color();
    setForegroundBrush(QBrush(QColor(foreCol.red(), foreCol.green(),
        foreCol.blue(), _foreOpa * 255)));
}

bool BaseScene::start()const
{
    return m_start;
}

void BaseScene::setStart(const bool& _start)
{
    m_start = _start;
}

bool BaseScene::forwardEnter()const
{
    return m_forwardEnter;
}

void BaseScene::progress()
{
    if (m_isEntering)enterProgress();
    if (m_isStaying)stayProgress();
    if (m_isLeaving)leaveProgress();
}

QPointF BaseScene::cursorPos()
{
    QList<QGraphicsView*> viewList = views();
    if (viewList.isEmpty())return QPointF(0xfffff, 0xfffff);
    QGraphicsView* view = viewList.at(0);
    QRect rect = view->geometry();
    QCursor cursor = view->cursor();
    int adjust = Game::adjust();
    QPointF ret = QPointF(cursor.pos().x() - adjust - rect.x(),
        cursor.pos().y() - adjust - rect.y());
    return ret;
}

BaseScene::~BaseScene()
{
    delete m_opaAni;
}

int BaseScene::nextScene()const
{
    return m_nextScene;
}

void BaseScene::setNextScene(const int& _nextScene)
{
    m_nextScene = _nextScene;
}

void BaseScene::addLineReflectWave(const QPointF& startPoint, const double& _xita,
    const double& maxLen, const double& maxDis, const double& maxTime,
    const int& maxCollideTimes, const bool& attractive, const int& oriW,
    QList<Monster*>* am, int* const wn)
{
    ReflectWave* rw = new ReflectWave(world, am, wn);
    rw->setStartPoint(startPoint);
    rw->setStartXita(_xita);
    rw->setMaxLen(maxLen);
    rw->setMaxDis(maxDis);
    rw->setMaxTime(maxTime);
    rw->setMaxCollideTimes(maxCollideTimes);
    rw->setParentItem(mapCanvas);
    rw->setIsAttactive(attractive);
    rw->setOriWidth(oriW);
    rw->createPointList();
}
void BaseScene::addLineCustomWave(const QPointF& startPoint, const double& _xita,
    const double& maxLen, const double& maxDis, const double& maxTime,
    const int& maxCollideTimes, const double& waveWidth, const QColor& waveColor,
    const double& stepLen)
{
    CustomWave* cw = new CustomWave(world);
    cw->setStartPoint(startPoint);
    cw->setStartXita(_xita);
    cw->setMaxLen(maxLen);
    cw->setMaxDis(maxDis);
    cw->setMaxTime(maxTime);
    cw->setMaxCollideTimes(maxCollideTimes);
    cw->setDefaultWidth(waveWidth);
    cw->setDefaultColor(waveColor);
    cw->setParentItem(mapCanvas);
    cw->setStepLen(stepLen);
    cw->createPointList();
}
void BaseScene::addCastWave(const QPointF& startPoint, const double& _xita,
    const double& maxLen, const double& maxDis, const int& maxTime)
{
    CastWave* cw = new CastWave(world);
    cw->setStartPoint(startPoint);
    cw->setStartXita(_xita);
    cw->setMaxLen(maxLen);
    cw->setMaxDis(maxDis);
    cw->setMaxTime(maxTime);
    cw->setParentItem(mapCanvas);
    cw->createPointList();
}
void BaseScene::addCircleReflectWave(const QPointF& startPoint, const int& waveNum,
    const double& maxLen, const double& maxDis, const double& maxTime,
    const int& maxCollideTimes, const bool& attractive, const int& oriW, const double& delta)
{
    double dXita = 2.0*M_PI / waveNum, xita = delta;
    int* wn = new int(waveNum);
    QList<Monster*>*am = new QList<Monster*>();
    for (int i = 0; i < waveNum; i++)
    {
        addLineReflectWave(startPoint, xita, maxLen, maxDis, maxTime,
            maxCollideTimes, attractive, oriW, am, wn);
        xita += dXita;
    }
}
void BaseScene::addCircleCustomWave(const QPointF& startPoint, const int& waveNum,
    const double& maxLen, const double& maxDis, const double& maxTime,
    const int& maxCollideTimes, const double& waveWidth, const QColor& waveColor,
    const double& stepLen, const double& delta)
{
    double dXita = 2.0*M_PI / waveNum, xita = delta;
    for (int i = 0; i < waveNum; i++)
    {
        addLineCustomWave(startPoint, xita, maxLen, maxDis, maxTime,
            maxCollideTimes, waveWidth, waveColor, stepLen);
        xita += dXita;
    }
}
