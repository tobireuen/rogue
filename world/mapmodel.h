#ifndef MAP_H
#define MAP_H

#include "abstractmapitem.h"
#include "dungeon.h"
#include "player.h"
#include "constants.h"

#include <QAbstractTableModel>
#include <QList>

/**
 * @brief The MapModel class manages all the data regarding object placement and behaviour
 */
class MapModel : public QAbstractTableModel
{
    Q_OBJECT
    typedef QAbstractTableModel SUPER;

signals:
    /**
     * @brief emits a signal if a turn has passed
     */
    void turnPassed();

public:
    /**
     * @brief constructs a MapModel with given parent
     * @param rowCount is amount of rows
     * @param columnCount is amount of columns
     */
    explicit MapModel(int rowCount, int columnCount, QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /**
     * @brief moves the player depending on the entered key with checking if the move is valid
     * @param direction in which the player will move
     * @return true if it is a valid move
     */
    bool movePlayer(Direction direction);

public slots:
    /**
     * @brief calls reset on the dungeon
     */
    void reset();

    /**
     * @brief initializes the model with desired size and generates a dungeon
     * @param rowCount
     * @param columnCount
     */
    void init(int rowCount, int columnCount);

protected:
    /**
     * @brief let's the player collect a collectible object at a specific index
     * @param index at which to be collected object is located
     */
    void collectObject(const QModelIndex &index);

    /**
     * @brief sets the Player at a starting position
     * @param start is the starting index
     */
    void setPlayer(const QModelIndex &start);

    /**
     * @return the current index at which the player is located
     */
    QModelIndex currentPlayerIndex() const;

private slots:
    /**
     * @brief calls dataChanged with new Player coordinates
     * @param oldRow
     * @param row
     * @param oldColumn
     * @param column
     */
    void onPlayerMoved(int oldRow, int row, int oldColumn, int column);

    /**
     * @brief calls dataChanged
     * @param index at which the object changed
     */
    void onObjectChanged(const QModelIndex &index);

    /**
     * @brief moves object from original index in desired direction
     * @param srcIndex is original index
     * @param direction
     */
    void onObjectAboutToMove(const QModelIndex &srcIndex, Direction direction);

private:
    /**
     * @brief m_dungeon contains a dungeon
     */
    Dungeon* m_dungeon;

    int m_rowCount = 0;
    int m_columnCount = 0;

};

#endif // MAP_H
