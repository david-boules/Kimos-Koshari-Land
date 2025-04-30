#ifndef FIREBALL_H
#define FIREBALL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "kimo.h"

class Fireball : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Fireball(qreal direction, QGraphicsItem* parent = nullptr);
    void setTargetKimo(Kimo* kimo) ;
    Kimo* kimoo;



private slots:
    void move();

private:
    QTimer* moveTimer;
    qreal speed;
    qreal damage;
};

#endif // FIREBALL_H
