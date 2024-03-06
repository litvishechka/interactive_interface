#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMouseEvent>
#include <QLineEdit>

//Класс окна графического представления QGraphicsView
class myGraphicsView : public QGraphicsView {

    Q_OBJECT
public:
    myGraphicsView(QWidget *parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QGraphicsScene *scene;
    QGraphicsLineItem *lineItem2;
    QGraphicsLineItem *lineItem1;
    QGraphicsRectItem *rectItem;
    QTimer *myLineTimer;
    QTimer *myRectTimer;
    QPointF position;
    QGraphicsTextItem *textItem;
    bool clic_rectItem = false;
    bool releasing_colliding_rectItem = false;
    int interval = 10;
    int count_wins = 0;
    QLineEdit *lineEdit;

private slots:
    void myTimerLine();
    void myTimerRect();


};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
// protected:
//     virtual void mousePressEvent(QMouseEvent *);
private:
    QHBoxLayout *myLayoutScene;
    myGraphicsView *myGraphics;
    // QPointF position;

};
#endif // WIDGET_H
