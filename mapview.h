#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QTableView>

class MapView : public QTableView
{

    typedef QTableView SUPER;

public:
    MapView(QWidget * parent = 0);

protected:
    void keyPressEvent(QKeyEvent * event);

private:
    void calculateSize();
};

#endif // MAPVIEW_H
