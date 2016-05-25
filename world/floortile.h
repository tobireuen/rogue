#ifndef FLOORTILE_H
#define FLOORTILE_H

#include "abstractmaptile.h"

class FloorTile : public AbstractMapTile
{
    Q_OBJECT
    typedef AbstractMapTile SUPER;
public:
    FloorTile(QObject *parent = 0);

    // AbstractMapItem interface
public:
    QChar appearance() const final;
    bool onEntered() const;
};

#endif // FLOORTILE_H
