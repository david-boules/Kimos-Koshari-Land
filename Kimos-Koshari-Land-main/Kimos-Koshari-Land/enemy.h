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

    Enemy(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void setTargetKimo(Kimo* kimo) { kimoo = kimo; }
    void SetHealth(int health);
   // void damage(int damage1);

signals:
    void enemyDefeated(Enemy* enemy);

private slots:
    virtual void move();
protected:
    qreal speed;
     Kimo* kimoo;
    qreal damage;

private:
    QTimer* moveTimer;


    int health;
    QGraphicsRectItem* healthBar;
    QGraphicsRectItem* healthBarBackground;


};

#endif // ENEMY_H
