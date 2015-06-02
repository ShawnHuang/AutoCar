#ifndef CAR_H
#define CAR_H
#include <QGraphicsItem>

class AutoMobiController;
class Wall;
class Fuzzy;
class GA;
class PSO;

class Car : public QGraphicsItem
{
  public:
    AutoMobiController &controller;
    QPointF init_pos,pos;
    float radius;
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
    Wall *wall;
    Fuzzy *fuzzy;
    GA *ga;
    PSO *pso;

    void handleCollisions();
};

#endif
