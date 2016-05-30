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
    /**
     * @brief Constructs a MainWindow with the given parent.
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief Destroys the main window.
     */
    ~MainWindow();

private slots:
    /**
     * @brief resets and re-initializes the player and model.
     */
    void reset();

    /**
     * @brief sets up tableView and model
     */
    void init();

private:
    Ui::MainWindow *m_ui;

    MapSizeDialog *m_dialog;
    MapModel *m_model = 0;
};

#endif // MAINWINDOW_H
