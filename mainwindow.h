#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MapSizeDialog;
class MapModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void reset();
    void init();

private:
    Ui::MainWindow *m_ui;

    MapSizeDialog *m_dialog;
    MapModel *m_model = 0;
};

#endif // MAINWINDOW_H
