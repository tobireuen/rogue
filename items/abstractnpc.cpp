#include "abstractnpc.h"

AbstractNPC::AbstractNPC(QObject *parent) : SUPER(parent)
{
}

bool AbstractNPC::isPassable() const
{
    return false;
}

bool AbstractNPC::isCollectible() const
{
    return false;
}

Direction AbstractNPC::nextDirection()
{
    return m_moveset.currentDirection();
}

void AbstractNPC::onMoved()
{
    m_moveset.nextDirection();
}
