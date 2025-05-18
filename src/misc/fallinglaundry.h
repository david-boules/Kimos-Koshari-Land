#ifndef FALLINGLAUNDRY_H
#define FALLINGLAUNDRY_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class FallingLaundry : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit FallingLaundry(const QPixmap& pixmap, QPointF spawnPos, QObject* parent = nullptr); // Two distinct clothing items, so a pixmap argument is needed, along with the spawn point which is determined randomly

public slots:
    void fall();

private:
    QTimer* fallTimer;
};

#endif // FALLINGLAUNDRY_H
