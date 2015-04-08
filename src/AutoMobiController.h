#ifndef AUTOMO
#define AUTOMOBICONTROLLER

#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QKeyEvent;

class Car;
class Wall;

class AutoMobiController : public QObject
{
  Q_OBJECT

  public:
    AutoMobiController( QGraphicsScene &scene, QObject *parent = 0);
    ~AutoMobiController();
  public slots:
    void process();

  //protected:

  private:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

    QTimer timer;
    QGraphicsScene &scene;
    Car *car;
    Wall *wall;
    int x,y;

};

#endif
