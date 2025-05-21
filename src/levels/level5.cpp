#include "level5.h"
#include "platform.h"
#include "cat.h"
#include "onion.h"
#include "chili.h"
#include "macaroni.h"
#include "boss.h";

Level5::Level5(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level5::setEnemies() {
  //  Add the enemies in Level 5


    // cat* cat1 = new cat(":/images/enemies/cat_left.png",":/images/enemies/streetcat.png", QPointF(780, 490));
    // addItem(cat1);
    // cat1->setMoveStyle(cat_move::level4);
    // cat1->setTargetKimo(kimo);


    onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(270,240));
    addItem(OnionEnemy);
    OnionEnemy->setMoveStyle(onion_move::level3);
    OnionEnemy->setTargetKimo(kimo);

    onion* OnionEnemy1 = new onion(":/images/enemies/onion.png",QPointF(430,140));
    addItem(OnionEnemy1);
    OnionEnemy1->setMoveStyle(onion_move::level3);
    OnionEnemy1->setTargetKimo(kimo);


    chili* ChiliEnemy = new chili(":/images/enemies/chiliLeft.png",":/images/enemies/chiliRight.png",QPointF(580,40));
    addItem(ChiliEnemy);
    ChiliEnemy->setMoveStyle(chili_move::level5);
    ChiliEnemy->setTargetKimo(kimo);


    macaroni* macaroni1 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(1030,480));
    macaroni1->setMoveStyle(macaroni_move::level2);
    addItem(macaroni1);
    macaroni1->setTargetKimo(kimo);



    Boss* boss1 = new Boss(":/images/enemies/Boss.png", QPointF(1550, 360));

    boss1->setTargetKimo(kimo);
    addItem(boss1);

}

void Level5::setEnvironment() {
    // Add the platforms, spikes, background, etc. for Level 5

    view->setBackgroundBrush(QPixmap(":/images/levels/L5background.png"));

    // Ground platform
    StaticPlatform *ground1 = new StaticPlatform(100, 50, 0, 550);
    addItem(ground1);

    StaticPlatform *ground2 = new StaticPlatform(50, 50, 300, 550);
    addItem(ground2);

    StaticPlatform *ground3 = new StaticPlatform(50, 50, 450, 550);
    addItem(ground3);

    StaticPlatform *ground4 = new StaticPlatform(100, 50, 600, 550);
    addItem(ground4);

    StaticPlatform *ground5 = new StaticPlatform(50, 50, 780, 550);
    addItem(ground5);

    StaticPlatform *ground6 = new StaticPlatform(50, 50, 910, 550);
    addItem(ground6);

    StaticPlatform *ground7 = new StaticPlatform(50, 50, 1040, 550);
    addItem(ground7);

    StaticPlatform *ground8 = new StaticPlatform(810, 50, 1190, 550);
    addItem(ground8);

    // Spiky platforms
    SpikyPlatform *spiky1 = new SpikyPlatform(100, 20, 200, 580);
    addItem(spiky1);

    SpikyPlatform *spiky2 = new SpikyPlatform(100, 20, 350, 580);
    addItem(spiky2);

    SpikyPlatform *spiky3 = new SpikyPlatform(100, 20, 500, 580);
    addItem(spiky3);

    SpikyPlatform *spiky4 = new SpikyPlatform(100, 20, 1090, 580);
    addItem(spiky4);


    // Floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(100, 20, 250, 300);
    addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(100, 20, 400, 200);
    addItem(platform2);

    StaticPlatform *platform3 = new StaticPlatform(100, 20, 550, 100);
    addItem(platform3);

    // Moving platform (moves horizontally)
    MovingPlatform *moving1 = new MovingPlatform(100, 20, 380, 420, 150, 2);
    addItem(moving1);

    MovingPlatform *moving2 = new MovingPlatform(100, 20, 700, 420, 250, 2);
    addItem(moving2);

    // Moving platform (moves vertically)
    VerticallyMovingPlatform *movingup = new VerticallyMovingPlatform(100, 20, 100, 300, 200, 2);
    addItem(movingup);

    view->show(); // Show the view

    // Timer for game updates (platforms, HUD)
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer, &QTimer::timeout, this, [=]() {
        if (!moving1 || !movingup || !moving2) return;
        // Update moving platforms
        moving1->update();
        movingup->update();
        moving2->update();
    });

    gameUpdateTimer->start(16); // ~60 FPS

}
