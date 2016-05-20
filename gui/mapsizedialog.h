#ifndef MAPSIZEDIALOG_H
#define MAPSIZEDIALOG_H

#include <QDialog>

namespace Ui {
class MapSizeDialog;
}

class MapSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapSizeDialog(QWidget *parent = 0);
    ~MapSizeDialog();

    int rowCount() const;
    int columnCount() const;
    int obstacleCount() const;

private slots:
    void changeObstacleMax();
    void randomize();

private:
    Ui::MapSizeDialog *m_ui;
};

#endif // MAPSIZEDIALOG_H
