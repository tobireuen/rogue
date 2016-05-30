#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QTableView>

class MapView : public QTableView
{

    typedef QTableView SUPER;

public:
    /**
     * @brief Constructs a MapView with the given parent
     */
    MapView(QWidget * parent = 0);

protected:
    /**
     * @brief checks for entered key required for player movement
     * @param entered key
     */
    void keyPressEvent(QKeyEvent * event);

private:
    /**
     * @brief calculates size of model
     */
    void calculateSize();
};

#endif // MAPVIEW_H
