#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <iostream>

#include "AutoMobiController.h"
#include "Car.h"
#include "Wall.h"

AutoMobiController::AutoMobiController( QGraphicsScene &scene, QObject *parent)
  : QObject(parent),
    scene(scene),
    x(0),
    y(0)
{ 
  timer.start( 1000/33 ); 
  wall = new Wall();
  car = new Car(*this, QPointF(x,y+6));
  car->setTarget(wall);
  scene.addItem(wall);
  scene.addItem(car);
  scene.installEventFilter(this);
  this->process();
}

AutoMobiController::~AutoMobiController()
{
  
}

void AutoMobiController::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            //car->pos+=QPointF( -0.1, 0);
            car->steer+=0.01;
            car->update();
            wall->update();
            break;
        case Qt::Key_Right:
            //car->pos+=QPointF( 0.1, 0);
            car->steer-=0.01;
            car->update();
            wall->update();
            break;
        case Qt::Key_Up:
            car->pos+=QPointF( 0, -0.1);
            //car->speed+=0.1;
            break;
        case Qt::Key_Down:
            car->pos+=QPointF( 0, 0.1);
            //car->speed-=0.1;
            break;
    }
}

bool AutoMobiController::eventFilter(QObject *object, QEvent *event)
{
   if (event->type() == QEvent::KeyPress) {
       this->keyPressEvent((QKeyEvent *)event);
       return true;
   } 
   else if (event->type() == QEvent::MouseButtonPress){
       QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
       int mx=mouseEvent->pos().x(),my=mouseEvent->pos().y();
       this->car->setPos(QPointF(mx,my));
       return true;
   }
   else {
       return QObject::eventFilter(object, event);
   } 
}

void AutoMobiController::process()
{
  connect(&timer, SIGNAL(timeout()),
              &scene, SLOT(advance()));
}
