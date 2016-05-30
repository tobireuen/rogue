#ifndef FLOORTILE_H
#define FLOORTILE_H

#include "abstractmaptile.h"

/**
 * @brief The FloorTile class is a derivative of AbstractMapTile
 */
class FloorTile : public AbstractMapTile
{
    Q_OBJECT
    typedef AbstractMapTile SUPER;
public:
    /**
     * @brief constructs a FloorTile with given parent
     */
    FloorTile(QObject *parent = 0);

public:
    /**
     * @brief defines appearance of a floortile on map
     * @return char representing a floortile
     */
    QChar appearance() const final;

    /**
     * @brief when entered by player adds gold to player inventory
     * @return true if entered, else returns false
     */
    bool onEntered() const;
};

#endif // FLOORTILE_H
