#include "monster.h"

Monster::Monster(QObject *parent)
    : AbstractNPC(parent)
{
    QList<Direction> directions;
    directions << Up
               << Right
               << Down
               << Left;
    m_moveset.setDirectionList(directions);
}

QChar Monster::appearance() const
{
    return 'X';
}

void Monster::setHealth(int health)
{
    m_health = health;
    emit healthChanged(m_health);
}

bool Monster::isHostile() const
{
    return true;
}

bool Monster::isMovable() const
{
    return true;
}

