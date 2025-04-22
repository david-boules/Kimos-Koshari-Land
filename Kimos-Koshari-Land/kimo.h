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
};

#endif // KIMO_H
