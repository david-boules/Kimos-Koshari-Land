#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"
#include <QElapsedTimer>

class Boss : public Enemy {
    Q_OBJECT
public:
    Boss(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void shoot_chili();

    void move() override;
    bool can_be_inhaled() const override {return false; }    

private:
    QTimer* shoot_timer;
    QPixmap boss_enemy;
    qreal damage;
    QPixmap boss_img;
};

#endif // BOSS_H
