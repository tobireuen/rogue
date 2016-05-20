#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapmodel.h"
#include "mapsizedialog.h"
#include "playerlog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_dialog(new MapSizeDialog(this))
{
    m_ui->setupUi(this);

    init();

    connect(m_ui->actionExit, &QAction::triggered, qApp, &QApplication::quit);
    connect(m_ui->actionReset, &QAction::triggered, this, &MainWindow::reset);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::reset()
{
    hide();

    Player::instance()->reset();

    m_model->reset();

    if (m_dialog->exec() == QDialog::Accepted) {
        m_model->init(m_dialog->rowCount(), m_dialog->columnCount());
    }

    show();
}

void MainWindow::init()
{
    m_ui->tableViewMap->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_ui->tableViewMap->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    if (m_dialog->exec() == QDialog::Accepted) {

        if(m_model)
            delete m_model;

        m_model = new MapModel(m_dialog->rowCount(), m_dialog->columnCount(), this);
        m_ui->tableViewMap->setModel(m_model);
    }

}


