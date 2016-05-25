#include "dungeon.h"
#include "player.h"

#include <obstacle.h>

Dungeon::Dungeon(QObject *parent) : QObject(parent)
{
}

void Dungeon::reset()
{
    foreach (const QModelIndex &index, m_objects.keys())
        removeObjectAtIndex(index);

}

AbstractMapItem *Dungeon::getObjectAtIndex(const QModelIndex &index) const
{
    return m_objects.value(index, 0);
}

bool Dungeon::containsObjectAtIndex(const QModelIndex &index)
{
    if(getObjectAtIndex(index) == 0)
        return false;
    else
        return true;
}

void Dungeon::createObjectAtIndex(const QModelIndex &index, AbstractMapItem *itemType)
{
    if(!index.isValid())
        return;

    m_objects.insert(index, itemType);
    emit objectAdded(index);
}

void Dungeon::moveObject(const QModelIndex &srcIndex, const QModelIndex &destinationIndex)
{
    AbstractMapItem* object = m_objects.take(srcIndex);
    m_objects.insert(destinationIndex, object);

    emit objectRemoved(srcIndex);
    emit objectAdded(destinationIndex);

    AbstractNPC* npc = qobject_cast<AbstractNPC*>(object);
    if(!npc)
        return;

    npc->onMoved();
}

void Dungeon::removeObjectAtIndex(const QModelIndex &index)
{
    delete m_objects.take(index);
    emit objectRemoved(index);
}

bool Dungeon::isWall(const QModelIndex &index) const
{
    AbstractMapItem* item = getObjectAtIndex(index);
    return qobject_cast<Obstacle*>(item);
}

void Dungeon::onTurnPassed()
{
    moveNPCs();
}

void Dungeon::moveNPCs()
{
    for(AbstractMapItem* item : m_objects.values()){
        AbstractNPC* npc = qobject_cast<AbstractNPC*>(item);
        if(!npc)
            continue;
        QModelIndex index = m_objects.key(npc);
        emit objectAboutToMove(index, npc->nextDirection());
    }
}
