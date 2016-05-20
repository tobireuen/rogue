#include "obstacle.h"

Obstacle::Obstacle(QObject *parent) : AbstractMapItem(parent)
{

}

QChar Obstacle::appearance() const
{
    return '#';
}

bool Obstacle::isPassable() const
{
    return false;
}

bool Obstacle::isCollectible() const
{
    return false;
}
