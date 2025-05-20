#include "level3.h"
#include "platform.h"
#include "onion.h"
#include "cat.h"

Level3::Level3(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level3::setEnemies() {
    // Add the enemies in Level 3
    onion* EagleEnemy = new onion(":/images/enemies/eagle_left.png",":/images/enemies/eagle.png",QPointF(340,420));
    addItem(EagleEnemy);
    EagleEnemy->setMoveStyle(onion_move::level3_1);
    EagleEnemy->setTargetKimo(kimo);

    onion* EagleEnemy1 = new onion(":/images/enemies/eagle_left.png",":/images/enemies/eagle.png",QPointF(700,380));
    addItem(EagleEnemy1);
     EagleEnemy1->setMoveStyle(onion_move::level3_2);
    EagleEnemy1->setTargetKimo(kimo);

    cat* cat1 = new cat(":/images/enemies/cat_left.png",":/images/enemies/streetcat.png", QPointF(850, 490));
    addItem(cat1);

    cat1->setTargetKimo(kimo);

    onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(1300,400));
    addItem(OnionEnemy);
    OnionEnemy->setMoveStyle(onion_move::level3);
    OnionEnemy->setTargetKimo(kimo);


    onion* OnionEnemy1 = new onion(":/images/enemies/onion.png",QPointF(1500,300));
    addItem(OnionEnemy1);
    OnionEnemy1->setMoveStyle(onion_move::level3);
    OnionEnemy1->setTargetKimo(kimo);



}




void Level3::setEnvironment() {
    QPixmap bgPixmap(":/images/levels/L3background.png");
    // Due to issues with the background, it will be loaded as a pixmap item and pushed to the back instead
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(bgPixmap.scaled(2000, 600));
    background->setZValue(-100);  // Push behind everything
    addItem(background);

    StaticPlatform *ground1 = new StaticPlatform(400, 50, 0, 550);
    StaticPlatform *ground2 = new StaticPlatform(500, 50, 600, 550);
    StaticPlatform *ground3 = new StaticPlatform(500, 50, 1700, 550);
    addItem(ground1);
    addItem(ground2);
    addItem(ground3);

    // Climbable steps
    addItem(new StaticPlatform(100, 20, 1200, 500));
    addItem(new StaticPlatform(100, 20, 1300, 450));
    addItem(new StaticPlatform(100, 20, 1400, 400));
    addItem(new StaticPlatform(100, 20, 1500, 350));

    // Spikes between jumps
    addItem(new SpikyPlatform(100, 20, 400, 580));
    addItem(new SpikyPlatform(100, 20, 500, 580));
    addItem(new SpikyPlatform(100, 20, 1600, 580));

}
