#include "widget.h"
#include <QMessageBox>
#include <QList>
#include <QProcess>
#include <QLabel>
//Конструктор виджета
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMouseTracking(true);
    myLayoutScene = new QHBoxLayout(this);
    myGraphics = new myGraphicsView;
    myLayoutScene->addWidget(myGraphics);
    setLayout(myLayoutScene);


}

Widget::~Widget() {}
//Конструктор графического представления
myGraphicsView::myGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(0, 0, 700, 700, this);
    scene->addRect(scene->sceneRect());
    setScene(scene);

    myLineTimer = new QTimer(this);
    connect(myLineTimer, SIGNAL(timeout()), this, SLOT(myTimerLine()));
    myRectTimer = new QTimer(this);
    connect(myRectTimer, SIGNAL(timeout()), this, SLOT(myTimerRect()));

    lineItem2 = new QGraphicsLineItem(220, 0, 220, 700);
    lineItem2->setPen(QPen(Qt::black, 2));
    scene->addItem(lineItem2);

    lineItem1 = new QGraphicsLineItem(100, 0, 100, 700);
    lineItem1->setPen(QPen(Qt::black, 2));
    scene->addItem(lineItem1);

    rectItem = new QGraphicsRectItem(140, 300, 40, 40);
    rectItem->setPen(QPen(Qt::black, 2));
    rectItem->setBrush(Qt::red);
    scene->addItem(rectItem);

    QGraphicsTextItem *textItem = new QGraphicsTextItem("Счёт:");
    textItem->setPos(0, 0);
    scene->addItem(textItem);

    // lineEdit = new QLineEdit(0, 0);
    // scene->addText(lineEdit);


    QLineEdit *lineEdit = new QLineEdit(QString::number(count_wins));
    lineEdit->setMaximumWidth(15);
    scene->addWidget(lineEdit);
    lineEdit->move(10, 20);


}
void myGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (clic_rectItem == true && !releasing_colliding_rectItem) rectItem->setPos(mapToScene(event->pos().x() - 160, event->pos().y() - 320));

    if (rectItem->collidesWithItem(lineItem1) || rectItem->collidesWithItem(lineItem2)) {
        myTimerRect();
        releasing_colliding_rectItem = true;
    }
}

void myGraphicsView::mousePressEvent(QMouseEvent *event) {
    position = mapToScene(event->pos());
    int leftBoundingRectX = rectItem->sceneBoundingRect().x()+ 1;
    int upBoundingRectY =rectItem->sceneBoundingRect().y()+ 1;
    int rightBoundingRectX = rectItem->sceneBoundingRect().x() + 41;
    int downBoundingRectY = rectItem->sceneBoundingRect().y() + 41;
    if(position.x() >= leftBoundingRectX && position.x() <= rightBoundingRectX
        && position.y() >= upBoundingRectY &&  position.y() <= downBoundingRectY) {
        myLineTimer->start(interval);
        clic_rectItem = true;
    }

    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void myGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
    if(clic_rectItem) releasing_colliding_rectItem = true;
}


void myGraphicsView::myTimerLine()
{
    static int i = 0, j = 0;
    i++;
    j++;
    lineItem1->setPos(j, 0);
    lineItem2->setPos(i, 0);
    if (releasing_colliding_rectItem) {
        myLineTimer->stop();
        myRectTimer->start(1000 / 200);
        myGraphicsView::myTimerRect();
    }

    if (i >= scene->width() - 220) {
        count_wins++;
        myLineTimer->stop();
        lineItem1->setPos(0, 0);
        lineItem2->setPos(0, 0);
        rectItem->setPos(0, 0);
        clic_rectItem = false;
        releasing_colliding_rectItem = false;
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        i = 0;
        j = 0;
        interval = interval - 1;
        QLineEdit *lineEdit = new QLineEdit(QString::number(count_wins));
        lineEdit->setMaximumWidth(15);
        scene->addWidget(lineEdit);
        lineEdit->move(10, 20);
        // // lineEdit->setText("Количество сыгранных раундов" + QString::number(count_wins));
        // QLabel *label = new QLabel(this);
        // label->setText("Количество сыгранных раундов" + QString::number(count_wins));
        // // myLayoutScene->
        // // scene->addItem(label);
        // scene->addItem(textItem);
        // scene->addText("Счёт: " + QString::number(count_wins))->setPos(0, 0);
    }

}


void myGraphicsView::myTimerRect() {
    static int i = 0;
    i++;
    int newPosX = rectItem->pos().x();
    rectItem->setPos(newPosX, i);
    if (i >= scene->height() - 340) {
        myRectTimer->stop();
        setAttribute(Qt::WA_TransparentForMouseEvents);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Информирование");
        msgBox.setText("Вы проиграли!");
        msgBox.exec();
    }
}
