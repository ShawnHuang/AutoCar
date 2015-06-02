#include <QPainter>

#include <cmath>

#include "constants.h"
#include "AutoMobiController.h"
#include "Car.h"
#include "Wall.h"
#include "Fuzzy/Fuzzy.h"
#include "PSO/PSO.h"
#include "GA/GA.h"

Car::Car(AutoMobiController &controller, QPointF pos)
  : controller(controller),
    radius(2.3),
    angle(0),
    steer(0),
    speed(0.1)
{
  this->init_pos = pos;
  this->setPos(pos);
  //this->fuzzy = new Fuzzy();
  //this->ga = new GA();
  this->pso = new PSO();
}

QRectF Car::boundingRect() const
{
  return QRectF( -radius, -radius, radius*2, radius*2);
}

void Car::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(this->shape(), QColor(70,130,180));

    //p.moveTo(QPointF(0,3));
    //p.lineTo(QPointF(0,0));
    painter->setPen(QPen(Qt::gray, 0.1, Qt::SolidLine)); 
    painter->drawLine(mapFromScene(this->pos),mapFromScene(this->cpoint));
    painter->drawLine(mapFromScene(this->pos),mapFromScene(this->lpoint));
    painter->drawLine(mapFromScene(this->pos),mapFromScene(this->rpoint));
    painter->setPen(QPen(Qt::yellow, 0.1, Qt::SolidLine)); 
    painter->drawLine(0, 3, 0, 0);
    painter->setPen(QPen(Qt::blue, 0.1, Qt::DotLine)); 
    painter->rotate(this->steer*(180)/PI);
    painter->drawLine(0, 3, 0, 0);

    painter->restore();
}

QPainterPath Car::shape() const
{
  QPainterPath p;
  p.addEllipse(QPointF(0,0), radius, radius);
  return p;
}

void Car::advance(int step)
{
  if (!step)
  {
    return;
  }

  this->detect();
  this->handleCollisions();

  //this->fuzzy->init(this->left, this->center, this->right);
  //float steer = this->fuzzy->getSteer();
  //float steer = this->ga->getSteer(this->left, this->center, this->right);
  float steer = this->pso->getSteer(this->left, this->center, this->right);

  //float speed = this->getSpeed();
  
  this->powerfunction(steer*PI/180);
  this->setRotation(this->angle*(-180)/PI);
  this->setPos(this->pos);

}

void Car::handleCollisions()
{
  QList<QGraphicsItem *> collisions = collidingItems();//Qt::ContainsItemShape
  int check=0;
  // Check collisions with other objects on screen
  
  foreach (QGraphicsItem *collidingItem, collisions) {
    if(collidingItem->data(GD_Type) == GO_Wall)
      check=1;
  }  
  if (check==1)
  {
    this->pos=this->init_pos;
    this->angle=0;
    this->steer=0;
  }
  else
  {
    //printf("not%f %f\n",this->pos.x(),this->pos.y());
  }
}

void Car::setTarget(Wall *wall)
{
  this->wall=wall;
}

void Car::detect()
{
  QPointF d1 = QPointF(pos.x()+3*sin(this->angle),pos.y()+3*cos(this->angle));
  QPointF d2 = QPointF(pos.x()+3*sin(this->angle+PI/4),pos.y()+3*cos(this->angle+PI/4));
  QPointF d3 = QPointF(pos.x()+3*sin(this->angle-PI/4),pos.y()+3*cos(this->angle-PI/4));
  //QPointF d2 = mapFromScene(d1);
  //printf("pos %f %f %f\n",this->left,this->center,this->right);
  //printf("hit %f %f\n",d1.rx(),d1.ry());
  for (;;)
  {
    d1.rx()+=0.1*sin(this->angle);
    d1.ry()+=0.1*cos(this->angle);
    if(wall->contains(d1))
    {
      //printf("center %f %f\n",d1.rx(),d1.ry());
      this->cpoint=d1;
      this->center=this->distance(pos,d1);
      break;
    }
  }
  for (;;)
  {
    d2.rx()+=0.1*sin(this->angle+PI/4);
    d2.ry()+=0.1*cos(this->angle+PI/4);
    if(wall->contains(d2))
    {
      //printf("left %f %f\n",d2.rx(),d2.ry());
      this->lpoint=d2;
      this->left=this->distance(pos,d2);
      break;
    }
  }
  for (;;)
  {
    d3.rx()+=0.1*sin(this->angle-PI/4);
    d3.ry()+=0.1*cos(this->angle-PI/4);
    if(wall->contains(d3))
    {
      //printf("right %f %f\n",d3.rx(),d3.ry());
      this->rpoint=d3;
      this->right=this->distance(pos,d3);
      break;
    }
  }
  
}

float Car::distance(QPointF& p1, QPointF& p2)
{
  return sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+(p1.y()-p2.y())*(p1.y()-p2.y()));
}

void Car::powerfunction(float fuzzy_steer,float fuzzy_speed)
{
  if (fuzzy_steer!=0)
  {
    this->steer=fuzzy_steer;
  }
  if (fuzzy_speed!=0)
  {
    this->speed=fuzzy_speed;
  }
  //if (this->angle<=-PI/2)
  //{
  //  this->angle=-PI/2;
  //}
  //if (this->angle>=3*PI/2)
  //{
  //  this->angle=3*PI/2;
  //}
  if (this->steer<=-40*PI/180)
  {
    this->steer=-40*PI/180;
  }
  if (this->steer>=40*PI/180)
  {
    this->steer=40*PI/180;
  }
  float init_angle=PI/2;
  this->pos.rx()=this->pos.x()-this->speed*cos(init_angle+this->angle+this->steer)-this->speed*sin(this->steer)*sin(init_angle+this->angle);
  this->pos.ry()=this->pos.y()+this->speed*sin(init_angle+this->angle+this->steer)-this->speed*sin(this->steer)*cos(init_angle+this->angle);
  this->angle=this->angle-this->speed*asin(2*sin(this->steer)/this->radius);
}
