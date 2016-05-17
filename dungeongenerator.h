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
    void smoothOutDungeon(int birthlimit, int deathlimit);
    void createBorders();
    void tweakDungeon(int birthlimit, int deathlimit, int steps);
    void placeTreasure(int hiddenTreasureLimit);

    int countAliveNeighbours(const QModelIndex &index);

private:
    Dungeon *m_dungeon;
    QAbstractItemModel *m_model;
};

#endif // DUNGEONGENERATOR_H
