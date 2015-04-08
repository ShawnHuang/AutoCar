#ifndef CAR_H
#define CAR_H
#include <QGraphicsItem>

class AutoMobiController;
class Wall;
class Fuzzy;

class Car : public QGraphicsItem
{
  public:
    QPointF init_pos,pos;
    float angle;
    float steer;
    float speed;
    float center,left,right;
    QPointF cpoint,lpoint,rpoint;

    
    Car(AutoMobiController &controller, QPointF pos);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    QPainterPath shape() const;

    void setTarget(Wall *wall);
    void detect();
    float distance(QPointF &p1, QPointF &p2);
    void powerfunction(float fuzzy_steer=0, float fuzzy_speed=0);
  
  protected:
    void advance(int step);

  private:
    AutoMobiController &controller;
    int radius;
    Wall *wall;
    Fuzzy *fuzzy;

    void handleCollisions();
};

#endif
