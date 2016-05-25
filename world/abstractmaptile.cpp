#include "abstractmaptile.h"

AbstractMapTile::AbstractMapTile(QObject *parent) : SUPER(parent)
{

}



bool AbstractMapTile::isPassable() const
{
    return true;
}


bool AbstractMapTile::isCollectible() const
{
    return false;
}
