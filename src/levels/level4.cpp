#include "level4.h"
#include "platform.h"
#include "macaroni.h"
#include "onion.h"
#include "chili.h"
#include "cat.h"

Level4::Level4(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, LevelOrchestrator* orchestrator, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, orchestrator) {}

void Level4::setEnemies() {
    // Add the enemies in Level 4

    macaroni* macaroni1 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(340,340));
    macaroni1->setMoveStyle(macaroni_move::level4);
    addItem(macaroni1);
    macaroni1->setTargetKimo(kimo);


    macaroni* macaroni2 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(650,340));
    macaroni2->setMoveStyle(macaroni_move::level4_1);
    addItem(macaroni2);
    macaroni2->setTargetKimo(kimo);



    // onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(660,340));
    // addItem(OnionEnemy);
    // OnionEnemy->setMoveStyle(onion_move::level3);
    // OnionEnemy->setTargetKimo(kimo); /// remove

    onion* EagleEnemy1 = new onion(":/images/enemies/eagle_left.png",":/images/enemies/eagle.png",QPointF(400,170));
    addItem(EagleEnemy1);
    EagleEnemy1->setMoveStyle(onion_move::level4);
    EagleEnemy1->setTargetKimo(kimo);

    // chili* ChiliEnemy = new chili(":/images/enemies/chiliLeft.png",":/images/enemies/chiliRight.png",QPointF(1300,200));
    // addItem(ChiliEnemy);
    // ChiliEnemy->setMoveStyle(chili_move::level4);
    // ChiliEnemy->setTargetKimo(kimo);


    onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(950,400));
    addItem(OnionEnemy);
    OnionEnemy->setMoveStyle(onion_move::level3);
    OnionEnemy->setTargetKimo(kimo);

    onion* OnionEnemy1 = new onion(":/images/enemies/onion.png",QPointF(1650,120));
    addItem(OnionEnemy1);
    OnionEnemy1->setMoveStyle(onion_move::level3);
    OnionEnemy1->setTargetKimo(kimo);





    cat* cat1 = new cat(":/images/enemies/cat_left.png",":/images/enemies/streetcat.png", QPointF(1480, 495));
    addItem(cat1);
    cat1->setMoveStyle(cat_move::level4);
    cat1->setTargetKimo(kimo);


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

    view->show(); // Show the view

    // Timer for game updates (platforms, HUD)
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer, &QTimer::timeout, this, [=]() {
        if (!moving1 || !movingup || !kimo->isEnabled()) return;
        // Update moving platforms
        moving1->update();
        movingup->update();
    });

    gameUpdateTimer->start(16); // ~60 FPS

}
