#ifndef MACARONIMISSILE_H
#define MACARONIMISSILE_H
#include "projectile.h"

class MacaroniMissile : public Projectile {
Q_OBJECT

public:
    MacaroniMissile(QGraphicsItem* parent = nullptr);
    void hit(QGraphicsItem* target) override; // Overrides pure virtual function 'hit' in 'Projectile'
};

#endif // MACARONIMISSILE_H
