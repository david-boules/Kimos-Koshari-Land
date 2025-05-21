#ifndef FIREBALL_H
#define FIREBALL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "kimo.h"
#include "projectile.h"

class Fireball : public Projectile {
    Q_OBJECT

public:
    Fireball(qreal direction,QGraphicsItem* shooter, QGraphicsItem* parent = nullptr);
    void hit(QGraphicsItem* target) override; // Overrides pure virtual function 'hit' in 'Projectile'

private:
    qreal damage;
    QGraphicsItem* shooter;
};

#endif // FIREBALL_H
