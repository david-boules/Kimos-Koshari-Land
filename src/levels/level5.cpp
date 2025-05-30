#include "level5.h"
#include "platform.h"
#include "onion.h"
#include "macaroni.h"
#include "boss.h"
#include "fallinglaundry.h"
#include "levelorchestrator.h"

Level5::Level5(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, LevelOrchestrator* orchestrator, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, orchestrator) {}

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



    onion* OnionEnemy2 = new onion(":/images/enemies/onion.png",QPointF(580,40));
    addItem(OnionEnemy2);
    OnionEnemy2->setMoveStyle(onion_move::level3);
    OnionEnemy2->setTargetKimo(kimo);


    macaroni* macaroni1 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(1250,480));
    macaroni1->setMoveStyle(macaroni_move::level2);
    addItem(macaroni1);
    macaroni1->setTargetKimo(kimo);



    Boss* boss = new Boss(":/images/enemies/Boss.png", QPointF(1550, 370));
    boss->setTargetKimo(kimo);
    addItem(boss);

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

    QTimer* laundryTimer = new QTimer(this);
    connect (laundryTimer, &QTimer::timeout, this, [this]() {
        QPixmap shirtPixmap(":/images/misc/shirt.png");
        QPixmap pantsPixmap(":/images/misc/pants.png");
        // Choosing which item to drop at random (for variety):
        QPixmap chosenObject = (rand() % 2 == 0) ? shirtPixmap : pantsPixmap;

        QPointF pos(kimo->x() + rand() % 100 - 50, 0); // Determine the random position where the laundry falls relative to Kimo (random number bewteen -100, 99 for around 100 pixels close to Kimo)

        if (!this->kimo->isEnabled()) return; // Don’t create laundry while paused
        FallingLaundry* laundry = new FallingLaundry(chosenObject, pos);
        this->addItem(laundry);

        connect(orchestrator, SIGNAL(pauseGame()), laundry, SLOT(pause()));
        connect(orchestrator, SIGNAL(resumeGame()), laundry, SLOT(resume()));

        if (!this->kimo->isEnabled()) {
            laundry->pause();
        }
    });
    laundryTimer->start(500);

    // Timer for game updates (platforms, HUD)
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer, &QTimer::timeout, this, [=]() {
        if (!moving1 || !movingup || !moving2 || !kimo->isEnabled()) return;
        // Update moving platforms
        moving1->update();
        movingup->update();
        moving2->update();
    });

    gameUpdateTimer->start(16); // ~60 FPS

}
