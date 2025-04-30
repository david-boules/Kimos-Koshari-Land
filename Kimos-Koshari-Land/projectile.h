#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <QGraphicsItem>
#include <QObject>

class Projectile : public QObject, public QGraphicsPixmapItem {
public:
    Projectile();
};

#endif // PROJECTILE_H
