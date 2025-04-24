#ifndef PLATFORM_H
#define PLATFORM_H
#include <QGraphicsRectItem>

class Platform : public QGraphicsRectItem
{
public:
    Platform(int width, int height, int x, int y);
};

#endif // PLATFORM_H
