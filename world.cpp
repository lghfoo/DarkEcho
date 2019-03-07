#include"world.h"
#include"monster.h"
QColor World::colorArr[5] =
{ Qt::white,Qt::blue,Qt::red,
Qt::black,Qt::yellow };
QPoint World::mapPoint(const QPointF& p)
{
    return QPoint(((int)(p.x())) / 10,
        ((int)(p.y())) / 10);
}
World::World()
{
    m_area = new int*[AREA_WIDTH];
    for (int i = 0; i < AREA_WIDTH; i++)
    {
        m_area[i] = new int[AREA_HEIGHT];
        for (int j = 0; j < AREA_HEIGHT; j++)
        {
            m_area[i][j] = World::NIL;
        }
    }
}
void World::setWall(QList<Wall*>_wall)
{
    m_wall = _wall;
}

const QList<Wall*>& World::wall()const
{
    return m_wall;
}

int** World::area()const
{
    return m_area;
}

void World::setArea(QDataStream& in)
{
    for (int i = 0; i < AREA_WIDTH; i++)
    {
        for (int j = 0; j < AREA_HEIGHT; j++)
        {
            in >> m_area[i][j];
        }
    }
}

const QList<Monster*>& World::monster()const
{
    return m_monster;
}

void World::setMonster(QList<Monster*> _monster)
{
    m_monster = _monster;
}

void World::clear()
{
    while (!m_wall.isEmpty())
    {
        delete m_wall.last();
        m_wall.pop_back();
    }
    while (!m_monster.isEmpty())
    {
        m_monster.pop_back();
    }
}

World::~World()
{
    clear();
    for (int i = 0; i < AREA_WIDTH; i++)
    {
        delete[]m_area[i];
    }
    delete[]m_area;
}
