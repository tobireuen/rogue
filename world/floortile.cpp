#include "floortile.h"

FloorTile::FloorTile(QObject *parent) : SUPER(parent)
{

}

QChar FloorTile::appearance() const
{
    return '_';
}

bool FloorTile::onEntered() const
{
    return true;
}
