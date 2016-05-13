#include "mapview.h"
#include "mapmodel.h"

#include <QHeaderView>
#include <QKeyEvent>

MapView::MapView(QWidget *parent)
    : SUPER(parent)
{
}

void MapView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() != Qt::Key_W && event->key() != Qt::Key_A
            && event->key() != Qt::Key_S && event->key() != Qt::Key_D)
        QTableView::keyPressEvent(event);

    MapModel* mapModel = qobject_cast<MapModel*>(model());
    if(!mapModel)
        QTableView::keyPressEvent(event);

    switch (event->key()) {
    case Qt::Key_W:
        mapModel->movePlayer(MapModel::Up);
        break;
    case Qt::Key_S:
        mapModel->movePlayer(MapModel::Down);
        break;
    case Qt::Key_A:
        mapModel->movePlayer(MapModel::Left);
        break;
    case Qt::Key_D:
        mapModel->movePlayer(MapModel::Right);
        break;
    default:
        break;
    }
}

void MapView::calculateSize()
{
    int width = horizontalOffset();
    for(int column = 0; column < this->model()->columnCount(); ++column)
        width += columnWidth(column);

    int height = verticalOffset();
    for(int row = 0; row < this->model()->rowCount(); ++row)
        height += rowHeight(row);

    this->resize(width, height);
}
