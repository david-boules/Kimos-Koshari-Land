#include "enemy.h"
#include "macaronimissile.h"
#include "projectile.h"
#include <QGraphicsScene>

MacaroniMissile::MacaroniMissile(QGraphicsItem* parent) : Projectile(parent) {
    // Speed is now magnitude, direction is handled separately
    speed = 3; 
    QPixmap missilePixmap = QPixmap(":/images/macaroni_missile.png").scaled(20,20);
    setPixmap(missilePixmap);
    // Direction defaults to 1 (right), can be changed by setDirection
}

// Implementation for setDirection
void MacaroniMissile::setDirection(int dir) {
    if (dir == -1 || dir == 1) { // Ensure direction is either 1 or -1
        direction = dir;
        // Optionally flip the pixmap if moving left
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
        // Check if the target is NOT another projectile (to avoid self-destruction or hitting other missiles)
        if (!dynamic_cast<Projectile*>(target)) {
            scene()->removeItem(target);
            delete e; // Consider using deleteLater() if issues arise
            scene()->removeItem(this);
            deleteLater(); // Safe deletion
            return; // Stop processing after hitting an enemy
        }
    }
    // Optionally handle collisions with other types of items (e.g., platforms)
    // else if (dynamic_cast<Platform*>(target)) { ... }
}

