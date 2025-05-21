#include "level1.h"
#include "chili.h"
#include "macaroni.h"
#include "onion.h"
#include "platform.h"
#include "coin.h"

Level1::Level1(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level1::setEnemies() {
    // Add the enemies in Level 1
    chili* ChiliEnemy = new chili(":/images/enemies/chiliLeft.png",":/images/enemies/chiliRight.png",QPointF(500,336));
    addItem(ChiliEnemy);
    ChiliEnemy->setTargetKimo(kimo);

    macaroni* MacaroniEnemy = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(364,236));
    addItem(MacaroniEnemy);
    MacaroniEnemy->setTargetKimo(kimo);

    onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(400,490));
    addItem(OnionEnemy);
    OnionEnemy->setTargetKimo(kimo);

    QTimer* enemySpawnTimer = new QTimer(this);
    QObject::connect(enemySpawnTimer, &QTimer::timeout, this, [this]() {
        if (!this) return;

        if (kimo->x() > 550 && !enemySpawned) {
            onion* onion2 = new onion(":/images/enemies/onion.png", QPointF(1000, 400));
            onion2->setBounds(850,1400);
            addItem(onion2);
            onion2->setTargetKimo(kimo);
            enemySpawned = true;
        }
    });
    enemySpawnTimer->start(16); // Check ~60 times per second
}

void Level1::setEnvironment() {
    // Add the platforms, spikes, background, etc. for Level 1

    // Background
    view->setBackgroundBrush(QPixmap(":/images/levels/L1background.png"));

    // Ground platform (extended for larger scene)
    StaticPlatform *ground1 = new StaticPlatform(200, 50, 0, 550);
    addItem(ground1);

    StaticPlatform *ground2 = new StaticPlatform(200, 50, 300, 550);
    addItem(ground2);

    StaticPlatform *ground3 = new StaticPlatform(200, 50, 600, 550);
    addItem(ground3);

    StaticPlatform *ground4 = new StaticPlatform(200, 50, 900, 550);
    addItem(ground4);

    StaticPlatform *ground5 = new StaticPlatform(800, 50, 1200, 550);
    addItem(ground5);

    // Spiky platforms
    SpikyPlatform *spiky1 = new SpikyPlatform(100, 20, 200, 580);
    addItem(spiky1);

    SpikyPlatform *spiky2 = new SpikyPlatform(100, 20, 500, 580);
    addItem(spiky2);

    SpikyPlatform *spiky3 = new SpikyPlatform(100, 20, 800, 580);
    addItem(spiky3);

    SpikyPlatform *spiky4 = new SpikyPlatform(100, 20, 1100, 580);
    addItem(spiky4);

    // Floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(160, 20, 100, 400);
    //platform1->setPixmap(QPixmap(":/images/tiles/brick.png").scaled(160, 20));
    addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(160, 20, 300, 300);
    addItem(platform2);

    StaticPlatform *platform3 = new StaticPlatform(160, 20, 700, 450);
    addItem(platform3);

    StaticPlatform *platform4 = new StaticPlatform(160, 20, 900, 300);
    addItem(platform4);

    // Moving platform (moves horizontally with range 200 and speed 2)
    MovingPlatform *moving1 = new MovingPlatform(160, 20, 400, 200, 200, 2);
    addItem(moving1);

    MovingPlatform *moving2 = new MovingPlatform(160, 20, 1100, 150, 250, 3);
    addItem(moving2);

    view->show(); // Show the view

    // Timer for game updates (platforms, HUD)
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer, &QTimer::timeout, this, [=]() {
        if (!moving1 || !moving2) return;
        // Update moving platforms
        moving1->update();
        moving2->update();
    });

    gameUpdateTimer->start(16); // ~60 FPS

    // Add coins in strategic locations
    // First platform coins
    addItem(new Coin(QPointF(130, 250)));
    addItem(new Coin(QPointF(180, 230)));
    addItem(new Coin(QPointF(230, 250)));

    // Second platform coins
    addItem(new Coin(QPointF(380, 270)));
    addItem(new Coin(QPointF(430, 270)));

    // Third platform coins
    addItem(new Coin(QPointF(700, 250)));
    addItem(new Coin(QPointF(750, 300)));
    addItem(new Coin(QPointF(800, 350)));

    // Fourth platform coins
    addItem(new Coin(QPointF(1000, 500)));
    addItem(new Coin(QPointF(1050, 500)));
}
