#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Canvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Canvas *mCanvas = new Canvas();

    this->setCentralWidget(mCanvas);
    this->setWindowTitle("Fuzzy Control Autonomous Mobile");
    this->setWindowIcon(QIcon(":/resources/automobi.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    // ignore keyPressEvent in parent widget
    e->ignore();
}
