#include "enemy.h"
#include "macaronimissile.h"
#include "projectile.h"
#include <QGraphicsScene>

MacaroniMissile::MacaroniMissile(QGraphicsItem* parent) : Projectile(parent) {
    speed = 3;
    QPixmap fireball = QPixmap(":/images/macaroni_missile.png").scaled(20,20);
    setPixmap(fireball);
}

void MacaroniMissile::hit(QGraphicsItem* target) {
    if(Enemy*e = dynamic_cast<Enemy*>(target)) {
        scene()->removeItem(target);
        delete e;
        scene()->removeItem(this);
        deleteLater(); // Safe deletion since object may be deleted while move() is still running
    }
}
