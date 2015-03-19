#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Canvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Canvas *mCanvas = new Canvas();

    setCentralWidget(mCanvas);
    setWindowTitle("Fuzzy AutoCar");
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
