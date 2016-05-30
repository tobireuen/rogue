#ifndef MOVESET_H
#define MOVESET_H

#include "constants.h"

#include <QObject>

/**
 * @brief The MoveSet class governs the movement behavious of an AbstractNPC
 */
class MoveSet : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief construct a MoveSet with given parent
     */
    explicit MoveSet(QObject *parent = 0);

    /**
     * @brief sets up a List with Directions
     * @param directions is a List containing all moves set in the List
     */
    void setDirectionList(QList<Direction> directions);

    /**
     * @return the current Direction the iterator is pointing at
     */
    Direction currentDirection() const;

    /**
     * @brief moves the iterator to the next item in the list
     */
    void nextDirection();

private:
    /**
     * @brief contains Directions
     */
    QList<Direction> m_directionList;

    /**
     * @brief iterates through Direction list
     */
    QList<Direction>::const_iterator m_iterator;
};

#endif // MOVESET_H
