#ifndef GAMESCENE_H
#define GAMESCENE_H
#include"basescene.h"
#include"../buttons/pixmapbutton.h"
#include"../buttons/textbutton.h"
#include"footprint.h"
class LevelScene;
class GameScene :public BaseScene
{
        Q_OBJECT
public:
        GameScene(const QRect& rect);
        ~GameScene();
        QPointF cenPos()const;
        QPointF cenPosInMap();
        void setLevel(const int& _level);
        void createFootprint();
        void setLevelScene(LevelScene* const l);
        void setTimer(QTimer* const _timer);
        private slots:
        void popupPauseDialog();
        void continueAction();
        void restartAction();
        void exitAction();
protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
        int m_level;
        QString levelName;
        Footprint* m_footprint;
        PixmapButton* m_pauseButton;
        TextButton* m_continueButton;
        TextButton* m_restartButton;
        TextButton* m_exitButton;
        QGraphicsTextItem* m_levelNumber;
        QGraphicsTextItem* m_levelName;
        LevelScene* levelScene;
        QTimer* m_timer;
        int m_walkCounter;
        int m_creepCounter;
        int m_standCounter;
        int m_runCounter;
        bool m_isPausing;
        bool m_exit;
        int m_footState;
        bool m_isWalking;
        bool m_isRunning;
        bool m_isStanding;
        int m_mousePressTime;
        int m_mouseRightPressTime;
        bool m_hasRightClicked;
        double m_xita;
        double m_creepDis;
        double m_walkDis;
    double m_runDis;
        bool m_hasClicked;
        bool m_standBeforeCreep;
        bool m_readyToStep;
        bool m_hasStood;
        int m_readyTime;
        bool m_enableMouseLater;
        bool m_connectLater;
        int m_areaType;
        bool m_markTime;

        void stand();
        void creep();
        void run();
        void walk();
        void win();
        void fail();
        bool check();
        void clearItem();
        void shiftFoot();
        void initialize();
        virtual void createWorld();
        virtual void stayProgress();
        virtual void enterProgress();
        virtual void leaveProgress();
        void computeXita(const QPointF& curPos);
        bool collide(const QPointF& p1, const QPointF& p2);
        void getDxDy(const double& dis, double& dx,
                double& dy);
};

#endif
