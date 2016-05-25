#ifndef ABSTRACTMAPTILE_H
#define ABSTRACTMAPTILE_H

#include <abstractmapitem.h>

class AbstractMapTile : public AbstractMapItem
{
    Q_OBJECT
    typedef AbstractMapItem SUPER;
public:
    AbstractMapTile(QObject * parent = 0);

    virtual bool onEntered() const = 0;
    bool isPassable() const;
    bool isCollectible() const;
};

#endif // ABSTRACTMAPTILE_H
