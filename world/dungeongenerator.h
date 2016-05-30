#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "abstractmapitem.h"
#include "dungeon.h"
#include "constants.h"

#include <QObject>
#include <QModelIndex>

#define DEFAULT_CORRIDOR_MIN_LENGTH 3
#define DEFAULT_CORRIDOR_MAX_LENGTH 5

/**
 * @brief The DungeonGenerator class is responsible for generating and populating a dungeon
 */
class DungeonGenerator : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief constructs a DungeonGenerator with given parent
     * @param model is necessary for index operations
     */
    explicit DungeonGenerator(QAbstractItemModel *model, QObject *parent = 0);

    /**
     * @brief generate dungeon with caves
     * @return Dungeon with caves
     */
    Dungeon* generateCaves();

    /**
     * @brief generate dungeon with Rooms
     * @return Dungeon with rooms and corridors
     */
    Dungeon* generateRooms();

private:
    //Caves
    /**
     * @brief fills the map with obstacles randomly
     * @param obstacleChance is probality for obstacles to be created
     */
    void initialiseMap(double obstacleChance);

    /**
     * @brief smooths out dungeon with cellular automaton
     * @param deathlimit is threshold for obstacles to be created if index contains obstacle
     * @param deathlimit is threshold for obstacles to be created if index contains no obstacle
     */
    void smoothOutDungeon(int birthlimit, int deathlimit);

    /**
     * @brief calls smoothOutDungeon multiple times
     * @param birthlimit
     * @param deathlimit
     * @param steps is number of iterations
     */
    void tweakDungeon(int birthlimit, int deathlimit, int steps);

    /**
     * @brief counts obstacles around specific index
     * @param index
     * @return number of obstacles around specific index
     */
    int countAliveNeighbours(const QModelIndex &index);

    //Rooms
    /**
     * @brief fills the map with obstacles
     */
    void fillMap();

    /**
     * @brief creates Room at specific index with given dimensions
     * @param startingPoint is pair of index and Direction in which room will be created
     * @param heigth
     * @param width
     * @return index after creation
     */
    QModelIndex createRoom(QPair<QModelIndex, Direction> startingPoint, int heigth, int width);

    //returns index of end of corridor
    /**
     * @brief creates corridor from specific index with given length
     * @param startingPoint is pair of index and Direction in which corridor will be created
     * @param length
     * @return index after creation
     */
    QModelIndex createCorridor(QPair<QModelIndex, Direction> startingPoint, int length);

    //returns QPair with index of wall and direction wall is facing
    /**
     * @brief selects first index, that is a wall in given direction
     * @param startingPoint is pair of index and Direction in which wall is facing
     * @param direction
     * @return pair of Index and Direction
     */
    QPair<QModelIndex, Direction> selectWall(const QModelIndex &startIndex, Direction direction);

    //
    /**
     * @brief checks for free space within given dimensions
     * @param checkCoordinates is Pair of starting index and direction in which prospective room is facing
     * @param height of prospective room
     * @param width of prospective room
     * @return true if free tiles are found in desired area
     */
    bool checkForRoomSpace(QPair<QModelIndex, Direction> checkCoordinates, int height, int width);

    /**
     * @brief checks for free space within given dimensions
     * @param checkCoordinates is Pair of starting index and direction in which prospective corridor is facing
     * @param length of prospective corridor
     * @return true if free tiles are found in desired area
     */
    bool checkForCorridorSpace(QPair<QModelIndex, Direction> checkCoordinates, int length);

    /**
     * @brief checks if a specific index is at or beyond model boundaries
     * @param checkIndex is index to be checked
     * @return true if index is at or beyond border
     */
    bool indexAtBorder(const QModelIndex &checkIndex);

    /**
     * @return calculates ratio of obstacles to total space
     */
    double checkObstacleDensity();

    /**
     * @brief create borders around map
     */
    void createBorders();

    /**
     * @brief randomly places treasure next to 5 or more obstacles
     * @param hiddenTreasureLimit is number of neighbours obstacles need to have
     */
    void placeTreasure(int hiddenTreasureLimit);

    /**
     * @brief randomly places monsters on the map
     * @param monsterLimit is number of monsters created
     */
    void placeMonster(int monsterLimit);

private:
    Dungeon *m_dungeon;
    QAbstractItemModel *m_model;

};

#endif // DUNGEONGENERATOR_H
