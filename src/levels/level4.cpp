#include "level4.h"
#include "platform.h"

Level4::Level4(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level4::setEnemies() {
    // Add the enemies in Level 4
}

void Level4::setEnvironment() {
    // Add the platforms, spikes, background, etc. for Level 4

    view->setBackgroundBrush(QPixmap(":/images/levels/L4background.png"));

    // Ground platform
    StaticPlatform *ground1 = new StaticPlatform(300, 50, 0, 550);
    addItem(ground1);

    // Spiky platforms
    SpikyPlatform *spiky1 = new SpikyPlatform(100, 20, 300, 580);
    addItem(spiky1);

    // Floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(150, 20, 100, 400);
    addItem(platform1);

    // Moving platform (moves horizontally)
    MovingPlatform *moving1 = new MovingPlatform(150, 20, 500, 200, 200, 2);
    addItem(moving1);

    // Moving platform (moves vertically)
    VerticallyMovingPlatform *movingup = new VerticallyMovingPlatform(150, 20, 800, 400, 200, 2);
    addItem(movingup);

}
