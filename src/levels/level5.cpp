#include "level5.h"

Level5::Level5(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level5::setEnemies() {
    // Add the enemies in Level 5
}

void Level5::setEnvironment() {
    // Add the platforms, spikes, background, etc. for Level 5

    view->setBackgroundBrush(QPixmap(":/images/levels/L5background.png"));

}
