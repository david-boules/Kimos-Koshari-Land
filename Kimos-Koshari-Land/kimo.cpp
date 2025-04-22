#include "kimo.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>

Kimo::Kimo(QGraphicsItem * parent) : QGraphicsPixmapItem(parent) {
    // make sure Kimo.png has a transparent background:
    QPixmap KimoLarge(":/images/Kimo.png");
    QPixmap Kimo = KimoLarge.scaled(64, 64);
    setPixmap(Kimo);
}

void Kimo::keyPressEvent(QKeyEvent * event) {
    if (event->key() == Qt::Key_Left)
    {
        setPos(x()-3, y());
    }
    else if (event->key() == Qt::Key_Right)
    {
        setPos(x()+3, y());
    }

    else if (event->key() == Qt::Key_Up)
    {
        jump();
    }
    else if (event->key() == Qt::Key_Down)
    {
        //crouch
    }

    // 'space_bar' for inhale/spit

}

void Kimo::jump() {
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT (move()));
    timer->start(20);

    setPos(x(), y()-10);
}
