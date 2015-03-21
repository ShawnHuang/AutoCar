#include "Canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    init();
}

Canvas::~Canvas()
{

}

void Canvas::init()
{
    // get event focus
    this->setFocusPolicy(Qt::StrongFocus);
    canvasWidth = 512;
    canvasHeight =  512;

    offset = 50;

    start = QPoint(60 + offset, canvasHeight - 0 - offset);
    end = QPoint(300 + offset, canvasHeight - 370 - offset);
    curPosition= QPoint(60 + offset, canvasHeight - 0 - offset);
    curDegree = 90;


    points[0] = QPoint(0 + offset, canvasHeight - 0 - offset);
    points[1] = QPoint(0 + offset, canvasHeight - 220 - offset);
    points[2] = QPoint(240 + offset, canvasHeight - 220 - offset);
    points[3] = QPoint(240 + offset, canvasHeight - 370 - offset);
    points[4] = QPoint(360 + offset, canvasHeight - 370 - offset);
    points[5] = QPoint(360 + offset, canvasHeight - 100 - offset);
    points[6] = QPoint(120 + offset, canvasHeight - 100 - offset);
    points[7] = QPoint(120 + offset, canvasHeight - 0 - offset);


}


void Canvas::drawWall(QPainter *p)
{
    p->begin(this);
    p->setPen(QPen(Qt::black, 3));
    for (int line = 0; line < 7; line++) {
        p->drawLine(points[line], points[line +1]);
        if (line == 2) {
            line++;
        }
    }

    p->drawEllipse(start, 20, 20);
    p->end();
}

void Canvas::drawPoint(QPainter *p)
{
    p->begin(this);
    p->setPen(QPen(Qt::red, 3));

    p->drawEllipse(start, 20, 20);
    p->drawEllipse(end, 10, 10);
    p->end();
}

void Canvas::drawCar(QPainter *p)
{
    p->begin(this);
    p->setPen(QPen(Qt::blue, 1));
//    p->drawRect(QRectF(0, 0, 100, 20));
//    p->drawEllipse(curPosition, 12, 12);

    float direction = (curDegree / 180.0 * M_PI);

//    p->fillRect(rect(), Qt::white);

    QRect rect(curPosition.x() - 6,curPosition.y() - 12,12,24);
    QPoint center = rect.center();
//    p->save();
    p->translate(center.x(), center.y());
    p->rotate(-30);
    rect = QRect(-center.x(), -center.y(), rect.width(), rect.height());
    qDebug() << rect.x() << " , "<< rect.y();
    qDebug() << rect.width() << " , "<< rect.height();
    p->drawRect(rect);
//    p->restore();

//    // head point
//    QPoint head_dir = QPoint(curPosition.x() + 6 * qCos(direction),
//                         curPosition.y() - 6 * qSin(direction));

//    // head point
//    QPoint head = QPoint(curPosition.x() + 12 * qCos(direction),
//                         curPosition.y() - 12 * qSin(direction));

//    float direction_left = ((curDegree + 45) / 180.0 * M_PI);
//    // left point
//    QPoint left = QPoint(head_dir.x() + 6 * qCos(direction_left),
//                         head_dir.y() - 6 * qSin(direction_left));
//    float direction_right = ((curDegree - 45) / 180.0 * M_PI);
//    // right point
//    QPoint right = QPoint(head_dir.x() + 6 * qCos(direction_right),
//                         head_dir.y() - 6 * qSin(direction_right));

//    p->drawEllipse(head_dir, 2, 2);

//    p->drawEllipse(head, 2, 2);
//    p->drawEllipse(left, 2, 2);
//    p->drawEllipse(right, 2, 2);
//    p->drawEllipse(curPosition, 2, 2);
    p->end();
}
void Canvas::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    drawWall(&p);
    drawPoint(&p);
    drawCar(&p);
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{

}

void Canvas::mousePressEvent(QMouseEvent *event)
{

}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{

}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Right :
        if (curPosition.x() < 509) {
            curPosition.setX(curPosition.x() + 3);
        }
        break ;
    case Qt::Key_Up :
        if (curPosition.y() > 3) {
            curPosition.setY(curPosition.y() - 3);
        }
        break ;
    case Qt::Key_Left :
        if (curPosition.x() > 3) {
            curPosition.setX(curPosition.x() - 3);
        }
        break ;
    case Qt::Key_Down :
        if (curPosition.y() < 509) {
            curPosition.setY(curPosition.y() + 3);
        }
        break ;
    default :
        break ;
    }

    QWidget::update();
}
