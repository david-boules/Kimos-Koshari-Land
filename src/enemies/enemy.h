#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include "kimo.h"

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Enemy(QPixmap path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void setTargetKimo(Kimo* kimo) { kimoo = kimo; }
    void SetHealth(int health);
    void setSpeed(qreal s);
    int get_enemy_health() const;
    void takedamage(int enemydamage);

signals:
    void enemyDefeated(Enemy* enemy);

private slots:
    virtual void move()=0;
protected:
    qreal speed;
    Kimo* kimoo;
    qreal damage;
    int health;

private:
    QTimer* moveTimer;

    QGraphicsRectItem* healthBar;
    QGraphicsRectItem* healthBarBackground;


};

#endif // ENEMY_H
