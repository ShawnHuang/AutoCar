#include <QPainter>
#include <stdio.h>

#include "constants.h"
#include "Wall.h"

Wall::Wall()
  : pos(0,0)
{
  this->setPos(pos);
  this->setData(GD_Type, GO_Wall);
}

QRectF Wall::boundingRect() const
{
  return QRectF( pos.x()-10, pos.y()-10, 55, 55);
}

void Wall::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(this->shape(), QColor(80,80,80));

    painter->restore();
}

QPainterPath Wall::shape() const
{
  QPainterPath p,q;
  p.addRect(-10,-10, 55, 55);
  //p.addEllipse(this->pos, 149, 149);
  QVector<QPointF> vect(9);
  //vect<<QPointF(-6,-6)<<QPointF(-6,22)<<QPointF(18,22)<<QPointF(18,37)<<QPointF(30,37)<<QPointF(30,10)<<QPointF(6,10)<<QPointF(6,-6)<<QPointF(-6,-6);
  vect<<QPointF(-6,0)<<QPointF(-6,28)<<QPointF(18,28)<<QPointF(18,43)<<QPointF(30,43)<<QPointF(30,16)<<QPointF(6,16)<<QPointF(6,0)<<QPointF(-6,0);
  q.addPolygon(QPolygonF(vect));
  return p-q;
}

void Wall::advance(int step)
{
  //if(this->contains(QPointF(0,30)))
  //  printf("wall\n");
  //else
  //  printf("not wall\n");
  this->update();
}
