#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "abstractmapitem.h"
#include "dungeon.h"
#include "constants.h"

#include <QObject>
#include <QModelIndex>

#define DEFAULT_CORRIDOR_MIN_LENGTH 3
#define DEFAULT_CORRIDOR_MAX_LENGTH 5


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
    QModelIndex createRoom(QPair<QModelIndex, Direction> startingPoint, int heigth, int width);

    //returns index of end of corridor
    QModelIndex createCorridor(QPair<QModelIndex, Direction> startingPoint, int length);

    //returns QPair with index of wall and direction wall is facing
    QPair<QModelIndex, Direction> selectWall(const QModelIndex &startIndex, Direction direction);

    //returns true if free tiles are found in desired area
    bool checkForRoomSpace(QPair<QModelIndex, Direction> checkCoordinates, int height, int width);
    //returns true if free tiles are found in desired area
    bool checkForCorridorSpace(QPair<QModelIndex, Direction> checkCoordinates, int length);
    //returns true if index is at or beyond border
    bool indexAtBorder(const QModelIndex &checkIndex);
    double checkObstacleDensity();


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
