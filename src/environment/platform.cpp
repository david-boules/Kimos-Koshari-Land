#include "platform.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter> // Needed to resize Pixmap items
#include "kimo.h" // Add this include for Kimo class

// Platform base constructor: sets size and position
Platform::Platform(int width, int height, int x, int y) {
    QPixmap original_brick(":/images/tiles/brick.png");
    // Ensuring platform is exactly the intended size ('IgnoreAspectRatio') & Making scaling visually clean ('SmoothTransformation')
    QPixmap scaled = original_brick.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaled);
    setPos(x, y);

    // Create hitbox exactly matching the pixmap's dimensions and position
    hitbox = new QGraphicsRectItem(0, 0, width, height, this); 
    // Make hitbox invisible but still functional for collision detection
    hitbox->setBrush(Qt::NoBrush);
    hitbox->setPen(Qt::NoPen);
    // Ensure hitbox stays with the platform when it moves
    hitbox->setPos(0, 0);
}

QGraphicsRectItem* Platform::getHitbox() const {
    return hitbox;
}

// StaticPlatform constructor: calls base Platform constructor
// Static platforms do not move, so update() does nothing
StaticPlatform::StaticPlatform(int width, int height, int x, int y)
    : Platform(width, height, x, y) {}
void StaticPlatform::update() {
    // No movement or special behavior for static platforms
}

// MovingPlatform constructor: calls base Platform constructor and initializes movement variables
MovingPlatform::MovingPlatform(int width, int height, int x, int y, int range, int speed)
    : Platform(width, height, x, y), startX(x), moveRange(range), moveSpeed(speed), direction(1) {}

// MovingPlatform update: moves the platform back and forth horizontally
void MovingPlatform::update() {
    if(isPaused) return;
    // Move the platform using QGraphicsItem coordinates
    setPos(x() + direction * moveSpeed, y());
    
    // Check if platform has reached movement boundaries
    if (x() >= startX + moveRange || x() <= startX) {
        direction *= -1;
    }
}

// VerticallyMovingPlatform constructor: calls base Platform constructor and initializes movement variables
VerticallyMovingPlatform::VerticallyMovingPlatform(int width, int height, int x, int y, int range, int speed)
    : Platform(width, height, x, y), startY(y), moveRange(range), moveSpeed(speed), direction(1) {}

// VerticallyMovingPlatform update: moves the platform up and down
void VerticallyMovingPlatform::update() {
    if(isPaused) return;
    // Store the previous Y position
    qreal oldY = y();
    
    // Move the platform using QGraphicsItem coordinates
    setPos(x(), y() + direction * moveSpeed);
    
    // If Kimo is on the platform, move them with it
    if (currentKimo) {
        qreal deltaY = y() - oldY;
        currentKimo->setPos(currentKimo->x(), currentKimo->y() + deltaY);
    }
    
    // Check if platform has reached movement boundaries
    if (y() >= startY + moveRange || y() <= startY) {
        direction *= -1;
    }
}

void VerticallyMovingPlatform::moveKimoWithPlatform(Kimo* kimo) {
    currentKimo = kimo;
}

void VerticallyMovingPlatform::clearKimo() {
    currentKimo = nullptr;
}

// SpikyPlatform constructor overlays a spike PNG on the platform
SpikyPlatform::SpikyPlatform(int width, int height, int x, int y)
    : Platform(width, height, x, y), spikeOverlay(nullptr)
{
    QPixmap spikePixmap(":/images/tiles/spikes.png");
    if (!spikePixmap.isNull()) {
        // Making the spikes appear in between the ground tiles
        spikePixmap = spikePixmap.scaled(width, 20, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        spikeOverlay = new QGraphicsPixmapItem(spikePixmap, this);
        spikeOverlay->setPos(0, - 20);
    }
}
void SpikyPlatform::update() {
    // Spiky platforms do not move by default
    // You can add animation or effects here if desired
}

void SpikyPlatform::handleCollision(Kimo* kimo) {
    // Check if Kimo is falling onto the spikes
    if (kimo->y() + kimo->pixmap().height() <= y() + 20) { // 20 is spike height
        // Apply damage
        kimo->takeDamage(1);
        
        // Apply knockback
        // Knockback direction depends on which side of the platform Kimo is on
        double knockbackForce = -8.0; // Upward force
        double horizontalKnockback = (kimo->x() < x() + pixmap().width() / 2) ? -5.0 : 5.0; // Left or right knockback
        
        // Set Kimo's velocities for knockback
        kimo->setKnockback(knockbackForce, horizontalKnockback);
    }
}
