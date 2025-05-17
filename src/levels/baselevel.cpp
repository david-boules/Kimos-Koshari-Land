#include "baselevel.h"

BaseLevel::BaseLevel(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : QGraphicsScene(parent), view(view), kimo(kimo), HUD_health(healthText), HUD_levelName(levelText)
{}

void BaseLevel::setupScene(QString levelName) {
    qDebug() << "[SETUP] BaseLevel::setupScene() called";
    setSceneRect(0, 0, 2000, 600);

    setKimo();
    setHUD(levelName);
    setEnemies();
    setEnvironment();
    kimo->setView(view);

    QTimer* hudUpdateTimer = new QTimer(this);
    connect(hudUpdateTimer, &QTimer::timeout, this, [this]() {
        if (!view || !HUD_health || !HUD_levelName) {
            qDebug() << "[HUD] skipped update due to null pointer";
            return;
        }

        QPointF viewTopLeft = view->mapToScene(0, 0);
        HUD_health->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 10);
        HUD_levelName->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 35);
    });

    hudUpdateTimer->start(16); // ~60 FPS
}


void BaseLevel::setKimo() {
    kimo->setFlag(QGraphicsItem::ItemIsFocusable);
    kimo->setFocus();
    kimo->setPos(25,450);
    kimo->setPixmap(QPixmap(":/images/kimo/Kimo_right.png").scaled(64,64));
    addItem(kimo);
    kimo->setParentItem(nullptr);
    kimo->setParent(nullptr); // Ensures that when 'currentLevel' (in 'LevelOrchestrator') is deleted, that Kimo is not deleted with it
    kimo->setView(view);
}

void BaseLevel::setHUD(QString levelName) {

    // Ensuring setHUD() doesn't reuse a scene-bound text item which leads to crashes
    if (HUD_health && HUD_health->scene()) {
        HUD_health->scene()->removeItem(HUD_health);
    }
    if (HUD_levelName && HUD_levelName->scene()) {
        HUD_levelName->scene()->removeItem(HUD_levelName);
    }

    // Health Text in HUD
    if (HUD_health) {
        if (HUD_health->scene()) HUD_health->scene()->removeItem(HUD_health);
        HUD_health->setPlainText("Health: " + QString::number(kimo->getHealth()));
        HUD_health->setDefaultTextColor(Qt::white);
        HUD_health->setFont(QFont("Arial", 16));
        addItem(HUD_health);
    }

    if (HUD_levelName) {
        if (HUD_levelName->scene()) HUD_levelName->scene()->removeItem(HUD_levelName);
        HUD_levelName->setPlainText("Level: " + levelName);
        HUD_levelName->setDefaultTextColor(Qt::white);
        HUD_levelName->setFont(QFont("Arial", 16));
        addItem(HUD_levelName);
    }
}
