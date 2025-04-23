#include "platform.h"
#include <QGraphicsScene>

Platform::Platform() {
    setRect(0,0,800,600);
    QPen redPen(Qt::lightGray);
    QBrush redBrush(Qt::lightGray);
    setPen(redPen);
    setBrush(redBrush);
}
