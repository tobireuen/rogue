#ifndef DUNGEON_H
#define DUNGEON_H

#include "abstractmapitem.h"
#include "abstractnpc.h"

#include <QObject>
#include <QModelIndex>
#include <QHash>

class Dungeon : public QObject
{
    Q_OBJECT

signals:
    void objectRemoved(const QModelIndex &index);
    void objectAdded(const QModelIndex &index);
    void objectAboutToMove(const QModelIndex &srcIndex, Direction direction);

public:
    explicit Dungeon(QObject *parent = 0);

    void reset();

    AbstractMapItem* getObjectAtIndex(const QModelIndex &index);

    bool containsObjectAtIndex(const QModelIndex &index);

    void createObjectAtIndex(const QModelIndex &index, AbstractMapItem *itemType);
    void moveObject(const QModelIndex &srcIndex, const QModelIndex &destinationIndex);
    void removeObjectAtIndex(const QModelIndex &index);

private slots:
    void moveNPCs();

private:
    QHash<QModelIndex, AbstractMapItem*> m_objects;

};

#endif // DUNGEON_H
