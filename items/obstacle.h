#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "abstractmapitem.h"

class Obstacle : public AbstractMapItem
{
    Q_OBJECT
public:
    /**
     * @brief constructs an Obstacle with given parent
     */
    Obstacle(QObject *parent = 0);

    /**
     * @brief checks if Obstacle is passable
     * @return true if passable, else returns false. Always false, since Obstacles are never passable
     */
    virtual bool isPassable() const final;

    /**
     * @brief checks if Obstacle is collectible
     * @return true if collectible, else returns false. Always false, since Obstacles are never collectible
     */
    virtual bool isCollectible() const final;

    /**
     * @brief defines appearance of obstacle on map
     * @return char representing obstacle
     */
    virtual QChar appearance() const;
};

#endif // OBSTACLE_H
