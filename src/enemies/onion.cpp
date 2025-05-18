#include "onion.h"

onion::onion(QString path, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(QPixmap(path), startingPos, parent), angle(0){
    speed=2.0;
    damage=1;
    health=1;
    max_health=1;
    update_health_bar();
}

void onion::setMoveStyle(onion_move style) {
    moveStyle = style;
}

onion_move onion::getMoveStyle() const {
    return moveStyle;
}

void onion::move() {

    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);
        double knockbackForce = -8.0; // Upward force
        double horizontalKnockback = (kimoo->x() < x() + pixmap().width() / 2) ? -5.0 : 5.0; // Left or right knockback

        // Set Kimo's velocities for knockback
        kimoo->setKnockback(knockbackForce, horizontalKnockback);


        // qreal Direction = (kimoo->x() < x()) ? 1 : -1;
        // kimoo->setPos(kimoo->x() - Direction * 120, kimoo->y());

        // scene()->removeItem(this);
        // delete this;
        // return;
    }

    switch (moveStyle)
    {
    case onion_move::level1:


    angle += 0.1;
    setPos(x() -speed, y() + qSin(angle) * 3.5);
    if (x() <= minX || x() >= maxX - pixmap().width()) {
        speed = -speed; // bounce between minX and maxX
    }
    break;

    case onion_move::level2:
        angle += 0.1;
        setPos(x() -speed, y() + qSin(angle) * 3.5);
        if (x() <= 500 || x() >= 800 - pixmap().width()) {
            speed = -speed; // bounce between minX and maxX
        }

break;

    case onion_move::level2_1:
        angle += 0.1;
        setPos(x() -speed, y() + qSin(angle) * 2.0);
        if (x() <= 1220 || x() >= 1310) {
            speed = -speed; // bounce between minX and maxX
        }


}

}
;


