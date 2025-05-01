#ifndef MACARONIMISSILE_H
#define MACARONIMISSILE_H
#include "projectile.h"

class MacaroniMissile : public Projectile {
Q_OBJECT

public:
    MacaroniMissile(QGraphicsItem* parent = nullptr);
    void hit(QGraphicsItem* target) override; // Overrides pure virtual function 'hit' in 'Projectile'

    // Added method to set the direction
    void setDirection(int dir); 

private:
    // Added member to store direction (1 for right, -1 for left)
    int direction = 1; 

private slots:
    // Override or connect to the move slot if necessary, check projectile.h/cpp
    // Assuming Projectile has a move slot that uses speed, we might need to adjust speed based on direction
    // Let's check projectile.cpp first, but for now, let's assume we modify speed in the constructor or setDirection
};

#endif // MACARONIMISSILE_H

