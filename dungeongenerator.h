#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "abstractmapitem.h"
#include "dungeon.h"
#include "constants.h"

#include <QObject>
#include <QModelIndex>

class DungeonGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DungeonGenerator(QAbstractItemModel *model, QObject *parent = 0);

    Dungeon* generateCaves();
    Dungeon* generateRooms();

private:
    //Caves
    void initialiseMap(double obstacleChance);
    void smoothOutDungeon(int birthlimit, int deathlimit);
    void tweakDungeon(int birthlimit, int deathlimit, int steps);
    int countAliveNeighbours(const QModelIndex &index);

    //Rooms
    void fillMap();
    void createRoom(const QModelIndex &start, int width, int height);

    void createBorders();
    void placeTreasure(int hiddenTreasureLimit);
    void placeMonster(int monsterLimit);

    //floodfill algorithm
    void floodfill();
    void colorIndex(QHash<QModelIndex, bool> &hash, const QModelIndex &index);

private:
    Dungeon *m_dungeon;
    QAbstractItemModel *m_model;
};

#endif // DUNGEONGENERATOR_H
