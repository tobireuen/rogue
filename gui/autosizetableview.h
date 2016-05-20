#ifndef AUTOSIZETABLEVIEW_H
#define AUTOSIZETABLEVIEW_H

#include <QTableView>

class AutoSizeTableView : public QTableView
{
    Q_OBJECT

    typedef QTableView SUPER;

public:
    explicit AutoSizeTableView(QWidget* parent = 0);

};

#endif // AUTOSIZETABLEVIEW_H
