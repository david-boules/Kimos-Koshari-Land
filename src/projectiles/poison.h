#ifndef POISON_H
#define POISON_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "kimo.h"
#include "projectile.h"

class Poison : public Projectile {
public:
    Poison(qreal direction, QGraphicsItem* parent = nullptr);
    void hit(QGraphicsItem* target) override;




private:

    qreal damage;


};





#endif // POISON_H
