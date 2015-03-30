#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;

class AutoMobiController;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  protected:

  private slots:
    void adjustViewSize();

  private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    
    AutoMobiController *controller;

};

#endif // MAINWINDOW_H
