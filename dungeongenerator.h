#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "abstractmapitem.h"

#include <QAbstractItemModel>
#include <QObject>

class DungeonGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DungeonGenerator(QAbstractItemModel *model, QObject *parent = 0);

    QHash<QModelIndex, AbstractMapItem*> generateDungeon();

private:
    void createRandom(QHash<QModelIndex, AbstractMapItem*>& hash);

    QAbstractItemModel *m_model;

signals:

public slots:
};

#endif // DUNGEONGENERATOR_H
