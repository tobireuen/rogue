#ifndef ABSTRACTCOLLECTIBLEITEM_H
#define ABSTRACTCOLLECTIBLEITEM_H

#include "abstractmaptile.h"

class AbstractCollectibleItem : public AbstractMapTile
{
    Q_OBJECT
    typedef AbstractMapTile SUPER;

public:
    AbstractCollectibleItem(QObject * parent = 0);

    virtual bool isPassable() const final;
    virtual bool isCollectible() const final;
    virtual bool onEntered() const = 0;
};

#endif // ABSTRACTCOLLECTIBLEITEM_H
