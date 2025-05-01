#include "fireball.h"
#include "projectile.h"
#include <QPixmap>
#include <QGraphicsScene>

Fireball::Fireball(qreal direction, QGraphicsItem* parent) : Projectile(parent)
{   damage=1;
    speed=direction*3;  // Speed: 3, direction: -1 or 1
    QPixmap fireball = QPixmap(":/images/projectiles/fireball.png").scaled(20,20);
    setPixmap(fireball);
}

void Fireball::hit(QGraphicsItem* target) {
    if(Kimo*k = dynamic_cast<Kimo*>(target)) {
        k->takeDamage(damage);
        scene()->removeItem(this);
        deleteLater(); // Safe deletion since object may be deleted while move() is still running
    }
}
