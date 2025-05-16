#include "level3.h"

Level3::Level3(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level3::setEnemies() {
    // Add the enemies in Level 3
}

void Level3::setEnvironment() {
    // Add the platforms, spikes, background, etc. for Level 3
}
