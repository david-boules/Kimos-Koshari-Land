#include "onion.h"

onion::onion(QString path, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(QPixmap(path), startingPos, parent), angle(0){
    speed=2.0;
    damage=1;
}
void onion::move() {

    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);


        qreal Direction = (kimoo->x() < x()) ? 1 : -1;
        kimoo->setPos(kimoo->x() - Direction * 120, kimoo->y());

        // scene()->removeItem(this);
        // delete this;
        // return;
    }



    angle += 0.1;
    setPos(x() -speed, y() + qSin(angle) * 5);
    if (x() <= minX || x() >= maxX - pixmap().width()) {
        speed = -speed; // bounce between minX and maxX
    }
}

;


