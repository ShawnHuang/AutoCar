#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>

#include "AutoMobiController.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),   // initialization list
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView( scene, this)),
    controller(new AutoMobiController( *scene, this))
{
  this->setWindowTitle("Fuzzy Control Autonomous Mobile");
  this->setWindowIcon(QIcon(":/resources/automobi.ico"));
  this->setCentralWidget(view);
  this->resize(600,600);
  
  scene->setSceneRect( -10, -10, 55, 55);


  QTimer::singleShot( 0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::adjustViewSize()
{
  view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
  //view->scale(1, -1);
}
