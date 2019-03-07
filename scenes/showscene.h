#ifndef SHOWSCENE_H
#define SHOWSCENE_H
#include"basescene.h"
class ShowScene :public BaseScene
{
public:
        ShowScene(const QRect& rect);
        enum { QT, RAC7 };
        enum { PNG_NUM = 2 };
        int curPng()const;
        void setCurPng(const int& pro);
private:
        QGraphicsPixmapItem* m_png[PNG_NUM];
        QPixmap m_qtPng;
        QPixmap m_rac7Png;
        int m_curPng;
        virtual void enterProgress();
        virtual void stayProgress();
        virtual void leaveProgress();
        virtual void createWorld();
};
#endif
