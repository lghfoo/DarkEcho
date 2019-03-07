#ifndef CHOICESCENE_H
#define CHOICESCENE_H
#include"basescene.h"
#include"../buttons/textbutton.h"
class ChoiceScene :public BaseScene
{
        Q_OBJECT
public:
        ChoiceScene(const QRect& rect, QGraphicsView* view);
        ~ChoiceScene();
        public slots:
        void pressPlay();
private:
        virtual void enterProgress();
        virtual void leaveProgress();
        virtual void stayProgress();
        virtual void createWorld();
        TextButton* playButton;
        int counter;
};

#endif
