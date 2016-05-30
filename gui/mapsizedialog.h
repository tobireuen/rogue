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
    /**
     * @brief Constructs a MapSizeDialog window with the given parent.
     */
    explicit MapSizeDialog(QWidget *parent = 0);

    /**
     * @brief Destroys MapSizeDialog
     */
    ~MapSizeDialog();

    /**
     * @brief counts rows entered in respective spinbox
     * @return integer with amount of entered rows
     */
    int rowCount() const;

    /**
     * @brief counts columns entered in respective spinbox
     * @return integer with amount of entered columns
     */
    int columnCount() const;

    /**
     * @brief counts obstacles entered in respective spinbox
     * @return integer with amount of entered obstacles
     */
    int obstacleCount() const;

private slots:
    /**
     * @brief recalculates maximum amount of obstacles that can be entered
     */
    void changeObstacleMax();

    /**
     * @brief randomizes amounts in spinboxes for rows, columns and obstacles within respective limits.
     */
    void randomize();

private:
    Ui::MapSizeDialog *m_ui;
};

#endif // MAPSIZEDIALOG_H
