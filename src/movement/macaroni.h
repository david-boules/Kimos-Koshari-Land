#ifndef MACARONI_H
#define MACARONI_H

#include "enemy.h"

class macaroni : public Enemy {
    Q_OBJECT

public:
    macaroni(QPixmap path, QPointF startingPos, QGraphicsItem* parent = nullptr);

private slots:
    void move() override; // Implement the pure virtual function
};

#endif // MACARONI_H
