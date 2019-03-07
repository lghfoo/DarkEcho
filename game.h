#ifndef GAME_H
#define GAME_H
#include"./scenes/showscene.h"
#include"./scenes/choicescene.h"
#include"./scenes/levelscene.h"
#include"./scenes/gamescene.h"
class Game:public QObject
{
    Q_OBJECT
public:
    Game();
    void run();
    ~Game();
    const QTimer& timer()const;
    enum { SHOW_SCENE, CHOICE_SCENE, LEVEL_SCENE, GAME_SCENE, NIL };
    enum { SCENE_NUM = 4};
    static bool mouseIsEnabled();
    static void enableMouse(const bool& _enable);
    static int adjust();
    static int chosenLevel();
    static void setChosenLevel(const int& _level);
    void setCurSce(const int& curSce);
    int curScene()const;
    int readCurLevel();
    public slots:
    void toScene(const int& sceneName, const bool& forward);
private:
    static bool s_mouseIsEnabled;
    static int s_adjust;
    static int s_chosenLevel;
    QGraphicsView* m_view;
    QTimer* m_timer;
    QGraphicsScene* m_scene[SCENE_NUM];
    int m_curScene;
};

#endif
