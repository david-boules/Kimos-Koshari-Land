#ifndef BASELEVEL_H
#define BASELEVEL_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "kimo.h"
#include "store.h"
#include <QMediaPlayer>
#include <QAudioOutput>

class LevelOrchestrator; // Forward declaration

class BaseLevel : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BaseLevel(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, LevelOrchestrator* orchestrator, QObject *parent = nullptr);
    void setupScene(QString levelName); // This function sets up each level, some of the sub-functions are pure virtual:

    // 'setupScene()' sub-functions:
    void setKimo();         // Need not be virtual: logic is the same (same spawn point, same size, etc.)
    void setHUD(QString levelName); // Need not be virtual: HUD elements (e.g. health, coins) are taken from Kimo, level name is passed in as a parameter
    virtual void setEnemies() = 0; // MUST be pure virtual: function must be overriden in each subclass due to different enemies in different levels
    virtual void setEnvironment() = 0; // MUST be pure virtual: function must be overriden in each subclass due to different objects, and environment in general, in different levels

    Kimo* getKimo() {return kimo;} // Kimo getter for disconnecting a signal in the 'Level Orchestrator'

    void stopMusic();

    QGraphicsTextItem* getLevelName() {return HUD_levelName;}

public slots:
    void updateAbilityCountdown(const QString &abilityName, int remainingTime);

signals:
    void storeOpened();
    void storeClosed();

protected:
    QGraphicsView* view;
    QGraphicsScene *scene;
    Kimo* kimo;
    LevelOrchestrator* orchestrator;

    QTimer* gameUpdateTimer = nullptr;
    QGraphicsTextItem* HUD_health;
    QGraphicsTextItem* HUD_levelName;

    QMediaPlayer* lvlMusicPlayer;
    QAudioOutput* lvlMusicOutput;

    QGraphicsTextItem* HUD_coins;
    QGraphicsTextItem* HUD_abilityCountdown; // Added for ability countdown
    Store* store;
    QPushButton* storeButton;
    QGraphicsProxyWidget* storeButtonProxy;

protected slots:
    void toggleStore();
};

#endif // BASELEVEL_H
