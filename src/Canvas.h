#ifndef CANVAS_H
#define CANVAS_H

#include "QWidget"
#include "QPainter"
#include "QSize"
#include "QPaintEvent"
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <QtCore>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

protected:
    void init();
    void drawWall(QPainter *p);
    void drawPoint(QPainter *p);
    void drawCar(QPainter *p);

    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

 private:
    QPoint points[8];
    QPoint start;
    QPoint end;
    QPoint curPosition;
    int offset;
    int canvasWidth;
    int canvasHeight;

};



#endif // CANVAS_H
