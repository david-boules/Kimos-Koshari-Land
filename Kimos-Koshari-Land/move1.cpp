#include "move1.h"

move1::move1(QString path, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(path, startingPos, parent), angle(0){
    speed=2.0;
}
void move1::move() {

    angle += 0.1;
    setPos(x() -speed, y() + qSin(angle) * 5);
    if (x() <= 0 || x() >= 800 - pixmap().width()) {
        speed = -speed; // Change direction
    }
}
;


