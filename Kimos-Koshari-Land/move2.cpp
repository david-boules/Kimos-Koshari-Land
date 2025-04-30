#include "move2.h"
#include <QGraphicsScene>

move2::move2(QString path, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(path, startingPos, parent){
    speed=2.0;
    damage=2;
}
void move2::move() {
    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);
        scene()->removeItem(this);
        delete this;
        return;
    }

    if (!kimoo) return; // If no Kimo linked, skip

    // Distance between enemy and Kimo
    qreal distancex = qAbs(x() - kimoo->x());
    qreal distancey=qAbs(y()-kimoo->y());

    // If Kimo is close (for example, within 50 pixels)
    if (distancex <200&&distancey<30) {
        // Move towards Kimo
        if (x() > kimoo->x()) {
            setPos(x() - qAbs(speed), y()); // Move left towards Kimo
        } else if (x() < kimoo->x()) {
            setPos(x() + qAbs(speed), y()); // Move right towards Kimo
        }
    }
    else {
        // Normal bouncing movement (if Kimo is far)
        setPos(x() - speed, y());

        // Bounce back when hitting screen edges
        if (x() <= 0 || x() >= 800 - pixmap().width()) {
            speed = -speed; // Change direction
        }
    }


}
;


