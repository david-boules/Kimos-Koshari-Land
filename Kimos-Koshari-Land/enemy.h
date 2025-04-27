#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "kimo.h"

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Enemy(QGraphicsItem* parent = nullptr);
    void setTargetKimo(Kimo* kimo) { kimoo = kimo; }

signals:
    void enemyDefeated(Enemy* enemy);

private slots:
    void move();


private:
    QTimer* moveTimer;
    qreal speed;
    Kimo* kimoo;

};

#endif // ENEMY_H
