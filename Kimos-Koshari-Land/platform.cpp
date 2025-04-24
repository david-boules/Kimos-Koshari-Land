#include "platform.h"
#include <QGraphicsScene>

Platform::Platform(int width, int height, int x, int y) {
    setRect(0, 0, width, height);
    QPen redPen(Qt::lightGray);
    QBrush redBrush(Qt::lightGray);
    setPen(redPen);
    setBrush(redBrush);
    setPos(x, y);
}
