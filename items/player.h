#ifndef PLAYER_H
#define PLAYER_H

#include "abstractcombatitem.h"

#include <QObject>

#define DEFAULT_GOLD_COUNT 0
#define DEFAULT_PLAYER_HEALTH 10
#define DEFAULT_PLAYER_ATTACKRATING 1

/**
 * @brief The Player class is singleton class which is derived from AbstractCombatItem and controlled by the user
 */
class Player : public AbstractCombatItem
{
    Q_OBJECT

signals:
    /**
     * @brief emits signal when Player moves
     * @param oldRow
     * @param newRow
     * @param oldColumn
     * @param newColumn
     */
    void moved(int oldRow, int newRow, int oldColumn, int newColumn);

    /**
     * @brief emits signal when Player row changes
     * @param row is the new row the player stands on
     */
    void rowChanged(int row);

    /**
     * @brief emits signal when Player column changes
     * @param column is the new cloumn the player stands on
     */
    void columnChanged(int column);

    /**
     * @brief emits signal when amount of gold the player holds changes
     * @param gold is the increment or decrement of gold by which the amount changes
     */
    void goldChanged(int gold);

public:

    /**
     * @brief since the Player class is considered to be a singleton instance() is needed
     * @return pointer on Player
     */
    static Player* instance();

    /**
     * @brief resets amount of gold the Player holds to default value
     */
    void reset();

    /**
     * @return row the Player is located at
     */
    int row() const;

    /**
     * @return column the Player is located at
     */
    int column() const;

    /**
     * @brief sets new row for Player
     * @param row is new row Player will be set on
     */
    void setRow(int row);

    /**
     * @brief sets new column for Player
     * @param row is new column Player will be set on
     */
    void setColumn(int column);

    /**
     * @return amount of gold the Player holds
     */
    int goldCount() const;

    /**
     * @brief add Gold to Player inventory
     * @param gold is increment of added gold
     */
    void addGold(int gold);

protected:
    explicit Player(QObject *parent = 0);

    /**
     * @brief sets amount of gold the Player holds
     * @param goldCount is amount of gold to be set
     */
    void setGoldCount(int goldCount);

private:
    /**
     * @brief s_instance is a pointer representing the Player as a singleton
     */
    static Player* s_instance;

    int m_row = 0;
    int m_column = 0;
    int m_goldCount = DEFAULT_GOLD_COUNT;

    // AbstractMapItem interface
public:
    /**
     * @brief defines appearance of Player on map
     * @return char representing Player
     */
    QChar appearance() const;

    /**
     * @brief checks if Player is passable
     * @return true if passable, else returns false. Always false, since Player is never passable
     */
    bool isPassable() const;

    /**
     * @brief checks if Player is collectible
     * @return true if collectible, else returns false. Always false, since Player is never collectible
    */
    bool isCollectible() const;
};

#endif // PLAYER_H
