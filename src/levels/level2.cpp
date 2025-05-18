#include "level2.h"
#include "chili.h"
#include "macaroni.h"
#include "onion.h"
#include "platform.h"
#include "fallinglaundry.h"

Level2::Level2(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level2::setEnemies() {
        chili* ChiliEnemy = new chili(":/images/enemies/chiliLeft.png",":/images/enemies/chiliRight.png",QPointF(420,300));
        addItem(ChiliEnemy);
        ChiliEnemy->setMoveStyle(chili_move::level2);
        ChiliEnemy->setTargetKimo(kimo);


        chili* ChiliEnemy1 = new chili(":/images/enemies/chiliLeft.png",":/images/enemies/chiliRight.png",QPointF(1450,300));
        addItem(ChiliEnemy1);
        ChiliEnemy1->setMoveStyle(chili_move::level2_1);
        ChiliEnemy1->setTargetKimo(kimo);


        macaroni* macaroni1 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(364,236));
        //macaroni1->setMoveStyle(macaroni_move::level2);
        addItem(macaroni1);
        macaroni1->setTargetKimo(kimo);


        macaroni* macaroni2 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(235,480));
        macaroni2->setMoveStyle(macaroni_move::level2);
        addItem(macaroni2);
        macaroni2->setTargetKimo(kimo);

        macaroni* macaroni3 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(180,340));
        macaroni3->setMoveStyle(macaroni_move::level2_1);
        addItem(macaroni3);
        macaroni3->setTargetKimo(kimo);


        onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(630,70));
        addItem(OnionEnemy);
        OnionEnemy->setMoveStyle(onion_move::level2);
        OnionEnemy->setTargetKimo(kimo);

        onion* OnionEnemy1 = new onion(":/images/enemies/onion.png",QPointF(1260,400));
        addItem(OnionEnemy1);
        OnionEnemy1->setMoveStyle(onion_move::level2_1);
        OnionEnemy1->setTargetKimo(kimo);
}

void Level2::setEnvironment() {

    // Background
    QPixmap bg(":/images/levels/L2background.png");
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(bg.scaled(2000,600));
    background->setZValue(-100);
    addItem(background);

    // Ground platform
    StaticPlatform *ground1 = new StaticPlatform(300, 50, 0, 550);
    addItem(ground1);

    StaticPlatform *ground2 = new StaticPlatform(100, 50, 400, 550);
    addItem(ground2);

    StaticPlatform *ground3 = new StaticPlatform(150, 50, 800, 550);
    addItem(ground3);

    StaticPlatform *ground4 = new StaticPlatform(100, 50, 1050, 550);
    addItem(ground4);

    StaticPlatform *ground5 = new StaticPlatform(300, 50, 1250, 550);
    addItem(ground5);

    StaticPlatform *step1 = new StaticPlatform(100, 50, 1250, 500);
    addItem(step1);

    StaticPlatform *step2 = new StaticPlatform(100, 100, 1350, 450);
    addItem(step2);

    StaticPlatform *step3 = new StaticPlatform(100, 150, 1450, 400);
    addItem(step3);

    StaticPlatform *ground6 = new StaticPlatform(350, 50, 1650, 550);
    addItem(ground6);

    // Spiky platforms
    SpikyPlatform *spiky1 = new SpikyPlatform(100, 20, 300, 580);
    addItem(spiky1);

    SpikyPlatform *spiky2 = new SpikyPlatform(100, 20, 500, 580);
    addItem(spiky2);

    SpikyPlatform *spiky3 = new SpikyPlatform(100, 20, 600, 580);
    addItem(spiky3);

    SpikyPlatform *spiky4 = new SpikyPlatform(100, 20, 700, 580);
    addItem(spiky4);

    SpikyPlatform *spiky5 = new SpikyPlatform(100, 20, 950, 580);
    addItem(spiky5);

    SpikyPlatform *spiky6 = new SpikyPlatform(100, 20, 700, 580);
    addItem(spiky6);

    SpikyPlatform *spiky7 = new SpikyPlatform(100, 20, 1550, 580);
    addItem(spiky7);

    // Floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(150, 20, 100, 400);
    addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(150, 20, 300, 300);
    addItem(platform2);

    StaticPlatform *platform3 = new StaticPlatform(150, 20, 800, 300);
    addItem(platform3);

    // Moving platform (moves horizontally)
    MovingPlatform *moving1 = new MovingPlatform(150, 20, 500, 200, 200, 2);
    addItem(moving1);

    MovingPlatform *moving2 = new MovingPlatform(150, 20, 1050, 250, 250, 3);
    addItem(moving2);

    // Falling Laundry

    QTimer* laundryTimer = new QTimer(this);
    connect (laundryTimer, &QTimer::timeout, this, [=]() {
        QPixmap shirtPixmap(":/images/misc/shirt.png");
        QPixmap pantsPixmap(":/images/misc/pants.png");
        // Choosing which item to drop at random (for variety):
        QPixmap chosenObject = (rand() % 2 == 0) ? shirtPixmap : pantsPixmap;

        QPointF pos(kimo->x() + rand() % 200 - 100, 0); // Determine the random position where the laundry falls relative to Kimo (random number bewteen -100, 99 for around 100 pixels close to Kimo)
        FallingLaundry* laundry = new FallingLaundry(chosenObject, pos);
        addItem(laundry);
    });
    laundryTimer->start(2000);

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
        if (!moving1 || !moving2) return;
        // Update moving platforms
        moving1->update();
        moving2->update();
    });

    gameUpdateTimer->start(16); // ~60 FPS
}
