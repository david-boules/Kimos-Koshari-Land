#include "onion.h"

onion::onion(QString path, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(QPixmap(path), startingPos, parent), angle(0){
    speed=2.0;
    damage=1;
    health=1;
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



    angle += 0.1;
    setPos(x() -speed, y() + qSin(angle) * 3.5);
    if (x() <= minX || x() >= maxX - pixmap().width()) {
        speed = -speed; // bounce between minX and maxX
    }
}

;


