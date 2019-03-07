#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include"basescene.h"
#include"../buttons/levelbutton.h"
#include"../buttons/buttonline.h"
class LevelScene :public BaseScene
{
        Q_OBJECT
public:
        LevelScene(const QRect& rect,const int& _curLevel);
        enum { LEVEL_NUM = 17 };
        static const QString romanNumber[LEVEL_NUM + 1];
        static const QString levelName[LEVEL_NUM + 1];
        void setCurLevel(const int& _curLevel);
        int curLevel()const;
        int levelNum()const;
        bool isLocked(const int& _level);
        void unlockLevel(const int& _level);
        public slots:
        void toGameScene(const int& _level);
private:
        virtual void enterProgress();
        virtual void leaveProgress();
        virtual void stayProgress();
        void createAndPlaceButton();
        virtual void createWorld();
        LevelButton* m_levelButton[LEVEL_NUM];
        ButtonLine* m_buttonLine[LEVEL_NUM - 1];
        int m_curLevel;
        int m_levelNum;
};

#endif
