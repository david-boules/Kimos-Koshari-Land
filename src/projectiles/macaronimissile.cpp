#include "enemy.h"
#include "macaronimissile.h"
#include "projectile.h"
#include "platform.h"
#include <QGraphicsScene>

MacaroniMissile::MacaroniMissile(QGraphicsItem* parent) : Projectile(parent) {
    // Speed is now magnitude, direction is handled separately
    speed = 7;
    QPixmap missilePixmap = QPixmap(":/images/projectiles/macaroni_missile.png").scaled(50,50);
    setPixmap(missilePixmap);
}

// Implementation for setDirection
void MacaroniMissile::setDirection(int dir) {
    if (dir == -1 || dir == 1) { // Ensure direction is either 1 or -1
        direction = dir;
        // Optionally flip the pixmap if moving left
        // if (Kimo::lastDirection == ...)
        if (dir == -1) {
             setTransform(QTransform().scale(-1, 1).translate(-pixmap().width(), 0));
        } else {
             setTransform(QTransform()); // Reset transform if moving right
        }
    }
}

void MacaroniMissile::hit(QGraphicsItem* target) {
    // Check if the target is an Enemy
    if(Enemy* e = dynamic_cast<Enemy*>(target)) {
        scene()->removeItem(target);
        delete e; // Consider using deleteLater() if issues arise
        scene()->removeItem(this);
        deleteLater(); // Safe deletion
        return; // Stop processing after hitting an enemy
    }
    if(Platform* p = dynamic_cast<Platform*>(target)) {
        scene()->removeItem(this);
        deleteLater();
        return;
    }
    // Handle collisions with other types of items if needed
}

