#ifndef FIRE_CHILI_H
#define FIRE_CHILI_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "kimo.h"
#include "projectile.h"

class fire_chili : public Projectile {
    Q_OBJECT

public:
    fire_chili(qreal direction, QGraphicsItem* parent = nullptr);
    void hit(QGraphicsItem* target) override;

private:
    qreal damage;
};

#endif // FIRE_CHILI_H
