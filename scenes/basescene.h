#ifndef BASESCENE_H
#define BASESCENE_H
#include"../allheader.h"
#include"../canvas.h"
#include"../waves/castwave.h"
#include"../waves/reflectwave.h"
#include"../waves/customwave.h"
class BaseScene :public QGraphicsScene
{
    Q_OBJECT
        Q_PROPERTY(double foreOpa READ foreOpa WRITE setForeOpa)
public:
    BaseScene(const QRect& rect);
    void enter(const bool& _isEntering, const bool& forward = true);
    void stay(const bool& _isStaying);
    void leave(const bool& _isLeaving);
    bool forwardEnter()const;
    const QPropertyAnimation& opaAni()const;
    void disappear(const int& dur = 1000);
    void appear(const int& dur = 1000,
        const QColor& oriCol = Qt::white);
    QPointF cursorPos();
    double foreOpa()const;
    int nextScene()const;
    bool start()const;
    void setStart(const bool& _start);
    void setForeOpa(const double& _foreOpa);
    void setNextScene(const int& _nextScene);
    void addLineReflectWave(const QPointF& startPoint, const double& _xita,
        const double& maxLen, const double& maxDis, const double& maxTime,
        const int& maxCollideTimes, const bool& attractive, const int& oriW,
        QList<Monster*>* am, int* const wn);
    void addLineCustomWave(const QPointF& startPoint, const double& _xita,
        const double& maxLen, const double& maxDis, const double& maxTime,
        const int& maxCollideTimes, const double& waveWidth, const QColor& waveColor,
        const double& stepLen);
    void addCastWave(const QPointF& startPoint, const double& _xita,
        const double& maxLen, const double& maxDis, const int& maxTime);
    void addCircleReflectWave(const QPointF& startPoint, const int& waveNum,
        const double& maxLen, const double& maxDis, const double& maxTime,
        const int& maxCollideTimes, const bool& attractive, const int& oriW,
        const double& delta = 0.0);
    void addCircleCustomWave(const QPointF& startPoint, const int& waveNum,
        const double& maxLen, const double& maxDis, const double& maxTime,
        const int& maxCollideTimes, const double& waveWidth, const QColor& waveColor,
        const double& stepLen, const double& delta=0.0);
    ~BaseScene();
    public slots:
    void progress();
protected:
    Canvas* m_baseCanvas;
    Canvas* mapCanvas;
    World* world;
private:
    virtual void enterProgress() = 0;
    virtual void leaveProgress() = 0;
    virtual void stayProgress() = 0;
    int m_nextScene;
    bool m_isEntering;
    bool m_isStaying;
    bool m_isLeaving;
    bool m_forwardEnter;
    double m_foreOpa;
    QPropertyAnimation* m_opaAni;
    bool m_start;
    virtual void createWorld() = 0;
signals:
    void sceneEnd(const int& nextSceneId,const bool& forward);
};

#endif
