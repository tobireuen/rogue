#ifndef MAP_H
#define MAP_H

#include "abstractmapitem.h"
#include "dungeon.h"
#include "player.h"
#include "constants.h"

#include <QAbstractTableModel>
#include <QList>

class MapModel : public QAbstractTableModel
{
    Q_OBJECT
    typedef QAbstractTableModel SUPER;

signals:
    void turnPassed();

public:
    explicit MapModel(int rowCount, int columnCount, QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool movePlayer(Direction direction);

public slots:
    void reset();
    void init(int rowCount, int columnCount);

protected:

    void collectObject(const QModelIndex &index);
    void setPlayer(const QModelIndex &start);

    QModelIndex currentPlayerIndex() const;

private slots:
    void onPlayerMoved(int oldRow, int row, int oldColumn, int column);
    void onObjectChanged(const QModelIndex &index);
    void onObjectAboutToMove(const QModelIndex &srcIndex, Direction direction);

private:
    Dungeon* m_dungeon;

    int m_rowCount = 0;
    int m_columnCount = 0;

};

#endif // MAP_H
