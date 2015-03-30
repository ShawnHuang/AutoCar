#ifndef WALL_H
#define WALL_H
#include <QGraphicsItem>

class Wall : public QGraphicsItem
{
  public:
    
    Wall();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;
  
    void advance(int step);

  private:
    QPointF pos;

};

#endif
