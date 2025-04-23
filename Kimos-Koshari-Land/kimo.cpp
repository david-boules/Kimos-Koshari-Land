#include "kimo.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>

Kimo::Kimo(QGraphicsItem * parent) : QGraphicsPixmapItem(parent) {
    // make sure Kimo.png has a transparent background:
    QPixmap KimoLarge(":/images/Kimo.png");
    QPixmap Kimo = KimoLarge.scaled(64, 64);
    setPixmap(Kimo);

    jumpTimer = new QTimer(this);
    connect(jumpTimer, SIGNAL(timeout()), this, SLOT(jumpChange()));
    //timer is created and connected to a...
}

void Kimo::keyPressEvent(QKeyEvent * event) {
    if (event->key() == Qt::Key_Left) {
        setPos(x()-3, y());
    }
    else if (event->key() == Qt::Key_Right) {
        setPos(x()+3, y());
    }

    else if (event->key() == Qt::Key_Up) {
        jump();
    }
    else if (event->key() == Qt::Key_Down) {
        //crouch
    }

    // 'space_bar' for inhale/spit

}

//'jump' function
void Kimo::jump() {
    isJumping = true;
    int jumpChanges = 0;
    jumpTimer->start(30);
}

//'jumpChange' function that is connected to the timer
void Kimo::jumpChange() {
    if(jumpChanges < 8){
        setPos(x(), y()-5);
    } else {
        if(jumpChanges > 7 && jumpChanges < 16){
            setPos(x(), y()+5);
        } else {
            jumpTimer->stop();
            isJumping = false;
            jumpChanges = 0;
            return;
        }
    }
    jumpChanges++;
}
