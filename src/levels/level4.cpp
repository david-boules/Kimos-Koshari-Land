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

    // Ground platforms
    StaticPlatform *ground1 = new StaticPlatform(300, 50, 0, 550);
    addItem(ground1);

    StaticPlatform *ground2 = new StaticPlatform(120, 50, 730, 550);
    addItem(ground2);

    StaticPlatform *ground3 = new StaticPlatform(280, 50, 890, 550);
    addItem(ground3);

    StaticPlatform *ground4 = new StaticPlatform(150, 300, 1170, 300);
    addItem(ground4);

    // Step platforms
    StaticPlatform *step1 = new StaticPlatform(120, 125, 730, 475);
    addItem(step1);

    StaticPlatform *step2 = new StaticPlatform(120, 125, 890, 475);
    addItem(step2);

    // Spiky platforms
    SpikyPlatform *spiky1 = new SpikyPlatform(100, 20, 300, 580);
    addItem(spiky1);

    SpikyPlatform *spiky2 = new SpikyPlatform(100, 20, 630, 580);
    addItem(spiky2);

    // Floating static platforms
    StaticPlatform *platform1 = new StaticPlatform(100, 20, 300, 400);
    addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(100, 20, 630, 400);
    addItem(platform2);

    // Moving platform (horizontal)
    MovingPlatform *moving1 = new MovingPlatform(100, 20, 380, 300, 150, 2);
    addItem(moving1);

    // Moving platform (vertical)
    VerticallyMovingPlatform *movingup = new VerticallyMovingPlatform(100, 20, 1030, 300, 200, 2);
    addItem(movingup);

    // Timer for game updates (platforms, HUD)
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer, &QTimer::timeout, this, [=]() {
        if (!moving1 || !movingup) return;
        // Update moving platforms
        moving1->update();
        movingup->update();
    });

    gameUpdateTimer->start(16); // ~60 FPS
}

