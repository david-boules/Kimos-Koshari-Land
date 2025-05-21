#include "level2.h"
#include "levelorchestrator.h"
#include "platform.h"
#include "onion.h"
#include "cat.h"
#include "fallinglaundry.h"
#include "coin.h"

Level2::Level2(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, LevelOrchestrator* orchestrator, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, orchestrator) {}

void Level2::setEnemies() {
    // Add the enemies in Level 3
    onion* EagleEnemy = new onion(":/images/enemies/eagle_left.png",":/images/enemies/eagle.png",QPointF(340,420));
    addItem(EagleEnemy);
    EagleEnemy->setMoveStyle(onion_move::level3_1);
    EagleEnemy->setTargetKimo(kimo);

    onion* EagleEnemy1 = new onion(":/images/enemies/eagle_left.png",":/images/enemies/eagle.png",QPointF(700,380));
    addItem(EagleEnemy1);
    EagleEnemy1->setMoveStyle(onion_move::level3_2);
    EagleEnemy1->setTargetKimo(kimo);

    cat* cat1 = new cat(":/images/enemies/cat_left.png",":/images/enemies/streetcat.png", QPointF(650, 490));
    addItem(cat1);
    cat1->setMoveStyle(cat_move::level3);
    cat1->setTargetKimo(kimo);

    onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(1100,400));
    addItem(OnionEnemy);
    OnionEnemy->setMoveStyle(onion_move::level3);
    OnionEnemy->setTargetKimo(kimo);


    onion* OnionEnemy1 = new onion(":/images/enemies/onion.png",QPointF(1300,300));
    addItem(OnionEnemy1);
    OnionEnemy1->setMoveStyle(onion_move::level3);
    OnionEnemy1->setTargetKimo(kimo);
}

void Level2::setEnvironment() {
    QPixmap bgPixmap(":/images/levels/L2background.png");
    // Due to issues with the background, it will be loaded as a pixmap item and pushed to the back instead
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(bgPixmap.scaled(2000, 600));
    background->setZValue(-100);  // Push behind everything
    addItem(background);

    StaticPlatform *ground1 = new StaticPlatform(200, 50, 0, 550);
    StaticPlatform *ground2 = new StaticPlatform(500, 50, 400, 550);
    StaticPlatform *ground3 = new StaticPlatform(500, 50, 1700, 550);
    addItem(ground1);
    addItem(ground2);
    addItem(ground3);

    // Climbable steps
    addItem(new StaticPlatform(100, 20, 1000, 500));
    addItem(new StaticPlatform(100, 20, 1100, 450));
    addItem(new StaticPlatform(100, 20, 1200, 400));
    addItem(new StaticPlatform(200, 20, 1300, 350));

    // Spikes between jumps
    addItem(new SpikyPlatform(100, 20, 200, 580));
    addItem(new SpikyPlatform(100, 20, 300, 580));
    addItem(new SpikyPlatform(100, 20, 1400, 580));
    addItem(new SpikyPlatform(100, 20, 1500, 580));
    addItem(new SpikyPlatform(100, 20, 1600, 580));

    QTimer* laundryTimer = new QTimer(this);
    connect (laundryTimer, &QTimer::timeout, this, [this]() {
        QPixmap shirtPixmap(":/images/misc/shirt.png");
        QPixmap pantsPixmap(":/images/misc/pants.png");
        // Choosing which item to drop at random (for variety):
        QPixmap chosenObject = (rand() % 2 == 0) ? shirtPixmap : pantsPixmap;

        QPointF pos(kimo->x() + rand() % 300 - 150, 0); // Determine the random position where the laundry falls relative to Kimo (random number bewteen -100, 99 for around 100 pixels close to Kimo)

        if (!this->kimo->isEnabled()) return; // Don’t create laundry while paused
        FallingLaundry* laundry = new FallingLaundry(chosenObject, pos);
        this->addItem(laundry);

        connect(orchestrator, SIGNAL(pauseGame()), laundry, SLOT(pause()));
        connect(orchestrator, SIGNAL(resumeGame()), laundry, SLOT(resume()));

        if (!this->kimo->isEnabled()) {
            laundry->pause();
        }
    });
    laundryTimer->start(2000);
}
