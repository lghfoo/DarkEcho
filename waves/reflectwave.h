#ifndef REFLECTWAVE_H
#define REFLECTWAVE_H
#include"normalwave.h"
class Monster;
class ReflectWave :public NormalWave
{
public:
        ReflectWave(World* const _world, QList<Monster*>* am,
                int* const _waveNum);
        ~ReflectWave();
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
        void advance(int phase);
        void createPointList();
        void setIsAttactive(const bool& a);
        void setOriWidth(const int& w);
private:
        QList<QColor>pointColorList;
        QList<QColor>turnColorList;
        QList<Monster*>*attractiveMonster;
        int* waveNum;

        bool isAbsorbed;
        void changeColor(const QColor& _color);
        void checkAbsorbe();
        bool isAttractive;
        int oriWidth;
};
#endif
