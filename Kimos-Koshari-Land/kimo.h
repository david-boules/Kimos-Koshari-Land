#ifndef KIMO_H
#define KIMO_H
#include <QGraphicsItem>
#include <QObject>

class Kimo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Kimo(QGraphicsItem *parent = nullptr);
public:
    void keyPressEvent(QKeyEvent * event);
    void jump();
private:
    double velocity;
    bool isGrounded; //doubles as checking if character jumping to prevent double jumps
};

#endif // KIMO_H
