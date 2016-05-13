#include "mapsizedialog.h"
#include "ui_mapsizedialog.h"
#include "randomizer.h"

MapSizeDialog::MapSizeDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::MapSizeDialog)
{
    m_ui->setupUi(this);
    connect(m_ui->spinBoxRow, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapSizeDialog::changeObstacleMax);
    connect(m_ui->spinBoxColumn, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MapSizeDialog::changeObstacleMax);
    connect(m_ui->pushButtonRandomize, &QPushButton::clicked,
            this, &MapSizeDialog::randomize);
}


MapSizeDialog::~MapSizeDialog()
{
    delete m_ui;
}

int MapSizeDialog::rowCount() const
{
    return  m_ui->spinBoxRow->value();
}

int MapSizeDialog::columnCount() const
{
    return  m_ui->spinBoxColumn->value();
}

int MapSizeDialog::obstacleCount() const
{
    return m_ui->spinBoxObstacles->value();
}

void MapSizeDialog::changeObstacleMax()
{
    int maxObstacleCount = (rowCount() * columnCount()) / 2;
    m_ui->spinBoxObstacles->setMaximum(maxObstacleCount);
}

void MapSizeDialog::randomize()
{
    Randomizer rd;
    m_ui->spinBoxRow->setValue(
                rd.randInt(m_ui->spinBoxRow->minimum(), m_ui->spinBoxRow->maximum()));
    m_ui->spinBoxColumn->setValue(
                rd.randInt(m_ui->spinBoxColumn->minimum(), m_ui->spinBoxColumn->maximum()));
    m_ui->spinBoxObstacles->setValue(
                rd.randInt(m_ui->spinBoxObstacles->minimum(), m_ui->spinBoxObstacles->maximum()));

}
