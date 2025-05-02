#ifndef PLATFORM_H
#define PLATFORM_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

// Abstract base class for all platform types
// Inherits from QGraphicsRectItem for rendering in the scene
class Platform : public QGraphicsPixmapItem
{
public:
    // Constructor for setting size and position
    Platform(int width, int height, int x, int y);
    // Pure virtual update function to be implemented by derived classes
    virtual void update() = 0;

    QGraphicsRectItem* getHitbox() const;

protected:
    QGraphicsRectItem* hitbox = nullptr; // 'Hitbox' to handle rectangular platform collisions (now that QGraphicsPixmapItems are being used)
};

// StaticPlatform: A platform that does not move
// Inherits from Platform and implements a update
class StaticPlatform : public Platform {
public:
    StaticPlatform(int width, int height, int x, int y);
    void update() override;
};

// MovingPlatform: A platform that moves back and forth horizontally
class MovingPlatform : public Platform {
public:
    // Constructor initializes platform size, position, movement range and speed
    MovingPlatform(int width, int height, int x, int y, int range, int speed = 2);
    // Called every frame or tick to update the platform's position
    void update() override;
private:
    int startX, moveRange, moveSpeed, direction;
};

// SpikyPlatform: A static platform with a spike PNG overlay
// Inherits from Platform and adds a QGraphicsPixmapItem for the spikes
class SpikyPlatform : public Platform {
public:
    // Constructor sets up the base platform and overlays the spike PNG
    SpikyPlatform(int width, int height, int x, int y);
    // No movement, but can override collision logic elsewhere
    void update() override;
private:
    QGraphicsPixmapItem* spikeOverlay;
};

#endif // PLATFORM_H
