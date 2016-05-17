#ifndef MAP_H
#define MAP_H

#include "abstractmapitem.h"
#include "dungeon.h"
#include "player.h"

#include <QAbstractTableModel>
#include <QList>

class MapModel : public QAbstractTableModel
{
    Q_OBJECT
    typedef QAbstractTableModel SUPER;

public:
    explicit MapModel(int rowCount, int columnCount, QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    enum Direction {
        Left,
        Right,
        Up,
        Down
    };

    bool movePlayer(Direction direction);

public slots:
    void reset();
    void init(int rowCount, int columnCount);

protected:

    void collectObject(const QModelIndex &index);

    QModelIndex currentPlayerIndex() const;

private slots:
    void onPlayerMoved(int oldRow, int row, int oldColumn, int column);

private:
    Dungeon* m_dungeon;

    int m_rowCount = 0;
    int m_columnCount = 0;

};

#endif // MAP_H
