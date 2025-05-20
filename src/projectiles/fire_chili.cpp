#include "fire_chili.h"
#include "projectile.h"
#include <QPixmap>
#include <QGraphicsScene>

fire_chili::fire_chili(qreal direction, QGraphicsItem* parent) : Projectile(parent)
{
    damage = 1;
    speed = direction * 3;  // Speed: 3, direction: -1 or 1
    QPixmap pixmap = QPixmap(":/images/projectiles/chiliLeft.png").scaled(80, 80);
    setPixmap(pixmap);
}

void fire_chili::hit(QGraphicsItem* target) {
    if (Kimo* k = dynamic_cast<Kimo*>(target)) {
        k->takeDamage(damage);
        scene()->removeItem(this);
        deleteLater(); // Safe deletion
    }
}
