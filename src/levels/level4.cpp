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

    StaticPlatform *ground2 = new StaticPlatform(104, 50, 730, 550);
    addItem(ground2);

    StaticPlatform *ground3 = new StaticPlatform(264, 50, 906, 550);
    addItem(ground3);

    StaticPlatform *ground4 = new StaticPlatform(100, 300, 1170, 300);
    addItem(ground4);

    StaticPlatform *ground5 = new StaticPlatform(100, 50, 1270, 550);
    addItem(ground5);

    StaticPlatform *ground6 = new StaticPlatform(50, 50, 1470, 550);
    addItem(ground6);

    StaticPlatform *ground7 = new StaticPlatform(380, 50, 1620, 550);
    addItem(ground7);

    StaticPlatform *step1 = new StaticPlatform(104, 125, 730, 475);
    addItem(step1);

    StaticPlatform *step2 = new StaticPlatform(104, 125, 906, 475);
    addItem(step2);

    // Spiky platforms
    SpikyPlatform *spiky1 = new SpikyPlatform(100, 20, 300, 580);
    addItem(spiky1);

    SpikyPlatform *spiky2 = new SpikyPlatform(100, 20, 630, 580);
    addItem(spiky2);

    SpikyPlatform *spiky3 = new SpikyPlatform(100, 20, 1370, 580);
    addItem(spiky3);

    SpikyPlatform *spiky4 = new SpikyPlatform(100, 20, 1520, 580);
    addItem(spiky4);


    // Floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(100, 20, 300, 400);
    addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(100, 20, 630, 400);
    addItem(platform2);

    StaticPlatform *platform3 = new StaticPlatform(100, 20, 1370, 180);
    addItem(platform3);

    StaticPlatform *platform4 = new StaticPlatform(100, 20, 1620, 180);
    addItem(platform4);


    // Moving platform (moves horizontally)
    MovingPlatform *moving1 = new MovingPlatform(100, 20, 380, 300, 150, 2);
    addItem(moving1);

    // Moving platform (moves vertically)
    VerticallyMovingPlatform *movingup = new VerticallyMovingPlatform(100, 20, 1030, 300, 200, 2);
    addItem(movingup);

    // Adding temporary 'Clear Condition' object
    QGraphicsRectItem* goal = new QGraphicsRectItem(0,0,64,64);
    goal->setBrush(Qt::red);
    goal->setPos(1800, 450);
    addItem(goal);
    kimo->setGoal(goal);

    view->show(); // Show the view

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
