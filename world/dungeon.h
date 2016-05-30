#ifndef DUNGEON_H
#define DUNGEON_H

#include "abstractmapitem.h"
#include "abstractnpc.h"

#include <QObject>
#include <QModelIndex>
#include <QHash>

/**
 * @brief The Dungeon class provides the model with all necessary information regarding object placement
 */
class Dungeon : public QObject
{
    Q_OBJECT

signals:
    /**
     * @brief emits a signal when an object is removed from the Dungeon
     * @param affected index
     */
    void objectRemoved(const QModelIndex &index);

    /**
     * @brief emits a signal when an object is added to the Dungeon
     * @param affected index
     */
    void objectAdded(const QModelIndex &index);

    /**
     * @brief emits a signal when an object is about to move
     * @param index object is located at and Direction in which to move
     */
    void objectAboutToMove(const QModelIndex &srcIndex, Direction direction);

public:
    /**
     * @brief constructs a Dungeon with given parent
     */
    explicit Dungeon(QObject *parent = 0);

    /**
     * @brief removes all entries from the objects hash
     */
    void reset();

    /**
     * @param index to be checked
     * @return AbstractMapItem at given Index
     */
    AbstractMapItem* getObjectAtIndex(const QModelIndex &index) const;

    /**
     * @brief checks if an object is located at a specific index
     * @param index to be checked
     * @return true if index contains an object, else return false
     */
    bool containsObjectAtIndex(const QModelIndex &index);

    /**
     * @brief creates an AbstractMapItem at a specific index and calls objectAdded
     * @param index at which object is created
     * @param itemType of object to create
     */
    void createObjectAtIndex(const QModelIndex &index, AbstractMapItem *itemType);

    /**
     * @brief moves Object from one index to another and calls objectAboutToMove();
     * @param srcIndex is original index
     * @param destinationIndex is new index
     */
    void moveObject(const QModelIndex &srcIndex, const QModelIndex &destinationIndex);

    /**
     * @brief removes an object from a specific index and calls objectRemoved
     * @param index at which object will be removed
     */
    void removeObjectAtIndex(const QModelIndex &index);
    /**
     * @brief checks if an object at an index is an obstacle
     * @param index to be checked
     * @return true if object at index is a wall
     */
    bool isWall(const QModelIndex& index) const;

    bool isFloor(const QModelIndex &index) const;
public slots:
    /**
     * @brief calls moveNPCs
     */
    void onTurnPassed();

private slots:
    /**
     * @brief iterates through objects hash and moves all movable NPCs
     */
    void moveNPCs();

private:
    /**
     * @brief m_objects contains a derivative of an abstractMapItem at a given modelIndex
     */
    QHash<QModelIndex, AbstractMapItem*> m_objects;

};

#endif // DUNGEON_H
