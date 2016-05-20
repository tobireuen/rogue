#ifndef ABSTRACTCOLLECTIBLEITEM_H
#define ABSTRACTCOLLECTIBLEITEM_H

#include "abstractmapitem.h"

class AbstractCollectibleItem : public AbstractMapItem
{
    Q_OBJECT
    typedef AbstractMapItem SUPER;

public:
    AbstractCollectibleItem(QObject * parent = 0);

    virtual bool isPassable() const final;
    virtual bool isCollectible() const final;
    virtual bool onEntered();
};

#endif // ABSTRACTCOLLECTIBLEITEM_H
