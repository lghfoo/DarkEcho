#ifndef WORLD_H
#define WORLD_H
#include"allheader.h"
#include"./walls/linewall.h"
#include"./walls/bezierwall.h"
class Monster;
class World
{
public:
    World();
    ~World();
    enum { AREA_WIDTH = 600, AREA_HEIGHT = 300 };
    enum { NIL, WATER, TRAP, WAYOUT, TRIGGER };
    static QColor colorArr[5];
    static QPoint mapPoint(const QPointF& p);
    const QList<Wall*>& wall()const;
    const QList<Monster*>& monster()const;
    int** area()const;
    void clear();
    void setWall(QList<Wall*>_wall);
    void setMonster(QList<Monster*> _monster);
    void setArea(QDataStream& in);
private:
    QList<Wall*>m_wall;
    QList<Monster*>m_monster;
    int** m_area;
};

#endif
