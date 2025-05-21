#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Coin : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Coin(QPointF pos, QGraphicsItem *parent = nullptr);
    void startAnimation();

public slots:
    void pause();
    void resume();

private:
    QTimer *animationTimer;
    int animationFrame = 0;
    void updateAnimation();
};

#endif // COIN_H
