#include "abstractcollectibleitem.h"

AbstractCollectibleItem::AbstractCollectibleItem(QObject *parent) : AbstractMapItem(parent)
{

}
bool AbstractCollectibleItem::isPassable() const
{
    return true;
}

bool AbstractCollectibleItem::isCollectible() const
{
    return true;
}

bool AbstractCollectibleItem::onEntered()
{
    return false;
}
