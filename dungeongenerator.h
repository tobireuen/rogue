#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "abstractmapitem.h"
#include "dungeon.h"

#include <QObject>
#include <QModelIndex>

class DungeonGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DungeonGenerator(QAbstractItemModel *model, QObject *parent = 0);

    Dungeon* generate();

private:
    void initialiseMap(double obstacleChance);
    void smoothOutDungeon();

    int countAliveNeighbours(const QModelIndex &index);

private:
    Dungeon *m_dungeon;
    QAbstractItemModel *m_model;
};

#endif // DUNGEONGENERATOR_H
