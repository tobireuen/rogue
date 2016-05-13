#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "abstractmapitem.h"

class Obstacle : public AbstractMapItem
{
    Q_OBJECT
public:
    Obstacle(QObject *parent = 0);

    virtual QChar appearance() const;
    virtual bool isPassable() const final;
    virtual bool isCollectible() const final;
};

#endif // OBSTACLE_H
